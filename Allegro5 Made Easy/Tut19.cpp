// C++ ALLEGRO 5 MADE EASY TUTORIAL 19 - MUSIC
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_audio.h> 
#include<allegro5\allegro_acodec.h>

#define ScreenWidth 800 
#define ScreenHeight 600

int main()
{
	ALLEGRO_DISPLAY *display;

	const float FPS = 60.0;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 
	
	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true, active = false;
	float x = 10, y = 10, moveSpeed = 5;

	al_install_keyboard();
	al_install_audio();
	al_init_image_addon();
	al_init_acodec_addon();

	al_reserve_samples(2);

	ALLEGRO_SAMPLE *soundEffect = al_load_sample("soundEffect.wav");
	ALLEGRO_SAMPLE *song = al_load_sample("intro.ogg"); 

	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_play_sample_instance(songInstance);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);
		al_get_keyboard_state(&keyState);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			active = true;
			if(al_key_down(&keyState, ALLEGRO_KEY_DOWN))
			{
				y += moveSpeed;
				al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			}
			draw = true;
		}

		if(draw)
		{
			al_flip_display();
			al_clear_to_color(al_map_rgb(255, 255, 255));
		}
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_sample(soundEffect);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_event_queue(event_queue);

	return 0;
}