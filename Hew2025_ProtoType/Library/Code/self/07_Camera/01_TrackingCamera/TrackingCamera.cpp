#include"TrackingCamera.h"

TrackingCamera::TrackingCamera():p_target{nullptr}, offset{DirectX::XMFLOAT3()}
{}

TrackingCamera::~TrackingCamera(){}

/**	@brief 	更新
*/
void TrackingCamera::Update()
{
	if (this->p_target)
	{
		DirectX::XMFLOAT3 targetPos = this->p_target->GetPos();
		this->SetPosition(targetPos.x + this->offset.x, targetPos.y + this->offset.y);
	}
}

/**	@brief 	ターゲットの設定
*   @param Object* _p_target	追尾するオブジェクト
*/
void TrackingCamera::SetTarget(Object* _p_target)
{
	this->p_target = _p_target;
}

/**	@brief 	オフセットの設定
*   @param DirectX::XMFLOAT3 _offset	カメラをずらす距離
*/
void TrackingCamera::SetOffset(DirectX::XMFLOAT3 _offset)
{
	this->offset = _offset;
}