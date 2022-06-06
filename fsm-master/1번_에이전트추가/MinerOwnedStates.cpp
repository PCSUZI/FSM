#include "MinerOwnedStates.h"
#include "State.h"
#include "Miner.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
  if (pMiner->Location() != goldmine)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "�ݱ��� ����.";

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
		pMiner->ID(),        //ID of sender ���� ���̵�
		ent_Owner,            //ID of recipient �������� ����
		Msg_IgoGold,   //the message �޽��� 
		NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 

	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "��! ����� ����߽��ϴ�~~!!! ^0^ !! ";


    pMiner->ChangeLocation(goldmine);
  }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "�ݵ��̸� ���´�.";

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull()) //�ָӴϰ� ���� á�� ��
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance()); //�������� ����
  }

  if (pMiner->Thirsty()) //���� ���� ��
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance()); //�� �̽÷� ����.
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "�ָӴϸ� ���� ä������ �ݱ��� ������ ";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_Owner_Bad: //�������� ���ۼҸ�

						//�޽��� ���� �ð� ��� 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
			<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pMiner->ID())
			<< "�������� ���� �Ҹ��� �� ����� ���� �� .. ���� �ǰ�������. ( �Ƿε� +1 ) ";

		pMiner->IncreaseFatigue();

		return true;

	case Msg_Owner_Good: //�������� ������ �Ҹ�

						//�޽��� ���� �ð� ��� 
						/*	cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
						<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pMiner->ID())
			<< "�� �ƹ��� ���� �ѱ�̱�~!! ";


		return true;

	}//end switch
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

//���� �湮
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance() //�̱���
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner) //���� ����
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "���࿡ �Դ�. Yes siree ~ ";

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "���� ����~!!~ �ݵ��� ���� : "<< pMiner->Wealth();

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
         << "��! ����� �ݵ��̰� ������ ���� �Ϳ��� �Ƴ��� ���ư���.";
      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      //������
  }

  //otherwise get more gold �� ������ ������ �ݱ�����
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance()); //�ݱ�
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner) //���� ���� ��
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "������ ������.... ";
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg) //���� �޽��� X
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance() //�� , �� ��Ŭ��
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner) //�� ����
{
  if (pMiner->Location() != shack) //���� ��ġ�� ���� �ƴϸ� ����
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "���� �����ߴ�. ���� �� ���� �Ծ�� ! ";

    pMiner->ChangeLocation(shack);  // ��ġ ������ �ٲ� 

    //let the wife know I'm home �Ƴ����� �޽��� ����
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
                              pMiner->ID(),        //ID of sender ���� ���̵�
                              ent_Elsa,            //ID of recipient �Ƴ����� ����
                              Msg_HiHoneyImHome,   //the message �޽��� ���� ���Ծ�
                              NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 


	//���������׵� �޽��� ����
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay ������ Ÿ�� 0 
		pMiner->ID(),        //ID of sender ���� ���̵�
		ent_Dog,            //ID of recipient �Ƴ����� ����
		Msg_HiHoneyImHome,   //the message �޽���
		NO_ADDITIONAL_INFO);   //�߰����� ���� ���� 
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner) //���� ��
{ 
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued()) //�ǰ����� 5���� ũ�� true  ( Fatigued ) �ƴϸ� ���Ϸ� ����.
  {
     cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
          << "����� �޽��� �������� �ٽ� ���Ϸ� �����߱� ! �Ф��� "; 

     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance()); //�ٽ� �ݱ�����
  }

  else 
  {
    //sleep
    pMiner->DecreaseFatigue(); //�ܴ�. �ǰ��� ����

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ...����  ";
  } 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner) 
{ 

}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg) //���� ������ �޴� �޼���
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady: //�� �ٵƾ�� �޽���

	   //�޽��� ���� �ð� ��� 
    /* cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) 
     << " at time: " << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pMiner->ID()) 
          << ": �׷��� ������� ������ !";

     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance() //�񸶸�
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner) 
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon); //��� �ٲ�

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "�� ,, ���� ������.  ������ ���߰ھ�! ";
  }
}

void QuenchThirst::Execute(Miner* pMiner)
{
  pMiner->BuyAndDrinkAWhiskey(); //�� ���������� �� ���� , �񸶸� �����

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "���� ���� ���̾�. �񸶸��� �������";

  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "( ������ �����鼭 ) ����� ���� ~!";
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance() //��Ʃ �Դ°�
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "�� ������ ���� ���ƿ� ! ";
}

void EatStew::Execute(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "�ȳ� ��û ���־�� ~~~";

  pMiner->GetFSM()->RevertToPreviousState(); //���� ���·� ���ư���
}

void EatStew::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "���ְ� �߸Ծ���� ! ���� ���̵� �ٽ� �����ϴ°� ���ھ�.. ";
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


