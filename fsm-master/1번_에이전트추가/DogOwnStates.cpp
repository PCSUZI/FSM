#include "DogOwnStates.h"
#include "State.h"
#include "Dog.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "utils.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

HomeAndSleepTilRested* HomeAndSleepTilRested::Instance() //Áý , Áý ½ÌÅ¬Åæ
{
	static HomeAndSleepTilRested instance;

	return &instance;
}

void HomeAndSleepTilRested::Enter(Dog* dog) //Áý ÀÔÀå
{

}

void HomeAndSleepTilRested::Execute(Dog* dog) //³ª°¥ ¶§
{
	//¾ÈÇÇ°ï ÇÏ¸é ³í´Ù
	if (!dog->Fatigued()) 
	{
		switch (RandInt(0, 2))
		{
		case 0:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": °ø °¡Áö°í ³ë´ÂÁß ";

			break;

		case 1:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": ¿Õ¿Õ~~!!! ( ³ë·¡ºÎ¸£´Â Áß ) ";

			break;

		case 2:

			cout << "\n" << GetNameOfEntity(dog->ID()) << ": ´Þ¸®°í ³ë´ÂÁß ";

			break;
		}

		dog->IncreaseFatigue(); //ÇÇ°ïÇÔ Áõ°¡
	}
	else if(dog->Thirsty())
	{
		dog->GetFSM()->ChangeState(QuenchHungry::Instance());
	}

	else
	{
		//sleep
		dog->DecreaseFatigue(); //ÀÜ´Ù. ÇÇ°ïÇÔ °¨¼Ò

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << ".. ¸Û¸Û ...ZZZ";
	}
}

void HomeAndSleepTilRested::Exit(Dog* dog)
{

}


bool HomeAndSleepTilRested::OnMessage(Dog* dog, const Telegram& msg) //¹äÀÌ Áý¿¡¼­ ¹Þ´Â ¸Þ¼¼Áö
{
//	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_PetReady: //»ç·á ¸Þ½ÃÁö

						//¸Þ½ÃÁö ¹ÞÀº ½Ã°£ Ãâ·Â 
		cout << "\nMessage handled by " << GetNameOfEntity(dog->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(dog->ID())
			<< ": ¸Û¸Û ! ( ¾ö¸¶°¡ »ç·á¸¦ ÁÖ¼Ì´Ù ¸ÔÀ¸·¯ °¡ÀÚ! ) ";

		dog->GetFSM()->ChangeState(Eat::Instance());

		return true;


	case Msg_HiHoneyImHome: //¾Æºü¿Ô´Ù

					   //¸Þ½ÃÁö ¹ÞÀº ½Ã°£ Ãâ·Â 
	/*	cout << "\nMessage handled by " << GetNameOfEntity(dog->ID())
			<< " at time: " << Clock->GetCurrentTime();*/

		SetTextColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(dog->ID())
			<< ": ¸Û¸Û¸Ø¸Û¸Û¸Û!!!!!!!!!!!!!!!! ¸Û¸Û¸Ø¸Û¸Û¸Û ( ¾Æºü°¡ µ¹¾Æ ¿Ô´Ù !!!!!!!! ) ¿µ¿õ ¿µ¿õ!!!!!!!!!";

		dog->GetFSM()->ChangeState(HomeAndSleepTilRested::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchHungry* QuenchHungry::Instance() //¸ñ¸¶¸§
{
	static QuenchHungry instance;

	return &instance;
}

void QuenchHungry::Enter(Dog* dog)
{
	if (dog->Thirsty())
	{
		dog->ChangeLocation(saloon); //Àå¼Ò ¹Ù²ñ

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << " '¹è°¡ °íÇÁ±º !! ¾ö¸¶ÇÑÅ× ¹ä ´Þ¶óÇØ¾ß°Ú¾î' ";

		cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << " ¸Û¸Û !!! ¸Û¸Û¸Û¸Û !! ( ¾ö¸¶ ³ª ¹è°íÆÄ¿ä ! )  ";

		//dog->ChangeLocation(shack);  // À§Ä¡ ÁýÀ¸·Î ¹Ù²Þ 

		//let the wife know I'm home ¾Æ³»¿¡°Ô ¸Þ½ÃÁö º¸³¿
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay µô·¹ÀÌ Å¸ÀÓ 0 
			dog->ID(),        //ID of sender ±¤ºÎ ¾ÆÀÌµð
			ent_Elsa,            //ID of recipient ¾Æ³»ÇÑÅ× º¸³¿
			Msg_IamHungry,   //the message ¸Þ½ÃÁö ¾ö¸¶ ¹è°íÆÄ 
			NO_ADDITIONAL_INFO);   //Ãß°¡ÀûÀÎ Á¤º¸ ¾øÀ½ 


	}
}

void QuenchHungry::Execute(Dog* dog)
{
	dog->GetFSM()->ChangeState(HomeAndSleepTilRested::Instance());
}


void QuenchHungry::Exit(Dog* dog)
{

}


bool QuenchHungry::OnMessage(Dog* dog, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------EatStew

Eat* Eat::Instance() //½ºÆ© ¸Ô´Â°Å
{
	static Eat instance;

	return &instance;
}


void Eat::Enter(Dog* dog)
{
	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "Å¯Ä² Å¯Ä² ! (³¿»õ ¸Ã±â )  ";
}

void Eat::Execute(Dog* dog)
{

	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "¿Í±¸ ¿Í±¸ ~~~ ( ¹ä¸Ô´Â Áß )";
	dog->BuyAndDrinkAWhiskey(); //Çã±â »ç¶óÁü

	dog->GetFSM()->RevertToPreviousState(); //ÀÌÀü »óÅÂ·Î µ¹¾Æ°¡Áö
}

void Eat::Exit(Dog* dog)
{
	cout << "\n" << GetNameOfEntity(dog->ID()) << ": " << "¸Û¸Û !!!!!! ( Àß¸Ô¾ú½À´Ï´Ù. ) ";
}


bool Eat::OnMessage(Dog* dog, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


