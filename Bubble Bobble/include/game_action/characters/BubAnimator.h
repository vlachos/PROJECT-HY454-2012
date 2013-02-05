#ifndef BUBANIMATOR_H
#define BUBANIMATOR_H

#include "FrameRangeAnimator.h"
#include "MovingPathAnimator.h"
#include "MovingAnimator.h"
#include "Sprite.h"

namespace BubAnimatorActions{
	extern void OnCollisionWithEnemy(Sprite*, Sprite*, void*);
}
		
class BubStandAnimator : public MovingAnimator{
	public:
		BubStandAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubStandAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnOpenMouth(void);
		static void OnFinishCallback(Animator*, void*);
};

class BubWalkingAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{

	public:
		BubWalkingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubWalkAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
		void OnOpenMouth(void);
};

class BubFallingAnimator : public MovingAnimator, public Sprite::SpriteStopFallingListener{

	public:
		BubFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		void OnOpenMouth(void);
		void OnStopFalling(Sprite * sprite);
};

class BubOpenMouthAnimator : public FrameRangeAnimator, public Sprite::SpriteStartFallingListener{
	public:
		BubOpenMouthAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubOpenMouthAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStartFalling(Sprite * sprite);
};

class BubOpenMouthFallingAnimator : public FrameRangeAnimator, public Sprite::SpriteStopFallingListener{
	public:
		BubOpenMouthFallingAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubOpenMouthFallingAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnStopFalling(Sprite * sprite);
};

class BubJumpAnimator : public MovingPathAnimator{
	public:
		BubJumpAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubJumpAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		void OnOpenMouth(void);
};

class BubJumpOpenMouthAnimator : public MovingPathAnimator{
	public:
		BubJumpOpenMouthAnimator(MovingPathAnimation *, int index);

		enum animatorType_t GetAnimatorType(void)
			{ return bubJumpOpenMouthAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
		MovingPathAnimation* GetJumpAnimation();
		int					 GetIndex();
	private:
		MovingPathAnimation* jumpAnimation;
		int index;
};

class BubDieAnimator : public MovingPathAnimator{
	public:
		BubDieAnimator();

		enum animatorType_t GetAnimatorType(void)
			{ return bubDieAnimator_t; }

		void RegistCollitions(Sprite*);
		static void OnFinishCallback(Animator*, void*);
};

#endif