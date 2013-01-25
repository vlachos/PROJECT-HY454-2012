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
	display = al_create_display(VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT);
	if(!display) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create display!\n", NULL, NULL);
		al_destroy_timer(timer);
		return false;
	}
	palette = al_create_bitmap(VIEW_WINDOW_WIDTH, VIEW_WINDOW_HEIGHT);
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

	Terrain::SingeltonCreate();

	CollisionChecker::SingletonCreate();
	AnimationsParser::SingletonCreate((char*) BubblePathnames::GetAnimationXML().c_str() );
	AnimationFilmHolder::SingletonCreate((char*) BubblePathnames::GetSpritesXML().c_str() );

	MovingAnimation *bubStandanimation= (MovingAnimation*)AnimationsParser::GetAnimation("BubStand");
	Sprite *bubSprite=new Sprite(350,79,true,AnimationFilmHolder::GetFilm("Bubwalk"), Terrain::GetActionLayer(), true);
	bubSprite->SetFrame(6);
	BubStandAnimator *bubStandanimator=new BubStandAnimator();

	MovingAnimation *zenChanAnimation = (MovingAnimation*) AnimationsParser::GetAnimation("ZenChanStand");
	Sprite *zenChanSprite=new Sprite(300,79,true,AnimationFilmHolder::GetFilm("zenchanwalk"), Terrain::GetActionLayer(), true);
	ZenChanStandAnimator * zenChanAnimator = new ZenChanStandAnimator();
	zenChanSprite->AddStartFallingListener(zenChanAnimator);
	
	al_start_timer(timer);
	SetGameTime(GetCurrTime());

	bubStandanimator->Start(bubSprite, bubStandanimation, GetGameTime());
	AnimatorHolder::Register(bubStandanimator);
	AnimatorHolder::MarkAsRunning(bubStandanimator);

	zenChanAnimator->Start(zenChanSprite, zenChanAnimation, GetGameTime());
	AnimatorHolder::Register(zenChanAnimator);
	AnimatorHolder::MarkAsRunning(zenChanAnimator);



	redraw = true;
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

	al_set_target_bitmap(palette);
	al_clear_to_color(BB_BLACK);

	Terrain::DisplayTerrain(palette);
	AnimatorHolder::Display(palette);
 
	if(al_is_event_queue_empty(event_queue)) {
		al_set_target_bitmap(al_get_backbuffer(display));
		al_draw_bitmap(palette, 0, 0, 0);
		al_flip_display();
	}
}

bool BubbleMain::InputManagement(){

	if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
		std::cout << "pressing Up\n";
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
		std::cout << "pressing Down\n";
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
		std::vector<Animator*> bub;
		
		if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
			DASSERT( bub.size()==1 );
			BubWalkingAnimator* bubWalk = (BubWalkingAnimator*) bub.front();
			offset_t offset = bubWalk->GetAnimation()->GetDx();
			DASSERT( offset!=0 );
			if(offset<0){
				bubWalk->GetAnimation()->SetDx(-offset);
				bubWalk->GetSprite()->SetGoesLeft(false);
			}
		}else
		if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
			DASSERT( bub.size()==1 );
			BubStandAnimator* _this = (BubStandAnimator*) bub.front();

			timestamp_t timestamp = GetGameTime();
			DASSERT( timestamp>0 );
			AnimatorHolder::MarkAsSuspended(_this);
			AnimatorHolder::Cancel(_this);
			//CollisionChecker::Cancel(_this->GetSprite());

			DASSERT( _this->GetAnimation() );
			DASSERT( _this->GetSprite() );

			animid_t id = _this->GetAnimation()->GetId();

			_this->GetAnimation()->Destroy();
			_this->Destroy(); 

			FrameRangeAnimation *ma = (FrameRangeAnimation*) AnimationsParser::GetAnimation("Bubwalkright");
			_this->GetSprite()->SetFrame(0);
			_this->GetSprite()->SetGoesLeft(false);

			BubWalkingAnimator* mar = new BubWalkingAnimator();
			_this->GetSprite()->AddStartFallingListener(mar);
			mar->SetOnFinish(BubWalkingAnimator::OnFinishCallback, mar);
			mar->Start(_this->GetSprite(), ma, timestamp);
	
			std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
			for(int i=0; i<enemy.size(); ++i){
				CollisionChecker::Register(_this->GetSprite(), ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), (void *)mar, BubWalkingAnimator::OnCollisionWithEnemy);
			}

			AnimatorHolder::Register(mar);
			AnimatorHolder::MarkAsRunning(mar);
		}
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
		std::vector<Animator*> bub;
		bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t);
		if(!(bub = AnimatorHolder::GetAnimators(bubWalkAnimator_t)).empty()){
			DASSERT( bub.size()==1 );
			BubWalkingAnimator* bubWalk = (BubWalkingAnimator*) bub.front();
			offset_t offset = bubWalk->GetAnimation()->GetDx();
			DASSERT( offset!=0 );
			if(offset>0){
				bubWalk->GetAnimation()->SetDx(-offset);
				bubWalk->GetSprite()->SetGoesLeft(true);
			}
		}else
		if(!(bub = AnimatorHolder::GetAnimators(bubStandAnimator_t)).empty()){
			DASSERT( bub.size()==1 );
			BubStandAnimator* _this = (BubStandAnimator*) bub.front();

			timestamp_t timestamp = GetGameTime();
			DASSERT( timestamp>0 );
			AnimatorHolder::MarkAsSuspended(_this);
			AnimatorHolder::Cancel(_this);
			//CollisionChecker::Cancel(_this->GetSprite());

			DASSERT( _this->GetAnimation() );
			DASSERT( _this->GetSprite() );

			animid_t id = _this->GetAnimation()->GetId();

			Sprite* newSprite = _this->GetSprite();

			_this->GetAnimation()->Destroy();
			_this->Destroy(); 

			FrameRangeAnimation * ma = (FrameRangeAnimation*) AnimationsParser::GetAnimation("Bubwalkleft");
			newSprite->SetFrame(0);
			newSprite->SetGoesLeft(true);

			BubWalkingAnimator* mar = new BubWalkingAnimator();
			newSprite->AddStartFallingListener(mar);
			mar->SetOnFinish(BubWalkingAnimator::OnFinishCallback, mar);
			mar->Start(newSprite, ma, timestamp);

			std::vector<Animator*> enemy = AnimatorHolder::GetAnimators(zenChanStandAnimator_t);
			for(int i=0; i<enemy.size(); ++i){
				CollisionChecker::Register(_this->GetSprite(), ( (ZenChanStandAnimator*)enemy[i] )->GetSprite(), (void *)mar, BubWalkingAnimator::OnCollisionWithEnemy);
			}
	
			AnimatorHolder::Register(mar);
			AnimatorHolder::MarkAsRunning(mar);
		}
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
		std::cout << "pressing Space\n";
	}

	return true;
}

void BubbleMain::AnimationProgress(timestamp_t timeNow){
	CollisionChecker::Check();
	AnimatorHolder::Progress(timeNow);
}

void BubbleMain::ArtificialIntelligence(){
}

void BubbleMain::CollisionChecking(){
}

void BubbleMain::CommitDestructions(){
}

void BubbleMain::FPSCalculation(){
}

void BubbleMain::SystemLoopDispatching(){
}

/* Game Termination */
void BubbleMain::GameOver(){

	Terrain::SingeltonCleanUp();

	CollisionChecker::SingletonCleanUp();
	AnimationsParser::SingletonDestroy();
	AnimationFilmHolder::SingletonDestroy();	

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