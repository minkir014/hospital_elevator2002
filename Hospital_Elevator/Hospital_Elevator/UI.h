#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "Defs.h"
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
	// not done yet 
	void SetAppMode();
	MODE GetAppMode() const;  
	string ReadFileName(); 
	void PrintMsg(const string& msg) const;

	

};
#endif
