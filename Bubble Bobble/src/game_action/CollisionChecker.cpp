#include "CollisionChecker.h"
#include "AnimatorHolder.h"
#include "GameActionUtilities.h"

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
	DASSERT(s1); DASSERT(s2); //DASSERT(callBack);
	DASSERT( s1!=s2 );

	unsigned int oldSize = CollisionPairs.size();
	CollisionPairsList::const_iterator info;

	if ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), Find(s1,s2) ) ) == CollisionPairs.end() ){

		CollisionInfo newCollisionInfo;
		newCollisionInfo.master = s1;
		newCollisionInfo.slave = s2;
		newCollisionInfo.Args = Args;
		newCollisionInfo.callBack = callBack;

		CollisionChecker::CollisionPairs.push_back(newCollisionInfo);

		DASSERT(CollisionPairs.size() == oldSize + 1);
	}
	else{
		DASSERT(CollisionPairs.size() == oldSize);
	}
}

void CollisionChecker::Register (Sprite* s, animatorType_t start, animatorType_t end, void* Args, CollisionCallback callBack){ 
	DASSERT(s); //DASSERT(callBack);

	unsigned int oldSize = CollisionPairs.size();
	CollisionPairsList::const_iterator info;

	std::vector<Animator*> relatedAnimators = AnimatorHolder::GetAnimators(start,end);

	for(unsigned int i=0; i<relatedAnimators.size(); ++i){
		DASSERT(0 <= start<= ANIMATORS_SIZE);

		if (true){

			CollisionInfo newCollisionInfo;
			newCollisionInfo.master = s;
			//newCollisionInfo.slave = ( ->GetSprite();
			newCollisionInfo.Args = Args;
			newCollisionInfo.callBack = callBack;

			CollisionChecker::CollisionPairs.push_back(newCollisionInfo);

			DASSERT(CollisionPairs.size() == oldSize + 1);
		}
		else{
			DASSERT(CollisionPairs.size() == oldSize);
		}
		
	}
}


void CollisionChecker::Cancel (Sprite* s){
	DASSERT(s);
	unsigned int oldSize;
	bool exists = false;

	CollisionPairsList::const_iterator info;
	while ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), FindAny(s) ) ) != CollisionPairs.end()){
		oldSize = CollisionPairs.size();
		CollisionPairs.erase(info);
		DASSERT(CollisionPairs.size() == oldSize - 1);
	}
}


void CollisionChecker::Cancel (Sprite* s1, Sprite* s2){
	DASSERT(s1); DASSERT(s2);
	unsigned int oldSize;
	CollisionPairsList::const_iterator info;

	oldSize = CollisionPairs.size();
	if ((info = std::find_if( CollisionPairs.begin(), CollisionPairs.end(), Find(s1,s2) ) ) != CollisionPairs.end() ){
		CollisionPairs.erase(info);
		DASSERT(CollisionPairs.size() == oldSize - 1);
	}
	else{
		DASSERT(CollisionPairs.size() == oldSize);
	}
}


void CollisionChecker::SingletonCleanUp(){
	delete Checker;
}

