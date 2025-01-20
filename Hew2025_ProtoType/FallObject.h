#pragma once
//インクルード
#include "../Hew2025_ProtoType/Library/Code/self/10_Object/Object.h"
#include <iostream>
#include <cmath>


//定数定義
#define GRAVITY 9.81//重力加速度（m/s^2）
#define TIME_STEP 0.01//時間のステップ（s）
#define FRICTION 0.1//摩擦係数


class FallObject:public Object
{
public:
	
	FallObject();//コンストラクタ
	~FallObject();//デストラクタ

	void Update();//更新処理
	double GetHeight() const;//高さのゲッター
	double GetAngle() const;//角度のゲッター

	//オブジェクト初期状態の設定
	void SetFallObject(float h, float v, float a); //{ this->f_velocity = { h, v, a }; }

	//オブジェクト状態の取得
	DirectX::XMFLOAT3 GetFallObject() const { return this->f_velocity; }

	



private:

	bool FallFlg=false;//倒れるフラグ（trueで倒れる、falseで通常）
	//float height;//物体の高さ(m)
	//float angle;//物体の倒れる角度(度)
	//float velocity;//各速度(度/s)
	DirectX::XMFLOAT3 f_velocity;//各速度(度/s)


};


