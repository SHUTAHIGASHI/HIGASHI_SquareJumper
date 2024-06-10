#pragma once
#include "ObjectBase.h"

class ObjectBlock :
    public ObjectBase
{
public:
    ObjectBlock();
    ~ObjectBlock(){}

    void Init(int hBlock);

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);

private:
    int m_hBlock;

    int m_drawTileNumX;
    int m_drawTileNumY;
};
