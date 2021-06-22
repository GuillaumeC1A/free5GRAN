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


tuple<int, int> fill_grid(vector<vector<fcomp>>grid) {
    for(int frame : FRAMES) {
        if(frame % X == Y) {
            for(int slot=0; slot < SLOTS; slot++) {
                for(int s=STARTING_SYMBOL; s<DURATION; s++) {
                    int t = frame * FRAME_SIZE + slot * SLOTS_SIZE + s;
                    grid[t][FREQUENCY_START] = zadoff_chu(s,u);
                    cout << "(" << t << ',' << FREQUENCY_START << ")" << endl;
                }
            }
        }
    }
}

fcomp zadoff_chu(int n, int u) {

}