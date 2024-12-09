/**	@file 	SceneManager.h
*	@brief 	�V�[���Ǘ��N���X
*	@date	2024/05/11
*/

#pragma once
//�V�[���N���X
#include"../../../../Scene/00_BaseScene/BaseScene.h"
#include<iostream>

//�V�[����
enum Scene
{
	TITLE,
	GAME,
	RESULT,

	TEST,

	TEST_IMAGAWA,
	TEST_UEDA,
	TEST_URYU,
	TEST_RI,
	//TEST_TAKAHASHI,
};

// �O���錾
class BaseScene;

/**	@brief 	�V�[���Ǘ��N���X
*	@date	2024/05/11
*	@memo	�V�[�����̂̎��s�A�V�[���J�ڂ��Ǘ�
*	@memo	����͔񓯊�������z�肵�Ȃ��̂ŊǗ�����|�C���^��1��
*	@memo	�V���O���g���p�^�[���AsceneManager���e�t�@�C���ŌĂяo���Ďg�p����
*/
class SceneManager
{
private:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/05/11
	*	@memo	�O�ł̐�����h��
	*/
	SceneManager();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/05/11
	*/
	~SceneManager();
	/**	@brief 	�V�[���̐���
	*	@param	Scene	sceneName	���̃V�[����
	*	@date	2024/05/11
	*	@memo	�񓯊��̎��͂�����߂�lBaseScene*�ɂ��ĕ�������悤�ɂ���\��͖���I�I�I�I�I
	*/
	void	CreateScene(Scene sceneName);

public:
	/**	@brief 	�V�[���S�̂̎��s�֐�
	*	@date	2024/05/11
	*	@memo	�V�[���S�̂̏����̗���(�������A�X�V�A�`��)�������ɏ���
	*/
	void	Run(void);
	/**	@brief 	�V�[���J�ڊ֐�
	*	@param	Scene	sceneName	���̃V�[����
	*	@date	2024/05/11
	*/
	void	ChangeScene(Scene	sceneName);

	/**	@brief 	�V�[���}�l�[�W���[�̐���
	*	@date	2024/05/11
	*	@memo	���̊֐����n�߂Ɏ��s����
	*/
	static	void	CreateInstance(void);
	/**	@brief 	�V�[���}�l�[�W���[�̍폜
	*	@date	2024/05/11
	*/
	static	void	DestroyInstance(void);
	/**	@brief 	�V�[���}�l�[�W���[�̎擾
	*	@return	SceneManager*	�V�[���}�l�[�W���[
	*	@date	2024/05/11
	*	@memo	���̊֐����g���Ċe�t�@�C���Ő����σV�[���}�l�[�W���[���擾����
	*/
	static	SceneManager* GetInstance(void);
	
private:
	bool	isInitialized;					//true:����������
	bool	isChangedScene;					//true:�V�[���J�ڂ��s��ꂽ
	BaseScene* nowScene;					//���݂̃V�[���̃A�h���X��ێ�����
	static	SceneManager* sceneManager;		//�V�[���}�l�[�W���[
};