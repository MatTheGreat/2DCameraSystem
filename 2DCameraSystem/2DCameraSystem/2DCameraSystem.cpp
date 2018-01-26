#include "2DCameraSystem.h"

CameraSystem::CameraSystem()
{
	//Set up Camera
	m_camera = new SDL_Rect();
	m_camera->x = 0;
	m_camera->y = 0;
	m_camera->w = 1600;
	m_camera->h = 900;

	//Set Default Zoom Level
	m_zooming = false;
	m_zoom = 1;

	//Set World Size
	m_worldSizeX = 3200;
	m_worldSizeY = 1800;

	//Initilize variable for tracking
	m_trackingObject = false;
	m_trackingIndex = 0;
	m_trackingPosition = SDL_Point();
}

CameraSystem::CameraSystem(float viewportSizeX, float viewportSizeY, float worldSizeX, float worldSizeY, SDL_Renderer * renderer)
{
	//Set up Camera
	m_camera = new SDL_Rect();
	m_camera->x = 0;
	m_camera->y = 0;
	m_camera->w = viewportSizeX;
	m_camera->h = viewportSizeY;

	//Set Default Zoom Level
	m_zooming = false;
	m_zoom = 1;

	//Set World Size
	m_worldSizeX = worldSizeX;
	m_worldSizeY = worldSizeY;

	//Initilize variable for tracking
	m_trackingObject = false;
	m_trackingIndex = 0;
	m_trackingPosition = SDL_Point();

	m_renderer = renderer;
}

CameraSystem::~CameraSystem()
{

}

void CameraSystem::Renderer()
{
	
	for (int i = 0; i < m_renderObjects.size(); i++) 
	{ 
		//Get Render Object Rect
		SDL_Rect* renderingRect = new SDL_Rect();
		renderingRect = &m_renderObjects.at(i)->rect;

		//Get Center of Object
		SDL_Point* center = new SDL_Point();
		center->x = renderingRect->w/2;
		center->y = renderingRect->h/2;

		// If currently zooming change renderingRect to take into account the zoom level
		if (m_zooming == true)
		{
			ZoomObject(renderingRect);
		}

		//Draw Render Object
		SDL_RenderCopyEx(m_renderer, m_renderObjects.at(i)->texture, NULL, renderingRect, (double)m_renderObjects.at(i)->rotation, center, SDL_FLIP_NONE);
	}

	// Do Object Tracking if active
	ObjectTracking();

	//Stop Zooming
	m_zooming = false;
}

void CameraSystem::AddRenderObject(RenderObject* renderObject)
{
	m_renderObjects.push_back(renderObject);
}

void CameraSystem::PanCamera(int panX, int panY)
{
	//Change render object position to take into account pan
	for (int i = 0; i < m_renderObjects.size(); i++)
	{
		m_renderObjects.at(i)->rect.x -= panX;
		m_renderObjects.at(i)->rect.y -= panY;
	}
	
	// change camera position
	m_camera->x -= panX;
	m_camera->y -= panX;
}

void CameraSystem::ZoomCamera(float Zoom)
{
	//Sets zoom
	m_zoom = Zoom;

	//Sets zoom to be true
	m_zooming = true;
}

void CameraSystem::ZoomToFit()
{
	//Checks to see if worldSizeX or worldSizeY is bigger
	//Sets the zoom to fit the entire level based on that
	if (m_worldSizeX > m_worldSizeY)
	{
		ZoomCamera(1/(m_worldSizeX / m_camera->w));
	}
	else
	{
		ZoomCamera(1/(m_worldSizeY / m_camera->h));
	}
}

void CameraSystem::SetWorldSize(float worldSizeX, float worldSizeY)
{
	m_worldSizeX = worldSizeX;
	m_worldSizeY = worldSizeY;
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
	if (m_trackingObject == true)
	{

		//Get Position of object being tracked
		SDL_Point objectPosition = SDL_Point();
		objectPosition.x = m_renderObjects.at(m_trackingIndex)->rect.x;
		objectPosition.y = m_renderObjects.at(m_trackingIndex)->rect.y;

		//if m_trackingPosition isn't not equal to the position of the object being tracked 
		if (m_trackingPosition.x != objectPosition.x || m_trackingPosition.y != objectPosition.y)
		{
			//Pan the camera based on the difference in position
			PanCamera((m_trackingPosition.x-objectPosition.x)+(m_camera->w/2), (m_trackingPosition.y - objectPosition.y) + (m_camera->h / 2));
		}
	}
}

void CameraSystem::SetObjectToBeTracked(int index)
{
	m_trackingIndex = index;
}
