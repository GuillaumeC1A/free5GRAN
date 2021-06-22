#ifndef INC_5GSCRAMBLE_FUNCTIONS_H
#define INC_5GSCRAMBLE_FUNCTIONS_H

#include <tuple>
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> fill_grid(vector<vector<fcomp>> grid);
fcomp zadoff_chu(int n,int u);

#endif INC_5GSCRAMBLE_FUNCTIONS_H
