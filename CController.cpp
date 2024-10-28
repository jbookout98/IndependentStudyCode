#include "CController.h"


//these hold the geometry of the sweepers and the mines
const int	 NumSweeperVerts = 16;
const SPoint sweeper[NumSweeperVerts] = { SPoint(-1, -1),
                                         SPoint(-1, 1),
                                         SPoint(-0.5, 1),
                                         SPoint(-0.5, -1),

                                         SPoint(0.5, -1),
                                         SPoint(1, -1),
                                         SPoint(1, 1),
                                         SPoint(0.5, 1),

                                         SPoint(-0.5, -0.5),
                                         SPoint(0.5, -0.5),

                                         SPoint(-0.5, 0.5),
                                         SPoint(-0.25, 0.5),
                                         SPoint(-0.25, 1.75),
                                         SPoint(0.25, 1.75),
                                         SPoint(0.25, 0.5),
                                         SPoint(0.5, 0.5) };



const int NumMineVerts = 4;
const SPoint mine[NumMineVerts] = { SPoint(-1, -1),
                                   SPoint(-1, 1),
                                   SPoint(1, 1),
                                   SPoint(1, -1) };


const int NumObjectVerts = 42;
const SPoint objects[NumObjectVerts] = { SPoint(80, 60),
                                        SPoint(200,60),
                                        SPoint(200,60),
                                        SPoint(200,100),
                                        SPoint(200,100),
                                        SPoint(160,100),
                                        SPoint(160,100),
                                        SPoint(160,200),
                                        SPoint(160,200),
                                        SPoint(80,200),
                                        SPoint(80,200),
                                        SPoint(80,60),

                                        SPoint(250,100),
                                        SPoint(300,40),
                                        SPoint(300,40),
                                        SPoint(350,100),
                                        SPoint(350,100),
                                        SPoint(250, 100),

                                        SPoint(220,180),
                                        SPoint(320,180),
                                        SPoint(320,180),
                                        SPoint(320,300),
                                        SPoint(320,300),
                                        SPoint(220,300),
                                        SPoint(220,300),
                                        SPoint(220,180),

                                        SPoint(12,15),
                                        SPoint(380, 15),
                                        SPoint(380,15),
                                        SPoint(380,360),
                                        SPoint(380,360),
                                        SPoint(12,360),
                                        SPoint(12,360),
                                        SPoint(12,340),
                                        SPoint(12,340),
                                        SPoint(100,290),
                                        SPoint(100,290),
                                        SPoint(12,240),
                                        SPoint(12,240),
                                        SPoint(12,15) };





//---------------------------------------constructor---------------------
//
//	initilaize the sweepers, their brains and the GA factory
//
//-----------------------------------------------------------------------
CController::CController(HWND hwndMain,
    int  cxClient,
    int  cyClient) : m_NumSweepers(CParams::iNumOnScreen),
    m_iNumSpawnedFromTheMultiset(0),
    m_iAliensCreatedSoFar(0),
    m_bFastRender(false),
    m_bRenderBest(false),
    m_iTicks(0),
    m_hwndMain(hwndMain),
    m_hwndInfo(NULL),
    m_iGenerations(0),
    m_cxClient(cxClient),
    m_cyClient(cyClient),
    m_iViewThisSweeper(0)
{
  
    m_pGunTurret = new CGun();
    

    //create the first few aliens
    
    for (int a = 0; a < m_NumSweepers; ++a)
    {
        m_vecActiveAliens.push_back(CAlien());

        ++m_iAliensCreatedSoFar;
    }
    for (int i = 0; i < CParams::iNumBestSweepers; ++i)
    {
        m_vecBestSweepers.push_back(CAlien());
        
    }
    for (int star = 0; star < NUM_STARS; ++star)
    {
        m_vecStarVB.push_back(SPoint(RandInt(0, cxClient), RandInt(0, cyClient)));
    }
    for (int i = 0; i < CParams::iNumBestSweepers; ++i)
    {
        m_vecBestSweepers[i].isBest = true;

    }

    
    
    m_pPop = new Cga(m_NumSweepers,
        CParams::iNumInputs,
        CParams::iNumOutputs,
        hwndMain,
        10, 10);
    
        //create the phenotypes
    vector<CNeuralNet*> pBrains = m_pPop->CreatePhenotypes();


    for (int i = 0; i < m_NumSweepers; i++)
    {
        //OutputDebugString(to_string(i).c_str());
        m_vecActiveAliens[i].InsertNewBrain(pBrains[i]);
    }
    m_pGunTurret->SetController(m_vecActiveAliens);
    //create a pen for the graph drawing
    m_BluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    m_RedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    m_GreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    m_GreyPenDotted = CreatePen(PS_DOT, 1, RGB(100, 100, 100));
    m_RedPenDotted = CreatePen(PS_DOT, 1, RGB(200, 0, 0));



    m_OldPen = NULL;
    m_GunPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 100));
    m_BarPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
    //and the brushes
    m_BlueBrush = CreateSolidBrush(RGB(0, 0, 244));
    m_RedBrush = CreateSolidBrush(RGB(150, 0, 0));


}

//--------------------------------------destructor-------------------------------------
//
//--------------------------------------------------------------------------------------
CController::~CController()
{
    if (m_pPop)
    {
        delete m_pPop;
    }

    DeleteObject(m_BluePen);
    DeleteObject(m_RedPen);
    DeleteObject(m_GreenPen);
    DeleteObject(m_OldPen);
    DeleteObject(m_GreyPenDotted);
    DeleteObject(m_RedPenDotted);
    DeleteObject(m_BlueBrush);
    DeleteObject(m_RedBrush);
}
void CController::Reset()
{
    //clear all current aliens
    m_vecActiveAliens.clear();
    m_setAliens.clear();

    //reset all variables
    m_iAliensCreatedSoFar = 0;
    m_iNumSpawnedFromTheMultiset = 0;
    m_bFastRender = true;

    m_pGunTurret->AutoGunOn();

    //create the first few aliens
    for (int a = 0; a < CParams::iNumOnScreen; ++a)
    {
        m_vecActiveAliens.push_back(CAlien());

        ++m_iAliensCreatedSoFar;
    }
}
/*
bool CController::Update()
{


    //get update from player for the turret movement
    //and update any bullets that may have been fired

    m_pGunTurret->Update();

    //move the stars
    for (int str = 0; str < m_vecStarVB.size(); ++str)
    {
        m_vecStarVB[str].y -= 0.2f;

        if (m_vecStarVB[str].y < 0)
        {
            //create a new star
            m_vecStarVB[str].x = RandInt(0, CParams::WindowWidth);
            m_vecStarVB[str].y = CParams::WindowHeight;
        }
    }


    bool deadOrNot = AllAliensAreDead();
  

    for (int i = 0; i < m_NumSweepers; ++i)
    {
        //update the NN and position
        if (!m_vecActiveAliens[i].Update(m_pGunTurret->m_vecBullets,
            m_pGunTurret->m_vPos))
        {
            averageAgePerTenAliens.push_back(m_vecActiveAliens[i].Fitness());
            m_setAliens.insert(m_vecActiveAliens[i]);

            //if the required population size has been reached, delete the 
            //worst performer from the multiset
            if (m_setAliens.size() >= CParams::iPopSize)
            {
                m_setAliens.erase(--m_setAliens.end());
            }
            ++m_iNumSpawnedFromTheMultiset;
            
            ++m_iGenerations;
            if (m_iAliensCreatedSoFar <= CParams::iPopSize)
            {
                m_iAliensCreatedSoFar++;
                m_vecActiveAliens[i].Reset();
            }
            else
            {
                //get best 10 aliens values from multi
                vector<CAlien> aliensPicked = TournamentSelection();
                OutputDebugString(to_string(aliensPicked.size()).c_str());

                m_vecActiveAliens[i].Reset();

                if (RandFloat() < 0.8)
                {
                    vector<CNeuralNet*> pBrains = m_pPop->Epoch(GetFitnessScores(aliensPicked));

                    //insert the new  brains back into the sweepers and reset their
                //positions
                    for (int i = 0; i < m_NumSweepers; ++i)
                    {
                        m_vecActiveAliens[i].InsertNewBrain(pBrains[i]);

                    }
                   

                    
                    
                    //grab the NNs of the best performers from the last generation
                    vector<CNeuralNet*> pBestBrains = m_pPop->GetBestPhenotypesFromLastGeneration();

                    //put them into our record of the best sweepers
                    for (int i = 0; i < m_vecBestSweepers.size(); ++i)
                    {
                        m_vecBestSweepers[i].InsertNewBrain(pBestBrains[i]);

                        m_vecBestSweepers[i].Reset();
                    }

                    //this will call WM_PAINT which will render our scene
                    InvalidateRect(m_hwndInfo, NULL, TRUE);
                    UpdateWindow(m_hwndInfo);

                }
            }


        }
    }

   

    
   

    return true;
}*/
//-----------------Update---------------------------------------
//
//	This is the main workhorse. The entire simulation is controlled from here.
//
//--------------------------------------------------------------------------------------

bool CController::Update()
{
    
    
    //get update from player for the turret movement
    //and update any bullets that may have been fired
    
    m_pGunTurret->Update();
    
    //move the stars
    for (int str = 0; str < m_vecStarVB.size(); ++str)
    {
        m_vecStarVB[str].y -= 0.2f;

        if (m_vecStarVB[str].y < 0)
        {
            //create a new star
            m_vecStarVB[str].x = RandInt(0, CParams::WindowWidth);
            m_vecStarVB[str].y = CParams::WindowHeight;
        }
    }
    
 
    bool deadOrNot = AllAliensAreDead();
   
    if (m_iTicks++ < CParams::iNumTicks && (deadOrNot ==false))
    {

        
        for (int i = 0; i < m_NumSweepers; ++i)
        {
            //update the NN and position
            if (!m_vecActiveAliens[i].Update(m_pGunTurret->m_vecBullets,
                m_pGunTurret->m_vPos))
            {
                m_vecActiveAliens[i].Reset();
            }
        }

        if (m_iGenerations > 0)
        {
            for (int i = 0; i < m_vecBestSweepers.size(); ++i)
            {
                //update the NN and position
                if (!m_vecBestSweepers[i].Update(m_pGunTurret->m_vecBullets,
                    m_pGunTurret->m_vPos))
                {
                    
                }
            }
        }

    }
    //We have completed another generation so now we need to run the GA
    else
    {
        //first add up each sweepers fitness scores. (remember for this task
        //there are many different sorts of penalties the sweepers may incur
        //and each one has a coefficient)
        hasntGrownFitnes++;
        for (int i = 0; i < m_NumSweepers; ++i)
        {
            double fit = m_vecActiveAliens[i].Fitness();
            averageAgePerTenAliens.push_back(fit);
            if (fit > highestFitness) {
                highestFitness = fit;
                hasntGrownFitnes = 0;
            }
 
        }
        
        
        
       
        vector<double> weights = m_pPop->GetWeights();
        for (int i = 0; i < weights.size(); i++) {
            saveOnWeightPerMutate.push_back(weights[i]);
        }
        lastEpochFitnes = highestFitness;
        //increment the generation counter
        ++m_iGenerations;

        //reset cycles
        m_iTicks = 0;
        
        //perform an epoch and grab the new brains
        vector<CNeuralNet*> pBrains = m_pPop->Epoch(GetFitnessScores(m_vecActiveAliens));

        //insert the new  brains back into the sweepers and reset their
    //positions
        for (int i = 0; i < m_NumSweepers; ++i)
        {
            m_vecActiveAliens[i].InsertNewBrain(pBrains[i]);

        }
        //grab the NNs of the best performers from the last generation
        vector<CNeuralNet*> pBestBrains = m_pPop->GetBestPhenotypesFromLastGeneration();
        
        //put them into our record of the best sweepers
        for (int i = 0; i < m_vecBestSweepers.size(); ++i)
        {
            m_vecBestSweepers[i].InsertNewBrain(pBestBrains[i]);

            m_vecBestSweepers[i].Reset();
        }
        if (m_iGenerations % 10 == 0) {
            OutputDebugString("Save Neuron Data");
            vector<SNeuron*> p = pBestBrains[0]->getNeurons();
            dataSaver.SaveNeuronsToTextFile(p,"C:\\Users\\Joshua\\Desktop\\SavedGameData\\Neurons\\Neurons"+to_string(m_iGenerations)+".txt");
        }
        //this will call WM_PAINT which will render our scene
        InvalidateRect(m_hwndInfo, NULL, TRUE);
        UpdateWindow(m_hwndInfo);

    }
    
    return true;
}

bool CController::AllAliensAreDead() {
    
    bool isDead = true;
    for (int i = 0; i < m_vecActiveAliens.size(); i++) {
        if (m_vecActiveAliens[i].isDead()==false) {
            isDead = false;
        }
        
    }
   
    return isDead;
}
//---------------------------------- RenderNetworks ----------------------
//
//  Renders the best four phenotypes from the previous generation
//------------------------------------------------------------------------
void CController::RenderNetworks(HDC& surface)
{
    if (m_iGenerations < 1)
    {
        return;
    }

    //draw the network of the best 4 genomes. First get the dimensions of the 
     //info window
    RECT rect;
    GetClientRect(m_hwndInfo, &rect);

    int	cxInfo = rect.right;
    int	cyInfo = rect.bottom;

    //now draw the 4 best networks
    m_vecBestSweepers[0].DrawNet(surface, 0, cxInfo / 2, cyInfo / 2, 0);
    m_vecBestSweepers[1].DrawNet(surface, cxInfo / 2, cxInfo, cyInfo / 2, 0);
    m_vecBestSweepers[2].DrawNet(surface, 0, cxInfo / 2, cyInfo, cyInfo / 2);
    m_vecBestSweepers[3].DrawNet(surface, cxInfo / 2, cxInfo, cyInfo, cyInfo / 2);
}



//------------------------------------Render()--------------------------------------
//
//----------------------------------------------------------------------------------
void CController::Render(HDC& surface)
{
    if (!m_bFastRender)
    {
        //change the mapping mode so that the origin is at the bottom left
        //of our window and so that the y axis increases as it goes from
        //bottom to top     
        SetMapMode(surface, MM_ANISOTROPIC);
        SetViewportExtEx(surface, 1, -1, NULL);
        SetWindowExtEx(surface, 1, 1, NULL);
        SetViewportOrgEx(surface, 0, m_cyClient, NULL);


        //-------------------first render the stars

        for (int i = 0; i < m_vecStarVB.size(); ++i)
        {
            //make them twinkle
            if (RandFloat() > 0.1)
            {
                SetPixel(surface, m_vecStarVB[i].x, m_vecStarVB[i].y, RGB(255, 255, 255));
            }
        }
        for (int i = 0; i < CParams::WindowWidth; i++) {
            SetPixel(surface, i, 20, RGB(0, 255, 0));
        }

        //-------------------render the aliens
        
        for (int i = 0; i < m_vecActiveAliens.size(); ++i)
        {
            m_vecActiveAliens[i].Render(surface, m_GreenPen, m_RedPen);
        }

        //-------------------render the gun and any bullets

        m_pGunTurret->Render(surface, m_GunPen);


        //-------------------render additional information

        SetBkMode(surface, TRANSPARENT);
        SetTextColor(surface, RGB(0, 0, 255));

        string s = "Generations Created " + itos(m_iGenerations);
        TextOut(surface, 5, m_cyClient - 5, s.c_str(), s.size());


        //return the mapping mode to its default state so text is rendered
        //correctly
        SetMapMode(surface, MM_ANISOTROPIC);
        SetViewportExtEx(surface, 1, 1, NULL);
        SetWindowExtEx(surface, 1, 1, NULL);
        SetViewportOrgEx(surface, 0, 0, NULL);

    }

    else
    {
        PlotStats(surface);

        RECT sr;
        sr.top = m_cyClient - 50;
        sr.bottom = m_cyClient;
        sr.left = 0;
        sr.right = m_cxClient;

        //render the species chart
        m_pPop->RenderSpeciesInfo(surface, sr);

        SetBkMode(surface, TRANSPARENT);
        SetTextColor(surface, RGB(0, 0, 255));

        string s = to_string(m_iTicks);
        TextOut(surface, 10, m_cyClient - 45, s.c_str(), s.size());

        HPEN OldPen = (HPEN)SelectObject(surface, m_BarPen);

        MoveToEx(surface, 10, m_cyClient - 20, NULL);
        //LineTo(surface, (m_cxClient / (double)CParams::iPreSpawns) * m_iNumSpawnedFromTheMultiset - 10, m_cyClient - 20);

        SelectObject(surface, OldPen);

    }
}


//------------------------- RenderSweepers -------------------------------
//
//  given a vector of sweepers this function renders them to the screen
//------------------------------------------------------------------------

//----------------------------- RenderSensors ----------------------------
//
//  renders the sensors of a given vector of sweepers
//------------------------------------------------------------------------


//--------------------------PlotStats-------------------------------------
//
//  Given a surface to draw on this function displays some simple stats 
//------------------------------------------------------------------------
void CController::PlotStats(HDC surface)const
{
    string s = "Generation:              " + itos(m_iGenerations);
    TextOut(surface, 5, 25, s.c_str(), s.size());

    s = "Num Species:          " + itos(m_pPop->NumSpecies());
    TextOut(surface, 5, 45, s.c_str(), s.size());

    s = "Best Fitness so far: " + ftos(m_pPop->BestEverFitness());
    TextOut(surface, 5, 5, s.c_str(), s.size());
}

vector<CAlien> CController::TournamentSelection()
{
    vector<CAlien> topAliens;  // This will store the top 10 aliens
    int numToSelect = 10;      // Number of aliens we want to select

    // Check if we have enough aliens in the population
    if (m_setAliens.size() < numToSelect)
    {
        // If the population is too small, return an empty vector
        return topAliens;
    }

    // Iterate through tournament competitors
    for (int i = 0; i < 10; ++i)
    {
        // Select a random alien from the population
        int randomIndex = RandInt(0, (int)(m_setAliens.size() - 1));
        AlienIterator curAlien = m_setAliens.begin();
        advance(curAlien, randomIndex);

        // Print debug information to check the fitness of the selected alien
        

        // Insert the current alien into the vector
        topAliens.push_back(*curAlien);

        // If we have more than 10 aliens, remove the weakest one
        if (topAliens.size() > numToSelect)
        {
            // Sort aliens based on fitness
            sort(topAliens.begin(), topAliens.end(), [](const CAlien& a, const CAlien& b) {
                return a.Fitness() > b.Fitness();  // Sort in descending order
            });

            // Remove the last alien, which has the lowest fitness
            topAliens.pop_back();
        }
    }

    // Sort the final top 10 aliens
    sort(topAliens.begin(), topAliens.end(), [](const CAlien& a, const CAlien& b) {
        return a.Fitness() > b.Fitness();  // Sort in descending order
    });

   
    // Return the top 10 selected aliens
    return topAliens;
}




//------------------------------- GetFitnessScores -----------------------
//
//  returns a std::vector containing the genomes fitness scores
//------------------------------------------------------------------------
vector<double> CController::GetFitnessScores(vector<CAlien> arrayToUsed)const
{
    vector<double> scores;
    
    for (int i = 0; i < arrayToUsed.size(); ++i)
    {
        double fitness = arrayToUsed[i].Fitness();
        scores.push_back(fitness);
        
        
    }
    
    return scores;
}