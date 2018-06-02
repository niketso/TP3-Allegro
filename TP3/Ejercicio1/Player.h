#ifndef PLAYER_H
#define PLAYER_H
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
class Player{
private:
int vidas;
int player_x = 10;
int player_y = 10;

public:
	Player();
	~Player();
	//void Movimiento(ALLEGRO_EVENT);



};




#endif // !PLAYER_H
