#pragma once
#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "TileManager.h"
class PsyjsmorTileManager
	: public TileManager
{
public:
	PsyjsmorTileManager();
	~PsyjsmorTileManager();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};
