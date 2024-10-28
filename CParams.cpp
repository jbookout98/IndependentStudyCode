#include "CParams.h"
#include <string>

double CParams::dPi                       = 0;
double CParams::dHalfPi                   = 0;
double CParams::dTwoPi                    = 0;
int CParams::WindowWidth                  = 400;
int CParams::WindowHeight                 = 400;
int CParams::iFramesPerSecond             = 0;
int CParams::iNumInputs                   = 0;
int CParams::iNumOutputs                  = 0;
double CParams::dBias                     = -1;
double CParams::dMaxTurnRate              = 0;
int CParams::iSweeperScale                = 0;
int CParams::iNumSensors                  = 0;
double CParams::dSensorRange              = 0;
int CParams::iNumSweepers                 = 0;
int CParams::iNumTicks                    = 0;
double CParams::dCollisionDist            = 0;
double CParams::dCellSize                 = 0;
double CParams::dSigmoidResponse          = 1;
int CParams::iNumAddLinkAttempts          = 0;
int CParams::iNumTrysToFindLoopedLink     = 5;
int CParams::iNumTrysToFindOldLink        = 5;
double CParams::dYoungFitnessBonus        = 0;
int CParams::iYoungBonusAgeThreshhold     = 0;
double CParams::dSurvivalRate             = 0;
int CParams::InfoWindowWidth              = 400;
int CParams::InfoWindowHeight             = 400;
int CParams::iNumGensAllowedNoImprovement = 0;
int CParams::iMaxPermittedNeurons         = 0;
double CParams::dChanceAddLink            = 0;
double CParams::dChanceAddNode            = 0;
double CParams::dChanceAddRecurrentLink   = 0;
double CParams::dMutationRate             = 0;
double CParams::dMaxWeightPerturbation    = 0;
double CParams::dProbabilityWeightReplaced= 0;

double CParams::dActivationMutationRate   = 0;
double CParams::dMaxActivationPerturbation= 0;

double CParams::dCompatibilityThreshold   = 0;
int CParams::iNumBestSweepers             = 4;
int CParams::iOldAgeThreshold             = 45;
double CParams::dOldAgePenalty            = 0.9;
double CParams::dCrossoverRate            = .26;

double CParams::dBulletSpeed = 0;
double CParams::dBulletScale = 0;

double CParams::dMaxTranslationPerTick = 2.5;
double CParams::dGunScale = 6;
int CParams::iMaxBullets = 0;
int CParams::iFiringRate = 15;

int CParams::iPopSize = 200;
int CParams::iNumOnScreen = 0;
double CParams::dPercentageBestToSelectFrom = 0;
int CParams::iNumTourneyCompetitors = 0;
int CParams::iPreSpawns = 0;

double CParams::dMaxThrustLateral = 30;
double CParams::dMaxThrustVertical = 20;
double CParams::dMaxVelocity = 2;
double CParams::dAlienMass = 100;
double CParams::dAlienScale = 3;
double CParams::dGravityPerTick = 0;

//this function loads in the parameters from a given file name. Returns
//false if there is a problem opening the file.

void CParams::IncreaseTicks(int value) {
    iNumTicks = value;
}

bool CParams::LoadInParameters(const char* szFileName) {
    
    std::ifstream grab(szFileName);

    // Check if file exists
    if (!grab)
    {
        
        return false;
    }

    // Variables to read parameter description and values
    std::string ParamDescription;
   
    while (grab >> ParamDescription) {

        if (ParamDescription == "iFramesPerSecond") {
            grab >> iFramesPerSecond;
        }
        else if (ParamDescription == "dMaxTurnRate") {
            grab >> dMaxTurnRate;
        }
        else if (ParamDescription == "iSweeperScale") {
            grab >> iSweeperScale;
        }
        else if (ParamDescription == "iNumSensors") {
            grab >> iNumSensors;
        }
        else if (ParamDescription == "iNumOnScreen") {
            grab >> iNumOnScreen;
        }
        else if (ParamDescription == "dSensorRange") {
            grab >> dSensorRange;
        }
        else if (ParamDescription == "iNumSweepers") {
            grab >> iNumSweepers;
        }
        else if (ParamDescription == "iNumTicks") {
            grab >> iNumTicks;
        }
        else if (ParamDescription == "dCellSize") {
            grab >> dCellSize;
        }
        else if (ParamDescription == "iNumAddLinkAttempts") {
            grab >> iNumAddLinkAttempts;
        }
        else if (ParamDescription == "dSurvivalRate") {
            grab >> dSurvivalRate;
        }
        else if (ParamDescription == "iNumGensAllowedNoImprovement") {
            grab >> iNumGensAllowedNoImprovement;
        }
        else if (ParamDescription == "iMaxPermittedNeurons") {
            grab >> iMaxPermittedNeurons;
        }
        else if (ParamDescription == "dChanceAddLink") {
            grab >> dChanceAddLink;
        }
        else if (ParamDescription == "dChanceAddNode") {
            grab >> dChanceAddNode;
        }
        else if (ParamDescription == "dChanceAddRecurrentLink") {
            grab >> dChanceAddRecurrentLink;
        }
        else if (ParamDescription == "dMutationRate") {
            grab >> dMutationRate;
        }
        else if (ParamDescription == "dMaxWeightPerturbation") {
            grab >> dMaxWeightPerturbation;
        }
        else if (ParamDescription == "dProbabilityWeightReplaced") {
            grab >> dProbabilityWeightReplaced;
        }
        else if (ParamDescription == "dActivationMutationRate") {
            grab >> dActivationMutationRate;
        }
        else if (ParamDescription == "dMaxActivationPerturbation") {
            grab >> dMaxActivationPerturbation;
        }
        else if (ParamDescription == "dCompatibilityThreshold") {
            grab >> dCompatibilityThreshold;
        }
        else if (ParamDescription == "iOldAgeThreshold") {
            grab >> iOldAgeThreshold;

        }
        else if (ParamDescription == "dOldAgePenalty") {
            grab >> dOldAgePenalty;
        }
        else if (ParamDescription == "dYoungFitnessBonus") {
            grab >> dYoungFitnessBonus;
        }
        else if (ParamDescription == "iYoungBonusAgeThreshhold") {
            grab >> iYoungBonusAgeThreshhold;
        }
        else if (ParamDescription == "dCrossoverRate") {
            grab >> dCrossoverRate;
        }
        else if (ParamDescription == "dBulletSpeed") {
            grab >> dBulletSpeed;
        }
        else if (ParamDescription == "dBulletScale") {
            grab >> dBulletScale;
        }
        else if (ParamDescription == "iMaxBullets") {
            grab >> iMaxBullets;
        }
        
    }

    
    return true;
}

/*
bool CParams::LoadInParameters(const char* szFileName)
{
    OutputDebugString("Initialized the Parameters\n");
    std::ifstream grab(szFileName);

    // Check if file exists
    if (!grab)
    {
        OutputDebugString("Failed to open the file.\n");
        return false;
    }

    // Variables to read parameter description and values
    std::string paramDescription;
    int intValue;
    double doubleValue;

    // Read parameters from the file
    while (grab >> paramDescription)
    {
        if (paramDescription == "iFramesPerSecond") {
            grab >> iFramesPerSecond;
            OutputDebugString(("iFramesPerSecond: " + std::to_string(iFramesPerSecond) + "\n").c_str());
        }
        else if (paramDescription == "iNumHidden") {
            grab >> intValue;  // Example for an int value
            OutputDebugString(("iNumHidden: " + std::to_string(intValue) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iNeuronsPerHiddenLayer") {
            grab >> iNeuronsPerHiddenLayer;
            OutputDebugString(("iNeuronsPerHiddenLayer: " + std::to_string(intValue) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dActivationResponse") {
            grab >> dActivationResponse;
            OutputDebugString(("dActivationResponse: " + std::to_string(dActivationResponse) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dMutationRate") {
            grab >> dMutationRate;
            OutputDebugString(("dMutationRate: " + std::to_string(dMutationRate) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dMaxPerturbation") {
            grab >> dMaxWeightPerturbation;
            OutputDebugString(("dMaxPerturbation: " + std::to_string(dMaxWeightPerturbation) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iPopSize") {
            grab >> iPopSize;
            OutputDebugString(("iPopSize: " + std::to_string(iPopSize) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dPercentBestToSelectFrom") {
            grab >> dPercentageBestToSelectFrom;
            OutputDebugString(("dPercentBestToSelectFrom: " + std::to_string(dPercentageBestToSelectFrom) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iNumOnScreen") {
            grab >> iNumOnScreen;
            OutputDebugString(("iNumOnScreen: " + std::to_string(iNumOnScreen) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dBulletSpeed") {
            grab >> dBulletSpeed;
            OutputDebugString(("dBulletSpeed: " + std::to_string(dBulletSpeed) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "dBulletScale") {
            grab >> dBulletScale;
            OutputDebugString(("dBulletScale: " + std::to_string(dBulletScale) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iMaxBullets") {
            grab >> iMaxBullets;
            OutputDebugString(("iMaxBullets: " + std::to_string(intValue) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iNumTourneyCompetitors") {
            grab >> iNumTourneyCompetitors;
            OutputDebugString(("iNumTourneyCompetitors: " + std::to_string(iNumTourneyCompetitors) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iPreSpawns") {
            grab >> iPreSpawns;
            OutputDebugString(("iPreSpawns: " + std::to_string(iPreSpawns) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iNumSweepers") {
            grab >> iNumSweepers;
            OutputDebugString(("iNumSweepers: " + std::to_string(iNumSweepers) + "\n").c_str());
        }
        else if (paramDescription == "dSensorRange") {
            grab >> dSensorRange;
            OutputDebugString(("dSensorRange: " + std::to_string(dSensorRange) + "\n").c_str());
            // Assign to your appropriate variable
        }
        else if (paramDescription == "iNumTicks") {
            grab >> iNumTicks;
            OutputDebugString(("iNumTicks: " + std::to_string(iNumTicks) + "\n").c_str());
        }
        else if (paramDescription == "iNumAddLinkAttempts") {
            grab >> iNumAddLinkAttempts;
            OutputDebugString(("iNumAddLinkAttempts: " + std::to_string(iNumAddLinkAttempts) + "\n").c_str());
            // Assign to your appropriate variable
        }
        // Continue for all parameters...
    }
    
    return true;
}



bool CParams::LoadInParameters(const char* szFileName)
{
    
  ifstream grab(szFileName);

  //check file exists
  if (!grab)
  {
    return false;
  }

  //load in from the file
  char ParamDescription[40];

  grab >> ParamDescription;
  
  grab >> iFramesPerSecond;
  
  grab >> ParamDescription;
  grab >> dMaxTurnRate;
  
  grab >> ParamDescription;
  grab >> iSweeperScale;
  
  grab >> ParamDescription;
  grab >> iNumSensors;
  
  grab >> ParamDescription;
  grab >> iPopSize;
  
  grab >> ParamDescription;
  grab >> dPercentageBestToSelectFrom;
 
  grab >> ParamDescription;
  grab >> iNumOnScreen;
  
  grab >> ParamDescription;
  grab >> dSensorRange;
  
  grab >> ParamDescription;
  grab >> iNumSweepers;
 
  grab >> ParamDescription;
  grab >> iNumTicks;
  
  grab >> ParamDescription;
  grab >> dCellSize;
  grab >> ParamDescription;
  grab >> iNumAddLinkAttempts;
  grab >> ParamDescription;
  grab >> dSurvivalRate;
  grab >> ParamDescription;
  grab >> iNumGensAllowedNoImprovement;
  grab >> ParamDescription;
  grab >> iMaxPermittedNeurons;
  grab >> ParamDescription;
  grab >> dChanceAddLink;
  grab >> ParamDescription;
  grab >> dChanceAddNode;
  grab >> ParamDescription;
  grab >> dChanceAddRecurrentLink;
  grab >> ParamDescription;
  grab >> dMutationRate;
  grab >> ParamDescription;
  grab >> dMaxWeightPerturbation;
  grab >> ParamDescription;
  grab >> dProbabilityWeightReplaced;
  grab >> ParamDescription;
  grab >> dActivationMutationRate;
  grab >> ParamDescription;
  grab >> dMaxActivationPerturbation;
  grab >> ParamDescription;
  grab >> dCompatibilityThreshold;
  grab >> ParamDescription;
  grab >>iOldAgeThreshold;
  grab >> ParamDescription;
  grab >>dOldAgePenalty;
  grab >> ParamDescription;
  grab >> dYoungFitnessBonus;
  grab >> ParamDescription;
  grab >> iYoungBonusAgeThreshhold;
  grab >> ParamDescription;
  grab >>dCrossoverRate;
  grab >> ParamDescription;
  grab >> dBulletSpeed;
  grab >> ParamDescription;
  grab >> dBulletScale;
  grab >> ParamDescription;
  grab >> iMaxBullets;
  grab >> ParamDescription;
  OutputDebugString(("Number of Values: " + to_string(iNumTicks) + "\n").c_str());
  return true;
}
 
  
  
  */