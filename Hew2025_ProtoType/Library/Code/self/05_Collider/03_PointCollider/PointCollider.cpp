/** @file   PointCollider.cpp
*   @brief  ポイントコライダークラスの実装
*   @date   2025/01/23
*/
#include "PointCollider.h"
#include "../02_CircleCollider/CircleCollider.h"
#include "../01_BoxCollider/BoxCollider.h"

/** @brief  コンストラクタ
*   @date   2025/01/23
*   @param XMFLOAT3 _pos 設定したい座標
*/
PointCollider::PointCollider(DirectX::XMFLOAT3 _pos) : BaseCollider(_pos) {}

/** @brief  円との当たり判定
*   @date   2025/01/23
*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
*   @return bool 接触しているか
*/
bool PointCollider::CheckCollisionCircle(BaseCollider& _other)
{
    CircleCollider& otherCircle = static_cast<CircleCollider&>(_other);
    DirectX::XMFLOAT3 otherPos = otherCircle.GetPosition();
    float radius = otherCircle.GetRadius();
    float distX = position.x - otherPos.x;
    float distY = position.y - otherPos.y;
    return (distX * distX + distY * distY) <= (radius * radius);
}

/** @brief  矩形との当たり判定
*   @date   2025/01/23
*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
*   @return bool 接触しているか
*/
bool PointCollider::CheckCollisionRectangle(BaseCollider& _other)
{
    BoxCollider& otherBox = static_cast<BoxCollider&>(_other);
    DirectX::XMFLOAT3 otherPos = otherBox.GetPosition();
    DirectX::XMFLOAT3 size = otherBox.GetSize();
    float angle = otherBox.GetAngle();

    // 点を矩形の座標系に変換
    DirectX::XMFLOAT3 relativePos = BoxCollider::RotatePoint(position, otherPos, -angle);

    // 矩形の範囲内にあるか確認
    return (relativePos.x >= otherPos.x - size.x / 2 && relativePos.x <= otherPos.x + size.x / 2 &&
        relativePos.y >= otherPos.y - size.y / 2 && relativePos.y <= otherPos.y + size.y / 2);
}

/** @brief  点との当たり判定
*   @date   2025/01/23
*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
*   @return bool 接触しているか
*/
bool PointCollider::CheckCollisionPoint(BaseCollider& _other)
{
    PointCollider& otherPoint = static_cast<PointCollider&>(_other);
    DirectX::XMFLOAT3 otherPos = otherPoint.GetPosition();
    return position.x == otherPos.x && position.y == otherPos.y;
}

