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

    vector<fcomp> bloc = generate_PRACH();

    vector<fcomp> buffer = place_bloc(bloc);

    ofstream file("data");
    for(fcomp v : buffer) {
        file << v << endl;
    }


    return 0;
}