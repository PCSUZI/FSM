#include <fstream>
#include <time.h>
#include <Windows.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "Dog.h"
#include "Owner_call.h"

std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  Dog *Bogg = new Dog(ent_Dog);

  Owner_call *Owner = new Owner_call(ent_Owner);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Bogg);
  EntityMgr->RegisterEntity(Owner);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	Bogg->Update();
	Owner->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(1500);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Bogg;
  delete Owner;
  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






