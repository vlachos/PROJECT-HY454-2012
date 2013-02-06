#ifndef ZENCHANANIMATOR_H
#define ZENCHANANIMATOR_H

#include "MovingAnimator.h"
#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"


class ZenChanStandAnimator : public FrameRangeAnimator{
	public:
		ZenChanStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanStandAnimator_t; }
		
		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};


class ZenChanWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		ZenChanWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanWalkAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class ZenChanFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		ZenChanFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

class ZenChanJumpAnimator : public MovingPathAnimator{
	public:
		ZenChanJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanJumpAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);


};
////////////////////////////////////////////AngryAnimators
class ZenChanAngryStandAnimator : public FrameRangeAnimator{
	public:
		ZenChanAngryStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanAngryStandAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};

class ZenChanAngryWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		ZenChanAngryWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanAngryWalkAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class ZenChanAngryFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{
	public:
		ZenChanAngryFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanAngryFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

class ZenChanAngryJumpAnimator : public FrameRangeAnimator{
	public:
		ZenChanAngryJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanAngryJumpAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};
////////////////////////Die Animator is common
class ZenChanDieAnimator : public MovingPathAnimator, public Sprite::SpriteStartFallingListener{
	public:
		ZenChanDieAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanDieAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};


class ZenChanDieFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		ZenChanDieFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return zenChanDieFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

#endif
