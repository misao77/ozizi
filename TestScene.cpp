#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "Enemy.h"
#include "Engine/Text.h"

namespace
{
	int myScore = 10;
}


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	//pWp = Instantiate<Weapon>(this);
	Player* pPlayer =Instantiate <Player>(this);
	Ground* pGround =Instantiate<Ground>(this);
	pPlayer->SetGround(pGround);
	Enemy* pEnemy = Instantiate<Enemy>(this);
	//Food* pFood = Instantiate<Food>(this);


	Camera::SetPosition({ 0,10,-20 });
	Camera::SetTarget({ 0,0,0 });

	pText_ = new Text;
	pText_->Initialize();

}

//更新
void TestScene::Update()
{
}
//＜やること＞餌を数えて残り餌数を表示、スコアを表示
//sprintfでcの文字配列を直で使ても

//描画
void TestScene::Draw()
{
	std::string scrText;
	scrText = "SCORE" + std::to_string(myScore);
	pText_->Draw(20, 20, scrText.c_str());
	int esaCount, normalEsaCount, powerEsaCount;
	std::tuple<int, int, int>esa = pGround->GetEsaCount();
	esaCount
}

//開放
void TestScene::Release()
{
	pText_->Release();
}
