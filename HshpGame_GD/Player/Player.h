#include "game.h"
#include <memory>

class SceneMain;
class Stage;
class EffectRing;

class Player
{
public:
	Player() :
		m_pMain(nullptr),
		m_pStage(nullptr),
		m_updateFunc(&Player::CubeNormalUpdate),
		m_pos(),
		m_vec(),
		m_lastPos(),
		m_hPlayer(-1),
		m_hDeathEffect(-1),
		m_hDeathSound(-1),
		m_playerScale(0.0),
		m_effectHeight(0),
		m_effectWidth(0),
		m_angle(0.0f),
		m_lastAngle(),
		m_countFrame(0),
		m_deathCountFrame(0),
		m_brightness(0),
		m_tBrightness(0),
		m_isMoveRight(true),
		m_isRevGravity(false),
		m_isDashRingEnabled(false),
		m_isField(false),
		m_isScroll(false),
		m_isStageClear(false),
		m_isDead(false)
	{}
	virtual ~Player() {}

	void SetStage(Stage* stage) { m_pStage = stage; }
	void SetMain(SceneMain* main) { m_pMain = main; }

	// プレイヤーの初期化
	void Init(int playerHandle, int playerDeathEffect, int hDeathSound);

	void End();

	// プレイヤーのスポーン位置をセット
	void SetSpawnPos();

	// メンバ関数ポインタの中身を変更
	void ChangeUpdateType();
	// プレイヤーの更新処理
	void Update(const InputState& input);

	// オブジェクトと当たった時の処理
	void OnHitObject(const InputState& input);
	
	void OnDead();

	// プレイヤーの描画処理
	void Draw();
	// プレイヤーの移動時のエフェクト
	void DrawMoveEffect();
	// プレイヤーの出現位置強調表示
	void DrawSpawnPos();

	// 右移動するかどうかの設定
	void SetMoveRight(bool isRight) { m_isMoveRight = isRight; }
	// 右移動するかどうか取得
	bool IsMoveRight() const { return m_isMoveRight; }

	// 重力反転しているかを取得
	bool IsRevGravity() const { return m_isRevGravity; }

	// 画面スクロール時の横移動の切り替え
	void SetPlayerVec(int scroll);
	// 横方向のベクトル削除
	void DeleteVecX() { m_vec.x = 0.0f; }

	// 四方向の取得
	float GetLeft() const { return m_pos.x; }
	float GetTop() const { return m_pos.y; }
	float GetRight() const { return m_pos.x + Game::kBlockSize; }
	float GetBottom() const { return m_pos.y + Game::kBlockSize; }

	// プレイヤーの中心座標取得
	float GetCenterX() const { return m_pos.x + (Game::kBlockSize / 2); }	// キューブの中心
	float GetCenterY() const { return m_pos.y + (Game::kBlockSize / 2); }

	// クリアしたかどうかを取得
	bool IsStageClear() const { return m_isStageClear; }
	// 死亡判定を true にする
	void SetDead() { m_isDead = true; }
	// 死亡判定を取得
	bool IsDead() const { return m_isDead; }

	// プレイヤーの座標取得
	Vec2 GetPos() const { return m_pos; }

private:
	std::shared_ptr<EffectRing> m_pEffectRing;

	// ポインタ
	Stage* m_pStage;
	SceneMain* m_pMain;

	// キューブの通常時の更新処理
	void CubeNormalUpdate(const InputState& input);
	// キューブの重力反転時の更新処理
	void CubeRevGravityUpdate(const InputState& input);
	// プレイヤー死亡時の更新処理
	void GoalUpdate(const InputState& input);

	using m_tUpdateFunc = void (Player::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	// プレイヤー座標
	Vec2 m_pos;
	// 移動量
	Vec2 m_vec;

	Vec2 m_lastPos[5];

	// 画像データ
	int m_hPlayer;
	int m_hDeathEffect;

	// 音データ
	int m_hDeathSound;

	// プレイヤーのサイズ
	double m_playerScale;

	// エフェクト画像サイズ
	float m_effectHeight;
	float m_effectWidth;
	// 画像表示角度
	double m_angle;
	double m_lastAngle[5];

	// フレーム数をカウント
	int m_countFrame;
	int m_deathCountFrame;
	// スタートカウントダウン時明るさ
	int m_brightness;
	int m_tBrightness;

	// 移動方向
	bool m_isMoveRight;
	// 重力方向
	bool m_isRevGravity;
	// ダッシュリング用の判定
	bool m_isDashRingEnabled;
	// 地面との当たり判定用変数
	bool m_isField;
	// スクロール中かどうか
	bool m_isScroll;

	// ゴール判定
	bool m_isStageClear;
	// 死亡判定
	bool m_isDead;
};
