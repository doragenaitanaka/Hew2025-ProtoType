/**	@file 	Test_Ri.h
*	@brief 	���p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#pragma once

// �C���N���[�h
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include<iostream>

/**	@file	Test_Ri.h
*	@brief 	���p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	���N���X�̏������z�֐����p�����Ă��闠�t��(������p�������h������)�Ɍp�����������o�֐���override�w��q���g�p���Ă���
*/
class Test_Ri :public BaseScene
{
public:
	/**	@brief 	�R���X�g���N�^
	*	* @date 2024/05/21
	*/
	Test_Ri();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/05/21
	*/
	~Test_Ri()override;
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