#pragma once
#include "Engine/GameObject.h"

class Ground;//前方宣言

class Player :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetGround(Ground* ground) { ground_ = ground; }
private:
	int hWalkModel_;//歩き
	int hIdleModel_;//待機
	int hRunModel_;//走り
	int warpCooldown_ = 0;
	bool isRunning_ = false;
	float moveSpeed_ = 3.0f;
	float runSpeed_ = 6.0f;
	Ground* ground_;//地面オブジェクトのポインタ
};

