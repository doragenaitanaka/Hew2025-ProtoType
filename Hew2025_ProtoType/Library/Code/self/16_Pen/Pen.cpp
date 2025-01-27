#include "Pen.h"

//円周率
constexpr float PI=DirectX::XM_PI;

//角度をラジアンに変換するヘルパー関数
float Pen::DegToRed(float degrees)
{
    return degrees * (PI / 180.0f);
}

//コンストラクタ
Pen::Pen() :p_GrabbedObject(nullptr), p_Player(nullptr)
{
}


//デストラクタ
Pen::~Pen()
{
    this->UnInit();
}

/**	@brief 	終了処理
* @date 2024/12/21
*/
void Pen::UnInit()
{
    p_GrabbedObject = nullptr;
    p_Player = nullptr;

}

/**	@brief 	更新処理
* @date 2024/12/21
*/
void Pen::Update()
{
    if (p_Player && h_flag == 1)
    {
        Move(p_Player->GetPos());
    }
}

/**	@brief 	掴む処理
* @date 2024/12/21
*/
void Pen::have(Object* object)
{

    p_Player = object;
    h_flag = 1;//掴んだ状態にする
}

/**	@brief 	離す処理
* @date 2024/12/21
*/
void Pen::Release()
{
    p_Player = nullptr;
    h_flag = 0; // 離した状態にする
}

/**	@brief 	掴んだ持ち運び処理
* @date 2024/12/21
*/
void Pen::Move(const DirectX::XMFLOAT3 objectPos)
{
    if (p_Player)
    {
        // プレイヤーを掴んだオブジェクトの位置に追従させる
        p_Player->SetPos(objectPos.x, objectPos.y, objectPos.z);
    }
}

//ペンのアングルを変える処理
void Pen::Rotate(Object* objectangle)
{
    if (angle!=0.0f)
    {
        objectangle->SetAngle(angle += 3.0f);
    }


}

//ペンのアングルを変える処理
void Pen::Rotate2(Object* objectangle)
{
    if (angle!=-90.0f)
    {
        objectangle->SetAngle(angle -= 3.0f);
    }

}

//ペンのアングルを初期化する処理
void Pen::Reset(Object* objectangle)
{
    objectangle->SetAngle(angle = 0.0f);
}

/**	@brief 	ペンを発射する処理
*/
void Pen::Shoot(const Vector2& startPos, float speed, float angle, float DeltaTime)
{
    p_position = startPos;
    p_velocity.x = speed * cos(DegToRed(angle));
    p_velocity.y = speed * sin(DegToRed(angle));

    p_position.x += p_velocity.x * DeltaTime;
    p_position.y += p_velocity.y * DeltaTime;

	////ペンの位置を更新
 //   SetPos(p_position.x, p_position.y, 0.0f);


}

/**	@brief 	GrabStateのゲッター
* @date 2024/12/21
*/
int Pen::GetGrabState() const
{
    return h_flag;
}

/**	@brief 	GrabStateのセッター
* @date 2024/12/21
*/
void Pen::SetGrabState(int state)
{ //セッター
    h_flag = state;
}
