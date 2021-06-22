#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

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
    return 0;
}

calc_position