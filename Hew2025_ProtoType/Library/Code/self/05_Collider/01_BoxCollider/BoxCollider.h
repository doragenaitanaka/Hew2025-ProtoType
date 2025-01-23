#pragma once
#include "../00_BaseCollider/BaseCollider.h"
#include "../02_CircleCollider/CircleCollider.h"
#include "../03_PointCollider/PointCollider.h"
class BoxCollider : public BaseCollider
{
private:
    DirectX::XMFLOAT3 size;		// 矩形の大きさ
	float angle;				// 回転角度

	/**	@brief  外積を求める
	*	@param	DirectX::XMFLOAT3& _a
	*	@param	DirectX::XMFLOAT3& _b
	*	@return	float 外積
	*/
	inline float CrossProduct(DirectX::XMFLOAT3& _a, DirectX::XMFLOAT3& _b)
	{
		return _a.x * _b.y - _a.y * _b.x;
	}

	/**	@brief  ポリゴンの頂点を指定された軸に投影し、投影範囲を計算する
	 *	@param  std::array<Vector2D, 4>& _vertices ポリゴンの頂点配列
	 *	@param  Vector2D& _axis 投影軸
	 *	@return std::pair<float, float> 投影範囲の最小値と最大値
	 */
	std::pair<float, float> ProjectPolygon(const std::array<DirectX::XMFLOAT3, 4>& _vertices, const DirectX::XMFLOAT3& _axis);

public:

	/** @brief  2D回転行列を用いて点を回転させる
	 *  @param  point 回転させる点
	 *  @param  origin 原点となる点
	 *  @param  angle 回転角
	 *  @return 回転後の点
	 */
	static DirectX::XMFLOAT3 RotatePoint(const DirectX::XMFLOAT3& point, const DirectX::XMFLOAT3& origin, float angle);

	/**	@brief  コンストラクタ
	*/
	BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size, float _angle = 0);

	/**	@brief  デストラクタ
	*/
    ~BoxCollider();

	/**	@brief  サイズの変更
	*	@param XMFLOAT3 _size 変更したいサイズの値
	*/
    void SetSize(DirectX::XMFLOAT3);

	/**	@brief  サイズの取得
	*	@return	XMFLOAT3 size Objectのサイズ
	*/
	DirectX::XMFLOAT3 GetSize(void);

	/**	@brief  回転角度の変更
	*	@param float _angle 回転角度
	*/
	void SetAngle(float _angle);

	/**	@brief  回転角度の取得
	*	@return	float angle 回転角度
	*/
	float GetAngle(void);

	/**	@brief  円との当たり判定
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	bool CheckCollisionCircle(BaseCollider& _other) override;

	/**	@brief  矩形との当たり判定
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	bool CheckCollisionRectangle(BaseCollider& _other) override;

	/** @brief  点との当たり判定
	*   @param  BaseCollider& _other 接触判定を取る対象オブジェクト
	*   @return bool 接触しているか
	*/
	bool CheckCollisionPoint(BaseCollider& _other) override;
};