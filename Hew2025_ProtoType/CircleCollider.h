#pragma once
#include "BaseCollider.h"
#include "BoxCollider.h"
class CircleCollider :
    public BaseCollider
{
private:
	float radius;

public:

	/**	@brief  コンストラクタ
	*	@date	2024/12/16
	*/
	CircleCollider(DirectX::XMFLOAT3 _pos, float _radius);


	/**	@brief  デストラクタ
	*	@date	2024/12/16
	*/
	~CircleCollider();


	/**	@brief  半径の変更
	*	@date	2024/12/15
	*	@param XMFLOAT3 _radius 変更したい半径の値
	*/
	void SetRadius(float);


	/**	@brief  半径の取得
	*	@date	2024/12/16
	*	@return	XMFLOAT3 radius Objectの半径
	*/
	float GetRadius(void);


	/**	@brief  円との当たり判定
*	@date	2024/12/15
*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/
	bool CheckCollisionCircle(BaseCollider& _other) override;

	/**	@brief  矩形との当たり判定
	*	@date	2024/12/15
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	bool CheckCollisionRectangle(BaseCollider& _other) override;
};

