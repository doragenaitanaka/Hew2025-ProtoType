/**	@file	TitleScene.cpp
*	@brief 	�^�C�g���V�[���N���X
*	@date	2024/05/10
*/
#include"TitleScene.h"
#include"../../Library/Code/self/03_SceneManager/SceneManager.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
TitleScene::TitleScene()
{
	this->p_sceneManager = SceneManager::GetInstance();	
    //this->p_cd3d11 = CD3D11::GetInstance();

}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
TitleScene::~TitleScene()
{
	this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	TitleScene::Initialize(void)
{
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10W
*/
void	TitleScene::Update(void)
{
}

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	TitleScene::Draw(void)
{
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	TitleScene::Finalize(void)
{
    // �}�l�[�W���[   sss
    //this->p_cd3d11 = nullptr;
    this->p_sceneManager = nullptr;
}