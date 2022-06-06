#include "DoraemonOwnedStates.h"
#include "JinGooOwnedStates.h"
#include "Doraemon.h"
#include "Locations.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

DoraemonGlobalState* DoraemonGlobalState::Instance()
{
  static DoraemonGlobalState instance;

  return &instance;
}


void DoraemonGlobalState::Execute(Doraemon* dora) //전역 
{

  if ( (RandFloat() < 0.1) &&  ////도라에몽 화장실 갈 확률
       !dora->GetFSM()->isInState(*VisitBathroom::Instance()) ) //화장실 상태가 아니면
  {
    dora->GetFSM()->ChangeState(VisitBathroom::Instance()); //화장실로 가라! 
  }
}

bool DoraemonGlobalState::OnMessage(Doraemon* dora, const Telegram& msg) //전역 메시지 받는 곳
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_Dora_I_helpMe: //도라에몽 도와줘!!
   {
      /* cout << "\nMessage handled by " << GetNameOfEntity(dora->ID()) << " at time: " 
       << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(dora->ID()) << 
          ": 또 퉁퉁이가 괴롭혔어?! 기다려 쓸만한 도구를 찾아볼께 ";

     dora->GetFSM()->ChangeState(GiveItem::Instance()); //주머니 뒤적

	 return true;
   }
 

  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouse 도라에몽은 집에만 있음

DoHouse* DoHouse::Instance()
{
  static DoHouse instance;

  return &instance;
}


void DoHouse::Enter(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": 나만의 시간이군 !";
}


void DoHouse::Execute(Doraemon* dora)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": 팥빵을 먹는다. ";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": 만화책을 본다. ";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(dora->ID()) << ": 나비와 논다. ";

    break;
  }
}

void DoHouse::Exit(Doraemon* dora)
{
}

bool DoHouse::OnMessage(Doraemon* dora, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom 화장실

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(Doraemon* dora)
{  
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": 윽.. 계속 있었더니 화장실이... "; 
}


void VisitBathroom::Execute(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ": 아아 ~ ! 시원하다!";

  dora->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ":화장실에서 나온다.";
}


bool VisitBathroom::OnMessage(Doraemon* dora, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------GiveItem 요리

GiveItem* GiveItem::Instance()
{
  static GiveItem instance;

  return &instance;
}


void GiveItem::Enter(Doraemon* dora)
{
  //if not already cooking put the stew in the oven
  if (!dora->Cooking()) //요리중이 아니라면
  {
    cout << "\n" << GetNameOfEntity(dora->ID()) << ": 주머니에 손을 넣는다 . ";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay 대기 시간
                              dora->ID(),           //sender ID 자신이
                              dora->ID(),           //receiver ID  자신한테
                              Msg_Dora_GiveItem,        //msg 도구 찾았다.
                              NO_ADDITIONAL_INFO); 

    dora->SetCooking(true); // 물건 찾는중 
  }
}


void GiveItem::Execute(Doraemon* dora)
{
  cout << "\n" << GetNameOfEntity(dora->ID()) << ":뭐가 좋을까 ... 이것도 아니고 이것도 아니고 .... ( 뒤적 뒤적 )";
}

void GiveItem::Exit(Doraemon* dora)
{
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
}


bool GiveItem::OnMessage(Doraemon* dora, const Telegram& msg)
{
 // SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_Dora_GiveItem:
    {
     /* cout << "\nMessage received by " << GetNameOfEntity(dora->ID()) <<
           " at time: " << Clock->GetCurrentTime();*/

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(dora->ID()) << ": 자 이걸로 ! 퉁퉁이를 혼내주고 와!! ";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                dora->ID(), //도라에몽이
                                ent_JinGoo, //진구한테
		                        Msg_Dora_GiveItem, //물건 줌
                                NO_ADDITIONAL_INFO);

      dora->SetCooking(false); //뮬곤 뒤지기 끄기

      dora->GetFSM()->ChangeState(DoHouse::Instance());               
    }

    return true;

  }//end switch

  return false;
}

