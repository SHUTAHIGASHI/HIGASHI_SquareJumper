#pragma once

#include "Game.h"
#include "ObjectGoalGate.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectDashRing.h"
#include "ObjectReverseRing.h"

class Player;
class SceneMain;

enum class StageState
{
	tutrialCube,
	tutrialJumpPad,
	tutrialJumpRing,
	tutrialGravity,
	tutrialDash,
	tutrialRev,
	firstStage,
	secondStage,
	thirdStage,
	fourthStage,
	fifthStage,
	sixthStage,
	seventhStage,
	eighthStage,
	ninthStage,
	tenthStage,
	Empty
};

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void SetPlayer(Player* player) { m_pPlayer = player; }
	void SetMain(SceneMain* main) { m_pMain = main; }
	
	void Init(int hSpike, int hBg, int hPortal, int hBlock, int hJumpPad);

	void InitStage(int hSpike, int hPortal, int hBlock, int hJumpPad);

	void End();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, ObjectType &object);

	bool IsUnder(float &tempPos);

	bool IsTop(float& tempPos);

	// すべてのオブジェクトをクリア
	void ClearAllObject();

	// 現在のステージ情報の初期化
	void ResetStage();
	// 現在のステージ情報の変更
	void StageManage();

	// チュートリアルステージをセット1
	void SetTutorialStage() { m_stageState = StageState::tutrialCube; }
	// 選んだステージをセット
	void SetSelectedStage(StageState stage) { m_stageState = stage; }
	// 次のステージのセット
	void SetNextStageState();
	// ステージを一番最初にセット
	void SetFirstStage() { m_stageState = StageState::firstStage; }

	// スクロール処理に関して
	bool IsScrollStage() const { return m_isScrollStage; }
	int GetScroll() const { return m_scroll; }

	//ステージの状態を確保
	StageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	void ScrollUpdate();

	// メンバ関数ポインタ
	using m_tUpdateFunc = void (Stage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	std::vector<ObjectGoalGate> m_ObjectGoalGate;
	std::vector<ObjectBlock> m_ObjectBlock;
	std::vector<ObjectJumpRing> m_ObjectJumpRing;
	std::vector<ObjectJumpPad> m_ObjectJumpPad;
	std::vector<ObjectSpike> m_ObjectSpike;
	std::vector<ObjectGravityRing> m_ObjectGravityRing;
	std::vector<ObjectDashRing> m_ObjectDashRing;
	std::vector<ObjectReverseRing> m_ObjectReverseRing;

	Player* m_pPlayer;
	SceneMain* m_pMain;

	// ステージ管理用変数
	StageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthTripleNum];

	// 座標数値の一時保存
	int m_tempNum;

	// スクロール用変数
	// スクロールするステージかどうか
	bool m_isScrollStage;
	// 現在スクロール中かどうか
	bool m_isScroll;
	// スクロール数値
	int m_scroll;
	// スクロールの変化速度
	int m_scrollAcc;

	// 背景
	int m_hBg;
};

