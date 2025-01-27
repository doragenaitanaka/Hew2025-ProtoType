#include "BoxCollider.h"
#include<array>
// 角度をラジアンに変換するための定数 
const float PI = 3.14159265358979323846f;

/**	@brief  コンストラクタ
*	@date	2024/12/16
*/
BoxCollider::BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size, float _angle) : BaseCollider(_pos)
{
    SetSize(_size);
    SetAngle(_angle);
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

/**	@brief  回転角度の変更
*	@date	2024/12/31
*	@param float _angle 回転角度
*/
void BoxCollider::SetAngle(float _angle)
{
    this->angle = _angle;
}

/**	@brief  回転角度の取得
*	@date	2024/12/16
*	@return	float angle 回転角度
*/
float BoxCollider::GetAngle(void)
{
    return this->angle;
}

/** @brief  2D回転行列を用いて点を回転させる
 *  @param  point 回転させる点
 *  @param  origin 原点となる点
 *  @param  angle 回転角（度単位）
 *  @return 回転後の点
 */
DirectX::XMFLOAT3 BoxCollider::RotatePoint(const DirectX::XMFLOAT3& point, const DirectX::XMFLOAT3& origin, float angle)
{
    // 角度をラジアンに変換
    float radians = angle * (PI / 180.0f);

    float cosAngle = cosf(radians);
    float sinAngle = sinf(radians);
    float x = origin.x + (point.x - origin.x) * cosAngle - (point.y - origin.y) * sinAngle;
    float y = origin.y + (point.x - origin.x) * sinAngle + (point.y - origin.y) * cosAngle;
    return DirectX::XMFLOAT3(x, y, 0.0f);
}
/**	@brief  ポリゴンの頂点を指定された軸に投影し、投影範囲を計算する
 *	@param  std::array<Vector2D, 4>& _vertices ポリゴンの頂点配列
 *	@param  Vector2D& _axis 投影軸
 *	@return std::pair<float, float> 投影範囲の最小値と最大値
 */
std::pair<float, float> BoxCollider::ProjectPolygon(const std::array<DirectX::XMFLOAT3, 4>& _vertices, const DirectX::XMFLOAT3& _axis)
{
    // 最初の頂点の投影値
    float minProj = _vertices[0].x * _axis.x + _vertices[0].y * _axis.y;
    float maxProj = minProj;

    for (const auto& vertex : _vertices)
    {
        // 各頂点の投影値を計算
        float proj = vertex.x * _axis.x + vertex.y * _axis.y;

        // 最小投影値を更新
        if (proj < minProj) { minProj = proj; }

        // 最大投影値を更新
        else if (proj > maxProj) { maxProj = proj; }
    }

    // 最小投影値と最大投影値を返す
    return { minProj, maxProj }; 
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

    // 当たり判定情報の取得
    DirectX::XMFLOAT3 otherPos = otherBox.GetPosition();
    DirectX::XMFLOAT3 otherSize = otherBox.GetSize();
    float otherAngle = otherBox.GetAngle();
    float ownAngle = this->GetAngle();

    // 各頂点の定義および回転
    std::array<DirectX::XMFLOAT3, 4> ownVertex = {
        RotatePoint(DirectX::XMFLOAT3{this->position.x - size.x / 2, this->position.y + size.y / 2, 0.0f}, this->position, ownAngle),  // 左上
        RotatePoint(DirectX::XMFLOAT3{this->position.x + size.x / 2, this->position.y + size.y / 2, 0.0f}, this->position, ownAngle),  // 右上
        RotatePoint(DirectX::XMFLOAT3{this->position.x + size.x / 2, this->position.y - size.y / 2, 0.0f}, this->position, ownAngle),  // 右下
        RotatePoint(DirectX::XMFLOAT3{this->position.x - size.x / 2, this->position.y - size.y / 2, 0.0f}, this->position, ownAngle)   // 左下
    };

    std::array<DirectX::XMFLOAT3, 4> otherVertex = {
        RotatePoint(DirectX::XMFLOAT3{otherPos.x - otherSize.x / 2, otherPos.y + otherSize.y / 2, 0.0f}, otherPos, otherAngle),  // 左上
        RotatePoint(DirectX::XMFLOAT3{otherPos.x + otherSize.x / 2, otherPos.y + otherSize.y / 2, 0.0f}, otherPos, otherAngle),  // 右上
        RotatePoint(DirectX::XMFLOAT3{otherPos.x + otherSize.x / 2, otherPos.y - otherSize.y / 2, 0.0f}, otherPos, otherAngle),  // 右下
        RotatePoint(DirectX::XMFLOAT3{otherPos.x - otherSize.x / 2, otherPos.y - otherSize.y / 2, 0.0f}, otherPos, otherAngle)   // 左下
    };

    // 分離軸判定
    // 矩形のエッジに垂直な軸を求める
    std::array<DirectX::XMFLOAT3, 4> axes1 = {
        DirectX::XMFLOAT3{ownVertex[1].x - ownVertex[0].x, ownVertex[1].y - ownVertex[0].y, 0.0f},
        DirectX::XMFLOAT3{ownVertex[2].x - ownVertex[1].x, ownVertex[2].y - ownVertex[1].y, 0.0f},
        DirectX::XMFLOAT3{ownVertex[3].x - ownVertex[2].x, ownVertex[3].y - ownVertex[2].y, 0.0f},
        DirectX::XMFLOAT3{ownVertex[0].x - ownVertex[3].x, ownVertex[0].y - ownVertex[3].y, 0.0f}
    };

    std::array<DirectX::XMFLOAT3, 4> axes2 = {
        DirectX::XMFLOAT3{otherVertex[1].x - otherVertex[0].x, otherVertex[1].y - otherVertex[0].y, 0.0f},
        DirectX::XMFLOAT3{otherVertex[2].x - otherVertex[1].x, otherVertex[2].y - otherVertex[1].y, 0.0f},
        DirectX::XMFLOAT3{otherVertex[3].x - otherVertex[2].x, otherVertex[3].y - otherVertex[2].y, 0.0f},
        DirectX::XMFLOAT3{otherVertex[0].x - otherVertex[3].x, otherVertex[0].y - otherVertex[3].y, 0.0f}
    };

    // 各軸に対する投影範囲を計算し、重なりを判定
    for (const auto& axis : axes1)
    {
        auto [minProj1, maxProj1] = ProjectPolygon(ownVertex, axis);
        auto [minProj2, maxProj2] = ProjectPolygon(otherVertex, axis);

        // 投影範囲が重ならない軸が見つかった場合、衝突していないと判定
        if (maxProj1 < minProj2 || maxProj2 < minProj1)
        {
            return false; 
        }
    }

    for (const auto& axis : axes2) 
    {
        auto [minProj1, maxProj1] = ProjectPolygon(ownVertex, axis);
        auto [minProj2, maxProj2] = ProjectPolygon(otherVertex, axis);

        // 投影範囲が重ならない軸が見つかった場合、衝突していないと判定
        if (maxProj1 < minProj2 || maxProj2 < minProj1) 
        {
            return false; 
        }
    }

    // すべての軸に対して投影範囲が重なっている場合、衝突していると判定
    return true; 
}

/** @brief  点との当たり判定
*   @date   2025/01/23
*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
*   @return bool 接触しているか
*/
bool BoxCollider::CheckCollisionPoint(BaseCollider& _other)
{
    PointCollider& otherPoint = static_cast<PointCollider&>(_other);
    DirectX::XMFLOAT3 pointPos = otherPoint.GetPosition();

    // 点を矩形の座標系に変換
    DirectX::XMFLOAT3 relativePos = RotatePoint(pointPos, this->position, -this->angle);

    // 矩形の範囲内にあるか確認
    return (relativePos.x >= this->position.x - this->size.x / 2 && relativePos.x <= this->position.x + this->size.x / 2 &&
        relativePos.y >= this->position.y - this->size.y / 2 && relativePos.y <= this->position.y + this->size.y / 2);
}