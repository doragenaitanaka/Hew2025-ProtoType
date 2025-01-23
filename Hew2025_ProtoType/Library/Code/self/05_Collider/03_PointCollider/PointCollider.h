/** @file   PointCollider.h
*   @brief  ポイントコライダークラス
*   @date   2025/01/23
*/
#pragma once
#include "../00_BaseCollider/BaseCollider.h"

/** @brief  PointColliderクラス
*   @date   2025/01/23
*/
class PointCollider : public BaseCollider
{
public:
    /** @brief  コンストラクタ
    *   @date   2025/01/23
    *   @param XMFLOAT3 _pos 設定したい座標
    */
    PointCollider(DirectX::XMFLOAT3 _pos);

    /** @brief  デストラクタ
    *   @date   2025/01/23
    */
    virtual ~PointCollider() = default;  // 仮想デストラクタ

    /** @brief  円との当たり判定
    *   @date   2025/01/23
    *   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
    *   @return bool 接触しているか
    */
    bool CheckCollisionCircle(BaseCollider& _other) override;

    /** @brief  矩形との当たり判定
    *   @date   2025/01/23
    *   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
    *   @return bool 接触しているか
    */
    bool CheckCollisionRectangle(BaseCollider& _other) override;

    /** @brief  点との当たり判定
    *   @date   2025/01/23
    *   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
    *   @return bool 接触しているか
    */
    bool CheckCollisionPoint(BaseCollider& _other) override;
};

