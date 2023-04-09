#include "CommonFunc.h"
#include "BaseObject.h"
#include "map.h"
#include "PlayerObject.h"
#include "ImpTimer.h"

BaseObject g_background;

bool init(){
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("PinkMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		success = false;
	}
    else{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) {
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }
    return success;
}

bool LoadBackGround() {
	bool ret = g_background.LoadImage("./assets/img/bg.png",g_screen);
	return ret;
}


void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}


//main program
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;

    if(init() == false) 
        return -1;

    if(LoadBackGround() == false) 
        return -1;

    GameMap game_map;
    game_map.LoadMap("./map/map1.txt");
    game_map.LoadTiles(g_screen);

    PlayerObject player;
    player.LoadImage("./assets/img/runright.png", g_screen);
    player.SetClips();

    bool quit = false;
    while(!quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
            }

            player.HandleEvent(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);

        Map map_data = game_map.getMap();
        player.DoPlayer(map_data);
        player.Show(g_screen);

        SDL_RenderPresent(g_screen);
        int real_imp_time = fps_timer.get_tick();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    
    close();
    return 0;
}