#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
    x = 0;
    y = 0; 
    x_pos = 332; 
    y_pos = 664;
    frame = 0;
    w_frame = 0;
    h_frame = 0;
    status = -1;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.stay_left = 0;
    input_type.stay_right = 0;
    on_ground = false;
};

PlayerObject::~PlayerObject()
{
    Free();
};

//để tái sử dụng mà ko cần viết lại => sd hàm ảo
bool PlayerObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool check = BaseObject::LoadImage(path, screen);
    
    if(check == true)
    {
        w_frame = 32;
        h_frame = 32;
        
    }
    return check;
}

void PlayerObject :: SetClips()
{
    if (w_frame > 0 && h_frame > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = w_frame;
        frame_clip_[0].h = h_frame;

        frame_clip_[1].x = w_frame;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = w_frame;
        frame_clip_[1].h = h_frame;

        frame_clip_[2].x = 2*w_frame;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = w_frame;
        frame_clip_[2].h = h_frame;

        frame_clip_[3].x = 3*w_frame;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = w_frame;
        frame_clip_[3].h = h_frame;

        frame_clip_[4].x = 4*w_frame;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = w_frame;
        frame_clip_[4].h = h_frame;

        frame_clip_[5].x = 5*w_frame;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = w_frame;
        frame_clip_[5].h = h_frame;

        frame_clip_[6].x = 6*w_frame;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = w_frame;
        frame_clip_[6].h = h_frame;

        frame_clip_[7].x = 7*w_frame;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = w_frame;
        frame_clip_[7].h = h_frame;

        frame_clip_[8].x = 8*w_frame;
        frame_clip_[8].y = 0;
        frame_clip_[8].w = w_frame;
        frame_clip_[8].h = h_frame;

        frame_clip_[9].x = 9*w_frame;
        frame_clip_[9].y = 0;
        frame_clip_[9].w = w_frame;
        frame_clip_[9].h = h_frame;

        frame_clip_[10].x = 10*w_frame;
        frame_clip_[10].y = 0;
        frame_clip_[10].w = w_frame;
        frame_clip_[10].h = h_frame;

        frame_clip_[11].x = 11*w_frame;
        frame_clip_[11].y = 0;
        frame_clip_[11].w = w_frame;
        frame_clip_[11].h = h_frame;

       

    }
}

//show player func
void PlayerObject::Show(SDL_Renderer* des)
{
    if(on_ground)
    {
    if (status == RUN_LEFT)
    {
        LoadImage("./assets/img/runleft.png", des);
    }
    else if (status == RUN_RIGHT)
    {
        LoadImage("./assets/img/runright.png", des);
    }
    }

    if(input_type.left == 1 || input_type.right == 1)
    {
        frame++;
    }
    else
    {   
        frame = 0;
    }
    
    if(frame/12 >= 12)
    {
        frame = 0;
    }

    rect_.x = x_pos;
    rect_.y = y_pos;

    SDL_Rect* current_clip = &frame_clip_[frame];

    SDL_Rect renderQuad = {rect_.x, rect_.y, w_frame, h_frame};

    SDL_RenderCopy(des, texture, current_clip, &renderQuad);

}

//xu li keyboard input
void PlayerObject::HandleEvent(SDL_Event event, SDL_Renderer* screen)
{
    if (event.type == SDL_KEYDOWN) 
    {
    switch (event.key.keysym.sym) {
    case SDLK_RIGHT:
        status = RUN_RIGHT;
        input_type.right = 1;
        input_type.left = 0;
        
        break;

    case SDLK_LEFT:
        status = RUN_LEFT;
        input_type.left = 1;
        input_type.right = 0;


        break;
    case SDLK_UP:
        if (on_ground) {

            input_type.jump = 1;
            input_type.stay_left = 0;
            input_type.stay_right = 0;
        }
        break;
    default:
        break;
    }
}

else if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
    case SDLK_RIGHT:
        status = STAY_RIGHT;
        if (on_ground == true) {
            input_type.stay_right = 1;
            input_type.right = 0;
            input_type.stay_left = 0;
        }
        input_type.right = 0;
        input_type.stay_left = 0;

        break;
    case SDLK_LEFT:
        status = STAY_LEFT;
        if (on_ground == true) {
            input_type.stay_left = 1;
            input_type.left = 0;
            input_type.stay_right = 0;
        }
        input_type.left = 0;
        input_type.stay_right = 0;

        break;
    default:
        break;
    }
	}

if(event.type == SDL_MOUSEBUTTONDOWN)
{
    if(event.button.button == SDL_BUTTON_RIGHT)
    {
        input_type.jump = 1;
    }
}
}

//manage movement
void PlayerObject::DoPlayer(Map& map_data)
{
    x = 0;
    y += GRAVITY_SPEED; //toc do roi

    if(y >= MAX_FALL_SPEED)
    {
        y = MAX_FALL_SPEED;
    }
    if(input_type.left == 1)
    {
        x -= PLAYER_SPEED;
    }
    else if(input_type.right == 1)
    {
        x += PLAYER_SPEED;
    }
    if(input_type.jump == 1)
    {
        if(on_ground == true)
        {
        y -= JUMP_VAL;
        }
        input_type.jump = 0;
    }
    CheckMap(map_data);
}

void PlayerObject::CheckMap(Map& map_data)
{   //gioi han ktra theo chieu x1 -> x2
    int x1 = 0;
    int x2 = 0; 

    int y1 = 0;
    int y2 = 0;

    //Check theo chieu ngang: nvat dang nam tu o thu bao nhieu den o thu bnhiu cua map
    int h_min = h_frame < TILE_SIZE ? h_frame : TILE_SIZE;

    x1 = (x_pos + x)/TILE_SIZE;
    x2 = (x_pos + x + w_frame - 1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + h_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_Y && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x > 0) //nvat dang sang phai
        {
            if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
            {
                x_pos = x2*TILE_SIZE; //dung tai vi tri va cham
                x_pos -= w_frame + 1;
                x = 0;
            }
        }
        else if(x < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
            {
                x_pos = (x1 + 1)*TILE_SIZE;
                x = 0;
            }
        }
    }

    int w_min = w_frame < TILE_SIZE ? w_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + w_min)/TILE_SIZE;

    y1 = (y_pos + y)/TILE_SIZE;
    y2 = (y_pos + y + h_frame - 1)/TILE_SIZE;

     if(x1 >= 0 && x2 < MAX_MAP_Y && y1 >= 0 && y2 < MAX_MAP_Y)
     {
        if(y > 0)
        {
            if(map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= (h_frame + 1);
                y = 0;
                on_ground = true;
            }
        }
        else if(y < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y = 0;
            }
        }
     }

     x_pos += x;
     y_pos += y;

     if(x_pos < 0)
     {
        x_pos = 0;
     }
     else if(x_pos + w_frame > map_data.max_x)
     {
        x_pos = map_data.max_x - w_frame - 1;
     }
};
     //Update the player's status
void PlayerObject::UpdateImgPlayer(SDL_Renderer* des) {
	if (on_ground) {
		if (input_type.left==1) {
			LoadImage("assets/img/runleft.png", des);
		}
		else if (input_type.right==1) {
			LoadImage("assets/img/runright.png", des);
		}
		else if (status == STAY_LEFT && input_type.jump == 0&&input_type.left==0&&input_type.right==0) {
			LoadImage("assets/img/idle_left.png",des);
		}
		else if (status == STAY_RIGHT && input_type.jump == 0 && input_type.left == 0 && input_type.right == 0) {
			LoadImage("assets/img/idle_right.png",des);
		}

	}
	else {
		if (input_type.left == 1) {
		LoadImage("assets/jump.png", des);
		}
		else if (input_type.right == 1) {
		LoadImage("assets/jump.png", des);
		}
	}
};





        




