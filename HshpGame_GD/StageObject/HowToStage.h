#pragma once

#include "Game.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectDashRing.h"
#include "ObjectReverseRing.h"
#include <vector>

class HowToPlayer;

enum class HowToStageState
{
	CubeTest,
	JumpRingTest,
	GravityRingTest,
	DashRingTest,
	RevRingTest,
	End
};

class HowToStage
{
public:
	HowToStage();
	~HowToStage() {}

	void SetPlayer(HowToPlayer* player) { m_pHPlayer = player; }

	void Init(int hSpike, int hBg, int hPortal, int hBlock, int hJumpPad);

	void InitStage(int hSpike, int hPortal, int hBlock, int hJumpPad);

	void End();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(const Vec2 playerPos, ObjectType& object);

	bool IsUnder(float& tempPos);

	bool IsTop(float& tempPos);

	// ステージ情報の変更
	void StageManage();

	// 選んだステージをセット
	void SetSelectedStage(HowToStageState stage) { m_stageState = stage; }
	// 各ステージのセット
	void SetNextStageState();
	// ステージを一番最初にセット
	void SetFirstStage() { m_stageState = HowToStageState::CubeTest; }

	//ステージの状態を確保
	HowToStageState GetStageState() const { return m_stageState; }

private:
	void NormalUpdate();

	// メンバ関数ポインタ
	using m_tUpdateFunc = void (HowToStage::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	std::vector<ObjectBlock> m_ObjectBlock;
	std::vector<ObjectJumpRing> m_ObjectJumpRing;
	std::vector<ObjectJumpPad> m_ObjectJumpPad;
	std::vector<ObjectSpike> m_ObjectSpike;
	std::vector<ObjectGravityRing> m_ObjectGravityRing;
	std::vector<ObjectDashRing> m_ObjectDashRing;
	std::vector<ObjectReverseRing> m_ObjectReverseRing;

	HowToPlayer* m_pHPlayer;

	// ステージ管理用変数
	HowToStageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthNum];

	int m_tempNum;

	// 背景
	int m_hBg;
};

