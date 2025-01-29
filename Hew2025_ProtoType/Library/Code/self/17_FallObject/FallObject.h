#pragma once
//インクルード
#include"../10_Object/Object.h"
#include <iostream>
#include <cmath>


//定数定義
#define GRAVITY 9.81//重力加速度（m/s^2）
#define TIME_STEP 1.0//時間のステップ（s）
#define FRICTION 0.1//摩擦係数


class FallObject:public Object
{
public:
	
	FallObject();//コンストラクタ
	~FallObject();//デストラクタ

	void Update(float s_Angle,int version);//更新処理
	void StopFall(float StopAngle);//止まる処理
	void Draw(void)override;//描画処理
	double GetHeight() const;//高さのゲッター
	double GetAngle() const;//角度のゲッター

	



	



private:

	bool FallFlg=true;//倒れるフラグ（trueで倒れる、falseで通常）
	float Height=10.0f;//物体の高さ(m)
	float Angle;//物体の倒れる角度(度)
	float x_Velocity=10.0f;//xの各速度(度/s)
	float y_Velocity = 0.0f;//yの各速度(度/s)
	float AngleVelocity=1.0f;//角速度(度/s)

};


