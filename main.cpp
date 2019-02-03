#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/* minor scale
 { 2,1,2,2,2,1,2}
 starting note 48 , 49 ..... 60
 ending note is starting note plus 48
 generate scale :
 start with starting note
 each scale has 4*7 = 28 notes
 */
int minorScaleSteps [7] = { 2,1,2,2,2,1,2}; // chromatic skips of minor scale
// scales start at c below middle C and span 4 octaves each
// one for each note of chromatic scale
int dorianScales [12][35]; // static array to hold all 12 scales
int newNote; // next note
int note; // current note in scale
int chord[6]; // array to hold chord
int rangeBool = 0; // if a chord has notes up 126 this gets turned on to CLAMP
int randomRoot;

// start at a note from C up to B and populate the dorianScales array for that scale
// c is 0  ... B is 11
void createScale(int start){

    // repeat 4 times
    // start at starting note .. add notes to previous note
    note = 48 + start; // initial note
    dorianScales[start][0] = note;
    int iterator = 0;
    for (int i = 1; i < 35; i++){
        newNote = note + minorScaleSteps[iterator];
        dorianScales[start][i] = newNote;
        if (iterator == 6){
            iterator = 0;
        }
        else {iterator ++;}
    }
}

void createRandomVoicing(int root) {

    // v1 = rand() % 7 + 1;         // v1 in the range 0 to 99
    // select 6 notes randomly
    // skips are between 1 and 8
    // if any note is higher than 126 start turn on bool
    // if bool is on after chords are populated start again and just pick 6 random numbers between 0 and 35

    int note = (rand() % 8);
    int newNote = dorianScales[root][note];
    chord[0] = newNote;


    for (int g = 1; g < 5; g++) {
        note = note + (rand() % 7) + 1;
        chord[g] = dorianScales[root][note];
        if (note > 34) {
            rangeBool = 1;
        }
    }

    // if we have gone out of range just create a random chord
    if (rangeBool == 1) {
        for (int j = 0; j < 5; j++) {
            note = rand() % 34;
            chord[j] = dorianScales[root][note];
        }
        rangeBool = 0;
    }
}

void createRandomChord(int root){

    for (int j = 0; j < 5; j++) {
        note = rand() % 34;
        chord[j] = dorianScales[root][note];
    }

}

void printChord(){

    cout << endl;
    for ( int i = 0; i< 6; i ++ ){
        cout << chord[i] ;
        cout << " ,";
    }
    cout << endl;

}


int main() {

    cout << "RANDOM CHORDS " ;
    cout << endl;
    cout << endl;

    // populate array with scales
    for (int j = 0; j< 12; j++){
        createScale(j);
    }

    randomRoot = rand() % 10;
    createRandomChord(randomRoot);
    printChord();
    randomRoot = rand() % 10;
    createRandomChord(randomRoot);
    printChord();
    randomRoot = rand() % 10;
    createRandomVoicing(randomRoot);
    printChord();
    randomRoot = rand() % 10;
    createRandomVoicing(randomRoot);
    printChord();


}

