#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneDemo.h"
#include "SceneStageSelect.h"
#include "SceneHowTo.h"
#include "SceneRanking.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include <cassert>

SceneManager::SceneManager():
	m_kind(kSceneTitle),
	m_nextScene (NextSceneState::nextGameMain),
	m_lastScene(),
	m_pTitle(std::make_shared<SceneTitle>()),
	m_pDemo(std::make_shared<SceneDemo>()),
	m_pStageSelect(std::make_shared<SceneStageSelect>()),
	m_pRanking(std::make_shared<SceneRanking>()),
	m_pMain(std::make_shared<SceneMain>()),
	m_pClear(std::make_shared<SceneClear>())
{
}
SceneManager::~SceneManager()
{

}

// 初期化
void SceneManager::Init(int font24, int font48)
{	
	// 各シーンの初期化
	m_kind = kSceneTitle;
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pTitle->SetMain(m_pMain.get());
		m_pTitle->SetManager(this);
		m_pTitle->SetStageSelect(m_pStageSelect.get());
		m_pTitle->Init(font24, font48);	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->SetTitle(m_pTitle.get());
		m_pDemo->Init();	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->SetManager(this);
		m_pStageSelect->SetMain(m_pMain.get());
		m_pStageSelect->SetTitle(m_pTitle.get());
		m_pStageSelect->Init(font24, font48);	// シーンの初期化
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Init(font24);	// シーンクリアの初期化
		break;
	case SceneManager::kSceneMain:
		m_pMain->SetManager(this);
		m_pMain->SetClear(m_pClear.get());
		m_pMain->SetRanking(m_pRanking.get());
		m_pMain->Init(font24, font48);	// シーンメインの初期化
		break;
	case SceneManager::kSceneClear:
		m_pClear->SetMain(m_pMain.get());
		m_pClear->Init(font24, font48);	// シーンクリアの初期化
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 削除
void SceneManager::End()
{
	// 各シーンのデータ削除
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pTitle->End();	// シーンタイトルのデータ削除
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->End();	// シーンタイトルの初期化
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->End();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->End();	// シーンクリアの初期化
		break;
	case SceneManager::kSceneMain:
		m_pMain->End();	// シーンメインのデータ削除
		break;
	case SceneManager::kSceneClear:
		m_pMain->End();	// シーンメインのデータ削除
		m_pClear->End();	// シーンクリアのデータ削除
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

// 更新
void SceneManager::Update(const InputState& input, int font24, int font48, bool &isGameEnd)
{
	// 現在のシーンの更新処理を実行する
	bool isEnd = false;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pTitle->Update(input, isGameEnd, m_nextScene);	// シーンタイトルの更新
		isEnd = m_pTitle->IsEnd();
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->Update(input, m_nextScene);	// シーンデモの初期化
		isEnd = m_pDemo->IsEnd();
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->Update(input, isGameEnd, m_nextScene);	// シーンクリアの更新
		isEnd = m_pStageSelect->IsEnd();
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Update(input, isGameEnd, m_nextScene);	// シーンクリアの初期化
		isEnd = m_pRanking->IsEnd();
		break;
	case SceneManager::kSceneMain:
		m_pMain->Update(input, m_nextScene);	// シーンメインの更新
		isEnd = m_pMain->IsEnd();
		break;
	case SceneManager::kSceneClear:
		m_pClear->Update(input, m_nextScene);	// シーンクリアの更新
		isEnd = m_pClear->IsEnd();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}

	// isEnd が true のとき、各シーンの初期化とデータ削除を行う
	if (isEnd)
	{
		m_lastScene = m_kind;

		switch (m_nextScene)
		{
		case NextSceneState::nextTitle:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンのデータ削除
			m_pTitle->SetMain(m_pMain.get());
			m_pTitle->SetManager(this);
			m_pTitle->SetStageSelect(m_pStageSelect.get());
			m_pTitle->Init(font24, font48);	// シーンタイトルの初期化
			m_kind = kSceneTitle;
			break;
		case NextSceneState::nextDemo:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンのデータ削除
			m_pDemo->SetTitle(m_pTitle.get());
			m_pDemo->Init();	// シーンタイトルの初期化
			m_kind = kSceneDemo;
			break;
		case NextSceneState::nextStageSelect:
			End();	// シーンのデータ削除
			m_pStageSelect->SetMain(m_pMain.get());
			m_pStageSelect->SetManager(this);
			m_pStageSelect->SetTitle(m_pTitle.get());
			m_pStageSelect->Init(font24, font48);	// シーンメインの初期化
			m_kind = kSceneStageSelect;
			break;
		case NextSceneState::nextRanking:	// シーンがゲームクリアの場合、ゲーム終了
			End();	// シーンのデータ削除
			m_pRanking->SetMain(m_pMain.get());
			m_pRanking->Init(font24);	// シーンタイトルの初期化
			m_kind = kSceneRanking;
			break;
		case NextSceneState::nextGameMain:
			End();	// シーンのデータ削除
			m_pMain->SetClear(m_pClear.get());
			m_pMain->SetRanking(m_pRanking.get());
			m_pMain->Init(font24, font48);	// シーンメインの初期化
			m_kind = kSceneMain;
			break;
		case NextSceneState::nextClear:
			m_pClear->SetMain(m_pMain.get());
			m_pClear->Init(font24, font48);	// シーンクリアの初期化
			m_kind = kSceneClear;
			break;
		default:
			assert(false);
			break;
		}
	}
}

// 描画
void SceneManager::Draw()
{
	// 現在のシーンの描画処理を行う
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pTitle->Draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneDemo:
		m_pDemo->Draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneStageSelect:
		m_pStageSelect->Draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneRanking:
		m_pRanking->Draw();	// シーンタイトルの描画
		break;
	case SceneManager::kSceneMain:
		m_pMain->Draw();	// シーンメインの描画
		break;
	case SceneManager::kSceneClear:
		m_pMain->Draw();	// シーンメインの描画
		m_pClear->Draw();	// シーンクリアの描画
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}