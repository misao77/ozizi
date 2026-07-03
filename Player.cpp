#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"

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
	const float SPEED = 0.1f;
	float angle = 0.0f;
	pstate = PLAYER_STATE::PLAYER_IDLE;
	PLAYER_DIRECTION oldDir = pdirection;

	if (Input::IsKey(DIK_LEFT)) {
		//angle = 90.0f;
		pdirection = PLAYER_DIRECTION::PLAYER_LEFT;
		move += XMVectorSet(-1.0f, 0, 0, 0);
		pstate = PLAYER_STATE::PLAYER_WALK;
		
		
	}
	if (Input::IsKey(DIK_RIGHT)) {
		//angle = -90.0f;
		pdirection = PLAYER_DIRECTION::PLAYER_RIGHT;
		//move += XMVectorSet(1.0f, 0, 0, 0);
		pstate = PLAYER_STATE::PLAYER_WALK;
		
	}
	if (Input::IsKey(DIK_UP)) {
		//angle = 180.0f;
		pdirection = PLAYER_DIRECTION::PLAYER_UP;
		//move += XMVectorSet(0, 0, 1.0f, 0);
		pstate = PLAYER_STATE::PLAYER_WALK;
		
	}
	if (Input::IsKey(DIK_DOWN)) {
		//angle = 0.0f;
		pdirection = PLAYER_DIRECTION::PLAYER_DOWN;
		//move += XMVectorSet(0, 0, -1.0f, 0);
		pstate = PLAYER_STATE::PLAYER_WALK;
		
	}
	if (oldDir != pstate)
	{
		pstate = PLAYER_STATE::PLAYER_TURN;

	}

	//状態切り替えの処理
	//状態ごとの処理



	if (pstate != PLAYER_STATE::PLAYER_IDLE)
	{
		move = P_MOVE[pdirection];
		angle = P_ANGLE[pdirection];
		transform_.rotate_.y = angle;
	}
	else if (pstate == PLAYER_STATE::PLAYER_TURN)
	{
		//回転中の処理
		oldDir //今の角度
		pdirection//目標の角度
	}
	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);

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
	else if (pstate == PLAYER_STATE::PLAYER_WALK)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
	
}


void Player::Release()
{
}
