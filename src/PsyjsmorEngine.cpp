
#include "PsyjsmorEngine.h"
#include "PsyjsmorPlayer.h"
#include "PsyjsmorApple.h"
#include "JPGImage.h"
#include <fstream>
#include <sstream>

PsyjsmorEngine::PsyjsmorEngine()
{
}

PsyjsmorEngine::~PsyjsmorEngine()
{
}

void PsyjsmorEngine::SetupBackgroundBuffer()
{
	FillBackground(0x71aa7e);
	//DrawBackgroundRectangle(0, 0, GetWindowWidth() - 1, 39, 0x44714e);

	// TileManager Grid to determine border/obstacles
	std::ifstream level1;
	level1.open("level1.txt");
	std::string line;

	for (int i = 0; i < 14; i++)
	{
		level1 >> tiles1[i];
	}
	level1.close();

	std::ifstream level2;
	level2.open("level2.txt");

	for (int i = 0; i < 14; i++)
	{
		level2 >> tiles2[i];
	}
	level2.close();

	std::ifstream level3;
	level3.open("level3.txt");

	for (int i = 0; i < 14; i++)
	{
		level3 >> tiles3[i];
	}
	level3.close();

	// Specify how many tiles wide and high the grid is
	m_oTiles.SetSize(20, 14);
	// Assign each tile a value
	for (int x = 0; x < 20; x++)
		for (int y = 0; y < 14; y++)
			m_oTiles.SetValue(x, y, tiles1[y][x]);
	// Print each tile's value
	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 20; x++)
			printf("%d ", m_oTiles.GetValue(x, y));
		printf("\n");
	}
	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen(0, 40);
	// Draw all tiles from x1,y1 to x2,y2
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 19, 13);
}

int PsyjsmorEngine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get 
	// used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();
	// Set time limit depending on stage
	timeLimit = stageTime[stage - 1];
	// Load pause menu image
	pauseMenu.LoadImage("pause.png");
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(4);

	// You MUST set the array entry after the last one that you create to NULL, so 
	// that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in 
	// order to work out where the end of the array is.
	m_pPlayer = new PsyjsmorPlayer(this, 9, 5); // x <= 17, y <= 11
	m_pApple = new PsyjsmorApple(this, m_pPlayer);
	m_pApples = new PsyjsmorApples(this, m_pPlayer);

	StoreObjectInArray(0, m_pApple);
	StoreObjectInArray(1, m_pApples);
	StoreObjectInArray(2, m_pPlayer);
	StoreObjectInArray(3, NULL);

	return 0;
}

void PsyjsmorEngine::GameAction()
{
	if (lost && lives == 0)
	{
		stage = 1;
		lives = 3;
	}
	// If too early to act then do nothing
	if (!IsTimeToAct())
		return;
	// Reduce Cooldown if active
	if (m_pPlayer->currCooldown >= 0 && pause == 0)
		m_pPlayer->currCooldown = m_pPlayer->currCooldown - 1;
	// Reduce timelimit of level
	if (timeLimit > 0 && pause == 0)
		timeLimit = timeLimit - 1;
	// Reduce food timer
	if (m_pApple->currTimer > 0 && pause == 0 && state == 1)
		m_pApple->currTimer--;
	if (m_pApples->currTimer > 0 && pause == 0 && state == 1)
		m_pApples->currTimer--;
	// Don't act for another 250 ticks
	SetTimeToAct(250);

	UpdateAllObjects(GetTime());

	if (timeLimit == 0 && IsKeyPressed(SDLK_SPACE))
	{
		timeLimit = stageTime[stage - 1];
		if (stage == 1)
			lives = 3;
	}

	stagePoints[stage - 1] = points;

	if (stage == 1)
	{
		for (int x = 0; x < 20; x++)
			for (int y = 0; y < 14; y++)
				m_oTiles.SetValue(x, y, tiles1[y][x]);
	}
	else if (stage == 2)
	{
		for (int x = 0; x < 20; x++)
			for (int y = 0; y < 14; y++)
				m_oTiles.SetValue(x, y, tiles2[y][x]);
	}
	else if (stage == 3)
	{
		for (int x = 0; x < 20; x++)
			for (int y = 0; y < 14; y++)
				m_oTiles.SetValue(x, y, tiles3[y][x]);
	}
	// Draw an image loaded from a file.
	ImageData img;
	// Load the image file into an image object - at the normal size
	img.LoadImage("grass.jpg");

	if (img.IsLoaded())
	{
		img.RenderImage(
			this->GetBackground(),
			0, 0,
			0, 0,
			GetWindowWidth() - 1, GetWindowHeight() - 1
		);
	}

	ImageData header;
	header.LoadImage("header.png");

	if (header.IsLoaded())
	{
		header.RenderImageWithMask(
			this->GetBackground(),
			0, 0,
			0, 0,
			header.GetWidth(), header.GetHeight()
		);
	}

	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 19, 13);

	if (pause && pauseMenu.IsLoaded())
	{
		pauseMenu.RenderImageWithMask(
			this->GetBackground(),
			0, 0,
			(GetWindowWidth() / 2) - (pauseMenu.GetWidth() / 2),
			(GetWindowHeight() / 2) - (pauseMenu.GetHeight() / 2),
			pauseMenu.GetWidth(), pauseMenu.GetHeight()
		);
	}
}

void PsyjsmorEngine::UnDrawStrings()
{
	CopyBackgroundPixels(0, 0, GetWindowWidth(), GetWindowHeight());
}

void PsyjsmorEngine::DrawStringsUnderneath()
{
	if (m_pPlayer->currCooldown >= 0)
	{
		char buf[64];
		sprintf(buf, "%d", (int)m_pPlayer->currCooldown/4);
		DrawForegroundString(340, 530, "Cooldown:", 0xFFFFFF, NULL);
		DrawForegroundString(460, 530, buf, 0xFFFFFF, NULL);
	}
}

void PsyjsmorEngine::DrawStringsOnTop()
{
	char buf[64];
	sprintf(buf, "%d", points);
	DrawForegroundString(40, 10, "Points:", 0xFFFFFF, NULL);
	DrawForegroundString(140, 10, buf, 0xFFFFFF, NULL);
	sprintf(buf, "%d", (int)timeLimit / 4);
	DrawForegroundString(660, 10, "Time:", 0xFFFFFF, NULL);
	DrawForegroundString(740, 10, buf, 0xFFFFFF, NULL);
	sprintf(buf, "%d", stage);
	DrawForegroundString(340, 10, "Level:", 0xFFFFFF, NULL);
	DrawForegroundString(430, 10, buf, 0xFFFFFF, NULL);

	if (timeLimit == 0)
	{
		m_pApple->currTimer = m_pApple->timer;
		m_pApples->used = 0;
		m_pApples->currTimer = 0;

		if (stage == 3)
		{
			printf("\nLevel 1: %d, Level 2: %d, Level 3: %d\n", stagePoints[0], stagePoints[1], stagePoints[2]);
			m_pPlayer->currCooldown = -1;
			state = 0;
			stage = 1;
			lives = 3;
			char buf[64];
			sprintf(buf, "%d", points);
			DrawForegroundString(300, 280, "Congratulations!", 0xFFFFFF, NULL);
			if (points < 10)
				DrawForegroundString(135, 303, "You have completed the game with   points!", 0xFFFFFF, NULL);
			else
				DrawForegroundString(135, 303, "You have completed the game with    points!", 0xFFFFFF, NULL);
			DrawForegroundString(563, 303, buf, 0xFFFFFF, NULL);
			DrawForegroundString(165, 326, "Press SPACE to restart or ESC to exit.", 0xFFFFFF, NULL);
		}
		else
		{
			m_pPlayer->currCooldown = -1;
			state = 0;
			stage++;
			char buf[64];
			sprintf(buf, "%d", points);
			if (points < 10)
				DrawForegroundString(160, 295, "You have passed the level with   points!", 0xFFFFFF, NULL);
			else
				DrawForegroundString(160, 295, "You have passed the level with    points!", 0xFFFFFF, NULL);
			DrawForegroundString(563, 295, buf, 0xFFFFFF, NULL);
			DrawForegroundString(250, 318, "Press SPACE to progress.", 0xFFFFFF, NULL);
		}
	}
	else if (lost && lives == 1 && IsKeyPressed(SDLK_SPACE))
	{
		stage = 1;
		m_pApple->currTimer = m_pApple->timer;
		m_pApples->used = 0;
		m_pApples->currTimer = 0;
	}
	else if (lost && lives == 1)
	{
		lives--;
		DrawForegroundString(245, 295, "Unlucky! You have died!", 0xFFFFFF, NULL);
		DrawForegroundString(215, 318, "Press SPACE to restart game.", 0xFFFFFF, NULL);
	}
	else if (lost)
	{
		lives--;
		DrawForegroundString(215, 295, "Unlucky! You have lost a life!", 0xFFFFFF, NULL);
		DrawForegroundString(265, 318, "Press SPACE to revive.", 0xFFFFFF, NULL);
	}

	if (pause)
	{
		if (!pauseMenu.IsLoaded())
		{
			DrawForegroundString(360, 295, "PAUSED!", 0xFFFFFF, NULL);
			DrawForegroundString(130, 318, "Press Q to quit or ESC to continue playing.", 0xFFFFFF, NULL);
		}
	}
}

void PsyjsmorEngine::MouseDown(int iButton, int iX, int iY)
{
	if (iButton == 1 && m_pPlayer->currCooldown <= 0 && iY > 100 && pause == 0)
		m_pPlayer->SetPosition(iX, iY);

	printf("%d, %d", m_pApples->currTimer, m_pApples->used);

	if (iButton == 3 && m_pApples->currTimer == 0 && m_pApples->used == 0 && state == 1)
	{
		printf("time %d vis %d", m_pApples->currTimer, m_pApples->visible);
		m_pApples->visible = 1;
		m_pApples->currTimer = m_pApples->timer;
	}
}

void PsyjsmorEngine::KeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_q:
		if (pause)
		{
			SetExitWithCode(0);
			break;
		}
		else
			break;
	case SDLK_ESCAPE:
		if (stage == 1 && timeLimit == 0)
		{
			SetExitWithCode(0);
			break;
		}
		
		if (pause)
			pause = 0;
		else
			pause = 1;

		break;
	}
}
