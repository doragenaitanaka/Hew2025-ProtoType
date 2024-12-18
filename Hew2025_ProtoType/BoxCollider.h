#pragma once
#include "BaseCollider.h"
#include "CircleCollider.h"
class BoxCollider : public BaseCollider
{
private:
    DirectX::XMFLOAT3 size;

public:

	/**	@brief  �R���X�g���N�^
	*	@date	2024/12/16
	*/
    //BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size);
	BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size);

	/**	@brief  �f�X�g���N�^
	*	@date	2024/12/16
	*/
    ~BoxCollider();


	/**	@brief  �T�C�Y�̕ύX
	*	@date	2024/12/15
	*	@param XMFLOAT3 _size �ύX�������T�C�Y�̒l
	*	@return	bool idk �ڐG���Ă��邩
	*/
    void SetSize(DirectX::XMFLOAT3);


	/**	@brief  �T�C�Y�̎擾
	*	@date	2024/12/16
	*	@return	XMFLOAT3 size Object�̃T�C�Y
	*/
    DirectX::XMFLOAT3 GetSize(void);

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

