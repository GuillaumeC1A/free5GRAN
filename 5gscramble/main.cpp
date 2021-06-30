#include <iostream>
#include <complex>
#include <vector>
#include <tuple>
#include <fstream>
#include "functions.h"

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> calc_position;

int main() {

    // Generate the PRACH
    vector<fcomp> buffer = free5GRAN::prach::generate_PRACH();

    //Writing the PRACH in a file to be used in another program
    ofstream file("data");
    for(fcomp v : buffer) {
        file << v << endl;
    }

    return 0;
}