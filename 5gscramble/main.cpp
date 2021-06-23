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

    //vector<fcomp> new_line(1024, {0, 0});

    vector<fcomp> buffer(280, {0,0});

    for(int i = 0; i < 280; i++) {
        buffer[i] = ifft(1024, grid[i]);
    }
    return 0;
}