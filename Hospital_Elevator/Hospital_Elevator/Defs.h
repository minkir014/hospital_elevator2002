#pragma once
enum MODE {
	Interactive , 
	StepByStep, 
	Silent 
};
enum ElevatorType{
	CE, // cargo Elevator 
	VE, // visitor Elevator 
	PE //  Patient Elevator 
};
enum E_UserType { //  elevator user type 
	V , // visitor 
	P , // patient 
	C // cargo 
};
enum Events { // 
	Arrival,
	leave,
	Stair,
	AutoS
};