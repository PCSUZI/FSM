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
  if (pJinGoo->Location() != PlayGround) //因斗亜 焼艦虞檎
  {
    cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "因斗拭 尽陥.";


	if (!pJinGoo->m_revenge) 
	{
		//糖糖戚廃砺 五獣走 左蛙 
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 渠傾戚 展績 0 
			pJinGoo->ID(),
			ent_TongTong,
			Msg_IgoPlayGround,   //the message 五獣走 
			NO_ADDITIONAL_INFO);   //蓄亜旋昔 舛左 蒸製 
	}

	pJinGoo->DecreaseBoring(); //走欠敗 段奄鉢
    pJinGoo->ChangeLocation(PlayGround); //因斗稽
  }
}


void EnterPlayGround::Execute(JinGoo* pJinGoo)
{  

	if (pJinGoo->m_revenge) //差呪
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " 醤!!!!!!! 糖糖戚 !!!!!!!!!!!!!!!! ( 亀虞拭功 亀姥 掌 )  ";

	 Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 渠傾戚 展績 0 
	  pJinGoo->ID(),
	  ent_TongTong,
	  Msg_jinGoo_revenge,   //遭姥税 差呪
	  NO_ADDITIONAL_INFO);   //蓄亜旋昔 舛左 蒸製 

	}

	else if (!pJinGoo->m_revenge) //差呪雌殿 焼諌凶
	{
	 cout << "\n" << GetNameOfEntity(pJinGoo->ID())
	  << " 因斗拭辞 愚亜 愚亜~  "; 
	 pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
	}

 
}


void EnterPlayGround::Exit(JinGoo* pJinGoo)
{
 
	if (pJinGoo->m_revenge) //雁馬壱 蟹哀 凶
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": 砧壱坐 .. 鎧亜 差呪拝襖醤 ...  ";
	}

	else if (!pJinGoo->m_revenge) //差呪馬壱 蟹哀 凶
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID())
			<< ": 奄歳 疏惟 増生稽 亜切!  ";
	}
}


bool EnterPlayGround::OnMessage(JinGoo* pJinGoo, const Telegram& msg)
{

	switch (msg.Msg)
	{
	case Msg_Tong_FuckYou: //糖糖戚廃砺 雨罫毘

						//五獣走 閤精 獣娃 窒径 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
			<< " at time: " << Clock->GetCurrentTime();*/
		if (!pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": 生焼焼焼焼肖 ~~~~~~~~~~~~~~~~~~~~~ ばばばばば 糖糖戚亜 雨罫粕 ばばばばばばばばばばばばばばばばばば ( 什闘傾什 装亜 + 1 ) ";

			pJinGoo->IncreaseFatigue();

			pJinGoo->m_revenge = true; //差呪 獣拙
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());

		}
		return true;

	case Msg_Tong_OhhNo: //糖糖戚亜 神酔葛

						//五獣走 閤精 獣娃 窒径 
						/*	cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID())
						<< " at time: " << Clock->GetCurrentTime();*/

		if (pJinGoo->m_revenge)
		{
			SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pJinGoo->ID())
				<< ": 伯伯伯伯伯 差呪研 失因梅陥 !!!!!!!!!!!!!!!!!!! 壱原趨 亀虞拭功 ~~! ";

			pJinGoo->m_revenge = false;
			pJinGoo->GetFSM()->ChangeState(GoJinGooHouse::Instance());
		}

		return true;

	}//end switch
  //send msg to global message handler
  return false;
}



//------------------------------------------------------------------------

GoJinGooHouse* GoJinGooHouse::Instance() //増 , 増 縮適宕
{
  static GoJinGooHouse instance;

  return &instance;
}

void GoJinGooHouse::Enter(JinGoo* pJinGoo) //増 脊舌
{
  if (pJinGoo->Location() != JinGooHouse) //遭姥税 是帖亜 増戚 焼艦檎 叔楳
  {

	  if (pJinGoo->m_revenge)
	  {
		  SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << "亀虞拭功 蟹 岨 亀人操 ばばばばばばばば 糖糖戚亜 雨罫粕 ばばばばばばばばばばば 差呪馬惟 背操  ";

	
		  Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay 渠傾戚 展績 0 
			  pJinGoo->ID(),        //ID of sender 
			  ent_Dora,            //ID of recipient
			  Msg_Dora_I_helpMe,   //the message 五獣走 亀虞拭功 蟹 亀人操
			  NO_ADDITIONAL_INFO);   //蓄亜旋昔 舛左 蒸製 
	  }
	  else
	  {
		  cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": " << " 増拭 亀鐸梅陥 ! ";
	  }




	  pJinGoo->ChangeLocation(JinGooHouse);  // 是帖 増生稽 郊嘩 
  }
}

void GoJinGooHouse::Execute(JinGoo* pJinGoo) //蟹哀 凶
{ 

	if (pJinGoo->m_revenge ==false) //遭姥亜 差呪 雌殿亜 焼諌凶
	{

		if (pJinGoo->BoringOver()) // 走欠馬檎 因斗稽 娃陥
		{
			cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
				<< "生肖 格巷 救閏 暗携希艦 宿宿馬浦! 因斗拭 且君亜醤畏陥 ";

			pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance()); //因斗稽
		}
		else
		{

			pJinGoo->IncreaseBoring(); //走移崇 装亜

			switch (RandInt(0, 2))
			{
			case 0:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 幻鉢奪 左檎辞 救閏 救閏~~ ";

				break;

			case 1:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 惟績奄 亜走壱 葛澗掻 ~~~~ ";

				break;

			case 2:

				cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": 生章~~~~~~ 更馬壱 増拭辞 且走 ~~~ ";

				break;
			}
		}
	}
	else if (pJinGoo->m_revenge)
	{
		cout << "\n" << GetNameOfEntity(pJinGoo->ID()) << ": "
			<< "段繕廃 原製生稽 亀虞拭功 亀姥 奄陥軒澗掻 .. ";
	}
}

void GoJinGooHouse::Exit(JinGoo* pJinGoo) 
{ 

}


bool GoJinGooHouse::OnMessage(JinGoo* pJinGoo, const Telegram& msg) //剛戚 増拭辞 閤澗 五室走
{

   switch(msg.Msg)
   {
   case Msg_Dora_GiveItem: //亀虞拭功戚 亀姥 捜

	   //五獣走 閤精 獣娃 窒径 
    /* cout << "\nMessage handled by " << GetNameOfEntity(pJinGoo->ID()) 
     << " at time: " << Clock->GetCurrentTime();*/

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pJinGoo->ID()) 
          << ": 壱原趨 亀虞拭功 !! 蟹税 精昔戚醤 差呪馬君 亜畏嬢. ";

     pJinGoo->GetFSM()->ChangeState(EnterPlayGround::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}
