
#include "DemoBObject2.h"
#include <iostream>

DemoBObject2::DemoBObject2(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 50;
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth - 100;
	m_iCurrentScreenY = m_iPreviousScreenY = GetEngine()->GetWindowHeight() - m_iDrawHeight - 100;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// And make it visible
	SetVisible(true);
}

DemoBObject2::~DemoBObject2()
{
}

void DemoBObject2::Draw()
{
	GetEngine()->DrawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void DemoBObject2::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_iCurrentScreenY += 2;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY -= 2;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX += 2;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX -= 2;

	if (m_iCurrentScreenX <= 0)
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenY <= 0)
		m_iCurrentScreenY = GetEngine()->GetWindowHeight() - m_iDrawHeight;
	if (m_iCurrentScreenY >= GetEngine()->GetWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = 0;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
