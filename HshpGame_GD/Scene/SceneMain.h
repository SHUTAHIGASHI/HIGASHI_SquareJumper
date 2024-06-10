#pragma once
#include "game.h"
#include "Stage.h"
#include <memory>
#include <string>

enum class gameMode
{
	Empty,
	Arcade,
	Challenge,
	Practice
};

class Player;
class Stage;
class ScenePause;
class SceneManager;
class SceneClear;
class SceneRanking;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetClear(SceneClear* clear) { m_pClear = clear; }
	void SetRanking(SceneRanking* rank) { m_pRanking = rank; }

	// 初期化
	void Init(int fontS, int fontL);

	void OnGameStart();

	void PlayGameLoopBgm();

	// 終了処理
	void End();

	// 毎フレームの処理
	void Update(const InputState& input, NextSceneState& nextScene);
	
	// リトライ選択時の処理
	void OnRetry();
	// 死亡時の処理
	void OnDead();

	void OnDeadDraw();

	// 死亡時の描画スクリーン作成
	void CreateDeadScreen() { m_hDeadScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight); }
	void DeleteDeadScreen() { DeleteGraph(m_hDeadScreen); }

	// 毎フレームの描画
	void Draw();
	// ゲーム中の情報描画
	void DrawGameInfo();

	// 操作説明描画
	void DrawHowTo(int X, int Y);
	// ゲームスタート時のカウントダウン描画
	void OnStartCount();

	// ステージクリア時
	void OnStageClear(NextSceneState& nextScene);

	// m_isEndを取得
	virtual bool IsEnd() const { return m_isEnd; }

	// モード切り替え
	virtual void SetPracticeMode() { m_gameMode = gameMode::Practice; }
	virtual void SetArcadeMode() { m_gameMode = gameMode::Arcade; }
	virtual void SetChallengeMode() { m_gameMode = gameMode::Challenge; }
	virtual void SetTutorialMode() { m_isTutorial = true; }
	virtual void SetDoTutorialMode() { m_isDoTutorial = true; }

	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_selectedStage = stage; }

	// 現在のステージ情報取得
	StageState GetStageState() const { return m_pStage->GetStageState(); }

	// 挑戦回数を取得
	int GetAttempt() const { return m_countAttempt; }

	// BGMハンドル取得
	int GetMusicHandle() const { return m_hPlayBgm; }

private:
	using m_tUpdateFunc = void (SceneMain::*) (const InputState& input, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// 通常の更新処理
	void NormalUpdate(const InputState& input, NextSceneState& nextScene);
	// スタートカウント時の更新処理
	void StartDelayUpdate(const InputState& input, NextSceneState& nextScene);
	// シーン変更時の更新処理
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
	int m_hPadImg;
	// 背景のグラフィック
	int m_hBg;
	// フォントデータ
	int m_hFontL;
	int m_hFontS;
	// 効果音
	int m_hDeathSound;
	int m_hCountDown;
	// 音楽用
	int m_hPlayBgm;
	// 死亡時の揺れるスクリーンハンドル
	int m_hDeadScreen = 0;

	// 毎フレームカウント
	int m_countFrame;

	// フェード処理用カウント
	int m_fadeCount;

	// パッドカウント
	int m_padCount;

	// ゲームの制限時間
	int m_startDelay;
	// スタート遅延時のテキストサイズ
	int m_startTextSize;
	// スタート遅延の文字点滅
	int m_textTimer;
	// ゲームオーバー時の遅延時間
	int m_gameOverDelay;
	// 挑戦回数
	int m_countAttempt;
	// 挑戦回数描画時間
	int m_attemptDrawTime;
	// 挑戦回数描画の値
	int m_attemptDrawNum;
	// 画面振動
	int m_quakeScale = 0;
	int m_quakeY = 0;
	int m_quakeX = 0;

	// ゲームモード
	gameMode m_gameMode;
	bool m_isTutorial;
	bool m_isDoTutorial;

	// ポーズ中かどうか
	bool m_isPause;
	bool m_isPauseEnd;
	// シーン終了
	bool m_isEnd;

	// カウントダウンを一度だけ
	bool m_isOnlyOnceSE;

	std::string m_tutorialText;

	// 選ばれたステージ
	StageState m_selectedStage;

	// プレイヤー
	std::shared_ptr<Player> m_pPlayer;
	// ステージ
	std::shared_ptr<Stage> m_pStage;

	// ポーズメニューシーン
	std::shared_ptr<ScenePause> m_pPause;

	SceneManager* m_pManager;
	SceneClear* m_pClear;
	SceneRanking* m_pRanking;
};