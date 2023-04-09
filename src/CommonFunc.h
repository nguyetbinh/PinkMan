#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<string>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<bits/stdc++.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 25; //1s chạy dc 25 fr
const int SCREEN_WIDTH = 1760;
const int SCREEN_HEIGHT = 960;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 32 // lưu trữ kích thước của các ô vuông trên bản đồ.
#define MAX_MAP_X 55
#define MAX_MAP_Y 30
//có 400*10 = 4000 ô vuông

typedef struct Input
{
    int left;
    int right;
    int stay_left;
    int stay_right;
    int jump;
}Input;

typedef struct Map
{
    int start_x; //lưu trữ tọa độ x của điểm bắt đầu trên bản đồ.
    int start_y;

    int max_x;
    int max_y;
    //max x = start x / TILE_SIZE

    //dung mang 2 chieu de luu all trang thai cua cac o
    int tile[MAX_MAP_Y][MAX_MAP_X];
    const char* file_name;

    //=> Map la doi tuong du lieu cho 1 o
}Map;
#endif