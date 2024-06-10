#include "SceneHowTo.h"
#include "game.h"
#include "SceneClear.h"
#include "HowToStage.h"
#include "HowToPlayer.h"
#include <cassert>
#include <memory>
#include <string>

namespace
{
	// スタート時の遅延時間
	constexpr int kStartDelay = 0;
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;

	// キー表示位置
	constexpr int kKeyDrawY = Game::kScreenHeightHalf + 7;
	constexpr int kKeyDrawH = Game::kScreenHeightHalf + 63;
	constexpr int kKeyDrawW = 50;

	// テキスト点滅タイミング
	constexpr int kFlashingTime = 300;

	// オブジェクト名
	const char* const kNextStageText = "で下へ";
	const char* const kNextGimmickText = "で次へ";
	const char* const kJumpText = "でジャンプ";
	const char* const kGimmickText = "でギミック使用";
	const char* const kBackTitleText = "でタイトルへ";
}

SceneHowTo::SceneHowTo() :
	m_pHPlayer(std::make_shared<HowToPlayer>()),
	m_pHStage(std::make_shared<HowToStage>()),
	m_updateFunc(&SceneHowTo::SceneStartUpdate),
	m_hPlayer(-1),
	m_hDeathEffect(-1),
	m_hObjectSpike(-1),
	m_hPortal(-1),
	m_hBlock(-1), 
	m_hJumpPad(-1),
	m_hBg(-1),
	m_hPadImg(-1),
	m_hTutoText(-1),
	m_hFontS(-1),
	m_hFontL(-1),
	m_hDeathSound(-1),
	m_hPracBgm(-1),
	m_fadeCount(0),
	m_countPadNum(0),
	m_countFrame(0),
	m_startDelay(0),
	m_startTextSize(0),
	m_gameOverDelay(0),
	m_isPrac(true),
	m_isEnd(false),
	m_pClear(nullptr)
{
}

SceneHowTo::~SceneHowTo()
{
}

// 初期化
void SceneHowTo::Init(int font24, int font48)
{
	m_hFontS = font24;
	m_hFontL = font48;
	
	// シーン終了変数を初期化
	m_isEnd = false;
	m_isPrac = true;

	m_countPadNum = 1;
	m_fadeCount = 255;
	m_updateFunc = &SceneHowTo::SceneStartUpdate;

	// アドレスの設定
	m_pHPlayer->SetStage(m_pHStage.get());
	m_pHStage->SetPlayer(m_pHPlayer.get());

	// 画像読み込み
	m_hPlayer = LoadGraph(Game::kPlayerImg);
	m_hDeathEffect = LoadGraph(Game::kPlayerDeathEffectImg);
	m_hObjectSpike = LoadGraph(Game::kObjectSpikeImg);
	m_hPortal = LoadGraph(Game::kPortalImg);
	m_hBlock = LoadGraph(Game::kBlockImg);
	m_hJumpPad = LoadGraph(Game::kJumpPadImg);
	m_hBg = LoadGraph(Game::kBgImg);
	m_hPadImg = LoadGraph(Game::kPadImg);
	m_hTutoText = LoadGraph("imagedata/tutorialText.png");

	// 音データの読み込み
	m_hDeathSound = LoadSoundMem(Game::kDeathSound);
	m_hPracBgm = LoadSoundMem(Game::kTutorialBgm);

	// スタート遅延の初期化
	m_startDelay = kStartDelay;
	m_startTextSize = 100;

	m_pHStage->SetFirstStage();

	OnGameStart();

	m_pHPlayer->SetSpawnPos(m_isPrac);
}

void SceneHowTo::OnGameStart()
{
	// 各時間用変数の初期化
	m_gameOverDelay = kGameOverDelay;

	// プレイヤー初期化
	m_pHPlayer->Init(m_hPlayer, m_hDeathEffect, m_hDeathSound, m_isPrac);

	// ステージ初期化
	m_pHStage->Init(m_hObjectSpike, m_hBg, m_hPortal, m_hBlock, m_hJumpPad);
}

void SceneHowTo::PlayGameSound()
{
	if (!CheckSoundMem(m_hPracBgm)) PlaySoundMem(m_hPracBgm, DX_PLAYTYPE_BACK);
}

// 終了処理
void SceneHowTo::End()
{
	StopSoundMem(m_hPracBgm);

	// 画像データの削除
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hDeathEffect);
	DeleteGraph(m_hObjectSpike);
	DeleteGraph(m_hPortal);
	DeleteGraph(m_hBlock);
	DeleteGraph(m_hBg);
	DeleteGraph(m_hPadImg);
	DeleteGraph(m_hTutoText);

	DeleteSoundMem(m_hDeathSound);
	DeleteSoundMem(m_hPracBgm);
}

// 毎フレームの処理
void SceneHowTo::Update(const InputState& input, NextSceneState& nextScene)
{
	(this->*m_updateFunc)(input, nextScene);

	m_countFrame++;
	if(m_countFrame % 8 == 0)m_countPadNum++;
	if (m_countPadNum > 4) m_countPadNum = 1;
}

// 毎フレームの描画
void SceneHowTo::Draw()
{
	m_pHStage->Draw();

	if (m_pHPlayer->IsStageClear()) return;

	// プレイヤーの描画
	m_pHPlayer->Draw();

	DrawHowTo();

	DrawGraph(0,0,m_hTutoText, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneHowTo::DrawHowTo()
{
	DrawBox(0, static_cast<int>(Game::kBlockSize * 11), Game::kScreenWidth, static_cast<int>(Game::kBlockSize * 13), 0x000000, true);
	
	int textDrawX = Game::kScreenWidthHalf + 200, textDrawY = Game::kScreenHeightHalf + 27;
	std::string drawTextMessage;
	int imgX, imgY, imgW, imgH;
	imgX = Game::kPadChipSize, imgY = Game::kPadChipSize * 14, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

	if (m_isPrac)
	{
		drawTextMessage = kNextStageText;
	}
	else
	{
		drawTextMessage = kNextGimmickText;
	}

	if (m_countFrame > kFlashingTime)
	{
		if ((m_countFrame / 10) % 4 != 0)
		{
			DrawFormatStringToHandle(textDrawX, textDrawY, 0xffffff, m_hFontS, "%s", drawTextMessage.c_str());
			DrawRectExtendGraph(textDrawX - 50, kKeyDrawY, textDrawX, kKeyDrawH, imgX, imgY, imgW, imgH, m_hPadImg, true);
		}
	}
	else
	{
		DrawFormatStringToHandle(textDrawX, textDrawY, 0xffffff, m_hFontS, "%s", drawTextMessage.c_str());
		DrawRectExtendGraph(textDrawX - 50, kKeyDrawY, textDrawX, kKeyDrawH, imgX, imgY, imgW, imgH, m_hPadImg, true);
	}

	imgX = Game::kPadChipSize * 10, imgY = Game::kPadChipSize * 14, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;
	textDrawX = Game::kScreenWidthHalf + 400;
	DrawFormatStringToHandle(textDrawX, textDrawY, 0xffffff, m_hFontS, "%s", kBackTitleText);
	DrawRectExtendGraph(textDrawX - 50, kKeyDrawY, textDrawX, kKeyDrawH, imgX, imgY, imgW, imgH, m_hPadImg, true);

	imgX = Game::kPadChipSize * m_countPadNum, imgY = Game::kPadChipSize * 12;
	if (m_pHStage->GetStageState() == HowToStageState::CubeTest)
	{
		drawTextMessage = kJumpText;
	}
	else
	{
		drawTextMessage = kGimmickText;
	}
	SetFontSize(60);

	textDrawX = 500;
	textDrawY = Game::kScreenHeightHalf + 15;
	DrawFormatStringToHandle(textDrawX, textDrawY, 0xffff00, m_hFontL, "%s", drawTextMessage.c_str());
	DrawRectExtendGraph(textDrawX - 50, kKeyDrawY, textDrawX, kKeyDrawH, imgX, imgY, imgW, imgH, m_hPadImg, true);

	m_startTextSize--;
	if (m_startTextSize < 60) m_startTextSize = 60;

	SetFontSize(20);
}

void SceneHowTo::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_updateFunc = &SceneHowTo::SceneEndUpdate;
		return;
	}

	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		OnGameStart();
		return;
	}

	m_startDelay--;
	if (m_startDelay > 0) return;
	else m_startDelay = 0;

	if (input.IsTriggered(InputType::enter))
	{
		m_countFrame = 0;
		
		if (m_pHStage->GetStageState() == HowToStageState::RevRingTest && !m_isPrac)
		{
			m_updateFunc = &SceneHowTo::SceneEndUpdate;
			return;
		}
		
		if (m_isPrac)
		{
			m_isPrac = false;
		}
		else
		{
			m_isPrac = true;
			m_pHStage->SetNextStageState();
		}

		OnGameStart();
		return;
	}

	PlayGameSound();

	m_pHStage->Update();

	m_pHPlayer->Update(input, m_isPrac);

	// プレイヤーの死亡判定が true の場合
	if (m_pHPlayer->IsDead())
	{
		if (m_gameOverDelay < 0)
		{
			OnGameStart();
			return;
		}
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_gameOverDelay--;
		return;
	}
}

void SceneHowTo::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount -= 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_hPracBgm);

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneHowTo::NormalUpdate;
	}
}

void SceneHowTo::SceneEndUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount += 5;
	ChangeVolumeSoundMem(255 - m_fadeCount, m_hPracBgm);

	if (m_fadeCount > 255)
	{
		nextScene = NextSceneState::nextTitle;
		m_isEnd = true;
	}
}