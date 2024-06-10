#pragma once
#include "ObjectBase.h"

class ObjectSpike :
    public ObjectBase
{
public:
    ObjectSpike();
    ~ObjectSpike() {}

    void Init(int hSpike);

    void SetPos(float X, float Y);

    void Update();

    void Draw(int scroll);
};
