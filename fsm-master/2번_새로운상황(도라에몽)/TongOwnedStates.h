#ifndef TONG_TONG_STATES_H
#define TONG_TONG_STATES_H

#include "State.h"

class TongTong;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class TongTongOwnedStates : public State<TongTong> //���� ����
{
private:

	TongTongOwnedStates() {}

	//copy ctor and assignment should be private
	TongTongOwnedStates(const TongTongOwnedStates&);
	TongTongOwnedStates& operator=(const TongTongOwnedStates&);

public:

	//this is a singleton
	static TongTongOwnedStates* Instance();

	virtual void Enter(TongTong* tongtong) {}

	virtual void Execute(TongTong* tongtong);

	virtual void Exit(TongTong* tongtong) {}

	virtual bool OnMessage(TongTong* tongtong, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Harass_JinGoo : public State<TongTong> //���� ��������
{
private:

	Harass_JinGoo() {}

	//copy ctor and assignment should be private
	Harass_JinGoo(const Harass_JinGoo&);
	Harass_JinGoo& operator=(const Harass_JinGoo&);

public:

	//this is a singleton
	static Harass_JinGoo* Instance();

	virtual void Enter(TongTong* tongtong);

	virtual void Execute(TongTong* tongtong);

	virtual void Exit(TongTong* tongtong);

	virtual bool OnMessage(TongTong* tongtong, const Telegram& msg);

};


//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�

class Free : public State<TongTong> //���Ϳ��� ���
{
private:

	Free() {}

	//copy ctor and assignment should be private
	Free(const Free&);
	Free& operator=(const Free&);

public:

	//this is a singleton
	static Free* Instance();

	virtual void Enter(TongTong* tongtong);

	virtual void Execute(TongTong* tongtong);

	virtual void Exit(TongTong* tongtong);

	virtual bool OnMessage(TongTong* tongtong, const Telegram& msg);

};




#endif