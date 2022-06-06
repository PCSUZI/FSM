#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_IamHungry,
  Msg_PetReady,
  Msg_IgoGold, //밥이 금광 왔다고 상사한테 말함
  Msg_Owner_Bad, //상사가 잔소리 안함
  Msg_Owner_Good //상사가 잔소리함
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_IamHungry:

	  return "IamHungry";

  case Msg_PetReady:
	  return "PetReady";

  case Msg_IgoGold:
	  return "IgoGold";

  case Msg_Owner_Bad:
	  return "Owner_Bad";

  case Msg_Owner_Good:
	  return "Owner_Good";

  default:

    return "Not recognized!";
  }
}

#endif