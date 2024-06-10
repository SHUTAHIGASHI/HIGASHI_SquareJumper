#include "HowToStage.h"
#include "game.h"
#include "HowToPlayer.h"
#include <cassert>

namespace
{
	//マップデータ
	// 1 ゴール / 2 ブロック / 3 ジャンプリング / 4 ジャンプパッド 
	// 5 スパイク / 6 グラビティリング / 7 ダッシュリング / 8 リバースリング

	//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	// ステージ１
	int CubeTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2}
	};

	// ステージ２
	int JumpRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,0,4,0,0,4,0,0,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,3,0,5,5,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,2,0,4,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	// ステージ３
	int GravityRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{5,5,5,5,5,5,5,5,5,5,5,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5,5,5},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2}
	};

	// ステージ４
	int DashRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
		// ステージ地面
	};

	// ステージ５
	int RevRingTest[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0}
	};
}

namespace
{
	// スクロールの速度
	constexpr int kScrollSpeed = 7;

	// サイズ調整用定数
	constexpr int kResizeScale = 8;

	// リングの当たり判定範囲
	constexpr int kRingResizeScale = 10;
}

HowToStage::HowToStage() :
	m_updateFunc(&HowToStage::NormalUpdate),
	m_pHPlayer(nullptr),
	m_stageState(HowToStageState::CubeTest),
	m_stage(),
	m_tempNum(0),
	m_hBg(-1)
{
}

void HowToStage::Init(int hSpike, int hBg, int hPortal, int hBlock, int hJumpPad)
{
	End();
	StageManage();

	m_hBg = hBg;

	InitStage(hSpike, hPortal, hBlock, hJumpPad);
	SetStage();
}

void HowToStage::InitStage(int hSpike, int hPortal, int hBlock, int hJumpPad)
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if (m_stage[i][j] == 2)
			{
				m_ObjectBlock.push_back(ObjectBlock());
			}
			if (m_stage[i][j] == 3)
			{
				m_ObjectJumpRing.push_back(ObjectJumpRing());
			}
			if (m_stage[i][j] == 4)
			{
				m_ObjectJumpPad.push_back(ObjectJumpPad());
			}
			if (m_stage[i][j] == 5)
			{
				m_ObjectSpike.push_back(ObjectSpike());
			}
			if (m_stage[i][j] == 6)
			{
				m_ObjectGravityRing.push_back(ObjectGravityRing());
			}
			if (m_stage[i][j] == 7)
			{
				m_ObjectDashRing.push_back(ObjectDashRing());
			}
			if (m_stage[i][j] == 8)
			{
				m_ObjectReverseRing.push_back(ObjectReverseRing());
			}
		}
	}

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		m_ObjectBlock[i].Init(hBlock);
	}

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Init();
	}

	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		m_ObjectJumpPad[i].Init(hJumpPad);
	}

	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		m_ObjectSpike[i].Init(hSpike);
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Init();
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Init();
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Init();
	}
}

void HowToStage::End()
{
	m_ObjectBlock.clear();
	m_ObjectJumpRing.clear();
	m_ObjectJumpPad.clear();
	m_ObjectSpike.clear();
	m_ObjectGravityRing.clear();
	m_ObjectDashRing.clear();
	m_ObjectReverseRing.clear();
}

void HowToStage::SetStage()
{
	int countGoal = 0;
	int countBlock = 0;
	int countJumpRing = 0;
	int countJumpPad = 0;
	int countSpike = 0;
	int countGravRing = 0;
	int countDashRing = 0;
	int countRevRing = 0;

	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			float blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;

			if (m_stage[i][j] == 2)
			{
				m_ObjectBlock[countBlock].SetPos(blockPosX, blockPosY);
				countBlock++;
				if (countBlock > m_ObjectBlock.size()) countBlock = static_cast<int>(m_ObjectBlock.size());
			}
			if (m_stage[i][j] == 3)
			{
				m_ObjectJumpRing[countJumpRing].SetPos(blockPosX, blockPosY);
				countJumpRing++;
				if (countJumpRing > m_ObjectJumpRing.size()) countJumpRing = static_cast<int>(m_ObjectJumpRing.size());
			}
			if (m_stage[i][j] == 4)
			{
				m_ObjectJumpPad[countJumpPad].SetPos(blockPosX, blockPosY);
				countJumpPad++;
				if (countJumpPad > m_ObjectJumpPad.size()) countJumpPad = static_cast<int>(m_ObjectJumpPad.size());
			}
			if (m_stage[i][j] == 5)
			{
				m_ObjectSpike[countSpike].SetPos(blockPosX, blockPosY);
				countSpike++;
				if (countSpike > m_ObjectSpike.size()) countSpike = static_cast<int>(m_ObjectSpike.size());
			}
			if (m_stage[i][j] == 6)
			{
				m_ObjectGravityRing[countGravRing].SetPos(blockPosX, blockPosY);
				countGravRing++;
				if (countGravRing > m_ObjectGravityRing.size()) countGravRing = static_cast<int>(m_ObjectGravityRing.size());
			}
			if (m_stage[i][j] == 7)
			{
				m_ObjectDashRing[countDashRing].SetPos(blockPosX, blockPosY);
				countDashRing++;
				if (countDashRing > m_ObjectDashRing.size()) countDashRing = static_cast<int>(m_ObjectDashRing.size());
			}
			if (m_stage[i][j] == 8)
			{
				m_ObjectReverseRing[countRevRing].SetPos(blockPosX, blockPosY);
				countRevRing++;
				if (countRevRing > m_ObjectReverseRing.size()) countRevRing = static_cast<int>(m_ObjectReverseRing.size());
			}
		}
	}
}

void HowToStage::Update()
{
	(this->*m_updateFunc)();
}

void HowToStage::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	DrawExtendGraph(bgX + (Game::kScreenWidth) * 2, bgY, bgW + (Game::kScreenWidth) * 2, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Draw(0,0xFFD700);
	}

	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		m_ObjectJumpPad[i].Draw(0);
	}

	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		m_ObjectSpike[i].Draw(0);
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Draw(0,0x00bfff);
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Draw(0,0xdc143c);
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Draw(0,0x9932cc);
	}

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		m_ObjectBlock[i].Draw(0);
	}
}

// プレイヤーとオブジェクトの当たり判定チェック
bool HowToStage::CollisionCheck(const Vec2 playerPos, ObjectType& object)
{
	int playerScale = 1;

	for (int i = 0; i < m_ObjectBlock.size(); i++)
	{
		if (m_ObjectBlock[i].CollisionCheck(m_pHPlayer->GetPos()))
		{
			m_tempNum = i;
			object = ObjectType::Block;
			return true;
		}
	}
	// ジャンプリングの当たり判定
	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		if (m_ObjectJumpRing[i].CollisionCheck(m_pHPlayer->GetPos(), kRingResizeScale))
		{
			object = ObjectType::JumpRing;
			return true;
		}
	}
	// ジャンプパッドの当たり判定
	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		if (m_ObjectJumpPad[i].CollisionCheck(m_pHPlayer->GetPos(), static_cast<int>(Game::kBlockSize - (Game::kBlockSize / 4))))
		{
			object = ObjectType::JumpPad;
			return true;
		}
	}
	// スパイクの当たり判定
	for (int i = 0; i < m_ObjectSpike.size(); i++)
	{
		if (m_ObjectSpike[i].CollisionCheck(m_pHPlayer->GetPos(), kResizeScale, playerScale))
		{
			object = ObjectType::Spike;
			return true;
		}
	}
	// グラビティリングの当たり判定
	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		if (m_ObjectGravityRing[i].CollisionCheck(m_pHPlayer->GetPos(), kRingResizeScale))
		{
			object = ObjectType::GravityRing;
			return true;
		}
	}
	// ダッシュリングの当たり判定
	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		if (m_ObjectDashRing[i].CollisionCheck(m_pHPlayer->GetPos(), kRingResizeScale))
		{
			object = ObjectType::DashRing;
			return true;
		}
	}
	// リバースリングの当たり判定
	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		if (m_ObjectReverseRing[i].CollisionCheck(m_pHPlayer->GetPos(), kRingResizeScale))
		{
			object = ObjectType::ReverseRing;
			return true;
		}
	}

	// 当たっていない場合、falseを返す
	return false;
}

// オブジェクトがプレイヤーの下にあるかどうか
bool HowToStage::IsUnder(float& tempPos)
{
	if (m_ObjectBlock[m_tempNum].GetTop() > m_pHPlayer->GetCenterY())
	{
		// ブロックの座標を代入
		tempPos = m_ObjectBlock[m_tempNum].GetTop() - Game::kBlockSize;
		return true;
	}

	// 下ではない場合、falseを返す
	return false;
}

bool HowToStage::IsTop(float& tempPos)
{
	if (m_ObjectBlock[m_tempNum].GetTop() + Game::kBlockSize < m_pHPlayer->GetCenterY())
	{
		// ブロックの座標を代入
		tempPos = m_ObjectBlock[m_tempNum].GetTop() + Game::kBlockSize;
		return true;
	}

	// 上ではない場合、falseを返す
	return false;
}

void HowToStage::StageManage()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if (m_stageState == HowToStageState::CubeTest)
			{
				m_stage[i][j] = CubeTest[i][j];
			}
			else if (m_stageState == HowToStageState::JumpRingTest)
			{
				m_stage[i][j] = JumpRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::GravityRingTest)
			{
				m_stage[i][j] = GravityRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::DashRingTest)
			{
				m_stage[i][j] = DashRingTest[i][j];
			}
			else if (m_stageState == HowToStageState::RevRingTest)
			{
				m_stage[i][j] = RevRingTest[i][j];
			}
			else
			{
				assert(0);
			}
		}
	}
}

void HowToStage::SetNextStageState()
{
	m_stageState = static_cast<HowToStageState>(static_cast<int>(m_stageState) + 1);
	if (m_stageState == HowToStageState::End) m_stageState = HowToStageState::CubeTest;
}

void HowToStage::NormalUpdate()
{
	if (m_pHPlayer->IsDead()) return;

	for (int i = 0; i < m_ObjectJumpRing.size(); i++)
	{
		m_ObjectJumpRing[i].Update();
	}

	for (int i = 0; i < m_ObjectJumpPad.size(); i++)
	{
		m_ObjectJumpPad[i].Update();
	}

	for (int i = 0; i < m_ObjectGravityRing.size(); i++)
	{
		m_ObjectGravityRing[i].Update();
	}

	for (int i = 0; i < m_ObjectDashRing.size(); i++)
	{
		m_ObjectDashRing[i].Update();
	}

	for (int i = 0; i < m_ObjectReverseRing.size(); i++)
	{
		m_ObjectReverseRing[i].Update();
	}
}
