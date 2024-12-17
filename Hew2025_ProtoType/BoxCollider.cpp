#include "BoxCollider.h"

/**	@brief  コンストラクタ
*	@date	2024/12/16
*/
//BoxCollider::BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size)
//{
//    SetPosition(_pos);
//    SetSize(_size);
//}
BoxCollider::BoxCollider()
{
    DirectX::XMFLOAT3 _pos = {1.0f, 1.0f, 1.0f};
    DirectX::XMFLOAT3 _size = { 1.0f, 1.0f, 1.0f };
    SetPosition(_pos);
    SetSize(_size);
}

/**	@brief  デストラクタ
*	@date	2024/12/16
*/
BoxCollider::~BoxCollider()
{
    
}


/**	@brief  サイズの変更
*	@date	2024/12/15
*	@param XMFLOAT3 _size 変更したいサイズの値
*	@return	bool size 接触しているか
*/
void BoxCollider::SetSize(DirectX::XMFLOAT3 _size)
{
	this->size = _size;
}


/**	@brief  サイズの取得
*	@date	2024/12/16
*	@return	XMFLOAT3 size Objectのサイズ
*/
DirectX::XMFLOAT3 BoxCollider::GetSize(void)
{
	return this->size;
}

/**	@brief  矩形と円の当たり判定
*	@date	2024/12/15
*	@param BaseCollider& _other 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/
bool BoxCollider::CheckCollisionCircle(BaseCollider& _other)
{
    // 矩形と円の当たり判定
    CircleCollider& otherCircle = static_cast<CircleCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherCircle.GetPosition();
    float radius = otherCircle.GetRadius();

    // 最も近い点を計算
    float closestX = std::max(this->GetPosition().x - this->size.x / 2, std::min(otherPos.x, this->GetPosition().x + this->size.x / 2));
    float closestY = std::max(this->GetPosition().y - this->size.y / 2, std::min(otherPos.y, this->GetPosition().y + this->size.y / 2));

    // 円の中心と最近接点の距離を計算
    float distX = otherPos.x - closestX;
    float distY = otherPos.y - closestY;
    return (distX * distX + distY * distY) <= (radius * radius);
}


/**	@brief  矩形同士の当たり判定
*	@date	2024/12/15
*	@param BaseCollider& _other 接触判定を対象取るオブジェクト
*	@return	bool idk 接触しているか
*/
bool BoxCollider::CheckCollisionRectangle(BaseCollider& _other) 
{
    // 矩形同士の当たり判定
    BoxCollider& otherBox = static_cast<BoxCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherBox.GetPosition();
    DirectX::XMFLOAT3 otherSize = otherBox.GetSize();

    return (this->GetPosition().x + size.x / 2 >= otherPos.x - otherSize.x / 2 &&
        this->GetPosition().x - size.x / 2 <= otherPos.x + otherSize.x / 2 &&
        this->GetPosition().y + size.y / 2 >= otherPos.y - otherSize.y / 2 &&
        this->GetPosition().y - size.y / 2 <= otherPos.y + otherSize.y / 2);
}

