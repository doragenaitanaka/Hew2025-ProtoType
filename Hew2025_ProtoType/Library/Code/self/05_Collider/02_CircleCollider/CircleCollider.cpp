#include "CircleCollider.h"

/**	@brief  コンストラクタ
*	@date	2024/12/16
*/
CircleCollider::CircleCollider(DirectX::XMFLOAT3 _pos, float _radius) :BaseCollider(_pos)
{
    SetRadius(_radius);
}


/**	@brief  デストラクタ
*	@date	2024/12/16
*/
CircleCollider::~CircleCollider()
{

}


/**	@brief  サイズの変更
*	@date	2024/12/15
*	@param XMFLOAT3 _size 変更したいサイズの値
*	@return	bool size 接触しているか
*/
void CircleCollider::SetRadius(float _raduis)
{
    this->radius = _raduis;
}


/**	@brief  サイズの取得
*	@date	2024/12/16
*	@return	XMFLOAT3 size Objectのサイズ
*/
float CircleCollider::GetRadius(void)
{
    return this->radius;
}

/**	@brief  円同士の当たり判定
*	@date	2024/12/16
*	@param BaseCollider& _other 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/
bool CircleCollider::CheckCollisionCircle(BaseCollider& _other)
{
    // 円同士の当たり判定
    CircleCollider& otherCircle = static_cast<CircleCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherCircle.GetPosition();
    float otherRadius = otherCircle.GetRadius();

    float distX = this->GetPosition().x - otherPos.x;
    float distY = this->GetPosition().y - otherPos.y;
    float distance = std::sqrt(distX * distX + distY * distY);

    return distance <= (radius + otherRadius);
}

/**	@brief  矩形と円の当たり判定
*	@date	2024/12/16
*	@param BaseCollider& _other 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/
bool CircleCollider::CheckCollisionRectangle(BaseCollider& _other)
{
    // 円と矩形の当たり判定 (逆向き)
    BoxCollider& otherBox = static_cast<BoxCollider&>(_other);
    return otherBox.CheckCollisionCircle(*this);
}

/** @brief  点との当たり判定
*   @date   2025/01/23
*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
*   @return bool 接触しているか
*/
bool CircleCollider::CheckCollisionPoint(BaseCollider& _other)
{
    PointCollider& otherPoint = static_cast<PointCollider&>(_other);
    DirectX::XMFLOAT3 pointPos = otherPoint.GetPosition();
    float distX = position.x - pointPos.x;
    float distY = position.y - pointPos.y;
    return(distX * distX + distY * distY) <= (radius * radius);
}