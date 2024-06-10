#pragma once
#include "ObjectBase.h"

class ObjectJumpPad :
    public ObjectBase
{
public:
    ObjectJumpPad();
    ~ObjectJumpPad() {}

    void Init(int hJumpPad);

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);

    bool CollisionCheck(Vec2 player, int resizeScale);
private:
    double m_countFrame;

    int m_hJumpPad;
};

