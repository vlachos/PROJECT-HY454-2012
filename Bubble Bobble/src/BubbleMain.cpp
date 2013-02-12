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
	al_set_window_position(display, 0, 0);

	al_install_keyboard();
	al_init_image_addon();

	if(!al_install_audio()){
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	if(!al_init_acodec_addon()){
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio codecs!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create event_queue!\n", NULL, NULL);
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

	StageStartingAttributesParser::SingletonCreate("..\\data\\bitmaps\\sprites\\info\\stages_starting_data.xml");
	BubbleLogic::SingletonCreate();

	CollisionChecker::SingletonCreate();
	AnimationsParser::SingletonCreate((char*) PathNames::GetAnimationXML().c_str() );
	AnimationFilmHolder::SingletonCreate((char*) PathNames::GetSpritesXML().c_str() );
	Terrain::SingeltonCreate();
	BitmapFontHolder::SingletonCreate();
	InvisibleSprites::SingletonCreate();
	SoundAPI::SingletonCreate("..\\data\\soundtrack");
	StageStartingAttributesParser::SingletonDestroy();
	
	al_start_timer(timer);
	SetGameTime(GetCurrTime());

	SoundAPI::PlaySoundContinue(SoundAPI::soundKind_enterYourInitials_t, true);
	StartScreenAnimatorActions::StartStartScreen();

	redraw = true;
}

/* Game Loop */
void BubbleMain::ManageGameLoop(){

	using namespace BubbleMain;

	while (1){
		al_wait_for_event(event_queue, &ev);
		al_get_keyboard_state(&keyState);
		timestamp_t max=0;
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			timestamp_t nowTime = GetCurrTime();

			Rendering(nowTime);
			if(!InputManagement())
				break;
			if( !BubbleLogic::IsGamePaused() ){
				AnimationProgress(nowTime);
				ArtificialIntelligence();
				CollisionChecking();
				CommitDestructions();
				FPSCalculation();
				SystemLoopDispatching();
				timestamp_t diff = ( nowTime - GetGameTime());
				if(diff>max){
					max=diff;
				}
				std::cout<<"gl: "<<diff<<"\n";
				
				SetGameTime(GetGameTime() + diff);
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}
}

void BubbleMain::Rendering(timestamp_t nowTime){

	if(al_is_event_queue_empty(event_queue)) {

		al_clear_to_color(BB_BLACK);

		Terrain::DisplayTerrain(al_get_backbuffer(display), nowTime);
		AnimatorHolder::Display(al_get_backbuffer(display));

		al_flip_display();
	}
}

bool BubbleMain::InputManagement(){
	bool retVal = true;

	if (!BubbleLogic::IsGamePaused()){

		if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
			InputManageHandling::OnKeyUp();
			retVal = InputManageHandling::OnBubKeyUp();
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
			retVal = InputManageHandling::OnBubKeyRight();	
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
			retVal = InputManageHandling::OnBubKeyLeft();
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
			InputManageHandling::OnKeySpace();
				InputManageHandling::OnBubKeySpace();
		}

		if(al_key_down(&keyState, ALLEGRO_KEY_W)){
			retVal = InputManageHandling::OnBobKeyUp();
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_D)){
			retVal = InputManageHandling::OnBobKeyRight();	
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_A)){
			retVal = InputManageHandling::OnBobKeyLeft();
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_S)){
			InputManageHandling::OnBobKeySpace();
		}

		if(al_key_down(&keyState, ALLEGRO_KEY_Z))
			InputManageHandling::OnKeySelect();

		if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
			InputManageHandling::OnKeyDown();
		}
		if(al_key_down(&keyState, ALLEGRO_KEY_Z)){
			retVal = InputManageHandling::OnKeySelect();
		}
	}
	if(al_key_down(&keyState, ALLEGRO_KEY_P)){
		retVal = InputManageHandling::OnKeyP();
	}
	return true;
}

void BubbleMain::AnimationProgress(timestamp_t timeNow){
	AnimatorHolder::Progress(timeNow);
}

void BubbleMain::ArtificialIntelligence(){
	ArtificialIntelligence::HandleZenChan();
	ArtificialIntelligence::HandleMighta();
	ArtificialIntelligence::HandleAngryZenChan();
	ArtificialIntelligence::HandleAngryMighta();
	ArtificialIntelligence::HandleBarronVonBluba();
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

	BitmapFontHolder::SingletonCleanUp();
	Terrain::SingeltonCleanUp();

	CollisionChecker::SingletonCleanUp();
	AnimationsParser::SingletonDestroy();
	AnimationFilmHolder::SingletonDestroy();
	InvisibleSprites::SingletonDestroy();
	SoundAPI::SingletonDestroy();
	DestructionManager::Commit();

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