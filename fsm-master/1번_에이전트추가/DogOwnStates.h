#ifndef DOG_OWNED_STATES_H
#define DOG_OWNED_STATES_H

#include "State.h"


class Dog;
struct Telegram;



class HomeAndSleepTilRested : public State<Dog>
{
private:

	HomeAndSleepTilRested() {}

	//copy ctor and assignment should be private
	HomeAndSleepTilRested(const HomeAndSleepTilRested&);
	HomeAndSleepTilRested& operator=(const HomeAndSleepTilRested&);

public:

	//this is a singleton
	static HomeAndSleepTilRested* Instance();

	virtual void Enter(Dog* dog);

	virtual void Execute(Dog* dog);

	virtual void Exit(Dog* dog);

	virtual bool OnMessage(Dog* agent, const Telegram& msg);
};


class QuenchHungry : public State<Dog>
{
private:

	QuenchHungry() {}

	//copy ctor and assignment should be private
	QuenchHungry(const QuenchHungry&);
	QuenchHungry& operator=(const QuenchHungry&);

public:

	//this is a singleton
	static QuenchHungry* Instance();

	virtual void Enter(Dog* dog);

	virtual void Execute(Dog* dog);

	virtual void Exit(Dog* dog);

	virtual bool OnMessage(Dog* agent, const Telegram& msg);
};



class Eat : public State<Dog>
{
private:

	Eat() {}

	//copy ctor and assignment should be private
	Eat(const Eat&);
	Eat& operator=(const Eat&);

public:

	//this is a singleton
	static Eat* Instance();

	virtual void Enter(Dog* dog);

	virtual void Execute(Dog* dog);

	virtual void Exit(Dog* dog);

	virtual bool OnMessage(Dog* agent, const Telegram& msg);
};




#endif