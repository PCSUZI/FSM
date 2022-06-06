#ifndef DORAEMON_H
#define DORAEMON_H
//------------------------------------------------------------------------
//
//  Name: Doraemon.h
//
//  Desc: class to implement JinGoo jingoo's dora.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DoraemonOwnedStates.h"
#include "ConsoleUtils.h"
#include "JinGoo.h"
#include "StateMachine.h"
#include "utils.h"



class Doraemon : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Doraemon>* m_pStateMachine;

  location_type   m_Location;

  //is she presently cooking?
  bool            m_Give_ing;

public:

  Doraemon(int id):m_Location(JinGooHouse),
				    m_Give_ing(false),
                     BaseGameEntity(id)
                                        
  {
    //set up the state machine
    m_pStateMachine = new StateMachine<Doraemon>(this);

    m_pStateMachine->SetCurrentState(DoHouse::Instance());

    m_pStateMachine->SetGlobalState(DoraemonGlobalState::Instance());
  }

  ~Doraemon(){delete m_pStateMachine;}


  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<Doraemon>* GetFSM()const{return m_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}

  bool          Cooking()const{return m_Give_ing;}
  void          SetCooking(bool val){ m_Give_ing = val;}

   
};

#endif
