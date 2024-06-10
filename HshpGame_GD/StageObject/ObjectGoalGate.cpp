#include "ObjectGoalGate.h"

ObjectGoalGate::ObjectGoalGate() :
	m_countFrame(0),
	m_hPortal(-1),
	m_imgX(0),
	m_imgY(0)
{
}

void ObjectGoalGate::Init(int hPortal)
{
	m_hPortal = hPortal;
	
	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectGoalGate::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectGoalGate::Update()
{
	m_countFrame++;

	m_drawFrame += m_countFrame % 2;
	if (m_drawFrame > 8) m_drawFrame = 0;
}

void ObjectGoalGate::Draw(int scroll)
{	
	Vec2 draw;
	draw.x = m_pos.x - scroll;
	draw.y = m_pos.y;

	m_imgX = static_cast<int>(m_drawFrame * Game::kBlockSize);
	m_imgY = 0;
	int imgW = 0, imgH = 0;
	imgW = static_cast<int>(Game::kBlockSize);
	imgH = static_cast<int>(Game::kBlockSize);

	DrawRectExtendGraphF(draw.x, draw.y,
		draw.x + Game::kBlockSize, draw.y + (Game::kBlockSize * 3), 
		m_imgX, m_imgY, imgW, imgH, 
		m_hPortal, true);
}

bool ObjectGoalGate::CollisionCheck(Vec2 player, int resizeScale)
{
	// スパイクの当たり判定
	if (GetRight() > player.x &&
		player.x + Game::kBlockSize > GetLeft() &&
		GetBottom() + resizeScale > player.y &&
		player.y + Game::kBlockSize > GetTop())
	{
		return true;
	}

	return false;
}
