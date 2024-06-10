#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "Vec2.h"
#include <vector>

enum class NextSceneState
{
	Empty,
	nextTitle,
	nextDemo,
	nextHowTo,
	nextRanking,
	nextStageSelect,
	nextGameMain,
	nextClear
};

enum class ObjectType
{
	Empty,
	GoalGate,
	Block,
	JumpRing,
	JumpPad,
	Spike,
	GravityRing,
	DashRing,
	ReverseRing,
	End
};

namespace Game
{
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif

	// ウィンドウ名
	const char* const kTitleText = "SquareJumper";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// カラーモード
	constexpr int kColorDepth = 32;
	
	// 画像データ
	const char* const kPlayerImg = "imagedata/cube.png";
	const char* const kPlayerDeathEffectImg = "imagedata/deathEffect.png";
	const char* const kObjectSpikeImg = "imagedata/ObjectSpike.png";
	const char* const kPortalImg = "imagedata/OrangePortal.png";
	const char* const kBlockImg = "imagedata/Tileset.png";
	const char* const kJumpPadImg = "imagedata/JumpPad.png";
	const char* const kBgImg = "imagedata/Bg.png";
	const char* const kPadImg = "imagedata/PadImg.png";

	// 音データ
	const char* const kSelectSound = "soundData/Select.mp3";

	// 音楽データ
	const char* const kDeathSound = "soundData/deathSound.mp3";
	const char* const kArcadeBgm = "soundData/Arcade.mp3";
	const char* const kPracBgm = "soundData/pracmode.wav";
	const char* const kChallengeBgm = "soundData/challeBGM.mp3";

	// 基準のフォントサイズ
	constexpr int kFontSize = 60;

	// パッド画像チップサイズ
	constexpr int kPadChipSize = 16;

	// ゲームの基本設定 //
	// プレイヤーの基本設定
	constexpr float kBlockSize = 48.0f;

	// 基本移動速度
	constexpr float kMoveSpeed = 7.0f;

	// ゲームのステージサイズ
	constexpr float kStageUpperLimit = Game::kBlockSize * 4;
	constexpr float kStageLowerLimit = Game::kBlockSize * 20;
	
	// ステージ横幅数
	constexpr int kScreenWidthNum = static_cast<int>(Game::kScreenWidth / Game::kBlockSize);
	constexpr int kScreenWidthTripleNum = static_cast<int>(Game::kScreenWidthTriple / Game::kBlockSize);
	// ステージ縦幅数
	constexpr int kScreenHeightNum = static_cast<int>(Game::kScreenHeight / Game::kBlockSize);

	constexpr int kScreenHeightTripleNum = static_cast<int>(Game::kScreenHeightTriple / Game::kBlockSize);

	// パーティクル用
	constexpr int kParticleNum = 4096;
}