/**	@file 	BaseScene.h
*	@brief 	�V�[�����N���X
*	@date	2024/05/10
*/

#pragma once
#include<iostream>

/**	@brief 	�V�[�����N���X
*	@date	2024/05/10
*	@memo	���ۃN���X�Ȃ̂ŃR���X�g���N�^�ȏ������z�֐��ɂ��Ă���
*/
class BaseScene
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/05/10
	*/
	BaseScene();
	
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/05/10
	*/
	virtual	~BaseScene();

	/**	@brief 	�V�[���S�̂̏�����
	*	@date	2024/05/10
	*/
	virtual	void	Initialize(void) = 0;

	/**	@brief 	�V�[���S�̂̍X�V
	*	@date	2024/05/10
	*/
	virtual	void	Update(void) = 0;

	/**	@brief 	�V�[���S�̂̕`��
	*	@date	2024/05/10
	*/
	virtual	void	Draw(void) = 0;

	/**	@brief 	�V�[���S�̂̏I������
	*	@date	2024/05/10
	*/
	virtual	void	Finalize(void) = 0;
};
