#pragma once
#include "../10_Object/Object.h"

// Ball クラス: ボールオブジェクトの状態管理と物理演算を担当
class Ball : public Object
{
public:
    // ボールの状態を表す列挙型
    enum BallState
    {
        ROLL, // 転がる状態
        STOP  // 停止状態
    };

    // デストラクタ
    ~Ball();

    // 更新処理 (毎フレーム実行される)
    void Update(void) override;

    // 描画処理
    void Draw(void) override;

    // 終了処理
    void Uninit(void);

    // 状態を設定
    void SetState(BallState state) { this->currentState = state; }

    // 状態を取得
    BallState GetState() const { return this->currentState; }

    // 速度を設定
    void SetVelocity(float x, float y, float z) { this->velocity = { x, y, z }; }

    // 速度を取得
    DirectX::XMFLOAT3 GetVelocity() const { return this->velocity; }

    // 重力を設定
    void SetGravity(float g) { this->gravity = g; }

    // 重力を取得
    float GetGravity() const { return this->gravity; }

    void SetFriction(float friction) { this->friction = friction; }

    float GetFriction() const { return this->friction; }

    void ApplyFriction(float frictionCoefficient);

private:
    BallState currentState = STOP;  // 現在の状態（デフォルトは停止状態）
    DirectX::XMFLOAT3 velocity;    // ボールの速度（x, y, z 成分）
    float gravity = 9.8f;          // 重力加速度（デフォルト値: 9.8）
    float friction = 0.9f;         // 摩擦係数 (デフォルトで0.98)
};
