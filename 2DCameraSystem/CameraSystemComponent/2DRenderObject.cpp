#include "2DRenderObject.h"


RenderObject::RenderObject()
{
	
}

RenderObject::~RenderObject()
{

}

RenderObject::RenderObject(int x, int y, const char * fileLocation, SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, fileLocation); //load image from assets
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
