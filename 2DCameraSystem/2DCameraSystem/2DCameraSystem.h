#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "2DRenderObject.h"

class CameraSystem
{
public:
	CameraSystem();
	~CameraSystem();

	void Renderer();

	void CameraSystem::AddRenderObject(RenderObject* renderObject);

	void CameraSystem::PanCamera(int panX, int panY);

	//void CameraSystem::RotateCamera(float rotation);

	void CameraSystem::ZoomCamera(float ZoomMultiplyer);

	void CameraSystem::ZoomToFit();

	void CameraSystem::ObjectTracking();

	void CameraSystem::SetObjectToBeTracked(int index);

	//SDL Renderer
	SDL_Renderer * renderer;

	//Vector of render objects
	std::vector<RenderObject*> renderObjects;

	//Camera
	SDL_Rect* camera;

	//zoom amount
	float m_zoom;

	//Is zooming in
	bool m_zooming;

	//World Size
	float worldSizeX;
	float worldSizeY;

	bool trackingObject;

	SDL_Point trackingPosition;

	int trackingIndex;

private:

	void CameraSystem::ZoomObject(SDL_Rect* rect);

};

