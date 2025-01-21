#pragma once
#include "../10_Object/Object.h"
#include <cmath> // sin, cos

class Pendulum : public Object
{
public:
    /**
     * @brief コンストラクタ
     * @param _amplitude 振り幅（半径）
     * @param _frequency 振動数
     * @param _phase 初期位相
     * @param _centerX 中心X座標
     * @param _centerY 中心Y座標
     */
    Pendulum(Camera* _p_camera,float _amplitude = 50.0f, float _frequency = 1.0f, float _phase = 0.0f, float _centerX = 0.0f, float _centerY = 0.0f);

    /**
     * @brief デストラクタ
     */
    ~Pendulum() override;

    void Update() override;   // 更新処理
    void Draw() override;     // 描画処理
    void UnInit() override;   // 解放処理

    void SetAmplitude(float _amplitude); // 振り幅を設定
    void SetFrequency(float _frequency); // 振動数を設定
    void SetPhase(float _phase);         // 初期位相を設定
    void SetCenter(float _centerX, float _centerY); // 中心座標を設定

private:
    float amplitude;   // 振り幅（半径）
    float frequency;   // 振動数
    float phase;       // 初期位相
    float elapsedTime; // 経過時間
    float centerX;     // 振り子の中心X座標
    float centerY;     // 振り子の中心Y座標
};
