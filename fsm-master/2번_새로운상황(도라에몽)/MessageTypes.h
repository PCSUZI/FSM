#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_IgoPlayGround, //진구가 공터감
  Msg_Dora_I_helpMe, //도라에몽 도와줘 ㅠㅜ 
  Msg_jinGoo_revenge, //진구 복수하러 간다.
  Msg_Tong_OhhNo, //퉁퉁이 당함
  Msg_Tong_FuckYou, //퉁퉁이가 진구 괴롭힘
  Msg_Dora_GiveItem //도라에몽이 도구 줌
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_IgoPlayGround:
    
    return "Msg_IgoPlayGround"; 

  case Msg_Dora_I_helpMe:
    
    return "Msg_Dora_I_helpMe";

  case Msg_jinGoo_revenge:
	  return "Msg_jinGoo_revenge";

  case Msg_Tong_OhhNo:
	  return "Msg_Tong_OhhNo";

  case Msg_Tong_FuckYou:
	  return "Msg_Tong_FuckYou";

  case Msg_Dora_GiveItem:
	  return "Msg_Dora_GiveItem";

  default:

    return "Not recognized!";
  }
}

#endif