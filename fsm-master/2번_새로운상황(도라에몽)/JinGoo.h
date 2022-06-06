#ifndef JinGoo_H
#define JinGoo_H
//------------------------------------------------------------------------
//
//  Name:   JinGoo.h
//
//  Desc:   A class defining a goldJinGoo.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "JinGooOwnedStates.h"
#include "StateMachine.h"
#include "utils.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of gold a JinGoo must have before he feels he can go home
const int MaxStress       = 5;
const int MaxBoring		  = 3;



//광부 클래스
class JinGoo : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<JinGoo>*  m_pStateMachine; 
  
  location_type         m_Location; //위치


  int                   m_stress; //진구 스트레스
  int					m_boaring;

public:

	//초기화
  JinGoo(int id):m_Location(JinGooHouse),
	  m_stress(0),
	  m_revenge(false),
	  m_boaring(0),
	  BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<JinGoo>(this); //상태 머신 만듬 
    
    m_pStateMachine->SetCurrentState(GoJinGooHouse::Instance()); //처음 상태 초기화


  }

  ~JinGoo(){delete m_pStateMachine;} //파괴자 데이터 정리 ( delete )

  //this must be implemented
  void Update(); //매 프레임마다 실행 

  //so must this
  virtual bool  HandleMessage(const Telegram& msg); //메시지 체크

  
  StateMachine<JinGoo>* GetFSM()const{return m_pStateMachine;} //현재 상태 줌


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  //진구 복수 상태
  bool					m_revenge; 
  //진구 스트레스
  bool          StressOver()const;
  void          DecreaseFatigue() { m_stress -= 1; }
  void          IncreaseFatigue() { m_stress += 1; }


  bool          BoringOver()const;
  void          DecreaseBoring() { m_boaring = 0; }
  void          IncreaseBoring() { m_boaring += 1; }

};



#endif
