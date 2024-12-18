#include "BaseCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

///**	@brief 	コンストラクタ
//	*	@date	2024/12/15
//	*/
BaseCollider::BaseCollider(DirectX::XMFLOAT3 _pos)
{
    SetPosition(_pos);
}

///**	@brief 	デストラクタ
//*	@date	2024/12/15
//*/
//BaseCollider::~BaseCollider()
//{
//
//}

/**	@brief  座標設定
*	@date	2024/12/15
*	@param XMFLOAT3 idk 設定したい座標
*/
void BaseCollider::SetPosition(DirectX::XMFLOAT3 _pos)
{
	position = _pos;
}

/**	@brief  座標取得
*	@date	2024/12/15
*	@return	XMFLOAT position 座標情報
*/
DirectX::XMFLOAT3 BaseCollider::GetPosition(void)
{
	return position;
}

/**	@brief  当たり判定
*	@date	2024/12/15
*	@param BaseCollider&  _other 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/ 
bool BaseCollider::CheckCollision(BaseCollider& _other) 
{
    if (typeid(_other) == typeid(BoxCollider)) 
    {
        return CheckCollisionRectangle(_other);
    }
    else if (typeid(_other) == typeid(CircleCollider)) 
    {
        return CheckCollisionCircle(_other);
    }
    return false;
}