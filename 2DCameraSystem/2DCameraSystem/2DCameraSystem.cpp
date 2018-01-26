#include "2DCameraSystem.h"

CameraSystem::CameraSystem()
{
	camera = new SDL_Rect();
	camera->x = 0;
	camera->y = 0;
	m_zooming = true;
	m_zoom = 1;
	camera->w = 1600;
	camera->h = 900;
	worldSizeX = 3200;
	worldSizeY = 1800;
	trackingObject = false;
	trackingIndex = 0;
	trackingPosition = SDL_Point();
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::Renderer()
{
	
	for (int i = 0; i < renderObjects.size(); i++) 
	{ 
		SDL_Rect* temp = new SDL_Rect();
		temp = &renderObjects.at(i)->rect;

		SDL_Point* center = new SDL_Point();
		center->x = temp->w/2;
		center->y = temp->h/2;

		SDL_RendererFlip flip = SDL_FLIP_NONE;

		if (m_zooming == true)
		{
			ZoomObject(temp);
		}

		SDL_RenderCopyEx(renderer, renderObjects.at(i)->texture, NULL, temp, (double)renderObjects.at(i)->rotation, center, flip);
	}
	ObjectTracking();
	m_zooming = false;
}

void CameraSystem::AddRenderObject(RenderObject* renderObject)
{
	renderObjects.push_back(renderObject);
}

void CameraSystem::PanCamera(int panX, int panY)
{
	for (int i = 0; i < renderObjects.size(); i++)
	{
		renderObjects.at(i)->rect.x += panX;
		renderObjects.at(i)->rect.y += panY;
	}
	camera->x += panX;
	camera->y += panX;
}

//void CameraSystem::RotateCamera(float rotation)
//{
//	for (int i = 0; i < renderObjects.size(); i++)
//	{
//		renderObjects.at(i)->rotation += rotation;
//	}
//}

void CameraSystem::ZoomCamera(float ZoomMultiplyer)
{
	m_zoom = ZoomMultiplyer;
	m_zooming = true;
}

void CameraSystem::ZoomToFit()
{
	if (worldSizeX > worldSizeY)
	{
		ZoomCamera(1/(worldSizeX / camera->w));
	}
	else
	{
		ZoomCamera(1/(worldSizeY / camera->h));
	}
}

void CameraSystem::ZoomObject(SDL_Rect * rect)
{
	rect->x = rect->x*m_zoom;
	rect->y = rect->y*m_zoom;
	rect->w = rect->w*m_zoom;
	rect->h = rect->h*m_zoom;
}

void CameraSystem::ObjectTracking()
{
	if (trackingObject == true)
	{
		SDL_Point objectPosition = SDL_Point();
		objectPosition.x = renderObjects.at(trackingIndex)->rect.x;
		objectPosition.y = renderObjects.at(trackingIndex)->rect.y;
		if (trackingPosition.x != objectPosition.x || trackingPosition.y != objectPosition.y)
		{
			PanCamera((trackingPosition.x-objectPosition.x)+(camera->w/2), (trackingPosition.y - objectPosition.y) + (camera->h / 2));
		}
	}
}

void CameraSystem::SetObjectToBeTracked(int index)
{
	trackingIndex = index;
}
