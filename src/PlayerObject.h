#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define JUMP_VAL 7
class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    enum WalkType {
		RUN_RIGHT = 0,
		RUN_LEFT = 1,
		STAY_LEFT = 2,
		STAY_RIGHT = 3,
		JUMP = 4,
	};

    bool LoadImage(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleEvent(SDL_Event event, SDL_Renderer* screen);
    void SetClips(); //xu li animation
    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    void UpdateImgPlayer(SDL_Renderer* des);
private: 
    float x;
    float y;
    
    float x_pos; //vi tri hien tai
    float y_pos;
    
    int w_frame;
    int h_frame;

    SDL_Rect frame_clip_[12];
    Input input_type; //bien luu trang thai
    int frame; //bien luu chi so cua frame
    int status; //luu trang thai

    bool on_ground;

};
#endif