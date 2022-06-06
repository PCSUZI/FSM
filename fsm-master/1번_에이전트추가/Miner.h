#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
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
#include "MinerOwnedStates.h"
#include "StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of gold a miner must have before he feels he can go home
const int ComfortLevel       = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets         = 3;
//above this value a miner is thirsty
const int ThirstLevel        = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;



//광부 클래스
class Miner : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Miner>*  m_pStateMachine; //광부 상태 머신 < 탬플릿 광부 > 
  
  location_type         m_Location; //위치

  //how many nuggets the miner has in his pockets
  int                   m_iGoldCarried; //금

  int                   m_iMoneyInBank;//은행 돈

  //the higher the value, the thirstier the miner
  int                   m_iThirst;//목마름

  //the higher the value, the more tired the miner
  int                   m_iFatigue; //피곤함

public:

	//초기화
  Miner(int id):m_Location(shack),
                          m_iGoldCarried(0),
                          m_iMoneyInBank(0),
                          m_iThirst(0),
                          m_iFatigue(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Miner>(this); //상태 머신 만듬 
    
    m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance()); //처음 상태 초기화

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  }

  ~Miner(){delete m_pStateMachine;} //파괴자 데이터 정리 ( delete )

  //this must be implemented
  void Update(); //매 프레임마다 실행 

  //so must this
  virtual bool  HandleMessage(const Telegram& msg); //메시지 체크

  
  StateMachine<Miner>* GetFSM()const{return m_pStateMachine;} //현재 상태 줌


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(int val){m_iGoldCarried = val;}
  void          AddToGoldCarried(int val);
  bool          PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  int           Wealth()const{return m_iMoneyInBank;}
  void          SetWealth(int val){m_iMoneyInBank = val;}
  void          AddToWealth(int val);

  bool          Thirsty()const; 
  void          BuyAndDrinkAWhiskey(){m_iThirst = 0; m_iMoneyInBank-=2;}

};



#endif
