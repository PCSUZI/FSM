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
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "금광에 간다.";

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
		pMiner->ID(),        //ID of sender 광부 아이디
		ent_Owner,            //ID of recipient 사장한테 보냄
		Msg_IgoGold,   //the message 메시지 
		NO_ADDITIONAL_INFO);   //추가적인 정보 없음 

	cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "예! 사장님 출근했습니다~~!!! ^0^ !! ";


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

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "금덩이를 집는다.";

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull()) //주머니가 가득 찼을 때
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance()); //은행으로 간다
  }

  if (pMiner->Thirsty()) //목이 마를 때
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance()); //물 미시러 간다.
  }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "주머니를 가득 채웠으니 금광을 나가자 ";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_Owner_Bad: //사장한테 나쁜소리

						//메시지 받은 시간 출력 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
			<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pMiner->ID())
			<< "사장한테 나쁜 소리를 들어서 기분이 상한 밥 .. 괜히 피곤해진다. ( 피로도 +1 ) ";

		pMiner->IncreaseFatigue();

		return true;

	case Msg_Owner_Good: //사장한테 괜찮은 소리

						//메시지 받은 시간 출력 
						/*	cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
						<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pMiner->ID())
			<< "휴 아무말 없이 넘기셨군~!! ";


		return true;

	}//end switch
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

//은행 방문
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance() //싱글톤
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner) //은행 입장
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "은행에 왔다. Yes siree ~ ";

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
       << "저금 저금~!!~ 금덩이 개수 : "<< pMiner->Wealth();

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
         << "휴! 충분히 금덩이가 모였으니 나의 귀여운 아내로 돌아가자.";
      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      //집으로
  }

  //otherwise get more gold 다 모이지 않으면 금광으로
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance()); //금광
  }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner) //은행 나갈 때
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "은행을 떠난다.... ";
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg) //은행 메시지 X
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance() //집 , 집 싱클톤
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner) //집 입장
{
  if (pMiner->Location() != shack) //밥의 위치가 집이 아니면 실행
  {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "집에 도착했다. 여보 나 집에 왔어요 ! ";

    pMiner->ChangeLocation(shack);  // 위치 집으로 바꿈 

    //let the wife know I'm home 아내에게 메시지 보냄
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
                              pMiner->ID(),        //ID of sender 광부 아이디
                              ent_Elsa,            //ID of recipient 아내한테 보냄
                              Msg_HiHoneyImHome,   //the message 메시지 여보 나왔어
                              NO_ADDITIONAL_INFO);   //추가적인 정보 없음 


	//강아지한테도 메시지 보냄
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
		pMiner->ID(),        //ID of sender 광부 아이디
		ent_Dog,            //ID of recipient 아내한테 보냄
		Msg_HiHoneyImHome,   //the message 메시지
		NO_ADDITIONAL_INFO);   //추가적인 정보 없음 
  }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner) //나갈 때
{ 
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued()) //피곤함이 5보다 크면 true  ( Fatigued ) 아니면 일하러 간다.
  {
     cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " 
          << "충분한 휴식을 취했으니 다시 일하러 가야했군 ! ㅠㅅㅠ "; 

     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance()); //다시 금광으로
  }

  else 
  {
    //sleep
    pMiner->DecreaseFatigue(); //잔다. 피곤함 감소

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ...쿨쿨  ";
  } 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner) 
{ 

}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg) //밥이 집에서 받는 메세지
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady: //밥 다됐어요 메시지

	   //메시지 받은 시간 출력 
    /* cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID()) 
     << " at time: " << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pMiner->ID()) 
          << ": 그래요 밥먹으러 갈께요 !";

     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance() //목마름
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Miner* pMiner) 
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon); //장소 바뀜

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "오 ,, 목이 마르군.  술집에 가야겠어! ";
  }
}

void QuenchThirst::Execute(Miner* pMiner)
{
  pMiner->BuyAndDrinkAWhiskey(); //돈 빠져나가고 술 샀음 , 목마름 사라짐

  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "정말 좋은 술이야. 목마름이 사라졌어";

  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "( 술집을 나가면서 ) 기분이 좋아 ~!";
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance() //스튜 먹는거
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "밥 냄새가 정말 좋아요 ! ";
}

void EatStew::Execute(Miner* pMiner)
{
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "냠냠 엄청 맛있어요 ~~~";

  pMiner->GetFSM()->RevertToPreviousState(); //이전 상태로 돌아가지
}

void EatStew::Exit(Miner* pMiner)
{ 
  cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "맛있게 잘먹었어요 ! 무슨 일이든 다시 시작하는게 좋겠어.. ";
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


