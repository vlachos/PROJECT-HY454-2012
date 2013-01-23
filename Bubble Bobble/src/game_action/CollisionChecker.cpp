#include "CollisionChecker.h"

CollisionChecker* CollisionChecker::Checker;
CollisionChecker::CollisionPairsList CollisionChecker::CollisionPairs;

CollisionChecker::CollisionChecker(){
	CollisionPairs.clear();
	DASSERT(CollisionPairs.size() == 0);
}

CollisionChecker::~CollisionChecker(){
	CollisionChecker::CollisionPairs.clear();
	DASSERT(CollisionPairs.size() == 0);
}

void CollisionChecker::SingletonCreate(){
	CollisionChecker::Checker = DNEWCLASS(CollisionChecker,() );
}


void CollisionChecker::Register (Sprite* s1, Sprite* s2, void* Args, CollisionCallback callBack){
	DASSERT(s1); DASSERT(s2); DASSERT(callBack);
	unsigned int oldSize = CollisionPairs.size();

	CollisionInfo newCollisionInfo;

	newCollisionInfo.master = s1;
	newCollisionInfo.slave = s2;
	newCollisionInfo.Args = Args;
	newCollisionInfo.callBack = callBack;

	CollisionChecker::CollisionPairs.push_back(newCollisionInfo);

	DASSERT(CollisionPairs.size() == oldSize + 1);
}

void CollisionChecker::Cancel (Sprite* s1, Sprite* s2){
	DASSERT(s1); DASSERT(s2);
	unsigned int oldSize = CollisionPairs.size();

	for (CollisionPairsList::const_iterator aPair = CollisionPairs.begin(),
										end = CollisionPairs.end(); 
										aPair != end; 
										++aPair) {

		if (s1 == (*aPair).master && s2 == (*aPair).slave){
			std::cout << "Delete Bitch !!! \n";
			CollisionPairs.erase(aPair);
			DASSERT(CollisionPairs.size() == oldSize - 1);
		}
		else{
			DASSERT(CollisionPairs.size() == oldSize);
		}
	}
}


void CollisionChecker::SingletonCleanUp(){
	delete Checker;
}

