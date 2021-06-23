#include "functions.h"

const int PCI = 160;        // PRACH Configuration Index
const char PF = 0xB4;       // Preamble Format
const int X = 1;            // Frames number n selected verifying
const int Y = 0;            // n % x = y
const int FRAMES[1] = {9};
const int STARTING_SYMBOL = 2;
const int SLOTS = 1;
const int OCCURENCES = 1;
const int DURATION = 12;

const int SLOTS_SIZE = 14;
const int FRAME_SIZE = 2*SLOTS_SIZE;

const int ROOT_SEQUENCE_INDEX = 1;
const int u = 837;
const int FREQUENCY_START = 0;

const int LRA = 139;
const int NCS = 15;

const int BW = 3070E4;  // Total Band With
const int PSS = 30E3;     //Prach Subcarrier Spacing

const int UBW = 2*48E3; // Uplink Bandwidth

/*
 * Fill the grid to send according to data
 * with the complexes in the Zadoff Chu serie
 */
tuple<int, int> fill_grid(vector<vector<fcomp>>grid) {
    // Listing all frames
    int f = (BW/PSS)/2 - UBW/2 + FREQUENCY_START;
    cout << "frequency: " << f << endl;
    for(int frame : FRAMES) {
        // Checking if the frame is allowed
        if(frame % X == Y) {
            // Listing slots
            for(int slot=0; slot < SLOTS; slot++) {
                // Filling the slot with the Zadoff Chu number
                for(int s=STARTING_SYMBOL; s<DURATION; s++) {
                    int t = frame * FRAME_SIZE + slot * SLOTS_SIZE + s;
                    grid[t][f] = zadoff_chu(s,u);
                    cout << "(" << t << ',' << FREQUENCY_START << ")" << endl;
                }
            }
        }
    }
}


/*
 * Frequency Domain Sequence Generation
 */

// Return the Zadoff Chu number
fcomp zadoff_chu(int n, int u) {
    return exp(fcomp(0,-M_PI*u*n*(n+1) / (LRA)));
}

fcomp cyclic_shift(int u, int nu, int n) {
    int Cnu = nu * NCS;
    return zadoff_chu((n + Cnu) % LRA, u);
}

fcomp y(int u, int nu, int n) {
    fcomp sum = {0,0};
    for(int m=0; m < LRA; m++) {
        sum += cyclic_shift(u,nu,m) * exp(fcomp(0, -2*M_PI*m*n/LRA));
    }
    return sum;
}

/*
 * Time Domain Sequence Generation
 */

/*
 * CONST TO CREATE
 */

const int betaPRACH = 0;
const int delta_fRA = 0;
const int delta_f = 0;
const int tstart = STARTING_SYMBOL;
const int Tc = 0;
const int NCPRA = 0;
const int kbarre = 0;
const int k1 = 0;


fcomp s(int l, int p, int mu, int t) {
    fcomp s = {0,0};
    int K = delta_f / delta_fRA;
    for(int k=0; k < LRA; k++) {
        int nu=0;
        s += exp(fcomp(betaPRACH,0)) * y(u, nu, k) * exp(fcomp(0, 2*M_PI*(k + K*k1 + kbarre) * delta_fRA * (t - NCPRA * Tc - tstart)));
    }
}