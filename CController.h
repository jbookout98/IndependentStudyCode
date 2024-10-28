#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Controller class for NEAT Sweepers  
//
//------------------------------------------------------------------------
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>
#include <math.h>
#include "CMinesweeper.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"
#include "Cga.h"
#include "CAlien.h"
#include <set>
#include "CGun.h"
#include "AfterGameSaveData.h"
using namespace std;


typedef multiset<CAlien>::iterator AlienIterator;

class CController
{

private:

	//storage for the entire population of chromosomes
	Cga* m_pPop;

	CGun* m_pGunTurret;

	//the pool of aliens
	multiset<CAlien> m_setAliens;
	AfterGameSaveData dataSaver;
	//the currently active aliens
	vector<CAlien>   m_vecActiveAliens;
	vector<CAlien> deadAliensBuffer;

	int m_iAliensCreatedSoFar;

	double highestFitness;
	double lastEpochFitnes;
	int hasntGrownFitnes;
	int aliensKilled;

	int              m_iNumSpawnedFromTheMultiset;

	//vertex buffer for the stars
	vector<SPoint>   m_vecStarVB;
	
	//array of sweepers
	vector<CAlien> m_vecSweepers;

	//array of best sweepers from last generation (used for
	//display purposes when 'B' is pressed by the user)
	vector<CAlien> m_vecBestSweepers;
	vector<double> saveOnWeightPerMutate;
	int					         m_NumSweepers;

	//vertex buffer for the sweeper shapes vertices
	vector<SPoint>		   m_SweeperVB;

	//vertex buffer for objects
	vector<SPoint>       m_ObjectsVB;

	//stores the average fitness per generation 
	vector<double>		   m_vecAvFitness;

	//stores the best fitness per generation
	vector<double>		   m_vecBestFitness;

	vector<int>  averageAgePerTenAliens;
	//best fitness ever
	double               m_dBestFitness;

	//pens we use for the stats
	HPEN				m_RedPen;
	HPEN				m_BluePen;
	HPEN				m_GreenPen;
	HPEN        m_GreyPenDotted;
	HPEN        m_RedPenDotted;
	HPEN				m_OldPen;
	HPEN             m_GunPen;
	HPEN             m_BarPen;

	HBRUSH      m_RedBrush;
	HBRUSH      m_BlueBrush;

	//local copy of the handle to the application window
	HWND				m_hwndMain;

	//local copy of the  handle to the info window
	HWND        m_hwndInfo;

	//toggles the speed at which the simulation runs
	bool				m_bFastRender;

	//when set, renders the best performers from the 
	//previous generaion.
	bool        m_bRenderBest;

	//cycles per generation
	int					m_iTicks;

	//generation counter
	int					m_iGenerations;

	//local copy of the client window dimensions
	int         m_cxClient, m_cyClient;

	//this is the sweeper who's memory cells are displayed
	int         m_iViewThisSweeper;

	void   PlotStats(HDC surface)const;

	void   RenderSweepers(HDC& surface, vector<CAlien>& sweepers);

	void   RenderSensors(HDC& surface, vector<CAlien>& sweepers);
	vector<CAlien> TournamentSelection();
public:

	CController(HWND hwndMain, int cxClient, int cyClient);

	~CController();

	void Reset();

	void DeleteTheAlienWithTheWorstFitness();

	void		Render(HDC& surface);

	//renders the phenotypes of the four best performers from
	//the previous generation
	void    RenderNetworks(HDC& surface);

	bool		Update();

	bool AllAliensAreDead();

	SVector2D getClosestAlien(SVector2D);

	//-------------------------------------accessor methods
	bool		        FastRender()const { return m_bFastRender; }
	void		        FastRender(bool arg) { m_bFastRender = arg; }
	void		        FastRenderToggle() { m_bFastRender = !m_bFastRender; }

	bool            RenderBest()const { return m_bRenderBest; }
	void            RenderBestToggle() { m_bRenderBest = !m_bRenderBest; }

	void            PassInfoHandle(HWND hnd) { m_hwndInfo = hnd; }
	vector<int>		GetLifeTimes() { return averageAgePerTenAliens; }
	vector<double>  GetFitnessScores(vector<CAlien> arrayToUsed)const;
	vector<double> getWeightsAll() {
		return saveOnWeightPerMutate;
	}

	void            ViewBest(int val)
	{
		if ((val > 4) || (val < 1))
		{
			return;
		}

		m_iViewThisSweeper = val - 1;
	}
};


#endif

