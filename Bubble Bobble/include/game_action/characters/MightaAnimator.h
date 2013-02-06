#ifndef MIGHTAANIMATOR_H
#define MIGHTAANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "Sprite.h"


class MightaStandAnimator : public FrameRangeAnimator{
	public:
		MightaStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaStandAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};


class MightaWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		MightaWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaWalkAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class MightaFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		MightaFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

class MightaJumpAnimator : public MovingPathAnimator{
	public:
		MightaJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaJumpAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);


};
//////////////////////////////Angry Animators
class MightaAngryStandAnimator : public FrameRangeAnimator{
	public:
		MightaAngryStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaAngryStandAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};

class MightaAngryWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		MightaAngryWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaAngryWalkAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class MightaAngryFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		MightaAngryFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaAngryFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

class MightaAngryJumpAnimator : public MovingPathAnimator{
	public:
		MightaAngryJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaAngryJumpAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);


};
//////////////////Die Animators are common
class MightaDieAnimator : public MovingPathAnimator, public Sprite::SpriteStartFallingListener{
	public:
		MightaDieAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaDieAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class MightaDieFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{

	public:
		MightaDieFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return mightaDieFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnStopFalling(Sprite * sprite);
};

#endif
