#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "Defs.h"
#include "Elevator.h"
using namespace std;
class UI
{
private:

	MODE AppMode;
	string InputFileName;
	string OutputFileName;

public:
	UI();
	~UI();

	void SetAppMode(); // get the mode from the user ; 
	void SetIOfileName(); 
	MODE GetAppMode() const;  
	void ReadIOFileName(); // read input and output file names 

	string getInputFileName() const;
	string getOutputFileName() const;

	void PrintMsg(const string& msg) const;
	
	void PrintTimeStep(const int& Time) const;   // current timestamp : 78 ; 
	
	void PressEnterToContinue() const; // after each timestamp  
	
	void PrintUpsAndDowns(int& sizeUp, int* Up, int& sizeDown, int* Down) const; // up[1,2,3] down [4,5,6] - will be called in printing Patient ,visitor , cargos ; 
	
	void PrintWaitingPatients(int& sizeUp, int* Up, int& sizeDown, int* Down) const; // 5 wating Patients : up[] down[]'

	void PrintWaitingCargos(int& sizeUp, int* Up, int& sizeDown, int* Down) const;
	
	void PrintWaitingVisitors(int& sizeUp, int* Up, int& sizeDown, int* Down) const;

	void PrintElevatorHeader();

	void PrintElevator(const Elevator* e) const; // type is elevetor type . type[].  will be called for all elevator on that floor ;

	void PrintFloor(int& FloorNumber) const; // ----- floor 4 ------ / if floornum =0  ---- Ground ---- 

	void PrintFinalStats(int & TotalWaiting , int & VisitorLeft , int & TotalInservice , int & VisitorOnStairs ,int &TotalCompleted ) const; 
	
	void WaitOneSecond() const ; // will be used in step-By-step mode 

	void PrintHeader() const; /* silent mode , Simulation Starts ,Simulation ends , Output file created*/
	void printFooter() const;
};
#endif
