#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase():
	m_isEnd(false)
	{}
	virtual ~SceneBase() {}

	// 初期化
	virtual void Init() {}
	// 削除
	virtual void End() {}
	// 更新
	virtual void Update() {}
	// 描画
	virtual void Draw() {}

	// シーン終了
	virtual bool IsEnd() { return m_isEnd; }

protected:
	bool m_isEnd;
};