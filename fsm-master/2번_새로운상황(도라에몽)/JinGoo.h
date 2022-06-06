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



//���� Ŭ����
class JinGoo : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<JinGoo>*  m_pStateMachine; 
  
  location_type         m_Location; //��ġ


  int                   m_stress; //���� ��Ʈ����
  int					m_boaring;

public:

	//�ʱ�ȭ
  JinGoo(int id):m_Location(JinGooHouse),
	  m_stress(0),
	  m_revenge(false),
	  m_boaring(0),
	  BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<JinGoo>(this); //���� �ӽ� ���� 
    
    m_pStateMachine->SetCurrentState(GoJinGooHouse::Instance()); //ó�� ���� �ʱ�ȭ


  }

  ~JinGoo(){delete m_pStateMachine;} //�ı��� ������ ���� ( delete )

  //this must be implemented
  void Update(); //�� �����Ӹ��� ���� 

  //so must this
  virtual bool  HandleMessage(const Telegram& msg); //�޽��� üũ

  
  StateMachine<JinGoo>* GetFSM()const{return m_pStateMachine;} //���� ���� ��


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  //���� ���� ����
  bool					m_revenge; 
  //���� ��Ʈ����
  bool          StressOver()const;
  void          DecreaseFatigue() { m_stress -= 1; }
  void          IncreaseFatigue() { m_stress += 1; }


  bool          BoringOver()const;
  void          DecreaseBoring() { m_boaring = 0; }
  void          IncreaseBoring() { m_boaring += 1; }

};



#endif
