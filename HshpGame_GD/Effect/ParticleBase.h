#pragma once
#include "Vec2.h"

class ParticleBase
{
public:
	ParticleBase();
	virtual ~ParticleBase();

	void init();

	virtual void update();
	virtual void draw();

	// 開始	とりあえず初期位置のみ設定	他のは個別設定
	void start(Vec2 pos);

	// 設定可能な項目
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setRadius(float r) { m_radius = r; }
	void setColor(unsigned int color) { m_color = color; }
	void setGravity(float gravity) { m_gravity = gravity; }
	void setAlphaDec(int dec) { m_alphaDec = dec; }
	void setRadiusAcc(float acc) { m_radiusAcc = acc; }

	bool isExist() const { return m_isExist; }

protected:
	Vec2 m_pos;
	Vec2 m_vec;
	float m_radius;
	unsigned int m_color;
	int m_alpha;
	bool m_isExist;

	// 重力加速度	落ちない場合は0.0を指定する
	float m_gravity;

	// 透明度の減衰速度	初期255から指定した数減っていく
	int m_alphaDec;

	// 半径の変化量
	float m_radiusAcc;
};

