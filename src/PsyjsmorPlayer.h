#pragma once
#include "header.h"
#include "templates.h"
#include "PsyjsmorEngine.h"
#include "MovementPosition.h"
#include "DisplayableObject.h"
class PsyjsmorPlayer :
	public DisplayableObject
{
public:
	PsyjsmorPlayer(PsyjsmorEngine*, int, int);
	~PsyjsmorPlayer();
	void Draw();
	void DoUpdate(int);
	void SetPosition(int, int);
	double currCooldown;

private:
	PsyjsmorEngine* m_pMainEngine;
	PsyjsmorTileManager& m_oTiles = m_pMainEngine->GetTileManager();
	ImageData farmer;

	int farmerWidth;
	int farmerHeight;
	int m_iMapX;
	int m_iMapY;
	int m_iDirX;
	int m_iDirY;
	int cooldown;
	int iTick;
};
