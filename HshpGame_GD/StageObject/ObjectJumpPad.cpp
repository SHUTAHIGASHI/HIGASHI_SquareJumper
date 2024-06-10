#include "ObjectJumpPad.h"
#include "game.h"

ObjectJumpPad::ObjectJumpPad() :
	m_countFrame(0.0),
	m_hJumpPad(-1)
{
}

void ObjectJumpPad::Init(int hJumpPad)
{
	m_hJumpPad = hJumpPad;
	m_countFrame = 0.0;

	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectJumpPad::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectJumpPad::Update()
{
	m_countFrame += 0.2;
	if(m_countFrame > 6) m_countFrame = 0.0;
}

void ObjectJumpPad::Draw(int scroll)
{
	Vec2 draw;
	draw.x = m_pos.x - scroll;
	draw.y = m_pos.y;

	int imgX, imgY, imgW, imgH;
	imgX = 50 * static_cast<int>(m_countFrame), imgY = 0;
	imgW = static_cast<int>(Game::kBlockSize), imgH = static_cast<int>(Game::kBlockSize);

	DrawRectExtendGraphF(draw.x, draw.y, draw.x + Game::kBlockSize, draw.y + Game::kBlockSize, imgX, imgY, imgW, imgH, m_hJumpPad, true);
}

bool ObjectJumpPad::CollisionCheck(Vec2 player, int resizeScale)
{
	// “–‚½‚è”»’è
	if (GetRight() - 5> player.x &&
		player.x + Game::kBlockSize > GetLeft() + 5 &&
		GetBottom() > player.y &&
		player.y + Game::kBlockSize > GetTop() + resizeScale)
	{
		return true;
	}

	return false;
}
