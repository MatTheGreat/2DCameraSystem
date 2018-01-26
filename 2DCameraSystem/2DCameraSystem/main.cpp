#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#undef main
#include "2DCameraSystem.h"

int main()
{
	SDL_Window* window;
	window = SDL_CreateWindow("Camera Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);

	
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	RenderObject * Background = new RenderObject(0, 0, "Resources/Background.png", renderer);
	RenderObject * Background2 = new RenderObject(1600, 900, "Resources/Background2.png", renderer);
	RenderObject * testObject = new RenderObject(100, 100, "Resources/Test.png", renderer);
	
	RenderObject * testObject2 = new RenderObject(800, 800, "Resources/Test.png", renderer);

	CameraSystem m_camera = CameraSystem(1600, 900, 3200, 1800, renderer);

	m_camera.AddRenderObject(Background);
	m_camera.AddRenderObject(Background2);
	m_camera.AddRenderObject(testObject);
	m_camera.AddRenderObject(testObject2);


	//The amount the user want to pan the camera by in the X-axis
	int panX = 20;
	//The amount the user wants to pan the camera by in the Y-axis
	int panY = 20;

	bool running = true;
	SDL_Event e;
	while (running == true)
	{
		testObject2->rect.x++;
		//Handle events on queue
		while (SDL_PollEvent(&e))
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_camera.PanCamera(-panX, 0);
				break;
			case SDLK_RIGHT:
				m_camera.PanCamera(panX, 0);
				break;
			case SDLK_UP:
				m_camera.PanCamera(0, -panY);
				break;
			case SDLK_DOWN:
				m_camera.PanCamera(0, panY);
				break;
			case SDLK_b:
				m_camera.SetObjectToBeTracked(3);
				m_camera.m_trackingObject = true;
				break;
			default:
				break;
			}
		}



		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		//Draw Objects
		m_camera.Renderer();


		SDL_RenderPresent(renderer);

	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return 0;
}