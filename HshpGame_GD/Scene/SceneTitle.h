#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;
class SceneManager;
class SceneStageSelect;

class SceneTitle : public SceneBase
{
public:
	SceneTitle() :
		m_updateFunc(&SceneTitle::SceneStartUpdate),
		m_selectPos(0),
		m_selectTutorial(0),
		m_textTimer(0),
		m_countFrame(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(-1),
		m_hPadImg(-1),
		m_hTitleImg(-1),
		m_hFontS(-1),
		m_hFontL(-1),
		m_hLoopBgm(LoadSoundMem("soundData/MenuLoop.wav")),
		m_hSelectSound(-1),
		m_textScroll(0),
		m_scroll(0),
		m_scrollAcc(0),
		m_pMain(nullptr),
		m_pManager(nullptr),
		m_pStageSelect(nullptr)
	{
	}
	virtual ~SceneTitle() 
	{
		DeleteSoundMem(m_hLoopBgm);
	}

	void SetMain(SceneMain* main) { m_pMain = main; }
	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetStageSelect(SceneStageSelect* stageSelect) { m_pStageSelect = stageSelect; }

	// 初期化
	virtual void Init(int fontS, int fontL);
	
	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene);
	// 描画
	void Draw();

	void StopMusic();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }

	int GetMusicHandle()const { return m_hLoopBgm; }
	int GetScroll()const { return m_scroll; }
private:
	using m_tUpdateFunc = void (SceneTitle::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	m_tUpdateFunc m_updateFunc = nullptr;

	// 通常の更新処理
	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	// チュートリアル選択
	void ModeSelectUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene);
	
	///
	using m_tDrawFunc = void (SceneTitle::*) ();
	m_tDrawFunc m_drawFunc = nullptr;
	// 通常の描画処理
	void NormalDraw();

	void ModeSelectDraw();

private:	
	// メニュー選択
	int m_selectPos;
	// チュートリアルモード切替の選択
	int m_selectTutorial;

	int m_textTimer;

	int m_countFrame;
	int m_fadeCount;
	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBg;
	int m_hPadImg;
	int m_hTitleImg;
	// フォントデータ
	int m_hFontS;
	int m_hFontL;
	// 音楽データ
	int m_hLoopBgm;
	int m_hSelectSound;

	int m_textScroll;

	int m_scroll;
	int m_scrollAcc;

	SceneMain* m_pMain;
	SceneManager* m_pManager;
	SceneStageSelect* m_pStageSelect;
};