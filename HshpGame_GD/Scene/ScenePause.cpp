#include "ScenePause.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include <string>

namespace
{
	// タイトル表示までの遅延時間 (2秒)
	constexpr int kTitleDelayMax = 120;

	// テキストサイズ
	constexpr int kTextSizeMin = 50;
	constexpr int kTextSizeMax = 80;

	// テキスト
	const char* const kGameClear = "Pause";
	const char* const kBackText = "閉じる";
	const char* const kSelectText = "選択";

	// メニューメッセージ
	const char* const kRetryText = "リスタート";
	const char* const kBackStageSelectText = "ステージ選択へ";
	const char* const kBackTitleText = "メニューに戻る";

	// メニューの選択項目の数
	constexpr int kMenuMax = 3;

	// メニューのサイズ
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void ScenePause::Init(int fontS)
{
	m_updateFunc = &ScenePause::NormalUpdate;
	m_drawFunc = &ScenePause::NormalDraw;

	m_hPadImg = LoadGraph(Game::kPadImg);
	m_hSelectSound = LoadSoundMem(Game::kSelectSound);

	m_hFontS = fontS;

	m_textScale = kTextSizeMin;
	m_textScaleAcc = 1;
	m_selectPos = 0;

	m_isNextStage = false;
}

// 終了処理
void ScenePause::End()
{
	DeleteGraph(m_hPadImg);

	DeleteSoundMem(m_hSelectSound);
}

// 更新
void ScenePause::Update(const InputState& input, NextSceneState& nextScene, bool& isEnd)
{
	m_textTimer++;

	(this->*m_updateFunc)(input, nextScene, isEnd);
}

void ScenePause::Draw()
{
	(this->*m_drawFunc)();
}

void ScenePause::DrawPadText()
{
	int drawX, drawY;
	int imgX, imgY, imgW, imgH;
	// フォントサイズの設定
	SetFontSize(25);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 8 != 0)
		{
			drawX = 100, drawY = Game::kScreenHeight - 80;
			// タイトルのテキストを表示
			DrawStringToHandle(drawX, drawY, kBackText, 0xe9e9e9, m_hFontS);

			imgX = Game::kPadChipSize, imgY = Game::kPadChipSize * 11, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

			DrawRectExtendGraph(drawX - 50, drawY - 15, drawX, drawY + 35, imgX, imgY, imgW, imgH, m_hPadImg, true);
		}

		m_textTimer++;
	}

	drawX = 250, drawY = Game::kScreenHeight - 80;
	// タイトルのテキストを表示
	DrawStringToHandle(drawX, drawY, kSelectText, 0xe9e9e9, m_hFontS);

	imgX = Game::kPadChipSize, imgY = Game::kPadChipSize * 14, imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

	DrawRectExtendGraph(drawX - 50, drawY - 15, drawX, drawY + 35, imgX, imgY, imgW, imgH, m_hPadImg, true);

	SetFontSize(20);
}

void ScenePause::NormalUpdate(const InputState& input, NextSceneState& nextScene, bool& isPEnd)
{
	if (m_textScale > kTextSizeMax) m_textScaleAcc *= -1;
	else if (m_textScale < kTextSizeMin) m_textScaleAcc *= -1;
	m_textScale += m_textScaleAcc;

	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		PlaySoundMem(m_hSelectSound, DX_PLAYTYPE_BACK);

		switch (m_selectPos)
		{
		case 0:
			m_pMain->OnRetry();
			return;
		case 1:
			isPEnd = true;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 2:
			isPEnd = true;
			nextScene = NextSceneState::nextTitle;
			return;
		default:
			break;
		}
	}

	if (input.IsTriggered(InputType::down))
	{
		m_selectPos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_selectPos--;
	}

	if (m_selectPos > 2) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 2;
}

void ScenePause::NormalDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(m_textScale);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2 + 3, Game::kScreenHeight / 4 + 5, kGameClear, 0x60CAAD);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameClear, 10) / 2, Game::kScreenHeight / 4, kGameClear, 0xe9e9e9);
	SetFontSize(20);

	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX, menuY, menuW, menuH + (kMenuH * i), 0xe9e9e9, false);

		// フォントサイズの設定
		SetFontSize(20);

		if (i == 0) drawText = kRetryText;
		if (i == 1) drawText = kBackStageSelectText;
		if (i == 2) drawText = kBackTitleText;

		menuY = menuY + (kMenuH / 2) - 15;
		DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX, menuY, menuW, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	if (m_selectPos == 0) drawText = kRetryText;
	if (m_selectPos == 1) drawText = kBackStageSelectText;
	if (m_selectPos == 2) drawText = kBackTitleText;

	menuY = menuY + (kMenuH / 2) - 15;
	DrawFormatStringToHandle(menuX + 22, menuY + 5, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());

	DrawPadText();
}