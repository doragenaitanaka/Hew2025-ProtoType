/**	@file 	Test_Otani.h
*	@brief 	��J�p�̃e�X�g�V�[���N���X
*	@date	2024/12/14
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#pragma once

// �C���N���[�h
#include"../00_BaseScene/BaseScene.h"

/**	@file	Test_Otani.h
*	@brief 	�A�c�p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	���N���X�̏������z�֐����p�����Ă��闠�t��(������p�������h������)�Ɍp�����������o�֐���override�w��q���g�p���Ă���
*/
class Test_Otani :public BaseScene
{
public:
	/**	@brief 	�R���X�g���N�^
	*	* @date 2024/05/21
	*/
	Test_Otani();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/05/21
	*/
	~Test_Otani()override;
	/**	@brief 	�V�[���S�̂̏�����
	*	@date 2024/05/21
	*/
	void	Initialize(void)override;

	/**	@brief 	�V�[���S�̂̍X�V
	*	@date 2024/05/21
	*/
	void	Update(void)override;

	/**	@brief 	�V�[���S�̂̕`��
	*	@date 2024/05/21
	*/
	void	Draw(void)override;

	/**	@brief 	�V�[���S�̂̏I������
	*	@date 2024/05/21
	*/
	void	Finalize(void)override;

private:
};