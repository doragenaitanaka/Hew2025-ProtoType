#include "CircleCollider.h"

/**	@brief  �R���X�g���N�^
*	@date	2024/12/16
*/
CircleCollider::CircleCollider(DirectX::XMFLOAT3 _pos, float _radius) :BaseCollider(_pos)
{
    SetRadius(_radius);
}


/**	@brief  �f�X�g���N�^
*	@date	2024/12/16
*/
CircleCollider::~CircleCollider()
{

}


/**	@brief  �T�C�Y�̕ύX
*	@date	2024/12/15
*	@param XMFLOAT3 _size �ύX�������T�C�Y�̒l
*	@return	bool size �ڐG���Ă��邩
*/
void CircleCollider::SetRadius(float _raduis)
{
    this->radius = _raduis;
}


/**	@brief  �T�C�Y�̎擾
*	@date	2024/12/16
*	@return	XMFLOAT3 size Object�̃T�C�Y
*/
float CircleCollider::GetRadius(void)
{
    return this->radius;
}

/**	@brief  �~���m�̓����蔻��
*	@date	2024/12/16
*	@param BaseCollider& _other �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
bool CircleCollider::CheckCollisionCircle(BaseCollider& _other)
{
    // �~���m�̓����蔻��
    CircleCollider& otherCircle = static_cast<CircleCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherCircle.GetPosition();
    float otherRadius = otherCircle.GetRadius();

    float distX = this->GetPosition().x - otherPos.x;
    float distY = this->GetPosition().y - otherPos.y;
    float distance = std::sqrt(distX * distX + distY * distY);

    return distance <= (radius + otherRadius);
}

/**	@brief  ��`�Ɖ~�̓����蔻��
*	@date	2024/12/16
*	@param BaseCollider& _other �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
bool CircleCollider::CheckCollisionRectangle(BaseCollider& _other)
{
    // �~�Ƌ�`�̓����蔻�� (�t����)
    BoxCollider& otherBox = static_cast<BoxCollider&>(_other);
    return otherBox.CheckCollisionCircle(*this);
}

