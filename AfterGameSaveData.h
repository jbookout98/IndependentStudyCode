#ifndef AFTER_GAME_SAVE_DATA
#define AFTER_GAME_SAVE_DATA

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "utils.h"

#include <fstream>
#include "phenotype.h"
class AfterGameSaveData
{	
private:
	vector<int> lifetimes;


public:
	AfterGameSaveData();
	void AddToLifeTime(int value);	

	void AddToLifeTime(vector<int> vectors);

	void SaveNeuronsToTextFile(vector<SNeuron*>& neurons, std::string filename);

	void WeightSaveDataToFile(vector<double> dataToSave);

	void SaveDataToFile();

};

#endif