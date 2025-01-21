#include "Ball.h"

// 更新処理
void Ball::Update(void)
{
    // 全状態共通の重力適用 (フレーム時間を考慮)
    this->velocity.y += this->gravity * 0.016f;

    // 現在の状態に基づいて処理を分岐
    switch (this->currentState)
    {
    case STOP:
        // 停止状態:
        // 水平方向の速度をゼロにする (転がらない)
        this->velocity.x = 0.0f;
        this->velocity.z = 0.0f;
        break;

    case ROLL:
        // 転がる状態:
        // 速度に基づいて位置を更新 (x軸のみ移動)
        this->pos.x += this->velocity.x;

        // 水平方向の速度を摩擦で減速
        velocity.x *= friction;
        velocity.y *= friction;  // 必要に応じてY方向にも適用


        // 水平方向の速度が非常に小さくなったら止まったとみなす
        if (fabs(velocity.x) < 0.01f && fabs(velocity.y) < 0.01f)
        {
            velocity.x = 0.0f;
            velocity.y = 0.0f;
            SetState(STOP); // 完全に停止
        }

        break;
    }

    // 地面 (y = 0) との衝突処理
    if (this->pos.y <= -600.0f)
    {
        this->pos.y = 200.0f;       // ボールを地面に固定
        this->velocity.y = 0.0f;  // 垂直方向の速度をゼロに
    }

    // 地面 (y = 0) との衝突処理
    if (this->pos.y <= 0.0f)
    {
        this->pos.y = 0.0f;       // ボールを地面に固定
        this->velocity.y = 0.0f;  // 垂直方向の速度をゼロに
    }

    // 親クラスの更新処理を呼び出す
    Object::Update();
}

void Ball::ApplyFriction(float frictionCoefficient)
{
    velocity.x *= frictionCoefficient;
    velocity.y *= frictionCoefficient;

    // 速度が小さすぎる場合、ボールを完全に停止させる
    if (fabs(velocity.x) < 0.01f && fabs(velocity.y) < 0.01f)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        SetState(STOP); // 停止状態に
    }
}

// 描画処理 (現在は親クラスの処理のみ呼び出し)
void Ball::Draw(void)
{
    Object::Draw();
}

// 終了処理 (リソース解放などの処理)
void Ball::Uninit(void)
{
}

// デストラクタ
Ball::~Ball()
{
}

// デストラクタ
Ball::Ball(Camera* _p_camera):Object( _p_camera)
{
}