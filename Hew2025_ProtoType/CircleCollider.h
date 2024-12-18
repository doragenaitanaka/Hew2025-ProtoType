#pragma once
#include "BaseCollider.h"
#include "BoxCollider.h"
class CircleCollider :
    public BaseCollider
{
private:
	float radius;

public:

	/**	@brief  �R���X�g���N�^
	*	@date	2024/12/16
	*/
	CircleCollider(DirectX::XMFLOAT3 _pos, float _radius);


	/**	@brief  �f�X�g���N�^
	*	@date	2024/12/16
	*/
	~CircleCollider();


	/**	@brief  ���a�̕ύX
	*	@date	2024/12/15
	*	@param XMFLOAT3 _radius �ύX���������a�̒l
	*/
	void SetRadius(float);


	/**	@brief  ���a�̎擾
	*	@date	2024/12/16
	*	@return	XMFLOAT3 radius Object�̔��a
	*/
	float GetRadius(void);


	/**	@brief  �~�Ƃ̓����蔻��
*	@date	2024/12/15
*	@param  BaseCollider& idk �ڐG��������ΏۃI�u�W�F�N�g
*	@return	bool idk �ڐG���Ă��邩
*/
	bool CheckCollisionCircle(BaseCollider& _other) override;

	/**	@brief  ��`�Ƃ̓����蔻��
	*	@date	2024/12/15
	*	@param  BaseCollider& idk �ڐG��������ΏۃI�u�W�F�N�g
	*	@return	bool idk �ڐG���Ă��邩
	*/
	bool CheckCollisionRectangle(BaseCollider& _other) override;
};

