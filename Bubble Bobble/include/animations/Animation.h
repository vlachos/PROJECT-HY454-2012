#ifndef	ANIMATION_H
#define	ANIMATION_H

#include "MemoryManage.h"
#include "utilities.h" 

typedef signed char	offset_t;
typedef unsigned short	delay_t;
typedef unsigned short	animid_t;

class Animation : public LatelyDestroyable{
	animid_t id;
	
public:
	Animation (animid_t _id);
	animid_t GetId (void);
	virtual Animation* Clone (animid_t newId) const = 0;
	virtual ~Animation();
};

#endif