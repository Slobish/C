#include "Obj.h"

const int WIDTH = 750;
const int HEIGHT = 600;
const int NUM_STONE = 10;
enum KEYS {UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5] = {false, false, false, false,false};

int main()
{
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isgameover = false;
    int sum = 10, life = 9,x = 3;

    Background BG;

    PLAYER player;
    STONE stones[NUM_STONE];

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;
    ALLEGRO_BITMAP *bgImage = NULL;

    if(!al_init())
    {
        printf("Allegro don't Init\n");
        return -1;
    }
    display = al_create_display(WIDTH, HEIGHT);
    if(!display)
    {
        printf("Display Don't Create\n");
        return -1;
    }
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    bgImage = al_load_bitmap("images/starBG.png");

    srand(time(NULL));
    initPlayer(player);
    initStone(stones, NUM_STONE);

    initBackground(BG, 0, 0, 5, 0, WIDTH, HEIGHT, -1, 1, bgImage);

    font18 = al_load_font("fonts/arial.ttf", 18, 0);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if(keys[UP])
                MovePlayerUp(player);
            if(keys[DOWN])
                MovePlayerDown(player);
            if(keys[LEFT])
                MovePlayerLeft(player);
            if(keys[RIGHT])
                MovePlayerRight(player);
            if(keys[SPACE])
            {
                if(player.Boost>0)
                {
                   BoostStone(stones,player, NUM_STONE);
                   player.Boost--;
                   keys[SPACE] = false;
                }
                //x--;
            }
            if(!isgameover)
            {
                UpdateBackground(BG);

                StartStone(stones, NUM_STONE);
                UpdateStone(stones, NUM_STONE);
                CollideStone(stones, NUM_STONE,player);

                if(player.lives <=0)
                {
                    isgameover = true;
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT]= true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT]= false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT]= false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            if(!isgameover)
            {
                DrawBackground(BG);

                DrawPlayer(player);
                DrawStone(stones, NUM_STONE);
                if(player.score>=sum)
                {
                    player.level++;
                    player.Boost = ++x;
                    sum*=2;
                    player.lives = life;
                    life--;
                    if(life<=3) life = 3;
                }
                al_draw_textf(font18, al_map_rgb(25, 10, 245), 5, 5, 0, "Life : %i. Score : %i. Level : %i Boost : %i", player.lives, player.score,player.level, player.Boost);
            }
            else
            {
                al_draw_textf(font18, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2-40, ALLEGRO_ALIGN_CENTER, "Game Over");
                al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2-20, ALLEGRO_ALIGN_CENTER, "You Complete : %i \level", player.level-1);
                al_draw_textf(font18, al_map_rgb(0, 255, 0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Final Score : %i", player.score);
            }
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    al_destroy_bitmap(bgImage);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font18);
    al_destroy_display(display);

    return 0;
}