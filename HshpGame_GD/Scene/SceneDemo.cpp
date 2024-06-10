#include "SceneDemo.h"
#include "game.h"
#include "SceneTitle.h"

namespace
{
	// ムービー表示時間
	constexpr int kDrawTime = 2400;
}

SceneDemo::SceneDemo() :
	m_countFrame(0),
	m_fadeCount(0),
	m_textTimer(0),
	m_hDemo(-1),
	m_pTitle(nullptr)
{
}

SceneDemo::~SceneDemo()
{
}

void SceneDemo::Init()
{
	m_isEnd = false;
	
	m_hDemo = LoadGraph("imagedata/stage6demo.mp4");
	PlayMovieToGraph(m_hDemo);

	m_updateFunc = &SceneDemo::SceneStartUpdate;
	m_countFrame = 0;
	m_fadeCount = 255;
	m_textTimer = 0;
}

void SceneDemo::End()
{
	DeleteGraph(m_hDemo);
}

void SceneDemo::Update(const InputState& input, NextSceneState& nextScene)
{
	m_textTimer++;
	m_countFrame++;

	if (!CheckSoundMem(m_pTitle->GetMusicHandle()))
	{
		PlaySoundMem(m_pTitle->GetMusicHandle(), DX_PLAYTYPE_BACK);
	}

	(this->*m_updateFunc)(input, nextScene);
}

void SceneDemo::Draw()
{
	DrawGraph(0, 0, m_hDemo, FALSE);

	SetFontSize(60);
	if (m_textTimer > 0)
	{
		if ((m_textTimer / 10) % 6 != 0)
		{
			DrawString(60, 60, "Demo Play", 0xff0000);
		}

		m_textTimer++;
	}	
	SetFontSize(20);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneDemo::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::all) || m_countFrame > kDrawTime)
	{
		m_updateFunc = &SceneDemo::SceneEndUpdate;
		nextScene = NextSceneState::nextTitle;
		return;
	}
}

void SceneDemo::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount -= 5;

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneDemo::NormalUpdate;
	}
}

void SceneDemo::SceneEndUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount += 5;

	if (m_fadeCount > 255)
	{
		m_isEnd = true;
	}
}

