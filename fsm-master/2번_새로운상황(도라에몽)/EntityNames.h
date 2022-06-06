#ifndef NAMES_H
#define NAMES_H

#include <string>

//캐릭터
enum 
{
  ent_JinGoo,

  ent_Dora,

  ent_TongTong,


};

//이름 셋팅
inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_JinGoo:

    return "노진구";

  case ent_Dora:
    
    return "도라에몽"; 

  case ent_TongTong:
	 return "퉁퉁이";


  default:

    return "UNKNOWN!";
  }
}

#endif