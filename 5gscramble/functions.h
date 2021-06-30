#ifndef INC_5GSCRAMBLE_FUNCTIONS_H
#define INC_5GSCRAMBLE_FUNCTIONS_H

#include <tuple>
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fftw3.h>

using namespace std;

// We define a type of complex easier to use
typedef complex<float> fcomp;

// The functions related to the generation of the Zadoff Chu sequence
vector<vector<fcomp>> generate_zadoff_mat();
fcomp zadoff_chu(int n,int u);
fcomp cyclic_shift(int u, int v, int n);
fcomp y(int i, int v, int n);

// These functions prepare the Zadoff Chu sequence to the ifft
vector<fcomp> prepare_ifft(vector<vector<fcomp>> zadoff_mat, int preamble_num);
vector<fcomp> create_preamble(vector<fcomp> data, int frequency_offset, int resources_blocks);
vector<fcomp> split_and_concat(vector<fcomp> v);

// Two functions to switch between a dynamic array (vector) and the array needed for the fftw3 library
void fcomp2array(vector<fcomp> v, fftw_complex* in);
void array2fcomp(fftw_complex* in, vector<fcomp>& v);

// Do the ifft from a preamble
vector<fcomp> do_ifft(vector<fcomp> preamble);

// Generate the buffer without the zero-padding
vector<fcomp> make_buffer(vector<fcomp> ifft_out);

// Place the buffer on the right symbols
vector<fcomp> generate_PRACH();
#endif