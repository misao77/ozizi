#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("inosuke.fbx");
	Model::SetAnimFrame(hModel_, 0, 59, 1.0);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	transform_.scale_ = { 0.01,0.01,0.01 };
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
