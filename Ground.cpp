#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1), hburokkuk(-1)
{
}

void Ground::Initialize()
{
	hSilly = Model::Load("Ground.fbx");
	Model::SetAnimFrame(hSilly, 0, 59, 1.0);
	hburokkuk = Model::Load("bevel-hq-brick-2x2.fbx");
	Model::SetAnimFrame(hburokkuk, 0, 59, 1.0);
}

void Ground::Update()
{
}

void Ground::Draw()
{
	transform_.scale_ = { 1.0f, 1.0f, 1.0f };
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);

	//ブロック
	transform_.scale_ = { 0.3f, 0.3f, 0.4f };
	Model::SetTransform(hburokkuk, transform_);
	Model::Draw(hburokkuk);
}

void Ground::Release()
{
}
