#include "CGun.h"


const int NumGunVerts = 8;
const SPoint gun[NumGunVerts] = {SPoint(2,2),
                                 SPoint(2,0),
                                 SPoint(-2,0),
                                 SPoint(-2,2),
                                 SPoint(-1,2),
                                 SPoint(-1,3),
                                 SPoint(1,3),
                                 SPoint(1,2)};

//--------------------------------- ctor ---------------------------------
//
//------------------------------------------------------------------------
CGun::CGun(): m_iTicksToNextBullet(CParams::iFiringRate),
              m_dScale(CParams::dGunScale),
              m_bAutoGun(false),m_bClosestGun(true)
{ 
    
  //set its position
  m_vPos = SVector2D(CParams::WindowWidth/2, 20);
  
  //create the vertex buffer
  for (int i=0; i<NumGunVerts; ++i)
  {
    m_vecGunVB.push_back(gun[i]);
  }
  
  //create the bullets
  for (int i=0; i<CParams::iMaxBullets; ++i)
  {   
    m_vecBullets.push_back(CBullet());
  }
}


//------------------------------ Render ----------------------------------
//
//------------------------------------------------------------------------
void CGun::Render(HDC &surface, HPEN &GunPen)
{
  WorldTransform();

  HPEN OldPen = (HPEN)SelectObject(surface, GunPen);
  
  MoveToEx(surface, m_vecGunVBTrans[0].x, m_vecGunVBTrans[0].y, NULL);

  for (int vtx=0; vtx<m_vecGunVBTrans.size(); ++vtx)
  {
    LineTo(surface, m_vecGunVBTrans[vtx].x, m_vecGunVBTrans[vtx].y);
  }

  LineTo(surface, m_vecGunVBTrans[0].x, m_vecGunVBTrans[0].y);

  int BulletCounter = 0;

  //render any active bullets
  for (int blt=0; blt<m_vecBullets.size(); ++blt)
  {
    if (m_vecBullets[blt].Active())
    {
      m_vecBullets[blt].Render(surface, GunPen);

      ++BulletCounter;
    }
  }

  SelectObject(surface, OldPen);
}


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the ship and applies the
//	world transform to the ships vertex buffer
//-------------------------------------------------------------------
void CGun::WorldTransform()
{
	//copy the original vertices into the buffer about to be transformed
  m_vecGunVBTrans = m_vecGunVB;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(m_dScale, m_dScale);

	//and translate
	matTransform.Translate(m_vPos.x, m_vPos.y);
	
  //now transform the ships vertices
  matTransform.TransformSPoints(m_vecGunVBTrans);

  string s = "Gun Position: (" + to_string(m_vPos.x) + to_string(m_vPos.y) + ")\n";


  //OutputDebugString(s.c_str());

}

CAlien CGun::getClosestAlien(SVector2D gunPos) {

    CAlien closest;
    double _cdistnace = 1000000;
    for (CAlien& alien : *aliens) {
        SVector2D vec = gunPos;
        if (alien.isDead()==false) {

            vec = alien.getPos();

            
            double x = vec.x - gunPos.x;
            double y = vec.y - gunPos.y;
            double dis = sqrt(pow(x, 2) + pow(y, 2));
            if (dis < _cdistnace) {
                _cdistnace = dis;
                closest = alien;
            }

        }

    }
    return closest;
}

//----------------------------- Update -----------------------------------
//
//  Checks for user keypresses and updates the gun's parameters accordingly
//  When the gun has been updated any active bullets are also updated.
//------------------------------------------------------------------------
bool CGun::GetIfBulletsActive(int id) {
   return m_vecBullets[id].Active();
}

void CGun::Update()
{
  //if auto gun enabled, update accordingly
  if (m_bAutoGun)
  {
    AutoGun();
    
    return;
  }
  if (m_bClosestGun) {
      ClosestGun();
      return;

  }
  //move gun left
  if (KEYDOWN(VK_LEFT) && (!(m_vPos.x < m_dScale)))
  {
    m_vPos.x -= CParams::dMaxTranslationPerTick;   
  }

  //move right
  if ( KEYDOWN(VK_RIGHT) && (!(m_vPos.x > CParams::WindowWidth-m_dScale)) )
  {
    m_vPos.x += CParams::dMaxTranslationPerTick;   
  }
 
  //fire
  if (KEYDOWN(VK_SPACE) && (m_iTicksToNextBullet < 0))
  {
    //create a new bullet
    for (int blt=0; blt<m_vecBullets.size(); ++blt)
    {
      //choose the first non active bullet to switch on
      if (!m_vecBullets[blt].Active())
      {
         m_vecBullets[blt].SwitchOn(m_vPos.x);

         m_iTicksToNextBullet = CParams::iFiringRate;

         break;
      }
    }
  }

  
  //now update any active bullets.
  for (int blt=0; blt<m_vecBullets.size(); ++blt)
  {
    m_vecBullets[blt].Update();
  }

  m_iTicksToNextBullet -= 1;

}


//-------------------------------- AutoGun -------------------------------
//
//  automatically updates the gun. Moves its position and fires at random
//  
//------------------------------------------------------------------------
void CGun::AutoGun()
{
  //how long it will perform each action for
  static int duration = 0;

  //the action it will perform
  static int action   = 0;

  if (duration <= 0)
  {
    //choose another direction and duration
    duration = RandInt(30, 300);
    action   = RandInt(0,2);
  }

  --duration;
  
  switch(action)
  {

  case 0:  //move left
    {
      if (m_vPos.x > m_dScale)
      {
        m_vPos.x -= CParams::dMaxTranslationPerTick;
      }

      else
      {
        action = 1;
      }
    }

  break;

  case 1:  //move right
    {
      if (m_vPos.x < CParams::WindowWidth-m_dScale)
      {
        m_vPos.x += CParams::dMaxTranslationPerTick;
      }

      else
      {
        action = 0;
      }
    }

  break;
  
  }//end switch
  

  //create a new bullet
  for (int blt=0; blt<m_vecBullets.size(); ++blt)
  {
    if (!m_vecBullets[blt].Active())
    {
       m_vecBullets[blt].SwitchOn(m_vPos.x);           

       duration = -1;

       break;
    }
  }     
  
  //update any bullets which are active
  for (int blt=0; blt<m_vecBullets.size(); ++blt)
  {
    m_vecBullets[blt].Update();
  }
    
}
void CGun::Reset() {

    for(int blt = 0; blt < m_vecBullets.size(); ++blt)
    {
        m_vecBullets[blt].SwitchOff();
    }
    m_vPos.x = CParams::WindowWidth / 2;
}
void CGun::ClosestGun()
{
    
    // the action it will perform
    static int action = 0;

    // get the position of the closest alien
    CAlien closestAlienPos = getClosestAlien(m_vPos);
    SVector2D velocity = closestAlienPos.getVelocity();
    SVector2D target = closestAlienPos.getPos();
    // determine the direction to move based on the closest alien's position
    
    if (target.x < m_vPos.x) {
        action = 0;
    }
    else if (target.x > m_vPos.x) {
        action = 1;
    }

    switch (action)
    {
        case 0:  // move left
        {
            if (m_vPos.x > m_dScale)
            {
                m_vPos.x -= CParams::dMaxTranslationPerTick;
            }
            
        }
        break;

        case 1:  // move right
        {
            if (m_vPos.x < CParams::WindowWidth - m_dScale)
            {
                m_vPos.x += CParams::dMaxTranslationPerTick;
            }
           
        }
        break;
    } // end switch
    // create a new bullet if the alien is close enough
    //lets assume time is 2 seconds 
    const double shootingDistance = 30.0; // arbitrary value for closeness
    if (fabs(target.x - m_vPos.x) < shootingDistance)
    {
        for (int blt = 0; blt < m_vecBullets.size(); ++blt)
        {
            if (!m_vecBullets[blt].Active())
            {
                m_vecBullets[blt].SwitchOn(m_vPos.x);

                

                break;
            }
        }
    }

    // update any bullets which are active
    for (int blt = 0; blt < m_vecBullets.size(); ++blt)
    {
        m_vecBullets[blt].Update();
    }
}
