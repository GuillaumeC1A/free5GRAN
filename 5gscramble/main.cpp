#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <tuple>
#include <fftw3.h>
#include "functions.h"

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> calc_position;

int const LRA = 139;
int const NCS = 69;

int main() {

    fcomp y_value=0;

    /*
     * Init the grid to send
     * there are 280 slots in time (2 * 14 * 10)
     * and 1024 for the frequencies.
     */
    
    vector<vector<fcomp>> grid(280, vector<fcomp>(1024 , {0,0}));
    //fill_grid(grid);

    vector<vector<fcomp>> zadoff_mat(64, vector<fcomp>(139, {0,0}));
    int card_v = (int) floor(LRA/(double)NCS);
    for(int i=1; i<=32; i++) {
        for(int v=0; v < card_v; v++) {
            for(int n=0; n<LRA; n++) {
                y_value = y(i,v,n);
                zadoff_mat[(i-1)*card_v+v][n] = y_value;
                cout << "u=" << i << "; v=" << v << "; n=" << n << "y=" << y_value <<endl;
            }
        }
    }

    int preamble_num = rand() % 64;
    vector<fcomp> data = zadoff_mat[preamble_num];

    vector<fcomp> preamble = create_preamble(data, 0, 48);
    vector<fcomp> sorted_preamble = split_and_concat(preamble);

    vector<vector<float>> data_for_ifft = fcomp2array(sorted_preamble);





    return 0;
}