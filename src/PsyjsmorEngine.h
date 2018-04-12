#pragma once
#include "header.h"
#include "templates.h"
#include "BaseEngine.h"
#include "TileManager.h"
#include "PsyjsmorTileManager.h"
#include <string>

class PsyjsmorPlayer;
class PsyjsmorApple;
class PsyjsmorApples;

class PsyjsmorEngine :
	public BaseEngine
{
protected:
	PsyjsmorPlayer* m_pPlayer;
	PsyjsmorApple* m_pApple;
	PsyjsmorApples* m_pApples;

public:
	PsyjsmorEngine();
	~PsyjsmorEngine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void GameAction();
	void UnDrawStrings();
	void DrawStringsUnderneath();
	void DrawStringsOnTop();
	void MouseDown(int, int, int);
	virtual void KeyDown(int iKeyCode);
	PsyjsmorTileManager& GetTileManager() { return m_oTiles; }

	ImageData pauseMenu;
	int points = 0;
	int stageTime[3] = { 44, 44, 44 };
	int timeLimit;
	int stagePoints[3];
	int lost = 0;
	int state = 1; // 0 end state, 1 game ongoing
	int stage = 1;
	int stageBuf;
	int lives = 3;
	int pause = 0;
	SDL_Window* window = this->m_pSDL2Window;

private:
	PsyjsmorTileManager m_oTiles;
	std::string tiles1[14];
	std::string tiles2[14];
	std::string tiles3[14];
};
