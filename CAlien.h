#ifndef CALIEN_H
#define CALIEN_H
//-----------------------------------------------------------------------
//
//  Name: CAlien.h
//
//  Author: Mat Buckland 2002
//
//	Desc: class to define a space invader type alien. The alien has a 
//        neural net for a brain which controls its movement.
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



#include "phenotype.h"
#include "utils.h"

#include "collision.h"
#include "CMapper.h"
#include "CTimer.h"
using namespace std;



//------------------------------------------------------------------------
//
// class to define an alien 
//------------------------------------------------------------------------

//enumerated type to define thew actions the alien can perform each
//frame
enum action_type{thrust_left,
                 thrust_right,
                 thrust_up,
                 drift};

class CAlien
{

private:

    CNeuralNet*  m_ItsBrain;

    CMapper     m_MemoryMap;
    //its position in the world
    SVector2D       m_vPos;

    SVector2D       m_vVelocity;
    
    int livingLength;
    int cellsTravled = 0;
    int bulletDodged = 0;

    
    //its scale
    double          m_dScale;

    //fitness
    double			m_dFitness;
    int hasntGrownFitnes;
    //CAlien is dead
    bool dead;
    double bulletHit;
    //its mass
    double          m_dMass;   

    int time_distnaceToGun = 0;
    //its age (= its fitness)
    int             m_iAge;

    //its bounding box(for collision detection)
    RECT            m_AlienBBox;

    //vertex buffer for the alien's local coordinates
    vector<SPoint>  m_vecAlienVB;

    //vertex buffer to hold the alien's transformed vertices
    vector<SPoint>  m_vecAlienVBTrans;

    //when set to true a warning is displayed informing of
    //an input size mismatch to the neural net.
    bool            m_bWarning;


    void         WorldTransform();

    //checks for collision with any active bullets. Returns true if
    //a collision is detected
    bool         CheckForCollision(vector<CBullet> &bullets)const;

    //updates the alien's neural network and returns its next action
    action_type  GetActionFromNetwork(const vector<CBullet> &bullets,
                                      const SVector2D       &GunPos);

    
  
    //overload '<' used for sorting
	  friend bool operator<(const CAlien& lhs, const CAlien& rhs)
	  {
        
		  return (lhs.m_iAge > rhs.m_iAge);
	  }


public:
     
    CAlien();
    SVector2D getPos() { return m_vPos; }
    void DeathCalculations();
    

    void calculateFitness(const vector<CBullet>& bullets);

    
    void Render(HDC &surface, HPEN &GreenPen, HPEN &RedPen);
    
    //queries the alien's brain and updates it position accordingly
    bool Update(vector<CBullet> &bullets, const SVector2D &GunPos);

    //resets any relevant member variables ready for a new run
    void Reset();
    void FitnessReset();
    void setDeathLife();

    bool isDead();
    bool isBest;
    SVector2D getVelocity()const { return m_vVelocity; }
    //this mutates the connection weights in the alien's neural net
   // void Mutate();

    //-------------------------------------accessor methods
    SVector2D Pos()const{return m_vPos;}
    double    Fitness()const { //return  
        return m_iAge;
    }
   
    void      DrawNet(HDC& surface, int cxLeft, int cxRight, int cyTop, int cyBot)
    {
       m_ItsBrain->DrawNet(surface, cxLeft, cxRight, cyTop, cyBot);
    }

    void              InsertNewBrain(CNeuralNet* brain) {m_ItsBrain = brain; }
};


#endif