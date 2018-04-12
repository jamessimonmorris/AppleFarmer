
#include "PsyjsmorTileManager.h"

PsyjsmorTileManager::PsyjsmorTileManager()
	: TileManager(40,40)
{
}

PsyjsmorTileManager::~PsyjsmorTileManager()
{
}

void PsyjsmorTileManager::DrawTileAt(
	BaseEngine * pEngine, 
	SDL_Surface * pSurface, 
	int iMapX, int iMapY, 
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	if (GetValue(iMapX, iMapY) == 120)
	{
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX + 3,
			iStartPositionScreenY + 3,
			iStartPositionScreenX + GetTileWidth() - 3,
			iStartPositionScreenY + GetTileHeight() - 3,
			0x000000);
		
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX + 7,
			iStartPositionScreenY + 7,
			iStartPositionScreenX + GetTileWidth() - 7,
			iStartPositionScreenY + GetTileHeight() - 7,
			0xEADFB2);
		ImageData border;

		border.LoadImage("border.jpg");

		if (border.IsLoaded())
		{
			border.RenderImage(
				pSurface,
				0, 0,
				iStartPositionScreenX + 4, iStartPositionScreenY + 4,
				GetTileWidth() - 8, GetTileHeight() - 8
			);
		}
	}
}
