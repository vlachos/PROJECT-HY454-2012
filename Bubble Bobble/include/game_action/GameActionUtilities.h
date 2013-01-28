#ifndef GAMEACTIONUTILITIES_H
#define GAMEACTIONUTILITIES_H

#define REMOVE_FROM_ACTION_ANIMATOR( anim )		\
	AnimatorHolder::MarkAsSuspended( anim );	\
	AnimatorHolder::Cancel( anim );				\
	CollisionChecker::Cancel( anim->GetSprite() )

#define DESTROY_ANIMATOR_WITHOUT_SPRITE( anim )	\
	anim->GetAnimation()->Destroy();			\
	anim->Destroy()

#define DESTROY_ANIMATOR( anim )				\
	anim->GetSprite()->Destroy();				\
	DESTROY_ANIMATOR_WITHOUT_SPRITE( anim )

#define START_ANIMATOR( animr, sprite, anim, time )	\
	animr->Start( sprite, anim, time);				\
	AnimatorHolder::Register( animr );				\
	AnimatorHolder::MarkAsRunning( animr )




#endif