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

TileLayer* BubbleMain::InitTerrain(){
	DNEWPTR(TileLayer, actionLayer);
	DNEWPTR(TileBitmap, tilesBitmap);
	tilesBitmap = DNEW(TileBitmap);
	actionLayer = DNEWCLASS(TileLayer, (tilesBitmap) );
	
	actionLayer->ReadStage(BubblePathnames::GetStageInfo(1));
	actionLayer->WriteMap(BubblePathnames::GetTestActionLayerInfo() );

	return actionLayer;
}

void BubbleMain::InitGameEngine(){

	afh = new AnimationFilmHolder("..\\data\\bitmaps\\sprites\\data.xml");
	FrameRangeAnimation *fra=new FrameRangeAnimation(0,6,-2,0,100,false,1);
	Sprite *sprite=new Sprite(400,50,false,afh->GetFilm("Bubopenmouth"), actionLayer);
	FrameRangeAnimator *frtor=new FrameRangeAnimator();
	frtor->SetOnFinish(EventCallbacks::BubbleWalkStop, 0 ); 

	al_start_timer(timer);
	SetGameTime(GetCurrTime());

	frtor->Start(sprite,fra,GetGameTime());
	AnimatorHolder::Register(frtor);
	AnimatorHolder::MarkAsRunning(frtor);
	redraw = true;
}


/* Game Loop */
void BubbleMain::ManageGameLoop(){

	using namespace BubbleMain;

	while (1){
		ALLEGRO_EVENT ev;
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

	actionLayer->Display(palette);
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
		return true;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
		std::cout << "pressing Down\n";
		return true;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
		std::cout << "pressing Right\n";
		return true;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
		std::cout << "pressing Left\n";
		return true;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_SPACE)){
		std::cout << "pressing Space\n";
		return true;
	}
	else{
		std::cout << "pressing nothing\n";
		return false;
	}
}

void BubbleMain::AnimationProgress(timestamp_t timeNow){
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

   delete afh;
   delete actionLayer;

   al_destroy_bitmap(palette);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
}


int main(int argc, char **argv){

	using namespace BubbleMain;

	if (InitAllegro() ){
		actionLayer = InitTerrain();
		InitGameEngine();
		ManageGameLoop();
		GameOver();
	}
	system( "pause" );
}