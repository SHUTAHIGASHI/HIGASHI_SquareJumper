#include "ParticleBase.h"
#include "DxLib.h"

ParticleBase::ParticleBase() :
	m_pos(0, 0),
	m_vec(0, 0),
	m_radius(1.0f),
	m_color(0xffffff),
	m_alpha(255),
	m_isExist(false),
	m_gravity(0.0f),
	m_alphaDec(4),
	m_radiusAcc(0.0f)
{
}

ParticleBase::~ParticleBase()
{
}

void ParticleBase::init()
{
	m_pos = Vec2(0, 0);
	m_vec = Vec2(0, 0);
	m_radius = 1.0f;
	m_color = 0xffffff;
	m_alpha = 200;
	m_isExist = false;
	m_gravity = 0.0f;
	m_alphaDec = 4;
	m_radiusAcc = 0.0f;
}

void ParticleBase::update()
{
	if (!m_isExist)	return;
	m_pos += m_vec;
	m_vec.y += m_gravity;

	m_radius += m_radiusAcc;
	if (m_radius < 0.0f)
	{
		m_radius = 0.0f;
		m_isExist = false;
	}
	m_alpha -= m_alphaDec;
	if (m_alpha < 0)
	{
		m_isExist = false;
	}
}

void ParticleBase::draw()
{
	if (!m_isExist)	return;

	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	SetDrawBlendMode(DX_BLENDMODE_ADD, m_alpha);
	DrawCircleAA(m_pos.x, m_pos.y, m_radius, 16, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ParticleBase::start(Vec2 pos)
{
	init();
	m_pos = pos;
	m_isExist = true;
}
