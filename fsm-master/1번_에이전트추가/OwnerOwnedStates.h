#ifndef OWNER_OWNED_STATES_H
#define OWNER_OWNED_STATES_H

#include "State.h"

class Owner_call;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class OwnerOwnedStates : public State<Owner_call> //전역 상태
{
private:

	OwnerOwnedStates() {}

	//copy ctor and assignment should be private
	OwnerOwnedStates(const OwnerOwnedStates&);
	OwnerOwnedStates& operator=(const OwnerOwnedStates&);

public:

	//this is a singleton
	static OwnerOwnedStates* Instance();

	virtual void Enter(Owner_call* owner) {}

	virtual void Execute(Owner_call* owner);

	virtual void Exit(Owner_call* owner) {}

	virtual bool OnMessage(Owner_call* owner, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Call_Bob : public State<Owner_call> //전화받기
{
private:

	Call_Bob() {}

	//copy ctor and assignment should be private
	Call_Bob(const Call_Bob&);
	Call_Bob& operator=(const Call_Bob&);

public:

	//this is a singleton
	static Call_Bob* Instance();

	virtual void Enter(Owner_call* owner);

	virtual void Execute(Owner_call* owner);

	virtual void Exit(Owner_call* owner);

	virtual bool OnMessage(Owner_call* owner, const Telegram& msg);

};


//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

class Free : public State<Owner_call> //딩가딩가 거리기
{
private:

	Free() {}

	//copy ctor and assignment should be private
	Free(const Free&);
	Free& operator=(const Free&);

public:

	//this is a singleton
	static Free* Instance();

	virtual void Enter(Owner_call* owner);

	virtual void Execute(Owner_call* owner);

	virtual void Exit(Owner_call* owner);

	virtual bool OnMessage(Owner_call* owner, const Telegram& msg);

};




#endif