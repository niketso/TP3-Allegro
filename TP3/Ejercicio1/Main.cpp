#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Player.h"
#include <iostream>
#define PLAYER_SIZE 100
#define ENEMY_SIZE 100
#define SCREEN_W 640
#define SCREEN_H 480
#define FPS 60

using namespace std;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv) {

	//Player *p1 = new Player();
	bool gameOver = false;
	bool redraw = true;
	bool key[4] = { false, false, false, false };        
	int player_x = 10;
	int player_y = 10;

	int speedMov = 5;
	int enemy_x = 500;
	int enemy_y = 300;
	
	ALLEGRO_DISPLAY *display = NULL;                     //ventana
	ALLEGRO_BITMAP *image = NULL;                        //Player
	ALLEGRO_BITMAP *enemy = NULL;                        //Enemigo
	ALLEGRO_TIMER *timer = NULL;                         //Timer
	
	
	//Inicializo Allegro.
	if (!al_init()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
	// inicializo el timer. 
		timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize timer!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	//Inicializo la extension para cargar imagenes.
	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	//Creo una ventana
	display = al_create_display(SCREEN_W, SCREEN_H);

	//Inizializo la ventana.
	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	//carga
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
	
	//Instalo el teclado.
	al_install_keyboard();

	//Crea la cola de eventos
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	

	//gameloop
	while (!gameOver)
	{
		//variable evento
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		//Movimiento
		//p1->Movimiento(events);
		if (events.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && player_y >= speedMov) {
				player_y -= speedMov;
			}

			if (key[KEY_DOWN] && player_y <= SCREEN_H - PLAYER_SIZE - speedMov) {
				player_y += speedMov;
			}

			if (key[KEY_LEFT] && player_x >= speedMov) {
				player_x -= speedMov;
			}

			if (key[KEY_RIGHT] && player_x <= SCREEN_W - PLAYER_SIZE - speedMov) {
				player_x += speedMov;
			}

			redraw = true;
		}
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (events.type == ALLEGRO_EVENT_KEY_UP) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				gameOver = true;
				break;
			}
		}
		

		al_draw_bitmap(image, player_x, player_y, 0);
		al_draw_bitmap(enemy, enemy_x, enemy_y, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		//colision
		if (((player_x < enemy_x + ENEMY_SIZE) && (enemy_x < player_x + PLAYER_SIZE)
			&& (player_y < enemy_y + ENEMY_SIZE) && (enemy_y < player_y + PLAYER_SIZE))) 
		{
			gameOver = true;
		}
		
	}

	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	//delete p1;
	return 0;
}