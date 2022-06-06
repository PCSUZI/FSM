#ifndef NAMES_H
#define NAMES_H

#include <string>

//캐릭터
enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Dog,

  ent_Owner
};

//이름 셋팅
inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 

  case ent_Dog:
	 return "Dog";

  case ent_Owner:
	  return "Owner Phone : ";

  default:

    return "UNKNOWN!";
  }
}

#endif