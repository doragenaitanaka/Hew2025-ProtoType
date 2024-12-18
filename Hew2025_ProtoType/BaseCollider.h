
/**	@file 	BaseCollider.h
*	@brief 	�V�[�����N���X
*	@date	2024/12/15
*/

#pragma once
#include<DirectXMath.h> //  DirectX::XMFLOAT3�ɕK�v
#include <typeinfo>	//typeid�ɕK�v
#include <cmath>
#include <DirectXMath.h>
#include <iostream>

//#include "CircleCollider.h"
//#include "BoxCollider.h"


/**	@brief 	Collider���N���X
*	@date	2024/12/15
*/
class BaseCollider
{
private:
		DirectX::XMFLOAT3 position;

public:
	

	/**	@brief 	�R���X�g���N�^
	*	@date	2024/12/15
	*	@param XMFLOAT3 _pos �ݒ肵�������W
	*/
	BaseCollider(DirectX::XMFLOAT3 _pos);

	/**	@brief 	�f�X�g���N�^
	*	@date	2024/12/15
	*/
	virtual ~BaseCollider() = default;  // ���z�f�X�g���N�^

	/**	@brief  ���W�ݒ�
	*	@date	2024/12/15
	*	@param XMFLOAT3 _position �ݒ肵�������W
	*/
	void SetPosition(DirectX::XMFLOAT3 _pos);

	/**	@brief  ���W�擾
	*	@date	2024/12/15
	*	@return	XMFLOAT position ���W���
	*/
	DirectX::XMFLOAT3 GetPosition(void);

	/**	@brief  �~�Ƃ̓����蔻��
	*	@date	2024/12/15
	*	@param  BaseCollider& idk �ڐG��������ΏۃI�u�W�F�N�g
	*	@return	bool idk �ڐG���Ă��邩
	*/
	virtual bool CheckCollisionCircle(BaseCollider& _other) = 0;

	/**	@brief  ��`�Ƃ̓����蔻��
	*	@date	2024/12/15
	*	@param  BaseCollider& idk �ڐG��������ΏۃI�u�W�F�N�g
	*	@return	bool idk �ڐG���Ă��邩
	*/
	virtual bool CheckCollisionRectangle(BaseCollider& _other) = 0;

	/**	@brief  �����蔻��
*	@date	2024/12/15
*	@param  BaseCollider& _other �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
	bool CheckCollision(BaseCollider& _other);
};

