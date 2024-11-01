/**	@file	GameScene.h
*	@brief 	�Q�[���V�[���N���X
*	@date	2024/05/10
*/

#pragma once
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/03_SceneManager/SceneManager.h"
#include<iostream>

/**	@brief 	�Q�[���V�[���N���X
*	@date	2024/05/10
*	@memo	���N���X�̏������z�֐����p�����Ă��闠�t��(������p�������h������)�Ɍp�����������o�֐���override�w��q���g�p���Ă���
*/
class GameScene :public BaseScene
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/05/10
	*/
	GameScene();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/05/10
	*/
	~GameScene()override;
	/**	@brief 	�V�[���S�̂̏�����
	*	@date	2024/05/10
	*/
	void	Initialize(void)override;

	/**	@brief 	�V�[���S�̂̍X�V
	*	@date	2024/05/10
	*/
	void	Update(void)override;

	/**	@brief 	�V�[���S�̂̕`��
	*	@date	2024/05/10
	*/
	void	Draw(void)override;

	/**	@brief 	�V�[���S�̂̏I������
	*	@date	2024/05/10
	*/
	void	Finalize(void)override;
private:

};