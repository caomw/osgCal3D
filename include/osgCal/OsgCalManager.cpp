#include "OsgCalManager.h"

using namespace EveLifeOSteerRBody;
//singleton initialisation
OsgCalManager* OsgCalManager::_instance=NULL;

OsgCalManager::~OsgCalManager(){
/*No more used cause we manage it by ref ptr
for(std::map<CoreModelID,osgCal::CoreModel*>::iterator i=store.begin();i!=store.end();i++){
		delete(*i).second;
	}
*/

}

EveLifeCoreModel * OsgCalManager::getCoreModel(const CoreModelID &Name){
	//TODO USE THE MAP lol 	store[Name]
	for(std::map<CoreModelID,EveLifeCoreModel >::iterator i=store.begin();i!=store.end();i++){
		if((*i).first==Name)return&(*i).second;
	}

	return 0;
}
//add a corModel
void OsgCalManager::addCore(EveLifeCoreModel& c,CoreModelID &id){
	//c.getCoreModel()->getCalCoreModel()->se
	c.getCoreModel()->setName(id);
	store[id]=c;
	
}




