#ifndef JinGoo_OWNED_STATES_H
#define JinGoo_OWNED_STATES_H
//------------------------------------------------------------------------
//------------------------------------------------------------------------
#include "State.h"


class JinGoo;
struct Telegram;





//------------------------------------------------------------------------
class EnterPlayGround : public State<JinGoo> //���� ����
{
private:
  
  EnterPlayGround(){}

  //copy ctor and assignment should be private
  EnterPlayGround(const EnterPlayGround&);
  EnterPlayGround& operator=(const EnterPlayGround&);
 
public:

  //this is a singleton
  static EnterPlayGround* Instance(); //�̱���

  virtual void Enter(JinGoo* JinGoo); //����

  virtual void Execute(JinGoo* JinGoo); //�����Ҷ�

  virtual void Exit(JinGoo* JinGoo); //���� ��

  virtual bool OnMessage(JinGoo* agent, const Telegram& msg); //�޽���

};


//------------------------------------------------------------------------

//------------------------------------------------------------------------
class GoJinGooHouse : public State<JinGoo> //���� �� 
{
private:
  
  GoJinGooHouse(){}

  //copy ctor and assignment should be private
  GoJinGooHouse(const GoJinGooHouse&);
  GoJinGooHouse& operator=(const GoJinGooHouse&);
 
public:

  //this is a singleton
  static GoJinGooHouse* Instance();

  virtual void Enter(JinGoo* JinGoo);

  virtual void Execute(JinGoo* JinGoo);

  virtual void Exit(JinGoo* JinGoo);

  virtual bool OnMessage(JinGoo* agent, const Telegram& msg);
};


//------------------------------------------------------------------------

class CallEsul : public State<JinGoo> //�̽��̶� ��ȭ
{
private:
  
  CallEsul(){}

  //copy ctor and assignment should be private
  CallEsul(const CallEsul&);
  CallEsul& operator=(const CallEsul&);
 
public:

  //this is a singleton
  static CallEsul* Instance();

  virtual void Enter(JinGoo* JinGoo);

  virtual void Execute(JinGoo* JinGoo);

  virtual void Exit(JinGoo* JinGoo);

  virtual bool OnMessage(JinGoo* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The JinGoo eats the stew, gives
//  dora some compliments and then returns to his previous state
//------------------------------------------------------------------------
class GetItem : public State<JinGoo> //���󿡸����� ���� ����
{
private:
  
  GetItem(){}

  //copy ctor and assignment should be private
  GetItem(const GetItem&);
  GetItem& operator=(const GetItem&);
 
public:

  //this is a singleton
  static GetItem* Instance();

  virtual void Enter(JinGoo* JinGoo);

  virtual void Execute(JinGoo* JinGoo);

  virtual void Exit(JinGoo* JinGoo);

  virtual bool OnMessage(JinGoo* agent, const Telegram& msg);
};




#endif