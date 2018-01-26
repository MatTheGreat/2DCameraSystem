#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

class RenderObject
{
public:
	RenderObject();
	~RenderObject();

	SDL_Texture* texture;

	SDL_Rect rect;

	RenderObject(int x, int y, const char * fileLocation, SDL_Renderer* renderer);

	double rotation;

private:

};

