#ifndef DORAEMON_OWNED_STATES_H
#define DORAEMON_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   JinGoosWifeOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Doraemon class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "State.h"

class Doraemon;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoraemonGlobalState : public State<Doraemon> //도라에몽 화장실
{  
private:
  
  DoraemonGlobalState(){}

  //copy ctor and assignment should be private
  DoraemonGlobalState(const DoraemonGlobalState&);
  DoraemonGlobalState& operator=(const DoraemonGlobalState&);
 
public:

  //this is a singleton
  static DoraemonGlobalState* Instance();
  
  virtual void Enter(Doraemon* dora){}

  virtual void Execute(Doraemon* dora);

  virtual void Exit(Doraemon* dora){}

  virtual bool OnMessage(Doraemon* dora, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouse : public State<Doraemon> //도라에몽 집에서 놀기
{
private:

  DoHouse(){}
  
  //copy ctor and assignment should be private
  DoHouse(const DoHouse&);
  DoHouse& operator=(const DoHouse&);

public:

  //this is a singleton
  static DoHouse* Instance();
  
  virtual void Enter(Doraemon* dora);

  virtual void Execute(Doraemon* dora);

  virtual void Exit(Doraemon* dora);
  
  virtual bool OnMessage(Doraemon* dora, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public State<Doraemon> //화장실
{
private:
  
  VisitBathroom(){}

  //copy ctor and assignment should be private
  VisitBathroom(const VisitBathroom&);
  VisitBathroom& operator=(const VisitBathroom&);
 
public:

  //this is a singleton
  static VisitBathroom* Instance();
  
  virtual void Enter(Doraemon* dora);

  virtual void Execute(Doraemon* dora);

  virtual void Exit(Doraemon* dora);

  virtual bool OnMessage(Doraemon* dora, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GiveItem : public State<Doraemon> //도구 꺼내주기
{
private:
  
  GiveItem(){}

  //copy ctor and assignment should be private
  GiveItem(const GiveItem&);
  GiveItem& operator=(const GiveItem&);
 
public:

  //this is a singleton
  static GiveItem* Instance();
  
  virtual void Enter(Doraemon* dora);

  virtual void Execute(Doraemon* dora);

  virtual void Exit(Doraemon* dora);

  virtual bool OnMessage(Doraemon* dora, const Telegram& msg);
};




#endif