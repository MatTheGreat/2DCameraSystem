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

	CameraSystem(float viewportSizeX, float viewportSizeY, float worldSizeX, float worldSizeY, SDL_Renderer * renderer);

	~CameraSystem();

	//Draws RenderObjects
	void Renderer();

	//Adds a RenderObject to m_renderObjects
	void CameraSystem::AddRenderObject(RenderObject* renderObject);

	//Pans the camera by the specified amount on x and y axis.
	void CameraSystem::PanCamera(int panX, int panY);

	//Changes the zoom by percentage specified with 1 being 100% zoom.
	void CameraSystem::ZoomCamera(float ZoomMultiplyer);

	//Sets the zoom to fit the entire world based on world size
	void CameraSystem::ZoomToFit();

	//Has the camera track an object
	void CameraSystem::ObjectTracking();

	//Sets Object to be tracked based on index in m_renderObjects
	void CameraSystem::SetObjectToBeTracked(int index);

	//Sets World Size
	void SetWorldSize(float worldSizeX, float worldSizeY);

	//Vector of render objects
	std::vector<RenderObject*> m_renderObjects;

	//Holds information to do with the Camera's position and size
	SDL_Rect* m_camera;

	//World Size on x-axis
	float m_worldSizeX;

	//World Size on y-axis
	float m_worldSizeY;

	//Is the camera tracking an object
	bool m_trackingObject;

	//The last known position of the tracked object
	SDL_Point m_trackingPosition;

	//The index position in m_renderObjects of the object being tracked
	int m_trackingIndex;

protected:

	//Method that changes a SDL_Rect in order to take into account the zoom level
	void CameraSystem::ZoomObject(SDL_Rect* rect);

	//Pointer to SDL Renderer
	SDL_Renderer * m_renderer;

	//zoom amount
	float m_zoom;

	//Is zooming in
	bool m_zooming;

};

