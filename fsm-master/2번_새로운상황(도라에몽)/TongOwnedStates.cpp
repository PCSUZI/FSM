#include "TongOwnedStates.h"
#include "JinGooOwnedStates.h"
#include "Tong.h"
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

TongTongOwnedStates* TongTongOwnedStates::Instance()
{
	static TongTongOwnedStates instance;

	return &instance;
}


void TongTongOwnedStates::Execute(TongTong* tongtong) //전역 
{


}

bool TongTongOwnedStates::OnMessage(TongTong* tongtong, const Telegram& msg) //전역 메시지 받는 곳
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_IgoPlayGround: //진구가 공터에 왔다
	{
	
			SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(tongtong->ID()) <<
				": 노진구 주제에 이 몸이 있는 공터로 와??? ";

			if (!tongtong->Harassing())
			{
				tongtong->GetFSM()->ChangeState(Harass_JinGoo::Instance()); //진구랑 접촉
				tongtong->SetHarassing(true);
			}

			return true;

	}


	}//end switch

	return false;
}


Harass_JinGoo* Harass_JinGoo::Instance()
{
	static Harass_JinGoo instance;

	return &instance;
}


void Harass_JinGoo::Enter(TongTong* tongtong)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	
}


void Harass_JinGoo::Execute(TongTong* tongtong)
{


	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	if (tongtong->Harassing())
	{
		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": " << "  야 노진구 너 여기가 어디라고 와??? 퍽 - 퍽---- 퍼퍼퍼퍼퍼ㅓ퍼퍼퍼퍼퍽  ";


		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
			tongtong->ID(),        //ID of sender 오너 아이디
			ent_JinGoo,            //ID of recipient 밥에게
			Msg_Tong_FuckYou,   //the message 잔소리 메시지
			NO_ADDITIONAL_INFO);   //추가적인 정보 없음 

	
	}


	tongtong->GetFSM()->ChangeState(Free::Instance());
}

void Harass_JinGoo::Exit(TongTong* tongtong)
{


}

bool Harass_JinGoo::OnMessage(TongTong* tongtong, const Telegram& msg)
{


	return false;
}


//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 딩가 딩가 거리기 

Free* Free::Instance()
{
	static Free instance;

	return &instance;
}


void Free::Enter(TongTong* tongtong)
{


}


void Free::Execute(TongTong* tongtong)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( 공터에서 ) 나는야 퉁퉁이~~ 골목 대장이라네 ~~~ ";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( 공터에서 ) 어이~~~! 비실이 공 받아라~~~. ";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(tongtong->ID()) << ": ( 공터에서 ) 아~~~ 심심해 노진구 괴롭히고 싶다~ ";

		break;
	}
}

void Free::Exit(TongTong* tongtong)
{
}

bool Free::OnMessage(TongTong* tongtong, const Telegram& msg)
{
	//SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_jinGoo_revenge:
	{

		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);


		if (tongtong->Harassing())
		{

			cout << "\n" << GetNameOfEntity(tongtong->ID()) <<
				": 으아아아악 --- 노진구 이상한 도구로 날 괴롭히네 다음에 보자 !!!!!!!!!!!!! ";

			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
				tongtong->ID(),        //ID of sender 오너 아이디
				ent_JinGoo,            //ID of recipient 밥에게
				Msg_Tong_OhhNo,   //the message 잔소리 메시지
				NO_ADDITIONAL_INFO);   //추가적인 정보 없음 


			tongtong->SetHarassing(false);
			tongtong->GetFSM()->RevertToPreviousState();
		}

		return true;

	}


	}//end switch

	return false;
	return false;
}
