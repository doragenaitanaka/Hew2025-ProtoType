/**	@file 	TrackingCamera.h
*	@brief 	追尾するクラス
*	@date	2025/01/21
*/
#pragma once
#include"../Camera.h"
#include"../../10_Object/Object.h"

class TrackingCamera :public Camera
{
public:
	TrackingCamera();
	~TrackingCamera();

	/**	@brief 	更新
	*/
	void Update()override;

	/**	@brief 	ターゲットの設定
	*   @param Object* _p_target	追尾するオブジェクト
	*/
	void SetTarget(Object* _p_target);

	/**	@brief 	ターゲットの解除
	*/
	inline void ClearTarget()
	{
		this->p_target = nullptr;
	}

	/**	@brief 	オフセットの設定
	*   @param DirectX::XMFLOAT3 _offset	カメラをずらす距離
	*/
	void SetOffset(DirectX::XMFLOAT3 _offset);

private:
	Object* p_target;			// カメラの基準
	DirectX::XMFLOAT3 offset;	// どれくらいずらすか
};
