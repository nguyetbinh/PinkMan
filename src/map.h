#ifndef MAP_H_
#define MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20
//baseob là ông cơ sở sử dụng cho tất cả các đối tượng, nên phải dùng kế thừa
class TileMap : public BaseObject
{
public:
    TileMap() {
		;
	}
	~TileMap() {
		;
	}

};
//xay dựng lớp quản lí đối tượng map

class GameMap
{
public:
    GameMap(){
        ;
    }
    ~GameMap(){
        ;
    }
    //ham doc toan bo thong tin trong file txt
    void LoadMap(const char* name);
    //ham load toan bo hinh anh
    void LoadTiles(SDL_Renderer* screen);
    //ham fill h/a vao cac vi tri
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {
		return game_map;
	}

private:
    Map game_map; //chua toan bo thong tin ve ban do
    TileMap tile_map[MAX_TILES]; //doi tuong luu giu hinh anh

};

#endif