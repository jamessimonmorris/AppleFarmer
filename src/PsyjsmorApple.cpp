
#include "PsyjsmorApple.h"

PsyjsmorApple::PsyjsmorApple(PsyjsmorEngine* pEngine, PsyjsmorPlayer* pPlayer)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_pPlayer(pPlayer)
	, playerPosX(pPlayer->GetXCentre())
	, playerPosY(pPlayer->GetYCentre())
	, timer(11)
	, currTimer(0)
{
	// Food coords will be at centre
	m_iStartDrawPosX = m_iStartDrawPosY = -(iSize / 2);
	// Record food size
	m_iDrawHeight = m_iDrawWidth = iSize;
	// Food coords placed randomly
	do
	{
		m_iCurrentScreenX = m_iPreviousScreenX = (rand() % 20) * 40 + 20;
		m_iCurrentScreenY = m_iPreviousScreenY = (rand() % 14) * 40 + 60;
	} while (m_iCurrentScreenX == 9 && m_iCurrentScreenY == 5);
	// Load apple
	apple.LoadImage("apple.png");
	appleWidth = apple.GetWidth();
	appleHeight = apple.GetHeight();
	// Make it visible
	SetVisible(true);
}

PsyjsmorApple::~PsyjsmorApple()
{
}

void PsyjsmorApple::Draw()
{
	if (m_pMainEngine->timeLimit >= 0)
	{
		if (apple.IsLoaded())
		{
			apple.RenderImageWithMask(
				m_pMainEngine->GetSDLSurface(),
				0, 0,
				m_iCurrentScreenX - (appleWidth / 2),
				m_iCurrentScreenY - (appleHeight / 2),
				21, 26
			);
		}
		else
		{
			m_pMainEngine->DrawForegroundOval(
				m_iCurrentScreenX - iSize,
				m_iCurrentScreenY - iSize,
				m_iCurrentScreenX + iSize - 1,
				m_iCurrentScreenY + iSize - 1,
				0x000000
			);

			m_pMainEngine->DrawForegroundOval(
				m_iCurrentScreenX - iSize + 2,
				m_iCurrentScreenY - iSize + 2,
				m_iCurrentScreenX + iSize - 3,
				m_iCurrentScreenY + iSize - 3,
				0xFF0000
			);
		}

		char buf[8];
		sprintf(buf, "%d", currTimer / 4);
		if (m_pMainEngine->stage > 1)
			GetEngine()->DrawForegroundString(m_iCurrentScreenX - 6, m_iCurrentScreenY - 6, buf, 0xFFFFFF);

		StoreLastScreenPositionForUndraw();
	}
}

void PsyjsmorApple::DoUpdate(int iCurrentTime)
{
	if (m_pMainEngine->state)
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		playerPosX = m_pPlayer->GetXCentre();
		playerPosY = m_pPlayer->GetYCentre();

		if ((playerPosX == m_iCurrentScreenX && playerPosY == m_iCurrentScreenY) || (m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) == 120) || (currTimer == 0 && m_pMainEngine->stage > 1))
		{
			if ((m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) != 120) && !(currTimer == 0 && m_pMainEngine->stage > 1))
				m_pMainEngine->points++;

			currTimer = timer;

			do
			{
				m_iCurrentScreenX = (rand() % 17) * 40 + 20;
				m_iCurrentScreenY = (rand() % 11) * 40 + 60;
			} while ((m_iCurrentScreenX == m_iPreviousScreenX && m_iCurrentScreenY == m_iPreviousScreenY) || (m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) == 120));
		}

		printf("Player: %d, %d - Food: %d, %d\n", playerPosX, playerPosY, m_iCurrentScreenX, m_iCurrentScreenY);

		RedrawObjects();
	}
}

PsyjsmorApples::PsyjsmorApples(PsyjsmorEngine* pEngine, PsyjsmorPlayer* pPlayer)
	: PsyjsmorApple(pEngine, pPlayer)
	, m_pMainEngine(pEngine)
	, m_pPlayer(pPlayer)
	, playerPosX(pPlayer->GetXCentre())
	, playerPosY(pPlayer->GetYCentre())
	, timer(27)
	, currTimer(0)
	, visible(0)
	, used(0)
{
	// Food coords will be at centre
	m_iStartDrawPosX = m_iStartDrawPosY = -(iSize / 2);
	// Record food size
	m_iDrawHeight = m_iDrawWidth = iSize;
	// Food coords placed randomly
	do
	{
		m_iCurrentScreenX = m_iPreviousScreenX = (rand() % 20) * 40 + 20;
		m_iCurrentScreenY = m_iPreviousScreenY = (rand() % 14) * 40 + 60;
	} while (m_iCurrentScreenX == 9 && m_iCurrentScreenY == 5);
	// Load apples
	apple.LoadImage("apples.png");
	appleWidth = apple.GetWidth();
	appleHeight = apple.GetHeight();
	// Make it visible
	SetVisible(true);
}

PsyjsmorApples::~PsyjsmorApples()
{
}

void PsyjsmorApples::Draw()
{
	if (m_pMainEngine->timeLimit > 0 && visible)
	{
		if (apple.IsLoaded())
		{
			apple.RenderImageWithMask(
				m_pMainEngine->GetSDLSurface(),
				0, 0,
				m_iCurrentScreenX - (appleWidth / 2),
				m_iCurrentScreenY - (appleHeight / 2),
				appleWidth, appleHeight
			);
		}
		else
		{
			m_pMainEngine->DrawForegroundOval(
				m_iCurrentScreenX - iSize,
				m_iCurrentScreenY - iSize,
				m_iCurrentScreenX + iSize - 1,
				m_iCurrentScreenY + iSize - 1,
				0x000000
			);

			m_pMainEngine->DrawForegroundOval(
				m_iCurrentScreenX - iSize + 2,
				m_iCurrentScreenY - iSize + 2,
				m_iCurrentScreenX + iSize - 3,
				m_iCurrentScreenY + iSize - 3,
				0xFF0000
			);
		}

		char buf[8];
		sprintf(buf, "%d", currTimer / 4);
		GetEngine()->DrawForegroundString(m_iCurrentScreenX - 6, m_iCurrentScreenY - 6, buf, 0xFFFFFF);

		StoreLastScreenPositionForUndraw();
	}
}

void PsyjsmorApples::DoUpdate(int iCurrentTime)
{
	if (visible)
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		playerPosX = m_pPlayer->GetXCentre();
		playerPosY = m_pPlayer->GetYCentre();

		if ((playerPosX == m_iCurrentScreenX && playerPosY == m_iCurrentScreenY) || (m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) == 120) || currTimer == 0 || m_pMainEngine->timeLimit == 0)
		{
			if ((playerPosX == m_iCurrentScreenX && playerPosY == m_iCurrentScreenY) || currTimer == 0 || m_pMainEngine->timeLimit == 0)
			{
				visible = 0;
				used = 1;
			}

			if ((m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) != 120) && currTimer != 0)
				m_pMainEngine->points+=3;

			currTimer = timer;

			do
			{
				m_iCurrentScreenX = (rand() % 17) * 40 + 20;
				m_iCurrentScreenY = (rand() % 11) * 40 + 60;
			} while ((m_iCurrentScreenX == m_iPreviousScreenX && m_iCurrentScreenY == m_iPreviousScreenY) || (m_oTiles.GetValue((m_iCurrentScreenX - 20) / 40, (m_iCurrentScreenY - 60) / 40) == 120));
		}

		printf("Player: %d, %d - Food: %d, %d\n", playerPosX, playerPosY, m_iCurrentScreenX, m_iCurrentScreenY);

		RedrawObjects();
	}
}