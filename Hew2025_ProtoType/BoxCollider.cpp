#include "BoxCollider.h"

/**	@brief  �R���X�g���N�^
*	@date	2024/12/16
*/
//BoxCollider::BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size)
//{
//    SetPosition(_pos);
//    SetSize(_size);
//}
BoxCollider::BoxCollider()
{
    DirectX::XMFLOAT3 _pos = {1.0f, 1.0f, 1.0f};
    DirectX::XMFLOAT3 _size = { 1.0f, 1.0f, 1.0f };
    SetPosition(_pos);
    SetSize(_size);
}

/**	@brief  �f�X�g���N�^
*	@date	2024/12/16
*/
BoxCollider::~BoxCollider()
{
    
}


/**	@brief  �T�C�Y�̕ύX
*	@date	2024/12/15
*	@param XMFLOAT3 _size �ύX�������T�C�Y�̒l
*	@return	bool size �ڐG���Ă��邩
*/
void BoxCollider::SetSize(DirectX::XMFLOAT3 _size)
{
	this->size = _size;
}


/**	@brief  �T�C�Y�̎擾
*	@date	2024/12/16
*	@return	XMFLOAT3 size Object�̃T�C�Y
*/
DirectX::XMFLOAT3 BoxCollider::GetSize(void)
{
	return this->size;
}

/**	@brief  ��`�Ɖ~�̓����蔻��
*	@date	2024/12/15
*	@param BaseCollider& _other �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
bool BoxCollider::CheckCollisionCircle(BaseCollider& _other)
{
    // ��`�Ɖ~�̓����蔻��
    CircleCollider& otherCircle = static_cast<CircleCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherCircle.GetPosition();
    float radius = otherCircle.GetRadius();

    // �ł��߂��_���v�Z
    float closestX = std::max(this->GetPosition().x - this->size.x / 2, std::min(otherPos.x, this->GetPosition().x + this->size.x / 2));
    float closestY = std::max(this->GetPosition().y - this->size.y / 2, std::min(otherPos.y, this->GetPosition().y + this->size.y / 2));

    // �~�̒��S�ƍŋߐړ_�̋������v�Z
    float distX = otherPos.x - closestX;
    float distY = otherPos.y - closestY;
    return (distX * distX + distY * distY) <= (radius * radius);
}


/**	@brief  ��`���m�̓����蔻��
*	@date	2024/12/15
*	@param BaseCollider& _other �ڐG�����Ώێ��I�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
bool BoxCollider::CheckCollisionRectangle(BaseCollider& _other) 
{
    // ��`���m�̓����蔻��
    BoxCollider& otherBox = static_cast<BoxCollider&>(_other);

    DirectX::XMFLOAT3 otherPos = otherBox.GetPosition();
    DirectX::XMFLOAT3 otherSize = otherBox.GetSize();

    return (this->GetPosition().x + size.x / 2 >= otherPos.x - otherSize.x / 2 &&
        this->GetPosition().x - size.x / 2 <= otherPos.x + otherSize.x / 2 &&
        this->GetPosition().y + size.y / 2 >= otherPos.y - otherSize.y / 2 &&
        this->GetPosition().y - size.y / 2 <= otherPos.y + otherSize.y / 2);
}

