#include "FallObject.h"

//コンストラクタ
FallObject::FallObject() 
{

}



//デストラクタ
FallObject::~FallObject()
{
}

//オブジェクトの設定
void FallObject::SetFallObject(float h, float v, float a)
{
	this->f_velocity = { h, v, a };
}


void FallObject::Update()
{
	this->f_velocity.y += GRAVITY * TIME_STEP;//速度の更新
	this->f_velocity.x -= f_velocity.y * TIME_STEP;//高さの更新
	this->f_velocity.z += FRICTION * TIME_STEP;//角度の更新

	this->angle = this->f_velocity.z;//角度の更新

	//地面に達したら停止する
	if (f_velocity.x <= 0)
	{
		f_velocity.x = 0;
		f_velocity.y = 0;
		
	}

}


double FallObject::GetHeight() const
{
	return this->f_velocity.x;
}

double FallObject::GetAngle() const
{
	return this->f_velocity.z;
}







