#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *enemy = NULL;

	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(800, 550);

	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	bool done = false;
	int x_I = 10;
	int y_I = 10;
	int moveSpeed = 5;
	int x_E = 500;
	int y_E = 300;

	while (!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type = ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				y_I += moveSpeed;
				break;
			case ALLEGRO_KEY_UP:
				y_I -= moveSpeed;
				break;
			case ALLEGRO_KEY_RIGHT:
				x_I += moveSpeed;
				break;
			case ALLEGRO_KEY_LEFT:
				x_I -= moveSpeed;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		image = al_load_bitmap("image.png");
		enemy = al_load_bitmap("enemy.png");

		if (!image) {
			al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			al_destroy_display(display);
			return 0;
		}
		if (!enemy) {
			al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
			al_destroy_display(display);
			return 0;
		}

		al_draw_bitmap(image, x_I, y_I, 0);
		al_draw_bitmap(enemy, x_E, y_E, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		
		if ((x_I >= x_E + 100 && x_I + 100 <= x_E) && (y_I >= y_E + 100 && y_I + 100 <= y_E)) //esta condicion no funciona
		{
			done = true;
			cout << "it works";
		}
		cout << x_I << "  " << y_I << "  " << endl << x_E << "  " << y_E << endl;
	}

	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);

	return 0;
}