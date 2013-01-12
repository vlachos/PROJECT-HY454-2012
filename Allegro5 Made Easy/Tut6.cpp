// C++ ALLEGRO 5 MADE EASY TUTORIAL 6 - DRAWING PRIMITIVES
// CODINGMADEEASY

#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 
#include<allegro5/allegro_primitives.h>

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
	
	ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);
	
	float points[8] = { 0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight };
	
	al_draw_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);
	//al_draw_filled_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);
	
	al_draw_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);
	//al_draw_filled_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);
	
	al_draw_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);
	//al_draw_filled_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);
	
	al_draw_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);
	//al_draw_filled_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);
	
	al_draw_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);
	//al_draw_filled_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);
	
	al_draw_arc(10, ScreenHeight - 100, 10, 0, 4.0, al_map_rgb(255, 0, 0), 2.0);
	
	al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
	
	al_draw_pixel(500, 500, electricBlue);
	
	al_draw_spline(points, electricBlue, 1.0);
	
	al_flip_display();
	al_rest(5.0);
	al_destroy_display(display);
	
	return 0;
}