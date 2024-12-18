#include "BaseCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

///**	@brief 	�R���X�g���N�^
//	*	@date	2024/12/15
//	*/
BaseCollider::BaseCollider(DirectX::XMFLOAT3 _pos)
{
    SetPosition(_pos);
}

///**	@brief 	�f�X�g���N�^
//*	@date	2024/12/15
//*/
//BaseCollider::~BaseCollider()
//{
//
//}

/**	@brief  ���W�ݒ�
*	@date	2024/12/15
*	@param XMFLOAT3 idk �ݒ肵�������W
*/
void BaseCollider::SetPosition(DirectX::XMFLOAT3 _pos)
{
	position = _pos;
}

/**	@brief  ���W�擾
*	@date	2024/12/15
*	@return	XMFLOAT position ���W���
*/
DirectX::XMFLOAT3 BaseCollider::GetPosition(void)
{
	return position;
}

/**	@brief  �����蔻��
*	@date	2024/12/15
*	@param BaseCollider&  _other �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/ 
bool BaseCollider::CheckCollision(BaseCollider& _other) 
{
    if (typeid(_other) == typeid(BoxCollider)) 
    {
        return CheckCollisionRectangle(_other);
    }
    else if (typeid(_other) == typeid(CircleCollider)) 
    {
        return CheckCollisionCircle(_other);
    }
    return false;
}