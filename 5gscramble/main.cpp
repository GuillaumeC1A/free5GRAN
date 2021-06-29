#include <iostream>
#include <complex>
#include <vector>
#include <tuple>
#include "functions.h"

using namespace std;
typedef complex<float> fcomp;

tuple<int, int> calc_position;

int main() {

    vector<fcomp> buffer = generate_PRACH();

    for(int i=0; i<buffer.size(); i++) {
        if(buffer[i].real() != 0 || buffer[i].imag() != 0) {
            cout << "i:" << i << " -> " << buffer [i] << endl;
        }
    }

    


    return 0;
}