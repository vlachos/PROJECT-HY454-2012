#ifndef	MEMORYMANAGE_H
#define	MEMORYMANAGE_H

#include <list>
#include <assert.h>

//will add gui effect in future

#define DASSERT( sent ) 
//assert( sent )

template <class T> void unullify (T*& p) 
	{ p = (T*) 0;}

template <class T>
T* _DNOTNULL (T* p) {
	DASSERT(p);
	return p;
}
 
struct ddestructors {
	template <typename T>
	static void udeletesubstitute(T* p) 
		{ delete p; }
	template <class T, const unsigned N> 
	static void udeletesubstitute (T (*&p)[N]) 
		{ delete[] p; }
	template <typename T> 
	static void udelarraysubstitute(T* p) 
		{ delete[] p; }
};

#define DNEWPTR(TYPE, VAR)		TYPE* VAR;  unullify(VAR)

#define DNEW(a)					_DNOTNULL(new a)
#define	DNEWCLASS(C,Args)		DNEW(C Args)
#define	DNEWARR(t,n)			DNEW(t[n])

#define	DDELARR(p)			ddestructors::udelarraysubstitute(p)
#define	DDELETE(p)			ddestructors::udeletesubstitute(p)

template <class T> void udelete (T*& p) 
	{ DASSERT(p); DDELETE((T*) p); unullify(p); }

template <class T> void udeleteasarray (T*& p) 
	{ DASSERT(p); DDELARR((T*) p); unullify(p); }

//////////DestructionManager

class LatelyDestroyable;
class DestructionManager {
	static std::list<LatelyDestroyable*> dead;
public:
	static void Register (LatelyDestroyable* o);
	static void Commit (void);
};
class LatelyDestroyable {
	friend class DestructionManager;
	bool alive;
	bool inDestruction;
	
	class Delete : public std::unary_function<LatelyDestroyable*, void>
		{ public: void operator()(LatelyDestroyable* o) const; };
	friend class Delete;
public:
	bool IsAlive (void) const { return alive; }
	void Destroy (void) { 
		if (alive) {
			alive = false; 
			DestructionManager::Register(this);
		}
	}
	LatelyDestroyable (void) : alive(true), inDestruction(false){}
	virtual ~LatelyDestroyable() { assert(inDestruction); }
};


#endif