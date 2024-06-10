#include "SceneTitle.h"
#include <DxLib.h>
#include <string>
#include "game.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneStageSelect.h"

namespace
{
	// �^�C�g�����b�Z�[�W
	const char* const kGameTitle = "SquareJumper";
	const char* const kSelectMessage = "�őI��";

	// ���j���[���b�Z�[�W
	const char* const kArcadeText = "�m�[�}�����[�h";
	const char* const kChallengeModeText = "�`�������W���[�h";
	const char* const kStageSelectText = "�X�e�[�W�I��";
	const char* const kRankText = "�����L���O";
	const char* const kGameEndText = "�Q�[���I��";

	// ���j���[�̑I�����ڂ̐�
	constexpr int kMenuMax = 5;

	// ���j���[�̃T�C�Y
	constexpr int kMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;
	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
	constexpr int kMenuMiniW = 200;

	// �f����\������܂ł̎���
	constexpr int kDrawDemoTime = 600;
}

// ������
void SceneTitle::Init(int fontS, int fontL)
{
	m_hFontS = fontS;
	m_hFontL = fontL;

	// �V�[���I���� false ����
	m_isEnd = false;

	m_countFrame = 0;
	m_textScroll = -Game::kScreenWidth;
	m_selectPos = 0;
	m_selectTutorial = 0;
	m_textTimer = 10;
	m_scroll = 0;
	m_scrollAcc = 7;
	m_fadeCount = 0;

	m_hBg = LoadGraph(Game::kBgImg);
	m_hPadImg = LoadGraph(Game::kPadImg);
	m_hTitleImg = LoadGraph("imageData/GameTitle.png");
	m_hSelectSound = LoadSoundMem(Game::kSelectSound);

	m_scroll = m_pStageSelect->GetScroll();

	m_updateFunc = &SceneTitle::SceneStartUpdate;
	m_drawFunc = &SceneTitle::NormalDraw;
	if (m_pManager->GetLastScene() != SceneManager::kSceneStageSelect)
	{
		m_fadeCount = 255;
		m_textScroll = 0;
	}
}

// �I������
void SceneTitle::End()
{
	StopMusic();

	DeleteGraph(m_hBg);
	DeleteGraph(m_hPadImg);
	DeleteGraph(m_hTitleImg);

	DeleteSoundMem(m_hSelectSound);
}

// �X�V����
void SceneTitle::Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene)
{	
	if (!CheckSoundMem(m_hLoopBgm))
	{
		PlaySoundMem(m_hLoopBgm, DX_PLAYTYPE_BACK);
	}

	if (m_textTimer > 1000) m_textTimer = 10;

	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;

	(this->*m_updateFunc)(input, isGameEnd, nextScene);

	if (input.IsTriggered(InputType::all))
	{
		m_countFrame = 0;
	}

	if (m_countFrame > kDrawDemoTime)
	{
		m_updateFunc = &SceneTitle::SceneEndUpdate;
		nextScene = NextSceneState::nextDemo;
	}
	m_countFrame++;
}

// �`�揈��
void SceneTitle::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0 + m_textScroll, 0, m_hTitleImg, true);

	int drawX = 0, drawY = 0;
	int imgX = Game::kPadChipSize, imgY = Game::kPadChipSize;
	int imgW = Game::kPadChipSize, imgH = Game::kPadChipSize;

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	if (m_textTimer > 0)
	{		
		if ((m_textTimer / 10) % 4 != 0)
		{
			drawX = (Game::kScreenWidthHalf - GetDrawStringWidth(kSelectMessage, 6) / 2) + 15, drawY = Game::kScreenHeightHalf + 300;
			// �^�C�g���̃e�L�X�g��\��
			DrawStringToHandle(drawX + m_textScroll, drawY, kSelectMessage, 0xe9e9e9, m_hFontS);

			imgY = Game::kPadChipSize * 14;
			DrawRectExtendGraph((drawX - 50) + m_textScroll, drawY - 10, drawX + m_textScroll, drawY + 40, imgX, imgY, imgW, imgH, m_hPadImg, true);
		}

		m_textTimer++;
	}

	(this->*m_drawFunc)();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::StopMusic()
{
	if (m_pManager->GetNextScene() != NextSceneState::nextStageSelect &&
		m_pManager->GetNextScene() != NextSceneState::nextDemo)
	{
		StopSoundMem(m_hLoopBgm);
	}
}

void SceneTitle::NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::start))
	{
		isGameEnd = true;
		return;
	}

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		PlaySoundMem(m_hSelectSound, DX_PLAYTYPE_BACK);

		switch (m_selectPos)
		{
		case 0:
			m_updateFunc = &SceneTitle::ModeSelectUpdate;
			m_drawFunc = &SceneTitle::ModeSelectDraw;
			return;
		case 1:
			m_pMain->SetChallengeMode();
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextGameMain;
			return;
		case 2:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextStageSelect;
			return;
		case 3:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextRanking;
			return;
		case 4:
			isGameEnd = true;
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

	if (m_selectPos > 4) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 4;
}

void SceneTitle::ModeSelectUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::start))
	{
		isGameEnd = true;
		return;
	}

	if (input.IsTriggered(InputType::back))
	{
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_drawFunc = &SceneTitle::NormalDraw;
	}

	// �L�[���͂��������ꍇ�A�V�[���I���� true �ɂ���
	if (input.IsTriggered(InputType::enter))
	{
		m_pMain->SetArcadeMode();
		m_updateFunc = &SceneTitle::SceneEndUpdate;
		PlaySoundMem(m_hSelectSound, DX_PLAYTYPE_BACK);

		switch (m_selectTutorial)
		{
		case 0:
			nextScene = NextSceneState::nextGameMain;
			m_pMain->SetDoTutorialMode();
			return;
		case 1:
			nextScene = NextSceneState::nextGameMain;
			return;
		}
	}

	if (input.IsTriggered(InputType::right))
	{
		m_selectTutorial++;
	}
	if (input.IsTriggered(InputType::left))
	{
		m_selectTutorial--;
	}

	if (m_selectTutorial > 1) m_selectTutorial = 1;
	if (m_selectTutorial < 0) m_selectTutorial = 0;

	if (input.IsTriggered(InputType::down))
	{
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_drawFunc = &SceneTitle::NormalDraw;
		m_selectPos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_drawFunc = &SceneTitle::NormalDraw;
		m_selectPos--;
	}

	if (m_selectPos > 4) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 4;
}

void SceneTitle::SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (m_pManager->GetLastScene() == SceneManager::kSceneStageSelect)
	{
		m_textScroll += 100;

		if (m_textScroll > 0)
		{
			m_textScroll = 0;
			m_updateFunc = &SceneTitle::NormalUpdate;
		}
	}
	else
	{
		m_fadeCount -= 5;
		if (m_pManager->GetLastScene() != SceneManager::kSceneDemo) ChangeVolumeSoundMem(255 - m_fadeCount, m_hLoopBgm);

		if (m_fadeCount < 0)
		{
			m_fadeCount = 0;
			m_updateFunc = &SceneTitle::NormalUpdate;
		}
	}
}

void SceneTitle::SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene)
{
	if (nextScene == NextSceneState::nextStageSelect)
	{
		m_textScroll -= 100;

		if (m_textScroll < -Game::kScreenWidth)
		{
			m_isEnd = true;
		}
	}
	else
	{
		m_fadeCount += 5;
		if (nextScene != NextSceneState::nextDemo) ChangeVolumeSoundMem(255 - m_fadeCount, m_hLoopBgm);

		if (m_fadeCount > 255)
		{
			m_isEnd = true;
		}
	}
}

void SceneTitle::NormalDraw()
{
	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuH + (kMenuH * i), 0xE9E9E9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) drawText = kArcadeText;
		else if (i == 1) drawText = kChallengeModeText;
		else if (i == 2) drawText = kStageSelectText;
		else if (i == 3) drawText = kRankText;
		else if (i == 4) drawText = kGameEndText;

		DrawFormatStringToHandle(menuX + 20 + m_textScroll, menuY, 0xE9E9E9, m_hFontS, "%s", drawText.c_str());
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuH + (kMenuH * m_selectPos), 0x60CAAD, true);

	menuY = menuY + (kMenuH / 2) - 15;
	if (m_selectPos == 0) drawText = kArcadeText;
	else if (m_selectPos == 1) drawText = kChallengeModeText;
	else if (m_selectPos == 2) drawText = kStageSelectText;
	else if (m_selectPos == 3) drawText = kRankText;
	else if (m_selectPos == 4) drawText = kGameEndText;

	DrawFormatStringToHandle(menuX + 22 + m_textScroll, menuY + 5, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20 + m_textScroll, menuY, 0xe9e9e9, m_hFontS, "%s", drawText.c_str());
}

void SceneTitle::ModeSelectDraw()
{
	int menuX = kMenuX, menuY = kMenuY, menuW = kMenuX + kMenuW, menuH = kMenuY + kMenuH;
	std::string drawText;

	for (int i = 1; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuH + (kMenuH * i), 0xE9E9E9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 1) drawText = kChallengeModeText;
		else if (i == 2) drawText = kStageSelectText;
		else if (i == 3) drawText = kRankText;
		else if (i == 4) drawText = kGameEndText;

		DrawFormatStringToHandle(menuX + 20 + m_textScroll, menuY, 0xE9E9E9, m_hFontS, "%s", drawText.c_str());
	}

	int repos = 0;

	for (int i = 0; i < 2; i++)
	{
		menuX = kMenuX + (kMenuMiniW * i), menuW = menuX + kMenuMiniW;
		menuY = kMenuY, menuH = menuY + kMenuH;
		DrawBox(menuX, menuY +10, menuW, menuH, 0xE9E9E9, false);

		// �t�H���g�T�C�Y�̐ݒ�
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0)
		{
			repos = -6;
			drawText = "�`���[�g���A��";
		}
		else if (i == 1)
		{
			repos = -6;
			drawText = "���C���X�e�[�W";
		}

		DrawFormatStringToHandle(menuX + 20 + repos, menuY + 10, 0xE9E9E9, m_hFontS, "%s", drawText.c_str());
	}

	menuX = kMenuX + (kMenuMiniW * m_selectTutorial), menuW = menuX + kMenuMiniW;
	menuY = kMenuY, menuH = menuY + kMenuH;
	DrawBox(menuX, menuY +10, menuW, menuH, 0x60caad, true);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);
	menuY = menuY + (kMenuH / 2) - 15;

	if (m_selectTutorial == 0)
	{
		drawText = "�`���[�g���A��";
		repos = -6;
	}
	else if (m_selectTutorial == 1)
	{
		drawText = "���C���X�e�[�W";
		repos = -6;
	}

	DrawFormatStringToHandle(menuX + 20 + repos, menuY + 15, 0x333333, m_hFontS, "%s", drawText.c_str());
	DrawFormatStringToHandle(menuX + 20 + repos, menuY + 10, 0xE9E9E9, m_hFontS, "%s", drawText.c_str());
}