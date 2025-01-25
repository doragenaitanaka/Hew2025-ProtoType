#include"Camera.h"
#include"../imagawa_Input/input.h"

Camera::Camera()
	:pos{ DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f) },
	tgt{ DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) },
	up{ DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) },
	nearPlane{ 0.1f },
	farPlane{ 1000.0f },
    zoomFactor{1.0f}
{}

Camera::~Camera()
{}

/**	@brief 	更新
*/
void Camera::Update()
{
}

/**	@brief 	ビュー変換行列の取得
*   @return DirectX::XMMATRIX   ビュー変換行列
*/
DirectX::XMMATRIX Camera::GetViewMat()
{
    DirectX::XMVECTOR posVector = DirectX::XMLoadFloat3(&this->pos);
    DirectX::XMVECTOR tgtVector = DirectX::XMLoadFloat3(&this->tgt);
    DirectX::XMVECTOR upVector = DirectX::XMLoadFloat3(&this->up);

    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(posVector, tgtVector, upVector);
    return DirectX::XMMatrixTranspose(viewMatrix); // トランスポーズ
}

/**	@brief 	プロジェクション変換行列の取得
*   @return DirectX::XMMATRIX   プロジェクション変換行列
*/
DirectX::XMMATRIX Camera::GetProjectionMat()
{
    DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixOrthographicLH(
        static_cast<float>(SCREEN_WIDTH) / this->zoomFactor,
        static_cast<float>(SCREEN_HEIGHT) / this->zoomFactor,
        this->nearPlane, this->farPlane);
    return DirectX::XMMatrixTranspose(projectionMatrix); // トランスポーズ
}

/**	@brief 	画面シェイク
*   @param float _intensity	揺れる強さ
*/
void Camera::Shake(float _intensity)
{
    float offsetX = (rand() % 1000 / 500.0f - 1.0f) * _intensity;
    float offsetY = (rand() % 1000 / 500.0f - 1.0f) * _intensity;
    this->SetPosition(this->pos.x + offsetX, this->pos.y + offsetY);
}