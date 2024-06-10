#pragma once
#include "SceneBase.h"
#include "game.h"

class SceneTitle;

class SceneDemo :
    public SceneBase
{
public:
    SceneDemo();
    ~SceneDemo();

    void SetTitle(SceneTitle* title) { m_pTitle = title; }

    void Init();

    void End();

    void Update(const InputState& input, NextSceneState& nextScene);

    void Draw();
private:
    using m_tUpdateFunc = void (SceneDemo::*) (const InputState& input, NextSceneState& nextScene);
    m_tUpdateFunc m_updateFunc = nullptr;

    void NormalUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);

    void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);
private:
    // フレーム数カウント
    int m_countFrame;
    // フェード用カウント
    int m_fadeCount;

    // テキスト点滅
    int m_textTimer;

    // デモムービーハンドル
    int m_hDemo;

    SceneTitle* m_pTitle;
};

