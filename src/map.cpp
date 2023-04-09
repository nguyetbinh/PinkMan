#include "map.h"

//dinh nghia ham LoadMap
void GameMap::LoadMap(const char* name)
{
    //doc file
   FILE* fp = fopen(name, "rb");
        if (fp == NULL) 
        {
            // Xử lý lỗi
            return;
        }

    game_map.max_x = 0;
    game_map.max_y = 0;

    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map.tile[i][j]); //doc cac gtri tu tep
            int val = game_map.tile[i][j];
            if(val > 0) 
            {
				if (j > game_map.max_x) {
					game_map.max_x = j;
				}
				if (i > game_map.max_y) {
					game_map.max_y = i;
				}
			}
            
        }
    }
    //de dam bao doi tuong khong vuot qua kich thuoc cua map
    game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

    game_map.start_x = 0;
	game_map.start_y = 0;

	game_map.file_name = name;
	fclose(fp);
}

//load assets
void GameMap::LoadTiles(SDL_Renderer* screen) {
	// string file_img = "../assets/img/blocks/block.png";
    char file_img[100];
	FILE* fp = NULL;
    for(int i = 1; i <= MAX_TILES; i++){
        snprintf(file_img, sizeof(file_img), "./map/block%d.png", i); //luu gtri cua i vao 
        // file_img.insert(25,to_string(i));
        //cuoi chuoi "...", ket qua chuyen vao file_img
        fp = fopen(file_img, "rb");
            if (fp == NULL)
            {
            // Xử lý lỗi
            // cout << "khong tim thay file block: " << file_img << endl;
            continue;
            }
        fclose(fp);

        tile_map[i].LoadImage(file_img, screen);
    }
}

//fill images into position
void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    
    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/TILE_SIZE;
    //tra ve k/c tu diem bat dau ben trai den diem kt ben phai cua o vuong
    x1 = (game_map.start_x % TILE_SIZE)* -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE); //dam bao screen dc fill day du

    map_y = game_map.start_y/TILE_SIZE;
    y1 = (game_map.start_y % TILE_SIZE)* -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {   
        map_x = game_map.start_x/TILE_SIZE; //map_x là ô thứ bao nhiêu - chỉ số của ô
        for(int j = x1; j < x2; j += TILE_SIZE){
            int val = game_map.tile[map_y][map_x];
            if(val > 0)
            {
                tile_map[val].SetRect(j, i);
                tile_map[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }

}