#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void initPlayer(PLAYER &player);
void DrawPlayer(PLAYER &player);
void MovePlayerUp(PLAYER &player);
void MovePlayerDown(PLAYER &player);
void MovePlayerLeft(PLAYER &player);
void MovePlayerRight(PLAYER &player);
void BoostStone(STONE stones[],PLAYER &player, int size);

void initStone(STONE stones[], int size);
void DrawStone(STONE stones[], int size);
void StartStone(STONE stones[], int size);
void UpdateStone(STONE stones[], int size);
void CollideStone(STONE stones[], int cSize, PLAYER &player);

void initBackground(Background &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(Background &back);
void DrawBackground(Background &back);



void initPlayer(PLAYER &player)
{
    player.x = WIDTH/2;
    player.y = HEIGHT - 20;
    player.lives = 10;
    player.speed = 7;
    player.boundx = 43;
    player.boundy = 30;
    player.score = 0;
    player.level = 1;
    player.Boost = 3;
}
void DrawPlayer(PLAYER &player)
{

    al_draw_filled_circle(player.x-30,player.y-100,20,al_map_rgb(0,255,0));
    al_draw_filled_rectangle(player.x-70, player.y-80, player.x + 10 , player.y + 10, al_map_rgb(255, 0, 0));
    al_draw_filled_rectangle(player.x+10, player.y - 70, player.x + 20 , player.y - 17, al_map_rgb(0, 255, 0));
    al_draw_filled_rectangle(player.x-80, player.y - 70, player.x - 70 , player.y - 17, al_map_rgb(0, 255, 0));
}
void MovePlayerUp(PLAYER &player)
{
    player.y  = player.y - player.speed;
    if(player.y <HEIGHT/2+100)
        player.y = HEIGHT/2+100;
}
void MovePlayerDown(PLAYER &player)
{
    player.y = player.y + player.speed;
    if(player.y >HEIGHT)
        player.y = HEIGHT;
}
void MovePlayerLeft(PLAYER &player)
{
    player.x = player.x -  player.speed;
    if(player.x < 0)
        player.x = 0;
}
void MovePlayerRight(PLAYER &player)
{
    player.x = player.x + player.speed;
    if(player.x > WIDTH)
        player.x = WIDTH;
}
void BoostStone(STONE stones[],PLAYER &player, int size)
{
    for(int i = 0; i<size; i++)
    {
        if(stones[i].live)
        {
            stones[i].live = false;
            player.score++;
        }
    }
    //player.Boost--;
}
void initStone(STONE stones[], int size)
{
    for(int i = 0; i<size; i++)
    {
        stones[i].live = false;
        stones[i].speed = 5;
        stones[i].boundx = 18;
        stones[i].boundy = 18;
    }
}
void DrawStone(STONE stones[], int size)
{
    for(int i = 0; i<size; i++)
    {
        if(stones[i].live)
        {
            al_draw_filled_circle(stones[i].x, stones[i].y, 20, al_map_rgb(246,255,003));
        }
    }
}
void StartStone(STONE stones[], int size)
{
    for(int i = 0; i<size; i++)
    {
        if(!stones[i].live)
        {
            if(rand() % 500 == 0)
            {
                stones[i].live = true;
                stones[i].y = 0;
                if((30+rand()%(WIDTH-60))>=5 && (30+rand()%(WIDTH-60))<=WIDTH-5)
                {
                    stones[i].x = 30 + rand() % (HEIGHT - 60);
                }
                break;
            }
        }
    }
}
void UpdateStone(STONE stones[], int size)
{
    for(int i = 0; i<size; i++)
    {
        if(stones[i].live)
        {
            stones[i].y += stones[i].speed;
        }
    }
}
void CollideStone(STONE stones[], int cSize, PLAYER &player)
{
    for(int i = 0; i<cSize; i++)
    {
        if(stones[i].live)
        {
            if(stones[i].x - stones[i].boundx < player.x + player.boundx &&
                    stones[i].x + stones[i].boundx > player.x - player.boundx &&
                    stones[i].y - stones[i].boundy < player.y + player.boundy &&
                    stones[i].y + stones[i].boundy > player.y - player.boundy)
            {
                player.score++;
                stones[i].live = false;
            }
            else  if(stones[i].y > HEIGHT )
            {
                stones[i].live = false;
                player.lives--;
            }
        }
    }
}

void initBackground(Background &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
    back.x = x;
    back.y = y;
    back.velX = velx;
    back.velY = vely;
    back.width = width;
    back.height = height;
    back.dirX = dirX;
    back.dirY = dirY;
    back.image = image;
}
void DrawBackground(Background &back)
{
    al_draw_bitmap(back.image, back.x, back.y, 0);

    if(back.x + back.width < WIDTH)
        al_draw_bitmap(back.image, back.x + back.width, back.y, 0);
}
void UpdateBackground(Background &back)
{
    back.x += back.velX * back.dirX;
    if(back.x + back.width <= 0)
        back.x = 0;
}


struct PLAYER{
    int x;
    int y;
    int lives;
    int speed;
    int boundx;
    int boundy;
    int score;
    int level;
    int Boost;
};

struct STONE{
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;
};

struct Background{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
};
