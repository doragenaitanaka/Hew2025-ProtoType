#include "FallObject.h"

//コンストラクタ
FallObject::FallObject() 
{

}



//デストラクタ
FallObject::~FallObject()
{
}



void FallObject::Update(float s_Angle,int version)
{
	if (FallFlg)//倒れるフラグがtrueの時
	{
		if (version == 1)//バージョン1の時
		{
			x_Velocity -= TIME_STEP;//速度の更新
			y_Velocity += TIME_STEP;//速度の更新
			AngleVelocity -= FRICTION * AngleVelocity * TIME_STEP;//角速度の更新
			Angle += AngleVelocity * TIME_STEP;//角度の更新

			this->SetPos(this->GetPos().x + x_Velocity, this->GetPos().y - y_Velocity, this->GetPos().z);//ポジションの更新
			this->SetAngle(angle - Angle);//角度の更新
			StopFall(s_Angle);//止まる処理
		}
		else if (version == 2)//バージョン2の時
		{
			x_Velocity += TIME_STEP;//速度の更新
			y_Velocity += TIME_STEP;//速度の更新
			AngleVelocity -= FRICTION * AngleVelocity * TIME_STEP;//角速度の更新
			Angle += AngleVelocity * TIME_STEP;//角度の更新

			this->SetPos(this->GetPos().x - x_Velocity, this->GetPos().y - y_Velocity, this->GetPos().z);//ポジションの更新
			this->SetAngle(angle + Angle);//角度の更新
			StopFall(s_Angle);//止まる処理
		}
	
	}
}

//止まる処理
void FallObject::StopFall(float StopAngle)
{
	if (angle >= StopAngle)//角度が指定角度以上になったら
	{
		FallFlg = false;//倒れるフラグをfalseにする
	}
	else if (angle <= -StopAngle)//角度が指定角度以下になったら
	{
		FallFlg = false;//倒れるフラグをfalseにする
	}
}

// 描画処理 (現在は親クラスの処理のみ呼び出し)
void FallObject::Draw(void)
{
	Object::Draw();
}

//高さのゲッター
double FallObject::GetHeight() const
{
	return this->Height;
}

//角度のゲッター
double FallObject::GetAngle() const
{
	return this->Angle;
}







