#ifndef CGUN_H
#define CGUN_H
//-----------------------------------------------------------------------
//
//  Name: CGun.h
//
//  Author: Mat Buckland 2002
//
//	Desc: class to define a gun turret
//
//-----------------------------------------------------------------------
#include <vector>
#include <windows.h>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "CBullet.h"
#include "CParams.h"
#include "SVector2D.h"
#include "CAlien.h"
using namespace std;


class CGun
{

private:

    //its position in the world
    SVector2D       m_vPos;

    //its scale
    double          m_dScale;
    
    //this is used to calculate when another bullet may be 
    //fired
    int             m_iTicksToNextBullet;

    
    //vertex buffer for the gun's vertices 
    vector<SPoint>  m_vecGunVB;

    vector<CAlien>* aliens;
    //vertex buffer to hold the gun's transformed vertices
    vector<SPoint>  m_vecGunVBTrans;

    //used to toggle the auto gun.
    bool            m_bAutoGun;
    bool            m_bClosestGun;

    //a container to hold the bullets the gun shoots
    vector<CBullet> m_vecBullets;

  
    void WorldTransform();
    
    //lets the gun fire and move position at random. Useful for
    //accelerating the aliens development in the early stages. 
    void AutoGun();

    void Reset();

    void ClosestGun();

    CAlien getClosestAlien(SVector2D pos);


public:

    CGun();
    
    void SetController(vector<CAlien>& c) {
        aliens = &c;
    }
    void Render(HDC &surface, HPEN &GreenPen);

    bool GetIfBulletsActive(int id);

    //Checks for user keypresses and updates the gun's parameters
    //accordingly. When the gun has been updated any active bullets
    //are also updated.
    void Update();    

    void AutoGunOff() { m_bAutoGun = false; m_bClosestGun = false; }
    void AutoClosestGunOn() { m_bClosestGun = true; }
    void AutoGunOn(){m_bAutoGun = true;}

    friend class CController;

};


#endif