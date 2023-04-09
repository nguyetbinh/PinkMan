#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"
using namespace std;
class BaseObject
{
public: //phuong thuc - methods
    //ham tao
    BaseObject();
    //ham huỷ
    ~BaseObject();
    //hàm set kích thước cho rect
    void SetRect(const int& x, const int& y){
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() const {return rect_;}
    //lay ra hinh anh
    SDL_Texture* GetTexture() const {return texture;}  

    //ham ao
    virtual bool LoadImage(string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();

protected: //object - doi tuong
    //biến lưu trữ các hình ảnh
    SDL_Texture* texture;
    //biến lưu kích thước các hình ảnh đó
    SDL_Rect rect_;

};

#endif