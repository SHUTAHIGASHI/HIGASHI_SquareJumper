#pragma once
#include "SceneBase.h"
#include "game.h"
#include <string>
#include <memory>
#include <array>

class SceneMain;
class ParticleBase;

class SceneClear : public SceneBase
{
public:
	SceneClear():
		m_hSelectSound(-1),
		m_hFontS(-1),
		m_hFontL(-1),
		m_hPadImg(-1),
		m_selectPos(0),
		m_selectNamePos(0),
		m_sceneChangeDelay(0),
		m_fadeCount(0),
		m_shadowScale(0),
		m_textFadeNum(0),
		m_textScale(0),
		m_textScaleAcc(0),
		m_isNextStage(false),
		m_isEnd(false),
		sinRate(0),
		auraFrame(0),
		m_pMain(nullptr)
	{
	}
	virtual ~SceneClear() {}

	// メインのポインタセット
	void SetMain(SceneMain* main) { m_pMain = main; }

	// 初期化
	void Init(int fontS, int fontL);
	
	// 終了処理
	void End();
	// 更新
	void Update(const InputState& input, NextSceneState& nextScene);
	// パーティクル用
	void ParticleUpdate();
	// 指定した色をランダムに取得
	int GetRandColor();
	
	// 描画
	virtual void Draw();

	// パッド画像描画
	void DrawPadText();

	// ステージ全クリ時
	void OnAllClear();

	// 次のステージへ進むかどうか
	bool IsNextStage() const { return m_isNextStage; }

	// m_isEnd を取得
	virtual bool IsEnd() { return m_isEnd; }

	void ResetIsNext() { m_isNextStage = false; }

private:
	// Update
	using m_tUpdateFunc = void (SceneClear::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// 通常更新処理
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	// ステージ全クリ時更新処理
	void AllClearUpdate(const InputState& input, NextSceneState& nextScene);

	// シーン終了時更新処理
	void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);

	// Draw
	using m_tDrawFunc = void (SceneClear::*) ();
	m_tDrawFunc m_drawFunc = nullptr;

	// 通常の描画処理
	void NormalDraw();

	// ステージ全クリ時の描画処理
	void AllClearDraw();
private:
	// 音データ
	int m_hSelectSound;

	// フォントのハンドル
	int m_hFontS;
	int m_hFontL;

	// 画像データ
	int m_hPadImg;

	// メニュー選択
	int m_selectPos;
	int m_selectNamePos;
	
	// タイトル表示までの遅延用変数
	int m_sceneChangeDelay;
	
	// 画面フェード処理
	int m_fadeCount;
	// ゲームクリアテキストの影
	int m_shadowScale;
	int m_textFadeNum;

	// テキストの文字サイズ
	int m_textScale;
	int m_textScaleAcc;

	// 次のステージ
	bool m_isNextStage;
	// シーン終了
	bool m_isEnd;

	// パーティクル用
	float sinRate;
	int auraFrame;
	std::array<std::shared_ptr<ParticleBase>, Game::kParticleNum> particle;

	SceneMain* m_pMain;
};