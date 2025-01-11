#include "Pendulum.h"
#include <DirectXMath.h> // DirectX::XM_PI

Pendulum::Pendulum(float _amplitude, float _frequency, float _phase, float _centerX, float _centerY)
    : amplitude(_amplitude), frequency(_frequency), phase(_phase), elapsedTime(0.0f), centerX(_centerX), centerY(_centerY)
{
}

Pendulum::~Pendulum()
{
    this->UnInit();
}

void Pendulum::Update()
{
    // 時間の更新
    elapsedTime += 1.0f / 60.0f; // assuming 60 FPS

    // 振り子の角度を計算（-PI/2 ～ PI/2 の範囲で動くように調整）
    float angle = (DirectX::XM_PI / 2.0f) * std::sinf(2.0f * DirectX::XM_PI * frequency * elapsedTime + phase);

    // 半円状の軌道を計算
    float x = centerX + amplitude * std::sinf(angle);
    float y = centerY - amplitude * std::cosf(angle);

    // 座標を設定
    this->SetPos(x, y, this->GetPos().z);

    // ベースクラスの更新処理を呼び出す
    Object::Update();
}

void Pendulum::Draw()
{
    // ベースクラスの描画処理を呼び出す
    Object::Draw();
}

void Pendulum::UnInit()
{
    // ベースクラスの解放処理を呼び出す
    Object::UnInit();
}

void Pendulum::SetAmplitude(float _amplitude)
{
    amplitude = _amplitude;
}

void Pendulum::SetFrequency(float _frequency)
{
    frequency = _frequency;
}

void Pendulum::SetPhase(float _phase)
{
    phase = _phase;
}

void Pendulum::SetCenter(float _centerX, float _centerY)
{
    centerX = _centerX;
    centerY = _centerY;
}
