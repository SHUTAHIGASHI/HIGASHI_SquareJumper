#pragma once

#include "game.h"
#include <memory>

class SceneTitle;
class SceneDemo;
class SceneStageSelect;
class SceneRanking;
class SceneMain;
class SceneClear;

class SceneManager
{
public:
	// シーンの種類定義
	typedef enum SceneKind
	{
		kSceneTitle,
		kSceneDemo,
		kSceneRanking,
		kSceneStageSelect,
		kSceneMain,
		kSceneClear,

		kSceneKindNum
	}SceneKind;

public:
	SceneManager();
	virtual ~SceneManager();

	// 初期化
	void Init(int font24, int font48);
	// 削除
	void End();

	// 更新
	void Update(const InputState& input, int font24, int font48, bool &isGameEnd);
	// 描画
	void Draw();

	SceneKind GetLastScene() { return m_lastScene; }
	NextSceneState GetNextScene() { return m_nextScene; }

private:	
	SceneKind m_kind;
	SceneKind m_lastScene;
	NextSceneState m_nextScene;

	std::shared_ptr<SceneTitle> m_pTitle;
	std::shared_ptr<SceneDemo> m_pDemo;
	std::shared_ptr<SceneStageSelect> m_pStageSelect;
	std::shared_ptr<SceneRanking> m_pRanking;
	std::shared_ptr<SceneMain> m_pMain;
	std::shared_ptr<SceneClear> m_pClear;
};