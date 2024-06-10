#include "ObjectBase.h"

ObjectBase::ObjectBase() :
	m_hObjectImg(-1)
{
}

void ObjectBase::Init()
{
}

void ObjectBase::SetPos()
{
}

void ObjectBase::Update()
{
}

void ObjectBase::Draw()
{
}

bool ObjectBase::CollisionCheck(Vec2 player, int resizeScale, int playerScale)
{
	// オブジェクトの当たり判定
	if (GetRight() - resizeScale > player.x + playerScale &&
		(player.x + Game::kBlockSize) - playerScale > GetLeft() + resizeScale &&
		GetBottom() - resizeScale > player.y + playerScale &&
		(player.y + Game::kBlockSize) - playerScale > GetTop() + resizeScale)
	{
		return true;
	}

	return false;
}

bool ObjectBase::CollisionCheck(Vec2 player)
{
	// オブジェクトの当たり判定
	if (GetRight() > player.x &&
		player.x + Game::kBlockSize > GetLeft()&&
		GetBottom() > player.y &&
		player.y + Game::kBlockSize > GetTop())
	{
		return true;
	}

	return false;
}
