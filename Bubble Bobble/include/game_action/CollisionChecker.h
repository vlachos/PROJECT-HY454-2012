#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "Sprite.h"
#include "Animator.h"
#include <list>

class CollisionChecker{

public:
	typedef void (*CollisionCallback) (Sprite*, Sprite*, void*);

	typedef struct collision_t{
		Sprite* master;
		Sprite* slave;
		void* Args;
		CollisionCallback callBack;
	} CollisionInfo;

private:
	typedef std::vector<CollisionInfo> CollisionPairsList ;

	struct Find{
		Find( Sprite* _master,  Sprite* _slave) : master(_master), slave(_slave) { }	
		bool operator() (const CollisionInfo &n){ 
			return (n.master==master && n.slave==slave) ||
				   (n.master==slave && n.slave==master);
		}

		Sprite* master;
		Sprite* slave;
	};

	struct FindAny{
		FindAny( Sprite* _sprite) : sprite(_sprite){ }	
		bool operator() (const CollisionInfo &n){ 
			return (n.master==sprite || n.slave==sprite);
		}
		Sprite* sprite;
	};

	private:
		CollisionChecker();
		~CollisionChecker();

	private:
		static CollisionChecker* Checker;
		static CollisionPairsList CollisionPairs;

	public:
		static void	SingletonCreate (void);

    public:
		static void Register (Sprite* s1, Sprite* s2, void* Args, CollisionCallback callBack);
		static void Register (Sprite* s1, animatorType_t start, animatorType_t end, void* Args, CollisionCallback callBack);
		static void Register (Sprite* s1, animatorType_t start, animatorType_t end, CollisionCallback callBack);
		static void RegisterPair(Sprite* s1, animatorType_t start, animatorType_t end, Animator* anim, CollisionCallback callBack);
		static void Cancel (Sprite* s);
		static void Cancel (Sprite* s1, Sprite* s2);
		static void Check (void){
			for(unsigned int i=0; i<CollisionPairs.size(); ++i){
				CollisionInfo p = CollisionPairs[i];
				if (p.master->CollisionCheck(p.slave) ){
					if(p.callBack){
						(*p.callBack)(p.master, p.slave, p.Args);
					}
				}
			}
		}

	public:
		static void	SingletonCleanUp (void);

};

#endif