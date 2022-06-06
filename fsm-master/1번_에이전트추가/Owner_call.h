#ifndef OWNER_CALL_H
#define OWNER_CALL_H

#include <string>

#include "State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "OwnerOwnedStates.h"
#include "ConsoleUtils.h"
#include "Miner.h"
#include "StateMachine.h"
#include "utils.h"



class Owner_call : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Owner_call>* m_pStateMachine;

	location_type   m_Location;


	bool            m_bCalling;
	

public:

	Owner_call(int id) :m_Location(shack),
		m_bCalling(false),
		BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Owner_call>(this);

		m_pStateMachine->SetCurrentState(Free::Instance());

		m_pStateMachine->SetGlobalState(OwnerOwnedStates::Instance());
	}

	~Owner_call() { delete m_pStateMachine; }


	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Owner_call>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Calling()const { return m_bCalling; }
	void          SetCalling(bool val) { m_bCalling = val; }



};

#endif
