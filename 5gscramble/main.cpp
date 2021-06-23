#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <tuple>
#include "functions.h"

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> calc_position;

int main() {

    /*
     * Init the grid to send
     * there are 280 slots in time (2 * 14 * 10)
     * and 1024 for the frequencies.
     */
    
    vector<vector<fcomp>> grid(280, vector<fcomp>(1024 , {0,0}));
    fill_grid(grid);

    vector<fcomp> new_line(1024, {0, 0});

    for(int i = 0; i < 280; i++) {
        ifft(1024, grid[i], new_line);
        grid[i] = new_line;

    }
    return 0;
}

void ifft(int n, vector<fcomp> A, vector<fcomp> F) {
    int k,j=0;
    vector<fcomp> omegak(n, {0, 0}), omega(n, {0, 0});
    int sft = n/2;
    if(n==1) {
        F[0] = A[0];
        return;
    }
    vector<fcomp> E(n/2, {0, 0}), O(n/2, {0, 0}), EF(n/2, {0, 0}), OF(n/2, {0, 0});
    for(k=0; k<n; k+=2) {
        E[j]=A[k];
        O[j]=A[k+1];
        j++;
    }
    ifft(n/2, E, EF);
    ifft(n/2, O, OF);
    omega[0]._Val[0] = cos(-2*M_PI/n);
    omega[0]._Val[1] = sin(-2*M_PI/n);
    omegak[0]._Val[0] = 1.0;
    omegak[0]._Val[1] = 0.0;
    for (k=0; k<n/2; k++, omegak = multiply(omegak,omega)) { 
        F[k] = add(EF[k] , multiply(omegak,OF[k]));
        F[k + sft] = subtract(EF[k] , multiply(omegak,OF[k]));
    }
}