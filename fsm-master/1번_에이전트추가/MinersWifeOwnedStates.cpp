#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWife.h"
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

WifesGlobalState* WifesGlobalState::Instance()
{
  static WifesGlobalState instance;

  return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife) //전역 
{
  //1 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.1) &&  ////화장실 갈 확률
       !wife->GetFSM()->isInState(*VisitBathroom::Instance()) ) //화장실 상태가 아니면
  {
    wife->GetFSM()->ChangeState(VisitBathroom::Instance()); //화장실로 가라! 
  }
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg) //전역 메시지 받는 곳
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome: //밥이 보낸 메시지 ( 여보 나 왔어 ! )
   {
      /* cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: " 
       << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(wife->ID()) << 
          ": 어서와요~ 맛있는 스튜를 만들어 줄께요 ^^ ";

     wife->GetFSM()->ChangeState(CookStew::Instance()); //요리상태로 변환

	 return true;
   }

  case Msg_IamHungry: //강아지가 보낸 메시지 배고파 
  {
	  /*cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
		  << Clock->GetCurrentTime();
*/
	    SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

	  cout << "\n" << GetNameOfEntity(wife->ID()) <<
		  ": 우리 강아지~~~ 배가 고프다구 ~~?~~? ";

	  wife->GetFSM()->ChangeState(CookPet::Instance()); //요리상태로 변환

	  return true;
  }

  return true;
 


  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouseWork 집안일

DoHouseWork* DoHouseWork::Instance()
{
  static DoHouseWork instance;

  return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": 집안일을 더 할 시간이군!";
}


void DoHouseWork::Execute(MinersWife* wife)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": 바닥을 쓴다 - ";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": 설거지를 한다 - ";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(wife->ID()) << ": 침대를 정리한다 - ";

    break;
  }
}

void DoHouseWork::Exit(MinersWife* wife)
{
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom 화장실

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{  
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": 통으로 걸어간다. 깨끗이 소변을 봐야겠구나. "; 
}


void VisitBathroom::Execute(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": 아아 ~ ! 시원하다!";

  wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ":화장실에서 나온다.";
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------CookStew 요리

CookStew* CookStew::Instance()
{
  static CookStew instance;

  return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
  //if not already cooking put the stew in the oven
  if (!wife->Cooking()) //요리중이 아니라면
  {
    cout << "\n" << GetNameOfEntity(wife->ID()) << ": 스튜를 오븐에 넣는다. ";
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    Dispatch->DispatchMessage(1.5,                  //time delay 대기 시간
                              wife->ID(),           //sender ID 자신이
                              wife->ID(),           //receiver ID  자신한테
                              Msg_StewReady,        //msg 스튜 다 됐다
                              NO_ADDITIONAL_INFO); 

    wife->SetCooking(true); //요리중 true
  }
}


void CookStew::Execute(MinersWife* wife)
{
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": 저녁밥을 차려 놓고 안달복달한다.";
}

void CookStew::Exit(MinersWife* wife)
{
  SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(wife->ID()) << ": 식탁 위에 국을 올려 놓는다.";
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
 // SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_StewReady:
    {
     /* cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
           " at time: " << Clock->GetCurrentTime();*/

      SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(wife->ID()) << ": 국이 준비됐군요! 듭시다.";

      //let hubby know the stew is ready
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                wife->ID(), //와이프가
                                ent_Miner_Bob, //밥한테
                                Msg_StewReady, //밥 다 됐어~~
                                NO_ADDITIONAL_INFO);

      wife->SetCooking(false); //요리 끄기

      wife->GetFSM()->ChangeState(DoHouseWork::Instance());               
    }

    return true;

  }//end switch

  return false;
}



//---------------------------------------------------------- 강아지 사료 주기 
CookPet* CookPet::Instance()
{
	static CookPet instance;

	return &instance;
}


void CookPet::Enter(MinersWife* wife)
{
	//if not already cooking put the stew in the oven
	if (!wife->Dog_Cooking()) //요리중이 아니라면
	{
		cout << "\n" << GetNameOfEntity(wife->ID()) << ": 사료를 찾는다 . ";

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		Dispatch->DispatchMessage(1.0,                  //time delay 대기 시간
			wife->ID(),           //sender ID 자신이
			wife->ID(),           //receiver ID  자신한테
			Msg_StewReady,        //msg 스튜 다 됐다
			NO_ADDITIONAL_INFO);

		wife->Dog_SetCooking(true); //요리중 true
	}
}


void CookPet::Execute(MinersWife* wife)
{
	cout << "\n" << GetNameOfEntity(wife->ID()) << ": 사료 붓는중 ...........";
}

void CookPet::Exit(MinersWife* wife)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(wife->ID()) << ": 멍멍아~~~~~  ( 강아지에게 사료를 준다.) ";
}


bool CookPet::OnMessage(MinersWife* wife, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StewReady:
	{
		/*cout << "\nMessage received by " << GetNameOfEntity(wife->ID()) <<
			" at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "\n" << GetNameOfEntity(wife->ID()) << ": 맛있게 먹으렴~~.";

		//let hubby know the stew is ready
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			wife->ID(), //와이프가
			ent_Dog, //개한테
			Msg_PetReady, //밥 다 됐어~~
			NO_ADDITIONAL_INFO);

		wife->Dog_SetCooking(false); //요리 끄기

		wife->GetFSM()->ChangeState(DoHouseWork::Instance());
	}

	return true;

	}//end switch

	return false;
}