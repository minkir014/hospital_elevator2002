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
	MODE GetMode() const;  
	string ReadFileName(); 
	

};
#endif
