// C++ ALLEGRO 5 MADE EASY TUTORIAL 5 - FONT & TEXT
// CODINGMADEEASY

#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 
#include<allegro5/allegro_allegro_ttf.h> 
#include<allegro5/allegro_allegro_font.h> 

#define ScreenWidth 800 
#define ScreenHeight 600 

int main()
{
	ALLEGRO_DISPLAY *display; 
	
	if(al_init())
	{
		al_show_native_message_box(NULL, NULL, "Error", "Could not initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR); 
		return -1;
	}
	display = al_create_display(ScreenWidth, ScreenHeight); 
	
	if(!display)
	{
		al_show_native_messagebox(NULL, NULL, "Error", "Could not create Allegro 5 display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
		
	// You generally want to do this after you check to see if the display was created. If the display wasn't created then there's
	// no point in calling this function
	al_set_new_display_flags(ALLEGRO_NOFRAME);
	al_set_window_poition(display, 200, 100);
	al_set_window_title(display, "CodingMadeEasy");
	
	al_init_font_addon(); 
	al_init_ttf_addon();
	
	ALLEGRO_FONT *font = al_load_font("font.ttf", 36, NULL); 
	al_draw_text(font, al_map_rgb(44, 117, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE, "www.codingmadeeasy.ca");
	
	al_flip_display(); 
	al_rest(10.0);
	
	al_destroy_font(font);
	al_destroy_display(display);
	
	return 0;
}