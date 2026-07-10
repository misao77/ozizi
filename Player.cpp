#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"
#include "Ground.h"

namespace
{
	enum PLAYER_STATE
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_TURN,
		PLAYER_STATE_MAX
	};
	PLAYER_STATE pstate = PLAYER_STATE::PLAYER_IDLE;

	enum PLAYER_DIRECTION
	{
		PLAYER_UP,
		PLAYER_DOWN,
		PLAYER_LEFT,
		PLAYER_RIGHT,
		PLAYER_DIRECTION_MAX

	};
	
	PLAYER_DIRECTION pdirection = PLAYER_DOWN;
	float P_ANGLE[4] = { 180.0f,0.0f,90.0f,270.0f };
	XMVECTOR P_MOVE[4] = { XMVectorSet(0, 0, 1.0f, 0) ,
						XMVectorSet(0, 0, -1.0f, 0) ,
						XMVectorSet(-1.0f, 0, 0, 0),
						XMVectorSet(1.0f, 0, 0, 0)  };
	float TURN_FRAME = 30.0f;

	float turnStartAngle = 0.0f;
	float turnEndAngle = 0.0f;
	PLAYER_DIRECTION turnEndDirection = PLAYER_DOWN;
	float AdjustAngle(float angle) 
	{
		if (angle >= 180.0f)
		{
			angle -= 360.0f;
		}
		else if (angle < -180.0f)
		{
			angle += 360.0f;
		}
		return angle;

	}
	std::vector<std::vector<int>> gmap;

}

Player::Player(GameObject* parent)
	:GameObject(parent), hWalkModel_(-1), hIdleModel_(-1) {
	//swordDirには、初期方向として、ローカルモデルの剣の根っこから
	//先端までのベクトルとして（0,1,0)を代入しておく
	//初期位置は原点
}

void Player::Initialize()
{
	hWalkModel_ = Model::Load("Walking.fbx");
	Model::SetAnimFrame(hWalkModel_, 0, 59, 1.0);


	hIdleModel_ = Model::Load("Idle.fbx");
	Model::SetAnimFrame(hIdleModel_, 0, 117, 1.0);

	if (ground_ != nullptr)
	{
		gmap = ground_->GetMapData();
	}
}

void Player::Update()
{
	//transform_.rotate_.y +=1;
	//static float angle = 0.0;
	//angle = angle + 0.3f;
	//XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(angle));
	//XMMATRIX rotate = XMMatrixRotationY(XMConvertToRadians(angle));
	//XMMATRIX translate = XMMatrixTranslation(1.0f, 0.0f, 0.0f);
	//SetWorldMatrix(scale *  rotate * translate);



	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	const float SPEED = 0.05f;
	float angle = 0.0f;
	static float turnFrame = 0.0f;

	if (pstate != PLAYER_STATE::PLAYER_TURN) {
		pstate = PLAYER_STATE::PLAYER_IDLE;
	}

	//PLAYER_DIRECTION ildDir = pdirection;
	//pstate = PLAYER_STATE::PLAYER_IDLE;


	PLAYER_DIRECTION oldDir = pdirection;


	if (pstate != PLAYER_STATE::PLAYER_TURN)
	{
		if (Input::IsKey(DIK_LEFT)) {
			
			pdirection = PLAYER_DIRECTION::PLAYER_LEFT;
			
			pstate = PLAYER_STATE::PLAYER_WALK;


		}
		if (Input::IsKey(DIK_RIGHT)) {
			
			pdirection = PLAYER_DIRECTION::PLAYER_RIGHT;
			
			pstate = PLAYER_STATE::PLAYER_WALK;

		}
		if (Input::IsKey(DIK_UP)) {
			
			pdirection = PLAYER_DIRECTION::PLAYER_UP;
			
			pstate = PLAYER_STATE::PLAYER_WALK;

		}
		if (Input::IsKey(DIK_DOWN)) {
			
			pdirection = PLAYER_DIRECTION::PLAYER_DOWN;
			
			pstate = PLAYER_STATE::PLAYER_WALK;

		}

	}
	if (oldDir != pdirection)
	{
		pstate = PLAYER_STATE::PLAYER_TURN;
		turnFrame = 0.0f;
		turnStartAngle = P_ANGLE[oldDir];
		float diff = AdjustAngle(P_ANGLE[pdirection] - P_ANGLE[oldDir]);
		turnEndDirection = pdirection;
		turnEndAngle = turnStartAngle + diff;

	}

	//状態切り替えの処理
	//状態ごとの処理

	if (pstate == PLAYER_STATE::PLAYER_TURN)
	{
		turnFrame += 1.0f;
		float t = turnFrame / TURN_FRAME;
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		angle = turnStartAngle + (turnEndAngle - turnStartAngle) * t;
		transform_.rotate_.y = angle;
		if (turnFrame >= TURN_FRAME)
		{
			pdirection = turnEndDirection;
			transform_.rotate_.y = P_ANGLE[pdirection];
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
	}
	else if (pstate != PLAYER_STATE::PLAYER_IDLE)
	{
		move = P_MOVE[pdirection];
		angle = P_ANGLE[pdirection];
		transform_.rotate_.y = angle;
	}
	//else if (pstate == PLAYER_STATE::PLAYER_IDLE)
	//{
	//	//回転中の処理
	//		oldDir; //今の角度
	//		pdirection;//目標の角度
	//}

	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);
	XMFLOAT3 wpos = transform_.position_;
	//壁オブジェクトに食い込んだら戻す
	gmap = ground_->GetMapData();
	int mapX = (int)((wpos.x) + 10) / 2;
	int mapZ = (int)(10 -(wpos.z))/ 2;
	if (gmap[mapZ][mapX] == 1)
	{
		pos = pos - SPEED * move;
		XMStoreFloat3(&transform_.position_, pos);
	}

}

void Player::Draw()
{
	//transform_.scale_ = { 0.01,0.01,0.01 };
	//transform_.position_ = { 0, 0.0, 0 };
	if (pstate == PLAYER_STATE::PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel_, transform_);
		Model::Draw(hIdleModel_);
	}
	else if (pstate == PLAYER_STATE::PLAYER_WALK || pstate == PLAYER_STATE::PLAYER_TURN)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
	
}


void Player::Release()
{
}
