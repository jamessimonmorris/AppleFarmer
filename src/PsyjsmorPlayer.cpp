
#include "PsyjsmorPlayer.h"

PsyjsmorPlayer::PsyjsmorPlayer(PsyjsmorEngine* pEngine, int iMapX, int iMapY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDirX(1)
	, m_iDirY(0)
	, cooldown(14)
	, currCooldown(-1)
{
	// Player coordinate will be centre of the ball
	m_iStartDrawPosX = m_iStartDrawPosY = -15;
	// Record the players size
	m_iDrawHeight = m_iDrawWidth = 30;
	// Initially set previous and current equal
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 40 + 60;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 40 + 100;
	// Load farmer
	farmer.LoadImage("farmer1.png");
	farmerWidth = farmer.GetWidth();
	farmerHeight = farmer.GetHeight();
	// Make it visible
	SetVisible(true);

	iTick = m_pMainEngine->GetTime() / 250;
}

PsyjsmorPlayer::~PsyjsmorPlayer()
{
}

void PsyjsmorPlayer::Draw()
{
	if (!IsVisible())
		return;

	int iSize = 15;

	if (m_pMainEngine->pause == 0)
		iTick = m_pMainEngine->GetTime() / 250; // 1 per 250ms

	int iFrame = iTick % 3;

	if (farmer.IsLoaded())
	{
		if (m_iDirX == 1)
		{
			if (iFrame == 0)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					0, 203,
					m_iCurrentScreenX - (23 / 2),
					m_iCurrentScreenY - (50 / 2),
					23, 50
				);
			}
			else if (iFrame == 1)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					41, 203,
					m_iCurrentScreenX - (24 / 2),
					m_iCurrentScreenY - (50 / 2),
					24, 50
				);
			}
			else if (iFrame == 2)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					93, 203,
					m_iCurrentScreenX - (27 / 2),
					m_iCurrentScreenY - (50 / 2),
					27, 50
				);
			}
		}
		else if (m_iDirX == -1)
		{
			if (iFrame == 0)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					0, 70,
					m_iCurrentScreenX - (23 / 2),
					m_iCurrentScreenY - (51 / 2),
					23, 51
				);
			}
			else if (iFrame == 1)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					46, 70,
					m_iCurrentScreenX - (25 / 2),
					m_iCurrentScreenY - (49 / 2),
					25, 49
				);
			}
			else if (iFrame == 2)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					94, 70,
					m_iCurrentScreenX - (26 / 2),
					m_iCurrentScreenY - (47 / 2),
					26, 47
				);
			}
		}
		else if (m_iDirY == 1)
		{
			if (iFrame == 0)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					0, 0,
					m_iCurrentScreenX - (24 / 2),
					m_iCurrentScreenY - (50 / 2),
					24, 50
				);
			}
			else if (iFrame == 1)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					47, 0,
					m_iCurrentScreenX - (25 / 2),
					m_iCurrentScreenY - (49 / 2),
					25, 49
				);
			}
			else if (iFrame == 2)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					95, 0,
					m_iCurrentScreenX - (25 / 2),
					m_iCurrentScreenY - (47 / 2),
					25, 47
				);
			}
		}
		else if (m_iDirY == -1)
		{
			if (iFrame == 0)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					0, 137,
					m_iCurrentScreenX - (24 / 2),
					m_iCurrentScreenY - (51 / 2),
					24, 51
				);
			}
			else if (iFrame == 1)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					45, 137,
					m_iCurrentScreenX - (23 / 2),
					m_iCurrentScreenY - (49 / 2),
					23, 49
				);
			}
			else if (iFrame == 2)
			{
				farmer.RenderImageWithMask(
					m_pMainEngine->GetSDLSurface(),
					97, 137,
					m_iCurrentScreenX - (23 / 2),
					m_iCurrentScreenY - (45 / 2),
					23, 45
				);
			}
		}
	}
	else
	{
		m_pMainEngine->DrawForegroundOval(
			m_iCurrentScreenX - iSize,
			m_iCurrentScreenY - iSize,
			m_iCurrentScreenX + iSize - 1,
			m_iCurrentScreenY + iSize - 1,
			0x000000);

		m_pMainEngine->DrawForegroundOval(
			m_iCurrentScreenX - iSize + 3,
			m_iCurrentScreenY - iSize + 3,
			m_iCurrentScreenX + iSize - 4,
			m_iCurrentScreenY + iSize - 4,
			0x6CCA00);
	}

	char buf[8];
	sprintf(buf, "%d", m_pMainEngine->lives);
	GetEngine()->DrawForegroundString(m_iCurrentScreenX - 6, m_iCurrentScreenY - 50, buf, 0xFFFFFF);

	StoreLastScreenPositionForUndraw();
}

void PsyjsmorPlayer::DoUpdate(int iCurrentTime)
{
	if (m_pMainEngine->state && m_pMainEngine->timeLimit > 0 && m_pMainEngine->pause == 0)
	{
		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		if (m_iDirY != 1 && (GetEngine()->IsKeyPressed(SDLK_UP) || GetEngine()->IsKeyPressed(SDLK_w)))
		{
			m_iDirX = 0;
			m_iDirY = -1;
		}
		if (m_iDirY != -1 && (GetEngine()->IsKeyPressed(SDLK_DOWN) || GetEngine()->IsKeyPressed(SDLK_s)))
		{
			m_iDirX = 0;
			m_iDirY = 1;
		}
		if (m_iDirX != 1 && (GetEngine()->IsKeyPressed(SDLK_LEFT) || GetEngine()->IsKeyPressed(SDLK_a)))
		{
			m_iDirX = -1;
			m_iDirY = 0;
		}
		if (m_iDirX != -1 && (GetEngine()->IsKeyPressed(SDLK_RIGHT) || GetEngine()->IsKeyPressed(SDLK_d)))
		{
			m_iDirX = 1;
			m_iDirY = 0;
		}

		m_iMapX = ((m_iCurrentScreenX - 20) / 40) + m_iDirX;
		m_iMapY = ((m_iCurrentScreenY - 60) / 40) + m_iDirY;

		switch (m_oTiles.GetValue(m_iMapX, m_iMapY))
		{
		case 98:
			if (m_iDirY == 1)
				m_iCurrentScreenY = m_iPreviousScreenY + 40;
			if (m_iDirY == -1)
				m_iCurrentScreenY = m_iPreviousScreenY - 40;
			if (m_iDirX == 1)
				m_iCurrentScreenX = m_iPreviousScreenX + 40;
			if (m_iDirX == -1)
				m_iCurrentScreenX = m_iPreviousScreenX - 40;

			break;
		case 120:
			if (m_iCurrentScreenX < m_iDrawWidth + m_iStartDrawPosX + 45)
				m_iCurrentScreenX = m_iDrawWidth + m_iStartDrawPosX + 45;
			if (m_iCurrentScreenX > GetEngine()->GetWindowWidth() - 60)
				m_iCurrentScreenX = GetEngine()->GetWindowWidth() - 60;
			if (m_iCurrentScreenY < m_iDrawHeight + m_iStartDrawPosY + 85)
				m_iCurrentScreenY = m_iDrawHeight + m_iStartDrawPosY + 85;
			if (m_iCurrentScreenY > GetEngine()->GetWindowHeight() - 60)
				m_iCurrentScreenY = GetEngine()->GetWindowHeight() - 60;

			m_pMainEngine->lost = 1;
			m_pMainEngine->state = 0;

			break;
		}

		RedrawObjects();
	}

	if (!m_pMainEngine->state && GetEngine()->IsKeyPressed(SDLK_SPACE))
	{
		if (m_pMainEngine->lost)
		{
			m_pMainEngine->points = m_pMainEngine->stagePoints[m_pMainEngine->stage - 2];
			//m_pMainEngine->lives--;
		}
		m_pMainEngine->lost = 0;
		m_pMainEngine->state = 1;
		currCooldown = -1;

		m_iPreviousScreenX = m_iCurrentScreenX;
		m_iPreviousScreenY = m_iCurrentScreenY;

		m_iCurrentScreenX = 9 * 40 + 60;
		m_iCurrentScreenY = 5 * 40 + 100;
		if (m_pMainEngine->stage == 3)
		{
			m_iDirX = 0;
			m_iDirY = -1;
		}
		else
		{
			if (m_pMainEngine->stage == 1)
				m_pMainEngine->points = 0;

			m_iDirX = 1;
			m_iDirY = 0;
		}

		RedrawObjects();
	}
}

void PsyjsmorPlayer::SetPosition(int iX, int iY)
{
	// iX = 248, iY = 172
	iX = iX - 20;
	int remX = iX % 40; // 28
	if (remX < 20)
		iX = iX - remX;
	else
		iX = iX + (40 - remX);

	iY = iY - 20;
	int remY = iY % 40; // 32
	if (remY < 20)
		iY = iY - remY;
	else
		iY = iY + (40 - remY);
	iX = iX + 20;
	iY = iY + 20;

	if (m_iDirX == 1)
		m_iCurrentScreenX = iX - 40;
	else if (m_iDirX == -1)
		m_iCurrentScreenX = iX + 40;
	else
		m_iCurrentScreenX = iX;

	if (m_iDirY == 1)
		m_iCurrentScreenY = iY - 40;
	else if (m_iDirY == -1)
		m_iCurrentScreenY = iY + 40;
	else
		m_iCurrentScreenY = iY;

	currCooldown = (double)cooldown + 1;
}
