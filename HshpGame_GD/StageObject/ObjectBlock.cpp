#include "ObjectBlock.h"

ObjectBlock::ObjectBlock():
	m_hBlock(-1),
	m_drawTileNumX(0),
	m_drawTileNumY(0)
{
}

void ObjectBlock::Init(int hBlock)
{
	m_drawTileNumX = 0;// GetRand(10);
	m_drawTileNumY = 0;// GetRand(1);

	m_pos.x = 0;
	m_pos.y = 0;

	m_hBlock = hBlock;
}

void ObjectBlock::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectBlock::Update()
{
}

void ObjectBlock::Draw(int scroll)
{
	Vec2 draw;
	draw.x = m_pos.x - scroll;
	draw.y = m_pos.y;

	int imgX, imgY, imgW, imgH;
	imgX = (16 * m_drawTileNumX) + 1, imgY = (16 * m_drawTileNumY) + 1, imgW = 14, imgH = 14;

	DrawRectExtendGraphF(draw.x, draw.y, draw.x + Game::kBlockSize, draw.y + Game::kBlockSize,
		imgX, imgY, imgW, imgH, m_hBlock, true);
}
