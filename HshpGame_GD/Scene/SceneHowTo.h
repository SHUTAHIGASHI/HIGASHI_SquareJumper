#pragma once

#include "ObjectBlock.h"
#include "game.h"
#include <memory>

class HowToPlayer;
class HowToStage;
class SceneClear;

class SceneHowTo
{
public:
	SceneHowTo();
	virtual ~SceneHowTo();

	void SetClear(SceneClear* clear) { m_pClear = clear; }

	// 初期化
	void Init(int font24, int font48);

	void OnGameStart();

	void PlayGameSound();

	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input, NextSceneState& nextScene);
	// 毎フレームの描画
	void Draw();

	void DrawHowTo();

	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

private:
	using m_tUpdateFunc = void (SceneHowTo::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, NextSceneState& nextScene);
	void SceneEndUpdate(const InputState& input, NextSceneState& nextScene);

private:
	// キャラクターのグラフィックハンドル
	int m_hPlayer;
	int m_hDeathEffect;
	// オブジェクトのグラフィックハンドル
	int m_hObjectSpike;
	int m_hPortal;
	int m_hBlock;
	int m_hJumpPad;
	// 背景のグラフィック
	int m_hBg;
	int m_hPadImg;
	// テキスト画像
	int m_hTutoText;

	// フォントハンドル
	int m_hFontS;
	int m_hFontL;

	// 効果音
	int m_hDeathSound;
	// 音楽用
	int m_hPracBgm;

	int m_fadeCount;
	int m_countPadNum;

	int m_countFrame;
	// ゲームの制限時間
	int m_startDelay;
	// スタート遅延時のテキストサイズ
	int m_startTextSize;
	// ゲームオーバー時の遅延時間
	int m_gameOverDelay;

	bool m_isPrac;
	// シーン終了
	bool m_isEnd;

	// プレイヤー
	std::shared_ptr<HowToPlayer> m_pHPlayer;
	
	// ステージ
	std::shared_ptr<HowToStage> m_pHStage;

	SceneClear* m_pClear;
};