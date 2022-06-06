#ifndef DOG_H
#define DOG_H

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "DogOwnStates.h"
#include "StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;


//above this value a miner is thirsty
const int Thirst_MAX = 5;
//above this value a miner is sleepy
const int Thire_MAX = 3;



//광부 클래스
class Dog : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Dog>*  m_pStateMachine; //개 상태 머신 < 탬플릿 광부 > 

	location_type         m_Location; //위치

							
	int                   m_iThirst;//배고픔, 목마름
				
	int                   m_iFatigue; //피곤함

public:

	//초기화
	Dog(int id) :m_Location(shack),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Dog>(this); //상태 머신 만듬 

		m_pStateMachine->SetCurrentState(HomeAndSleepTilRested::Instance()); //처음 상태 초기화

																			   /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Dog() { delete m_pStateMachine; } //파괴자 데이터 정리 ( delete )

										 //this must be implemented
	void Update(); //매 프레임마다 실행 

				   //so must this
	virtual bool  HandleMessage(const Telegram& msg); //메시지 체크


	StateMachine<Dog>* GetFSM()const { return m_pStateMachine; } //현재 상태 줌



																   //-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; } //위치 바꾸기

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; } //피로 감소
	void          IncreaseFatigue() { m_iFatigue += 1; } //피로 증가


	bool          Thirsty()const; //배고프냐 
	void          BuyAndDrinkAWhiskey() { m_iThirst = 0; } //밥 먹어서 배고픔 없어짐

};



#endif
