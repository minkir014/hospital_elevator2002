#include "Hospital.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main() {

	Hospital hospital;

	hospital.InitializeLists();

	hospital.ExecuteEvents();

	//hospital.OutputToFile();

	system("pause");
}