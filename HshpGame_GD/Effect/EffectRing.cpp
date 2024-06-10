#include "EffectRing.h"
#include "game.h"

#include <DxLib.h>

namespace
{
	constexpr int kCircleSizeMax = 100;

	constexpr int kCircleSpeed = 4;
	constexpr int kFadeSpeed = 15;
}

void EffectRing::Init()
{
	m_isExist = false;

	m_blendNum = 255;
	m_circleSize = 0;
}

void EffectRing::SetEffect()
{
	m_isExist = true;

	m_blendNum = 255;
	m_circleSize = 0;
}

void EffectRing::End()
{
	m_isExist = false;
}

void EffectRing::Update()
{
	if (!m_isExist) return;

	m_circleSize += kCircleSpeed;
	if (m_circleSize > kCircleSizeMax) m_circleSize = kCircleSizeMax;

	m_blendNum -= kFadeSpeed;
	if (m_blendNum < 0)
	{
		m_blendNum = 0;
		m_isExist = false;
	}
}

void EffectRing::Draw(Vec2 playerPos)
{
	if (!m_isExist) return;

	m_drawPos.x = (playerPos.x + (Game::kBlockSize / 2));
	m_drawPos.y = (playerPos.y + (Game::kBlockSize / 2));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blendNum);
	DrawCircle(static_cast<int>(m_drawPos.x), static_cast<int>(m_drawPos.y), m_circleSize, 0xffffff, false);
	DrawCircle(static_cast<int>(m_drawPos.x), static_cast<int>(m_drawPos.y), m_circleSize - 10, 0xffffff, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
