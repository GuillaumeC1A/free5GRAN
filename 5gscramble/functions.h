#ifndef INC_5GSCRAMBLE_FUNCTIONS_H
#define INC_5GSCRAMBLE_FUNCTIONS_H

#include <tuple>
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> fill_grid(vector<vector<fcomp>> grid);
fcomp zadoff_chu(int n,int u);
fcomp cyclic_shift(int u, int v, int n);
fcomp y(int u, int v, int n);
vector<fcomp> ifft(int n, vector<fcomp> A);
vector<fcomp> create_preamble(vector<fcomp> data, int frequency_offset, int resources_blocks);
vector<fcomp> split_and_concat(vector<fcomp> v);

vector<vector<float>> fcomp2array(vector<fcomp> v);
#endif INC_5GSCRAMBLE_FUNCTIONS_H