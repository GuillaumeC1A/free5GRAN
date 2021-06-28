#include "functions.h"

const int PCI = 160;        // PRACH Configuration Index
const char PF = 0xB4;       // Preamble Format
const int X = 1;            // Frames number n selected verifying
const int Y = 0;            // n % x = y
const int FRAMES[1] = {9};
const int STARTING_SYMBOL = 2;
const int SLOTS = 1;
const int OCCURENCES = 1;
const int DURATION = 12;

const int SLOTS_SIZE = 14;
const int FRAME_SIZE = 2*SLOTS_SIZE;

const int ROOT_SEQUENCE_INDEX = 1;
const int U[40] = {129,710,140,699,120,719,210,629,168,671,84,755,105,734,93,746,70,769,60,779,
                   2,837,1,838,56,783,112,727,148,691,80,759,42,797,40,799,35,804,73,766};
const int FREQUENCY_START = 0;

const int LRA = 139;
const int NCS = 15;

const int BW = 3072E4;  // Total Band With
const int PSS = 30E3;     //Prach Subcarrier Spacing

const int UBW = 2*48E3; // Uplink Bandwidth


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

    vector<fcomp> final;
    set_union(high.begin(), high.end(), low.begin(), low.end(), back_inserter(final));
    return final;
}

void fcomp2array(vector<fcomp> v, fftw_complex* in) {
    for(int i=0; i < v.size(); i++) {
        in[i][0] = v[i].real();
        in[i][1] = v[i].imag();
    }
    return;
}

void array2fcomp(fftw_complex* in, vector<fcomp> v) {
    for(int i=0; i<v.size(); i++) {
        v[i] = {(float)in[i][0], (float)in[i][1]};
    }
}