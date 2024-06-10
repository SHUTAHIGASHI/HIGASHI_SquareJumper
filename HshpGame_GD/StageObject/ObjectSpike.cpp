#include "ObjectSpike.h"

ObjectSpike::ObjectSpike()
{
}

void ObjectSpike::Init(int hSpike)
{
	m_hObjectImg = hSpike;

	m_pos.x = 0;
	m_pos.y = 0;
}

void ObjectSpike::SetPos(float X, float Y)
{
	m_pos.x = X;
	m_pos.y = Y;
}

void ObjectSpike::Update()
{
}

void ObjectSpike::Draw(int scroll)
{
	DrawRotaGraphF(GetCenterX() - scroll, GetCenterY(), 1, 0, m_hObjectImg, true, false);
}
