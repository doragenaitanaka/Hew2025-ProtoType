/**	@file 	GrabBox.h
*	@brief  掴めるオブジェクトの処理
*	@date	2024/12/21
*/
#include "GrabBox.h"
#include "../../../../Scene/98_Test_Uryu/Test_Uryu.h"

/**	@brief 	コンストラクタ
* @date 2024/12/21
* @memo grabbedObjectを初期化している
*/
GrabBox::GrabBox(Camera* _p_camera) :Object(_p_camera),p_GrabbedObject(nullptr), p_Player(nullptr)
{
}


/**	@brief 	デストラクタ
* @date 2024/12/21
*/
GrabBox::~GrabBox()
{
	this->UnInit();
}

/**	@brief 	終了処理
* @date 2024/12/21
*/
void GrabBox::UnInit()
{
    p_GrabbedObject = nullptr;
    p_Player = nullptr;

}

/**	@brief 	更新処理
* @date 2024/12/21
*/
void GrabBox::Update()
{
    if (p_Player && GrabState == 1) 
    {
        Move(p_Player->GetPos());
    }
}

/**	@brief 	掴む処理
* @date 2024/12/21
*/
void GrabBox::Grab(Object* object)
{

    p_Player = object;
    GrabState = 1;//掴んだ状態にする
}

/**	@brief 	離す処理
* @date 2024/12/21
*/
void GrabBox::Release()
{
    p_Player = nullptr;
    GrabState = 0; // 離した状態にする
}

/**	@brief 	掴んだ持ち運び処理
* @date 2024/12/21
*/
void GrabBox::Move(const DirectX::XMFLOAT3 objectPos)
{
    if (p_Player)
    {
        // プレイヤーを掴んだオブジェクトの位置に追従させる
        p_Player->SetPos(objectPos.x, objectPos.y, objectPos.z);
    }
}

/**	@brief 	GrabStateのゲッター
* @date 2024/12/21
*/
int GrabBox::GetGrabState() const
{
    return GrabState;
}

/**	@brief 	GrabStateのセッター
* @date 2024/12/21
*/
void GrabBox::SetGrabState(int state) 
{ //セッター
    GrabState = state;
}