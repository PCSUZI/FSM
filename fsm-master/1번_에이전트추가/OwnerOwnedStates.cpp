#include "OwnerOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Owner_call.h"
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

OwnerOwnedStates* OwnerOwnedStates::Instance()
{
	static OwnerOwnedStates instance;

	return &instance;
}


void OwnerOwnedStates::Execute(Owner_call* owner) //전역 
{


}

bool OwnerOwnedStates::OnMessage(Owner_call* owner, const Telegram& msg) //전역 메시지 받는 곳
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_IgoGold: //사장님 저 출근 했습니다.
	{
		/* cout << "\nMessage handled by " << GetNameOfEntity(wife->ID()) << " at time: "
		<< Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(owner->ID()) <<
			": 여보세요 강사장입니다. ";

		owner->GetFSM()->ChangeState(Call_Bob::Instance()); //전화상태로 변환

		return true;
	}



	}//end switch

	return false;
}


Call_Bob* Call_Bob::Instance()
{
	static Call_Bob instance;

	return &instance;
}


void Call_Bob::Enter(Owner_call* owner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(owner->ID()) << ": 여어 밥  - 자네인가 ";
	owner->SetCalling(true);
	
}


void Call_Bob::Execute(Owner_call* owner)
{


	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);


	if (owner->Calling())
	{
		if ((RandFloat() < 0.5))
		{
			cout << "\n" << GetNameOfEntity(owner->ID()) << ": " << "  너 계속 금덩어리만 파고 ~~!~!~!@#$#&*@^$*#  ( 나쁜말 나쁜말 )  ";

			//dog->ChangeLocation(shack);  // 위치 집으로 바꿈 

			//let the wife know I'm home 밥에게
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
				owner->ID(),        //ID of sender 오너 아이디
				ent_Miner_Bob,            //ID of recipient 밥에게
				Msg_Owner_Bad,   //the message 잔소리 메시지
				NO_ADDITIONAL_INFO);   //추가적인 정보 없음 
		}
		else
		{
			cout << "\n" << GetNameOfEntity(owner->ID()) << ": " << "  어어~~ 일 그대로 열심히 해~~! ( 좋은말 )  ";

			//dog->ChangeLocation(shack);  // 위치 집으로 바꿈 

			//let the wife know I'm home 밥에게
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
				owner->ID(),        //ID of sender 오너 아이디
				ent_Miner_Bob,            //ID of recipient 밥에게
				Msg_Owner_Good,   //the message 잔소리 메시지
				NO_ADDITIONAL_INFO);   //추가적인 정보 없음 
		}

		owner->SetCalling(false);

	}



	owner->GetFSM()->RevertToPreviousState();
}

void Call_Bob::Exit(Owner_call* owner)
{
}

bool Call_Bob::OnMessage(Owner_call* owner, const Telegram& msg)
{
	return false;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 딩가 딩가 거리기 

Free* Free::Instance()
{
	static Free instance;

	return &instance;
}


void Free::Enter(Owner_call* owner)
{


}


void Free::Execute(Owner_call* owner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(owner->ID()) << ": 딩가 - 딩가 - 둠칫 둠칫  ";
}

void Free::Exit(Owner_call* owner)
{
}

bool Free::OnMessage(Owner_call* owner, const Telegram& msg)
{
	return false;
}
