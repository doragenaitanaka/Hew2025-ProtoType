#include "Pen.h"

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

/**	@brief 	ペンを発射する処理
*/
void Pen::Shoot(const DirectX::XMFLOAT3 objectPos)
{
	//ペンのx座標を-10ずつしていく
    p_Player->SetPos(-10,0,0);
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
