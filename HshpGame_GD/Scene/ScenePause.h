#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>

class SceneMain;

class ScenePause : public SceneBase
{
public:
	ScenePause() :
		m_hFontS(-1),
		m_hPadImg(-1),
		m_hSelectSound(-1),
		m_selectPos(0),
		m_selectNamePos(0),
		m_textTimer(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_pMain(nullptr)
	{
	}
	virtual ~ScenePause() {}

	void SetMain(SceneMain* main) { m_pMain = main; }

	// 初期化
	void Init(int fontS);

	// 終了処理
	void End();
	// 更新
	virtual void Update(const InputState& input, NextSceneState& nextScene, bool &isPEnd);
	// 描画
	virtual void Draw();

	void DrawPadText();

private:
	// Update
	using m_tUpdateFunc = void (ScenePause::*) (const InputState& input, NextSceneState& nextScene, bool& isEnd);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene, bool& isEnd);

	// Draw
	using m_tDrawFunc = void (ScenePause::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	void NormalDraw();
private:
	// フォントデータ
	int m_hFontS;
	// 画像データ
	int m_hPadImg;
	// 音データ
	int m_hSelectSound;

	// メニュー選択
	int m_selectPos;
	int m_selectNamePos;

	// テキスト点滅
	int m_textTimer;

	// 文字のサイズ
	int m_textScale;
	int m_textScaleAcc;

	// 次のステージ
	bool m_isNextStage;

	SceneMain* m_pMain;
};