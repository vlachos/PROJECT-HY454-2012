#include "BubbleMain.h"

/* Initialization */
bool BubbleMain::InitAllegro(){

	if(!al_init()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize allegro!\n", NULL, NULL);
		return false;
	}
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create timer!\n", NULL, NULL);
		return false;
	}
	display = al_create_display(SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
	if(!display) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create display!\n", NULL, NULL);
		al_destroy_timer(timer);
		return false;
	}
	palette = al_create_bitmap(SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
	if(!palette) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create bouncer bitmap!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}
	al_set_window_position(display, 0, 0);
	al_install_keyboard();
	al_init_image_addon();
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create event_queue!\n", NULL, NULL);
		al_destroy_bitmap(palette);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	al_clear_to_color(BB_BLACK);
	al_flip_display();

	return true;
}

void BubbleMain::InitGameEngine(){

	BubbleLogic::SingletonCreate();

	CollisionChecker::SingletonCreate();
	AnimationsParser::SingletonCreate((char*) BubblePathnames::GetAnimationXML().c_str() );
	AnimationFilmHolder::SingletonCreate((char*) BubblePathnames::GetSpritesXML().c_str() );
	Terrain::SingeltonCreate();
	InvisibleSprites::SingletonCreate();
	
	BubbleLogic::SetBubScore(0);

	MovingPathAnimation *mpa = (MovingPathAnimation*) AnimationsParser::GetAnimation("BubInBubble");
	Sprite *sprite = new Sprite(
								250,
								30,
								false,						
								AnimationFilmHolder::GetFilm( "BubInBubble" ), 
								Terrain::GetActionLayer(), 
								false
							);
	sprite->SetOnDrugs(true);
	BubInBubbleAnimator* bibamr = new BubInBubbleAnimator();
	

	/*
	TickAnimation *ta = (TickAnimation*) AnimationsParser::GetAnimation("HurryUpStart");
	ta->SetTickAction( BaronVonBlubaAnimatorActions::StartHurryUpAnimator, 0 );
	TimerTickAnimator* ttar = new TimerTickAnimator(ta);
	ttar->SetOnFinish(BubblesAnimatorActions::OnTickTimerFinishCallback, 0);
	*/
	al_start_timer(timer);
	SetGameTime(GetCurrTime());
	START_ANIMATOR(bibamr, sprite, mpa, GetGameTime() );
	//START_TIME_ANIMATOR(ttar, GetGameTime());

	redraw = true;
}

void BubbleMain::InitSprites(void){
	InitBubblun();
	InitZenChan();
	InitMighta();
}

void BubbleMain::InitBubblun(void){
	BubbleLogic::SetBubScore(0);
	Sprite* sprite = new Sprite(BubbleLogic::GetBubProfile()->GetStartX(), BubbleLogic::GetBubProfile()->GetStartY(),
								BubbleLogic::GetBubProfile()->GetStartGravity(), AnimationFilmHolder::GetFilm("BubWalk"),
								Terrain::GetActionLayer(), BubbleLogic::GetBubProfile()->GetStartDirection());

	MovingAnimation* anim = (MovingAnimation*) AnimationsParser::GetAnimation("BubStand");															\
	BubStandAnimator* animr = new BubStandAnimator();
	animr->RegistCollitions(sprite);
	START_ANIMATOR( animr, sprite, anim, GetGameTime() );
}

void BubbleMain::InitZenChan(void){
	for (unsigned int i = 0; i < BubbleLogic::GetZenChanNum(); ++i){
		Sprite* sprite = new Sprite(BubbleLogic::GetZenChanPosXY(i).first, BubbleLogic::GetZenChanPosXY(i).second,
									BubbleLogic::GetZenChanGravity(i), AnimationFilmHolder::GetFilm("ZenChanWalk"),
									Terrain::GetActionLayer(), BubbleLogic::GetZenChanDirection(i));	

		FrameRangeAnimation* anim = (FrameRangeAnimation*) AnimationsParser::GetAnimation("ZenChanWalkLeft");															\
		MightaWalkingAnimator* animr = new MightaWalkingAnimator();
		sprite->AddStartFallingListener(animr);
		animr->RegistCollitions(sprite);
		START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	}
}

void BubbleMain::InitMighta(void){
	for (unsigned int i = 0; i < BubbleLogic::GetMightaNum(); ++i){
		Sprite* sprite = new Sprite(BubbleLogic::GetMightaPosXY(i).first, BubbleLogic::GetZenChanPosXY(i).second,
									BubbleLogic::GetMightaGravity(i), AnimationFilmHolder::GetFilm("MightaWalk"),
									Terrain::GetActionLayer(), BubbleLogic::GetMightaDirection(i));	

		FrameRangeAnimation* anim = (FrameRangeAnimation*) AnimationsParser::GetAnimation("MightaWalkLeft");															\
		ZenChanWalkingAnimator* animr = new ZenChanWalkingAnimator();
		sprite->AddStartFallingListener(animr);
		animr->RegistCollitions(sprite);
		START_ANIMATOR( animr, sprite, anim, GetGameTime() );
	}
}

/* Game Loop */
void BubbleMain::ManageGameLoop(){

	using namespace BubbleMain;

	while (1){
		al_wait_for_event(event_queue, &ev);
		al_get_keyboard_state(&keyState);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			timestamp_t nowTime = GetCurrTime();
			Rendering();
			InputManagement();
			AnimationProgress(nowTime);
			ArtificialIntelligence();
			CollisionChecking();
			CommitDestructions();
			FPSCalculation();
			SystemLoopDispatching();

			SetGameTime(GetGameTime() + ( nowTime - GetGameTime()));
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}
}

void BubbleMain::Rendering(){

	if(al_is_event_queue_empty(event_queue)) {
		al_set_target_bitmap(palette);
		al_clear_to_color(BB_BLACK);

		Terrain::DisplayTerrain(palette);
		AnimatorHolder::Display(palette);

		al_set_target_bitmap(al_get_backbuffer(display));
		al_draw_bitmap(palette, 0, 0, 0);
		al_flip_display();
	}
}

bool BubbleMain::InputManagement(){
	bool retVal = true;

	if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
		retVal = InputManageHandling::OnKeyUp();
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
		retVal = InputManageHandling::OnKeyDown();
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
		retVal = InputManageHandling::OnKeyRight();		
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
		retVal = InputManageHandling::OnKeyLeft();
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
		retVal = InputManageHandling::OnKeySpace();
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_Z)){
		std::vector<Animator*> zen;

		if(!(zen = AnimatorHolder::GetAnimators(zenChanWalkAnimator_t)).empty()){

			ZenChanWalkingAnimator* _this = (ZenChanWalkingAnimator*) zen.front();
			DASSERT( _this->GetAnimation() && _this->GetSprite() );
			REMOVE_FROM_ACTION_ANIMATOR( _this );

			Sprite* newSprite = _this->GetSprite();
			newSprite->ClearListeners();
			MovingPathAnimation * ma = (MovingPathAnimation*) AnimationsParser::GetAnimation( "ZenChanJump" );
			ZenChanJumpAnimator* mar = new ZenChanJumpAnimator();
			mar->RegistCollitions(newSprite);
	
			START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
			DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
		}else
		if(!(zen = AnimatorHolder::GetAnimators(mightaWalkAnimator_t)).empty()){

			MightaWalkingAnimator* _this = (MightaWalkingAnimator*) zen.front();
			DASSERT( _this->GetAnimation() && _this->GetSprite() );
			REMOVE_FROM_ACTION_ANIMATOR( _this );

			Sprite* newSprite = _this->GetSprite();
			newSprite->ClearListeners();
			MovingPathAnimation * ma = (MovingPathAnimation*) AnimationsParser::GetAnimation( "MightaJump" );
			MightaJumpAnimator* mar = new MightaJumpAnimator();
			mar->RegistCollitions(newSprite);
	
			START_ANIMATOR( mar, newSprite, ma, GetGameTime() );
			DESTROY_ANIMATOR_WITHOUT_SPRITE( _this );
		}
	}
	return retVal;
}

void BubbleMain::AnimationProgress(timestamp_t timeNow){
	AnimatorHolder::Progress(timeNow);
}

void BubbleMain::ArtificialIntelligence(){
	ArtificialIntelligence::HandleZenChan();
	ArtificialIntelligence::HandleMighta();
	ArtificialIntelligence::HandleAngryZenChan();
	ArtificialIntelligence::HandleAngryMighta();
	ArtificialIntelligence::HandleRiver();
}

void BubbleMain::CollisionChecking(){
	CollisionChecker::Check();
}

void BubbleMain::CommitDestructions(){
	DestructionManager::Commit();
}

void BubbleMain::FPSCalculation(){
}

void BubbleMain::SystemLoopDispatching(){
}

/* Game Termination */
void BubbleMain::GameOver(){

	BubbleLogic::SingletonCleanUp();

	Terrain::SingeltonCleanUp();

	CollisionChecker::SingletonCleanUp();
	AnimationsParser::SingletonDestroy();
	AnimationFilmHolder::SingletonDestroy();
	InvisibleSprites::SingletonDestroy();
	DestructionManager::Commit();

	al_destroy_bitmap(palette);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}


int main(int argc, char **argv){
	using namespace BubbleMain;

	if (InitAllegro() ){
		InitGameEngine();
		ManageGameLoop();
		GameOver();
	}
	system( "pause" );
}