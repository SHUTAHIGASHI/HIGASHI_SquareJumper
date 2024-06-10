#pragma once

#include "game.h"

class EffectRing
{
public:
	EffectRing() :
		m_drawPos(),
		m_isExist(false),
		m_circleSize(0),
		m_countFrame(0),
		m_blendNum(0)
	{}
	~EffectRing(){}

	void Init();

	void SetEffect();

	void End();

	void Update();

	void Draw(Vec2 playerPos);

private:
	Vec2 m_drawPos;

	bool m_isExist;

	int m_circleSize;

	int m_countFrame;

	int m_blendNum;
};

