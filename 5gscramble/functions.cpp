#include "functions.h"

const int PCI = 160;                // PRACH Configuration Index
const char PF = 0xB4;               // Preamble Format
const int X = 1;                    // Frames number n selected verifying
const int Y = 0;                    // n % x = y
const int FRAME = 9;                // The frame on which the buffer is sent
const int STARTING_SYMBOL = 2;      // The starting symbol
const int SLOT = 1;                 // The slot where we send the PRACH
const int OCCURENCES = 1;           // The number of repetitions
const int DURATION = 12;            // How many symbols are used

const int MS = 30720;               // One milliseconds

const int SLOTS_SIZE = 14;          // The numbers of symbols in a slot
const int FRAME_SIZE = 2*SLOTS_SIZE;// The numbers of symbols in a bloc

const int RSI = 1;                  // The Root Sequence Index
const int U[40] = {129,710,140,699,120,719,210,629,168,671,84,755,105,734,93,746,70,769,60,779,
                   2,837,1,838,56,783,112,727,148,691,80,759,42,797,40,799,35,804,73,766};
                                    // The values to put in the Zadoff Chu sequence
const int FREQUENCY_START = 0;      // The frequency offset
const int RESOURCES_BLOCKS = 48;    // The number of Resources blocks

int const LRA = 139;
int const NCS = 69;

int const NRACP = 936/2;


const int BW = 3072E4;  // Total Band With
const int PSS = 30E3;     //Prach Subcarrier Spacing

const int UBW = 2*48E3; // Uplink Bandwidth

int const FFT_SIZE = 1024;          // The total frequencies

/*
 * Frequency Domain Sequence Generation
 */

// Return the Zadoff Chu number Z(n,u)
fcomp zadoff_chu(int n, int u) {
    return exp(fcomp(0,-M_PI*u*n*(n+1) / (LRA)));
}

// Second step to generate the Zadoff Chu Sequence. We do a cyclic shift
fcomp cyclic_shift(int u, int v, int n) {
    int Cv = v * NCS;
    return zadoff_chu((n + Cv) % LRA, u);
}

// Last step to generate the sequence
fcomp y(int i, int v, int n) {
    fcomp sum = {0,0};
    for(int m=0; m < LRA; m++) {
        sum += cyclic_shift(U[i],v,m) * exp(fcomp(0, -2*M_PI*m*n/LRA));
    }
    return sum;
}

// Generate the 64 preamble to be used
vector<vector<fcomp>> generate_zadoff_mat() {
    fcomp y_value=0;
    vector<vector<fcomp>> zadoff_mat(64, vector<fcomp>(139, {0,0}));

    // We have to go through 64 values defines by the tuple (i,v)
    int card_v = (int) floor(LRA/(double)NCS);      // Formula to calculate v_max as v in |[0, v_max |[
    int i_length = 64/card_v;                          // i is in |[RSI, RSI + 64/v_max |[

    for(int i=RSI; i<RSI+i_length; i++) {
        for(int v=0; v < card_v; v++) {
            for(int n=0; n<LRA; n++) {
                y_value = y(i,v,n);
                zadoff_mat[(i-1)*card_v+v][n] = y_value;    // We add the sequence into the array
            }
        }
    }
    return zadoff_mat;
}

// Here we insert the "mini" preamble in the 1024 size vector
vector<fcomp> create_preamble(vector<fcomp> data, int frequency_offset, int resources_blocks) {
    vector<fcomp> preamble (FFT_SIZE, {0,0});
    // We calculate the frequency where we begin to insert the data, with an offset
    // It begins at the first frequency of the resources blocs, which is centered in the 1024 frequency total vector
    int f_start = (FFT_SIZE - 12 * resources_blocks) / 2 + frequency_offset;
    for(int f = 0; f < data.size(); f++) {
        preamble[f_start+f] = data[f];
    }
    return preamble;
}

// The frequencies go from -512 to 512, so we have to do a cyclic shift to obtain 0 to 1024
vector<fcomp> split_and_concat(vector<fcomp> v) {
    size_t const half_size = v.size() / 2;
    vector<fcomp> low(v.begin(), v.begin()+half_size);
    vector<fcomp> high(v.begin()+half_size, v.end());

    high.insert(high.end(), low.begin(), low.end());
    return high;
}

// This function prepare the data for the ifft
vector<fcomp> prepare_ifft(vector<vector<fcomp>> zadoff_mat, int preamble_num) {

    // A preamble is selected among teh 64 availables
    vector<fcomp> data = zadoff_mat[preamble_num];

    // Creation and shift of the generated preamble
    vector<fcomp> preamble = create_preamble(data, FREQUENCY_START, RESOURCES_BLOCKS);
    vector<fcomp> sorted_preamble = split_and_concat(preamble);

    return sorted_preamble;
}

// Transform a vector<fcomp> to a nx2 array
void fcomp2array(vector<fcomp> v, fftw_complex* in) {
    for(int i=0; i < v.size(); i++) {
        in[i][0] = v[i].real();
        in[i][1] = v[i].imag();
    }
    return;
}

// Transform a nx2 array to a vector<fcomp>
void array2fcomp(fftw_complex* in, vector<fcomp>& v) {
    for(int i=0; i<v.size(); i++) {
        v[i] = {(float)in[i][0], (float)in[i][1]};
    }
}

// IFFT
vector<fcomp> do_ifft(vector<fcomp> preamble) {

    // Define input and output arrays and the plan
    fftw_complex *in, *out;
    fftw_plan p;

    // Allocating memory
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);

    // Init the plan and the input
    p = fftw_plan_dft_1d(FFT_SIZE, in, out, FFTW_BACKWARD,  FFTW_MEASURE);
    fcomp2array(preamble, in);

    // The plan is executed
    fftw_execute(p);

    // The output is initialized with zeros
    vector<fcomp> ifft_out(FFT_SIZE, {0,0});

    // Transform the output in the correct format
    array2fcomp(out, ifft_out);

    // Free memory
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);

    return ifft_out;
}

// Buffer creation
vector<fcomp> make_buffer(vector<fcomp> ifft_out) {

    // The CP block to put at the beginning
    // It is made from the NRACP last bytes of the ifft output
    vector<fcomp> CP(ifft_out.end() - NRACP, ifft_out.end());

    // The buffer is the concatenation of the CP and twelve times the ifft output
    vector<fcomp> buffer = CP;
    for(int i=0; i<12; i++) {
        buffer.insert(buffer.end(), ifft_out.begin(), ifft_out.end());
    }
    return buffer;
}

// The final functions which generate the PRACH from scratch
vector<fcomp> generate_PRACH() {

    // A bloc is generated randomly
    vector<fcomp> bloc = make_buffer(do_ifft(prepare_ifft(generate_zadoff_mat(), rand() % 64)));

    // The buffer have a size of 10ms
    vector<fcomp> buffer(MS*10);

    // Time offset calculated from the format given. Here, B4
    int t = 0;
    t += FRAME * MS;
    t += SLOT * MS / 2;
    t += 1024 +88 + 1024 +72;   // The two first symbols have a size of 1024+88 and 1024+72

    // We insert the bloc into the buffer, and left zeros before and after
    for(int i=0; i < bloc.size(); i++) {
        buffer[t+i] = bloc[i];
    }
    return buffer;
}