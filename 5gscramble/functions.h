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
typedef complex<float> fcomp;

fcomp zadoff_chu(int n,int u);
fcomp cyclic_shift(int u, int v, int n);
fcomp y(int i, int v, int n);
vector<fcomp> ifft(int n, vector<fcomp> A);
vector<fcomp> create_preamble(vector<fcomp> data, int frequency_offset, int resources_blocks);
vector<fcomp> split_and_concat(vector<fcomp> v);

void fcomp2array(vector<fcomp> v, fftw_complex* in);
void array2fcomp(fftw_complex* in, vector<fcomp> v);

#endif INC_5GSCRAMBLE_FUNCTIONS_H