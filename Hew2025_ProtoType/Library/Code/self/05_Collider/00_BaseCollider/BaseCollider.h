
/**	@file 	BaseCollider.h
*	@brief 	シーン基底クラス
*	@date	2024/12/15
*/

#pragma once
#include<DirectXMath.h> //  DirectX::XMFLOAT3に必要
#include <typeinfo>	//typeidに必要
#include <cmath>
#include <iostream>

//#include "CircleCollider.h"
//#include "BoxCollider.h"


/**	@brief 	Collider基底クラス
*	@date	2024/12/15
*/
class BaseCollider
{
protected:
		DirectX::XMFLOAT3 position;

public:
	

	/**	@brief 	コンストラクタ
	*	@date	2024/12/15
	*	@param XMFLOAT3 _pos 設定したい座標
	*/
	BaseCollider(DirectX::XMFLOAT3 _pos);

	/**	@brief 	デストラクタ
	*	@date	2024/12/15
	*/
	virtual ~BaseCollider() = default;  // 仮想デストラクタ

	/**	@brief  座標設定
	*	@date	2024/12/15
	*	@param XMFLOAT3 _position 設定したい座標
	*/
	void SetPosition(DirectX::XMFLOAT3 _pos);

	/**	@brief  座標取得
	*	@date	2024/12/15
	*	@return	XMFLOAT position 座標情報
	*/
	DirectX::XMFLOAT3 GetPosition(void);

	/**	@brief  円との当たり判定
	*	@date	2024/12/15
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	virtual bool CheckCollisionCircle(BaseCollider& _other) = 0;

	/**	@brief  矩形との当たり判定
	*	@date	2024/12/15
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	virtual bool CheckCollisionRectangle(BaseCollider& _other) = 0;

	/**	@brief  当たり判定
*	@date	2024/12/15
*	@param  BaseCollider& _other 接触判定を取る対象オブジェクト
*	@return	bool idk 接触しているか
*/
	bool CheckCollision(BaseCollider& _other);
};