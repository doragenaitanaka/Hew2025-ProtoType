#include"Camera.h"
#include"../imagawa_Input/input.h"

Camera::Camera()
	:pos{ DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f) },
	tgt{ DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) },
	up{ DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) },
	nearPlane{ 1.0f },
	farPlane{ 1000.0f }
{}

Camera::~Camera()
{}

void Camera::Update()
{
	this->SetPosition(this->pos.x + 1.0f, 0.0f);
}

DirectX::XMMATRIX Camera::GetViewMat()
{
    DirectX::XMVECTOR posVector = DirectX::XMLoadFloat3(&this->pos);
    DirectX::XMVECTOR tgtVector = DirectX::XMLoadFloat3(&this->tgt);
    DirectX::XMVECTOR upVector = DirectX::XMLoadFloat3(&this->up);

    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(posVector, tgtVector, upVector);
    return DirectX::XMMatrixTranspose(viewMatrix); // トランスポーズ
}

DirectX::XMMATRIX Camera::GetProjectionMat()
{
    DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixOrthographicLH(static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT),
        this->nearPlane, this->farPlane);
    return DirectX::XMMatrixTranspose(projectionMatrix); // トランスポーズ
}
