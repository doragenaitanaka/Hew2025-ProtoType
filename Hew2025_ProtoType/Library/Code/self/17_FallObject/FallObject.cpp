#include "FallObject.h"

//コンストラクタ
FallObject::FallObject() 
{

}



//デストラクタ
FallObject::~FallObject()
{
}



void FallObject::Update(void)
{
	f_velocity.y += GRAVITY * TIME_STEP;//速度の更新
	f_velocity.x -= f_velocity.y * TIME_STEP;//高さの更新
	f_velocity.z += FRICTION * TIME_STEP;//角度の更新

	SetAngle(f_velocity.z);//角度の更新

	//地面に達したら停止する
	if (f_velocity.x <= 0)
	{
		f_velocity.x = 0;
		f_velocity.y = 0;
		
	}

	// 親クラスの更新処理を呼び出す
	Object::Update();
}

// 描画処理 (現在は親クラスの処理のみ呼び出し)
void FallObject::Draw(void)
{
	Object::Draw();
}


double FallObject::GetHeight() const
{
	return this->f_velocity.x;
}

double FallObject::GetAngle() const
{
	return this->f_velocity.z;
}







