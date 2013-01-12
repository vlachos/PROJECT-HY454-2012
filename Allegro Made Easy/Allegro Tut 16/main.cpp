// ALLEGRO TUTORIAL 16 - SOUND (SOURCE CODE) 
// CODE MADE BY: CODINGMADEEASY
// ALLEGRO VERSION: 4

#include<allegro.h> 

int main()
{
	allegro_init(); 
	install_keyboard(); 
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");

	MIDI *song = load_midi("midiName.mid");
	SAMPLE *sound = load_sample("sampleName.wav");
	
	bool done = false; 

	play_midi(song, true);
	play_sample(sound, 255, 127, 1000, false);
	while(!done)
	{
		if(key[KEY_ESC])
			done = true;
	}
	return 0;
}
END_OF_MAIN()