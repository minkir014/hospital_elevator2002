#include<iostream >
#include "UI.h"
#include <fstream>
using namespace std;


UI::UI() {
    cout << "---------------Hospital Queuing System Starts-------" << endl;
    this->ReadIOFileName();
    this->SetAppMode(); 
}

void UI::SetAppMode() {
    int SelectedMode = -1;
    int cnt = 0; 
    while (SelectedMode< 0 || SelectedMode> 2) {
        if (cnt > 0) cout << "PLEASE ENTER A VALIDE MODE." << endl;;
        cout << "----------------------------------------------------" << endl;
        cout << "SELECT THE APPLICATION MODE:" << endl;
        cout << "[0]: Interactive Mode" << endl;
        cout << "[1]: Step-By-Step Mode" << endl;
        cout << "[2]: Silent Mode" << endl;
        cout << "YOUR CHOICE >> ";
        cin >> SelectedMode;
        cnt++; 
    }

    if (SelectedMode == 0)
        AppMode = Interactive;
    else if (SelectedMode == 1)
        AppMode = StepByStep;
    else
        AppMode = Silent;

}
void UI::ReadIOFileName() {
    string Input;
    string Output;
    cout << "--------------------------------------" << endl;
    cout << "ENTER THE INPUT AND OUTPUT FILES NAMES:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Notes:" << endl;
    cout << "[!]: The Input File Should Be Inside The [Inputs] Directory" << endl; // to be added later 
    cout << "[!]: The Output File Should Be Inside The [Outputs] Directory" << endl; // to be added later 

 /* how to check if the input string is in the loads director   as well as ouput string is in output  dir */
 
    /*? check need to added */
        cout << "[+]: Input File Name:";
        cin >> Input;
        Input += ".txt";


        cout << "[+]: Output File Name: ";
        cin >> Output;
        Output += ".txt";
        
        
    this->InputFileName = "Inputs/" + Input;
    this->OutputFileName = "Outputs/" + Output;

}

string UI::getInputFileName() const {
    return InputFileName;
}

string UI::getOutputFileName() const {
    return OutputFileName;
}

UI::~UI() {}