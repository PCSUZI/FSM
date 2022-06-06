#include "JinGooOwnedStates.h"
#include "State.h"
#include "JinGoo.h"
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


//------------------------------------------------------------------------methods for EnterPlayGround
EnterPlayGround* EnterPlayGround::Instance()
{
  static EnterPlayGround instance;

  return &instance;
}


void EnterPlayGround::Enter(JinGoo* pJinGoo)
{
  if (pJinGoo->Location() != PlayGround) //공터가 아니라면
  {
    cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "공터에 왔다.";


	if (!pJinGoo->m_revenge) 
	{
		//퉁퉁이한테 메시지 보냄 
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
			pJinGoo->ID(),
			ent_TongTong,
			Msg_IgoPlayGround,   //the message 메시지 
			NO_ADDITIONAL_INFO);   //추가적인 정보 없음 
	}

	pJinGoo->DecreaseBoring(); //지루함 초기화
    pJinGoo->ChangeLocation(PlayGround); //공터로
  }
}


void EnterPlayGround::Execute(JinGoo* pJinGoo)
{  

	if (pJinGoo->m_revenge) //복수
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " 야!!!!!!! 퉁퉁이 !!!!!!!!!!!!!!!! ( 도라에몽 도구 씀 )  ";

	 Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
	  pJinGoo->ID(),
	  ent_TongTong,
	  Msg_jinGoo_revenge,   //진구의 복수
	  NO_ADDITIONAL_INFO);   //추가적인 정보 없음 

	}

	else if (!pJinGoo->m_revenge) //복수상태 아닐때
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " 공터에서 띵가 띵가~  "; 
	 pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
	}

 
}


void EnterPlayGround::Exit(JinGoo* pJinGoo)
{
 
	if (pJinGoo->m_revenge) //당하고 나갈 때
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": 두고봐 .. 내가 복수할꺼야 ...  ";
	}

	else if (!pJinGoo->m_revenge) //복수하고 나갈 때
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": 기분 좋게 집으로 가자!  ";
	}
}


bool EnterPlayGround::OnMessage(JinGoo* pJinGoo, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_Tong_FuckYou: //퉁퉁이한테 괴롭힘

						//메시지 받은 시간 출력 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
			<< " at time: " << Clock->GetCurrentTime();*/
		if (!pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": 으아아아아앙 ~~~~~~~~~~~~~~~~~~~~~ ㅠㅠㅠㅠㅠ 퉁퉁이가 괴롭혀 ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ ( 스트레스 증가 + 1 ) ";

			pJinGoo->IncreaseFatigue();

			pJinGoo->m_revenge = true; //복수 시작
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());

		}
		return true;

	case Msg_Tong_OhhNo: //퉁퉁이가 오우노

						//메시지 받은 시간 출력 
						/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
						<< " at time: " << Clock->GetCurrentTime();*/

		if (pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": 헤헤헤헤헤 복수를 성공했다 !!!!!!!!!!!!!!!!!!! 고마워 도라에몽 ~~! ";

			pJinGoo->m_revenge = false;
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
		}

		return true;

	}//end switch
  //send msg to global message handler
  return false;
}



//------------------------------------------------------------------------

GoJinGooHouse* GoJinGooHouse::Instance() //집 , 집 싱클톤
{
  static GoJinGooHouse instance;

  return &instance;
}

void GoJinGooHouse::Enter(JinGoo* pJinGoo) //집 입장
{
  if (pJinGoo->Location() != JinGooHouse) //진구의 위치가 집이 아니면 실행
  {

	  if (pJinGoo->m_revenge)
	  {
		  SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "도라에몽 나 좀 도와줘 ㅠㅠㅠㅠㅠㅠㅠㅠ 퉁퉁이가 괴롭혀 ㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠㅠ 복수하게 해줘  ";

	
		  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 딜레이 타임 0 
			  pJinGoo->ID(),        //ID of sender 
			  ent_Dora,            //ID of recipient
			  Msg_Dora_I_helpMe,   //the message 메시지 도라에몽 나 도와줘
			  NO_ADDITIONAL_INFO);   //추가적인 정보 없음 
	  }
	  else
	  {
		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << " 집에 도착했다 ! ";
	  }




	  pJinGoo->ChangeLocation(JinGooHouse);  // 위치 집으로 바꿈 
  }
}

void GoJinGooHouse::Execute(JinGoo* pJinGoo) //나갈 때
{ 

	if (pJinGoo->m_revenge ==false) //진구가 복수 상태가 아닐때
	{

		if (pJinGoo->BoringOver()) // 지루하면 공터로 간다
		{
			cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
				<< "으앙 너무 뒹굴 거렸더니 심심하군! 공터에 놀러가야겠다 ";

			pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance()); //공터로
		}
		else
		{

			pJinGoo->IncreaseBoring(); //지겨움 증가

			switch (RandInt(0, 2))
			{
			case 0:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 만화책 보면서 뒹굴 뒹굴~~ ";

				break;

			case 1:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 게임기 가지고 노는중 ~~~~ ";

				break;

			case 2:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 으암~~~~~~ 뭐하고 집에서 놀지 ~~~ ";

				break;
			}
		}
	}
	else if (pJinGoo->m_revenge)
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
			<< "초조한 마음으로 도라에몽 도구 기다리는중 .. ";
	}
}

void GoJinGooHouse::Exit(JinGoo* pJinGoo) 
{ 

}


bool GoJinGooHouse::OnMessage(JinGoo* pJinGoo, const Telegram& msg) //밥이 집에서 받는 메세지
{

   switch(msg.Msg)
   {
   case Msg_Dora_GiveItem: //도라에몽이 도구 줌

	   //메시지 받은 시간 출력 
    /* cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID()) 
     << " at time: " << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pJinGoo->ID()) 
          << ": 고마워 도라에몽 !! 나의 은인이야 복수하러 가겠어. ";

     pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}
