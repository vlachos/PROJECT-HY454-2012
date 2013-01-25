#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "Sprite.h"
#include <list>

class CollisionChecker{

	typedef void (*CollisionCallback) (Sprite*, Sprite*, void*);

	typedef struct collision_t{
		Sprite* master;
		Sprite* slave;
		void* Args;
		CollisionCallback callBack;
	} CollisionInfo;

	typedef std::list<CollisionInfo> CollisionPairsList ;

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

	typedef struct CheckFunctor : public std::unary_function<CollisionInfo, void> {
		void operator()(const CollisionInfo& p) const {
			if (p.master->CollisionCheck(p.slave) ){
				//(*p.callBack)(p.master, p.slave, p.Args);
				std::cout << "Collision Bitch \t";
			}
		}
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
		static CollisionPairsList::const_iterator PairLookUp (Sprite* s1, Sprite* s2);
		static void Cancel (Sprite* s);
		static void Cancel (Sprite* s1, Sprite* s2);
		static void Check (void){
 			std::for_each(
  				CollisionPairs.begin(), CollisionPairs.end(), CheckFunctor()
			); 
		}

	public:
		static void	SingletonCleanUp (void);

};

#endif