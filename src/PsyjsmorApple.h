#pragma once
#include "header.h"
#include "templates.h"
#include "PsyjsmorPlayer.h"
#include "PsyjsmorEngine.h"
#include "DisplayableObject.h"
#include "PsyjsmorTileManager.h"
class PsyjsmorApple :
	public DisplayableObject
{
public:
	PsyjsmorApple(PsyjsmorEngine*, PsyjsmorPlayer*);
	~PsyjsmorApple();
	void Draw();
	void DoUpdate(int);

	int timer;
	int currTimer;

private:
	PsyjsmorEngine* m_pMainEngine;
	PsyjsmorPlayer* m_pPlayer;
	PsyjsmorTileManager& m_oTiles = m_pMainEngine->GetTileManager();
	ImageData apple;

	int appleWidth;
	int appleHeight;
	int playerPosX;
	int playerPosY;
	int iSize = 10;
};

class PsyjsmorApples :
	public PsyjsmorApple
{
public:
	PsyjsmorApples(PsyjsmorEngine*, PsyjsmorPlayer*);
	~PsyjsmorApples();
	void Draw();
	void DoUpdate(int);

	int timer;
	int currTimer;
	int visible;
	int used;

private:
	PsyjsmorEngine * m_pMainEngine;
	PsyjsmorPlayer* m_pPlayer;
	PsyjsmorTileManager& m_oTiles = m_pMainEngine->GetTileManager();
	ImageData apple;

	int appleWidth;
	int appleHeight;
	int playerPosX;
	int playerPosY;
	int iSize = 10;
};
