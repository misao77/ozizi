#pragma once
#include "Engine/GameObject.h"
class GameClearScene :
    public GameObject
{
public:
    GameClearScene(GameObject* parent);

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

