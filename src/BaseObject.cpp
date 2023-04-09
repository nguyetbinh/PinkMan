#include "BaseObject.h"
//dinh nghia ham tao
BaseObject::BaseObject()
{ //ban dau chưa có gì cả 
    texture = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
//dinh nghia ham huy
BaseObject::~BaseObject()
{
    Free();
}
bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = NULL;
    load_surface = IMG_Load(path.c_str());
    if (load_surface == NULL) {
        cout << IMG_GetError() << endl;
    }
    else
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface); //luu giu toan bo thong tin cua tam anh
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        //khi load thanh cong thi ta se gan cac thong so cho BaseObject 
        SDL_FreeSurface(load_surface);
    }
    
    texture = new_texture;
    return texture != NULL;
    //sau cac buoc nay thì đối tượng BaseObject sẽ có được thông tin của rect và texture của tấm ảnh
}

//dinh nghia ham render
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h}; //vi tri va kich thuoc tam anh
    SDL_RenderCopy(des, texture, clip, &renderquad); //ham nay co nvu day toan bo thong so cua tex va renderquad len des
}

void BaseObject::Free()
{
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
  		texture = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}

