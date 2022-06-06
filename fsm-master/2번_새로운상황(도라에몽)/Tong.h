#ifndef OWNER_CALL_H
#define OWNER_CALL_H

#include <string>

#include "State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "TongOwnedStates.h"
#include "ConsoleUtils.h"
#include "JinGoo.h"
#include "StateMachine.h"
#include "utils.h"



class TongTong : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<TongTong>* m_pStateMachine;

	location_type   m_Location;


	bool            m_harass; //ÅüÅüÀÌ°¡ ±«·ÓÈ÷´Â »óÅÂ
	

public:

	TongTong(int id) :m_Location(PlayGround),
		m_harass(false),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<TongTong>(this);

		m_pStateMachine->SetCurrentState(Free::Instance());

		m_pStateMachine->SetGlobalState(TongTongOwnedStates::Instance());
	}

	~TongTong() { delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<TongTong>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Harassing()const { return m_harass; }
	void          SetHarassing(bool val) { m_harass = val; }



};

#endif
