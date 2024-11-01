/**	@file	TestScene.cpp
*	@brief 	�e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#include<DirectXMath.h> 
#include<time.h>
#include<algorithm>

#include"TestScene.h"
#include"../../Library/Code/self/01_Windows/WindowSetup.h"
#include"../../Library/Code/self/03_SceneManager/SceneManager.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
TestScene::TestScene()
{
    // �N���X�C���X�^���X�̎擾
    //this->p_cd3d11 = CD3D11::GetInstance();
    this->p_sceneManager = SceneManager::GetInstance();
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
TestScene::~TestScene()
{
    this->Finalize();
}

/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	TestScene::Initialize(void)
{
    //std::cout << "Initialize" << std::endl;
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	TestScene::Update(void)
{
    //std::cout << "Update" << std::endl;
}// Update()    end

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	TestScene::Draw(void)
{    
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	TestScene::Finalize(void)
{
    // �V���O���g���C���X�^���X
    if (this->p_sceneManager) { this->p_sceneManager = nullptr; }   // �V�[���}�l�[�W���[
    //if (this->p_cd3d11) { this->p_cd3d11 = nullptr; }               // cd3d11�N���X
}