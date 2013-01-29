#ifndef GAMEACTIONUTILITIES_H
#define GAMEACTIONUTILITIES_H

#define INIT_NEW_INSTANCE(anim_t, anim, animStateStr, animr_t, animr, sprite, spriteStateStr, _x, _y, gravAddict, goLeft)			\
	anim_t* anim = (anim_t*) AnimationsParser::GetAnimation(animStateStr);															\
	Sprite* sprite = new Sprite(_x,_y,gravAddict,AnimationFilmHolder::GetFilm(spriteStateStr), Terrain::GetActionLayer(), goLeft);	\
	animr_t* animr = new animr_t();																									\
	sprite->AddStartFallingListener(animr);

#define START_ANIMATOR( animr, sprite, anim, time )	\
	animr->Start( sprite, anim, time);				\
	AnimatorHolder::Register( animr );				\
	AnimatorHolder::MarkAsRunning( animr )

#define DESTROY_ANIMATOR( anim )				\
	anim->GetSprite()->Destroy();				\
	DESTROY_ANIMATOR_WITHOUT_SPRITE( anim )

#define DESTROY_ANIMATOR_WITHOUT_SPRITE( anim )	\
	anim->GetAnimation()->Destroy();			\
	anim->Destroy()

#define REMOVE_FROM_ACTION_ANIMATOR( anim )		\
	AnimatorHolder::MarkAsSuspended( anim );	\
	AnimatorHolder::Cancel( anim );				\
	CollisionChecker::Cancel( anim->GetSprite() )

#endif