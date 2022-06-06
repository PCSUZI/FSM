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



//���� Ŭ����
class Dog : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Dog>*  m_pStateMachine; //�� ���� �ӽ� < ���ø� ���� > 

	location_type         m_Location; //��ġ

							
	int                   m_iThirst;//�����, �񸶸�
				
	int                   m_iFatigue; //�ǰ���

public:

	//�ʱ�ȭ
	Dog(int id) :m_Location(shack),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)

	{
		//set up state machine
		m_pStateMachine = new StateMachine<Dog>(this); //���� �ӽ� ���� 

		m_pStateMachine->SetCurrentState(HomeAndSleepTilRested::Instance()); //ó�� ���� �ʱ�ȭ

																			   /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Dog() { delete m_pStateMachine; } //�ı��� ������ ���� ( delete )

										 //this must be implemented
	void Update(); //�� �����Ӹ��� ���� 

				   //so must this
	virtual bool  HandleMessage(const Telegram& msg); //�޽��� üũ


	StateMachine<Dog>* GetFSM()const { return m_pStateMachine; } //���� ���� ��



																   //-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; } //��ġ �ٲٱ�

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; } //�Ƿ� ����
	void          IncreaseFatigue() { m_iFatigue += 1; } //�Ƿ� ����


	bool          Thirsty()const; //������� 
	void          BuyAndDrinkAWhiskey() { m_iThirst = 0; } //�� �Ծ ����� ������

};



#endif
