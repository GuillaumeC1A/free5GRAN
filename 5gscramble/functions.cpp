#include "functions.h"

const int PCI = 160;        // PRACH Configuration Index
const char PF = 0xB4;       // Preamble Format
const int X = 1;            // Frames number n selected verifying
const int Y = 0;            // n % x = y
const int FRAME = 9;
const int STARTING_SYMBOL = 2;
const int SLOT = 1;
const int OCCURENCES = 1;
const int DURATION = 12;

const int SLOTS_SIZE = 14;
const int FRAME_SIZE = 2*SLOTS_SIZE;

const int ROOT_SEQUENCE_INDEX = 1;
const int U[40] = {129,710,140,699,120,719,210,629,168,671,84,755,105,734,93,746,70,769,60,779,
                   2,837,1,838,56,783,112,727,148,691,80,759,42,797,40,799,35,804,73,766};
const int FREQUENCY_START = 0;

int const LRA = 139;
int const NCS = 69;

int const NRACP = 936/2;


const int BW = 3072E4;  // Total Band With
const int PSS = 30E3;     //Prach Subcarrier Spacing

const int UBW = 2*48E3; // Uplink Bandwidth

int const FFT_SIZE = 1024;
int const SYMBOLS_PER_SUBFRAMES = 14;


/*
 * Frequency Domain Sequence Generation
 */

// Return the Zadoff Chu number
fcomp zadoff_chu(int n, int u) {
    return exp(fcomp(0,-M_PI*u*n*(n+1) / (LRA)));
}

fcomp cyclic_shift(int u, int v, int n) {
    int Cv = v * NCS;
    return zadoff_chu((n + Cv) % LRA, u);
}

fcomp y(int i, int v, int n) {
    fcomp sum = {0,0};
    for(int m=0; m < LRA; m++) {
        sum += cyclic_shift(U[i],v,m) * exp(fcomp(0, -2*M_PI*m*n/LRA));
    }
    return sum;
}

vector<vector<fcomp>> generate_zadoff_mat() {
    fcomp y_value=0;

    vector<vector<fcomp>> zadoff_mat(64, vector<fcomp>(139, {0,0}));
    int card_v = (int) floor(LRA/(double)NCS);
    for(int i=1; i<=32; i++) {
        for(int v=0; v < card_v; v++) {
            for(int n=0; n<LRA; n++) {
                y_value = y(i,v,n);
                zadoff_mat[(i-1)*card_v+v][n] = y_value;
            }
        }
    }
    return zadoff_mat;
}



vector<fcomp> create_preamble(vector<fcomp> data, int frequency_offset, int resources_blocks) {
    vector<fcomp> preamble (1024, {0,0});
    int f_start = (1024 - 12 * resources_blocks) / 2 + frequency_offset;
    for(int f = 0; f < data.size(); f++) {
        preamble[f_start+f] = data[f];
    }
    return preamble;
}

vector<fcomp> split_and_concat(vector<fcomp> v) {
    size_t const half_size = v.size() / 2;
    vector<fcomp> low(v.begin(), v.begin()+half_size);
    vector<fcomp> high(v.begin()+half_size, v.end());

    high.insert(high.end(), low.begin(), low.end());
    return high;
}

vector<fcomp> prepare_ifft(vector<vector<fcomp>> zadoff_mat) {

    int preamble_num = rand() % 64;
    vector<fcomp> data = zadoff_mat[preamble_num];

    vector<fcomp> preamble = create_preamble(data, 0, 48);
    vector<fcomp> sorted_preamble = split_and_concat(preamble);

    return sorted_preamble;
}


void fcomp2array(vector<fcomp> v, fftw_complex* in) {
    for(int i=0; i < v.size(); i++) {
        in[i][0] = v[i].real();
        in[i][1] = v[i].imag();
    }
    return;
}

void array2fcomp(fftw_complex* in, vector<fcomp>& v) {
    for(int i=0; i<v.size(); i++) {
        v[i] = {(float)in[i][0], (float)in[i][1]};
    }
}

vector<fcomp> do_ifft(vector<fcomp> preamble) {

    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);

    p = fftw_plan_dft_1d(FFT_SIZE, in, out, FFTW_BACKWARD,  FFTW_MEASURE);
    fcomp2array(preamble, in);

    fftw_execute(p);

    vector<fcomp> ifft_out(FFT_SIZE, {0,0});
    array2fcomp(out, ifft_out);

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);

    return ifft_out;
}

vector<fcomp> make_buffer(vector<fcomp> ifft_out) {
    vector<fcomp> CP(ifft_out.end() - NRACP, ifft_out.end());

    vector<fcomp> buffer = CP;
    for(int i=0; i<12; i++) {
        buffer.insert(buffer.end(), ifft_out.begin(), ifft_out.end());
    }
    return buffer;
}

vector<fcomp> generate_PRACH() {
    return make_buffer(do_ifft(prepare_ifft(generate_zadoff_mat())));
}



vector<fcomp> place_bloc(vector<fcomp> bloc) {
    int n = (1024*14 + 88 + 72)*2;
    vector<fcomp> buffer(n*10);
    int t = 0;
    t += FRAME * n;
    t += SLOT * n / 2;
    t += 1024 +88 + 1024 +72;

    for(int i=0; i < bloc.size(); i++) {
        buffer[t+i] = bloc[i];
    }
    return buffer;
}