#include "AfterGameSaveData.h"

AfterGameSaveData::AfterGameSaveData()
{

}

void AfterGameSaveData::AddToLifeTime(int value)
{
	lifetimes.push_back(value);
}

void AfterGameSaveData::AddToLifeTime(vector<int> vectors)
{
	lifetimes = vectors;
}



void AfterGameSaveData::SaveNeuronsToTextFile(vector<SNeuron*>& neurons, std::string filename)
{
    
    ofstream file(filename, ios::out | ios::trunc);
    

    if (file.is_open())
    {
        for (SNeuron* neuron : neurons) // No const here
        {
            if (neuron != nullptr) // Ensure the pointer is valid
            {
                file << "NeuronID: " << neuron->iNeuronID << std::endl;
                file << "NeuronType: " << neuron->NeuronType << std::endl;
                file << "dSumActivation: " << neuron->dSumActivation << std::endl;
                file << "dOutput: " << neuron->dOutput << std::endl;
                file << "dActivationResponse: " << neuron->dActivationResponse << std::endl;
                file << "iPosX: " << neuron->iPosX << ", iPosY: " << neuron->iPosY << std::endl;
                file << "dSplitY: " << neuron->dSplitY << ", dSplitX: " << neuron->dSplitX << std::endl;

                // Save incoming and outgoing links (if needed)
                file << "LinksInCount: " << neuron->vecLinksIn.size() << std::endl;
                for (auto& link : neuron->vecLinksIn) // No const here
                {
                    file << "LinkIn: FromNeuron: " << link.pIn << " ToNeuron: " << link.pOut
                        << " Weight: " << link.dWeight << std::endl;
                }

                file << "LinksOutCount: " << neuron->vecLinksOut.size() << std::endl;
                for (auto& link : neuron->vecLinksOut) // No const here
                {
                    file << "LinkOut: FromNeuron: " << link.pIn << " ToNeuron: " << link.pOut
                        << " Weight: " << link.dWeight << std::endl;
                }

                file << "-----------------------------" << std::endl;
            }
        }

        file.close();
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
    }
}




void AfterGameSaveData::WeightSaveDataToFile(vector<double> dataToSave)
{

    string filename = "C:\\Users\\Joshua\\Desktop\\SavedGameData\\WeightNormalNEAT.csv";
    ofstream outFile(filename, ios::out | ios::trunc);

    if (!outFile.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    for (const auto& data : dataToSave)
    {
        outFile << data << "\n";
    }

    outFile.close();
}

void AfterGameSaveData::SaveDataToFile()
{

    string filename = "C:\\Users\\Joshua\\Desktop\\SavedGameData\\ComleteNeatBrainyData.csv";
    ofstream outFile(filename, ios::out | ios::trunc);

    if (!outFile.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    for (const auto& lifetime : lifetimes)
    {
        outFile << lifetime << "\n";
    }

    outFile.close();
}
