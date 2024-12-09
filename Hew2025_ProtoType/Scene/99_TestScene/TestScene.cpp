/**	@file	TestScene.cpp
*	@brief 	�e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#include"TestScene.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
TestScene::TestScene()
{
    std::cout << "TestScene::TestScene()" << std::endl;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
TestScene::~TestScene()
{
    std::cout << "TestScene::~TestScene()" << std::endl;
    this->Finalize();
}

/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	TestScene::Initialize(void)
{
    std::cout << "TestScene::Initialize()" << std::endl;
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	TestScene::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST);
        return;
    }

    std::cout << "TestScene::Update()" << std::endl;
}// Update()    end

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	TestScene::Draw(void)
{    
    std::cout << "TestScene::Draw()" << std::endl;
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	TestScene::Finalize(void)
{
    std::cout << "TestScene::Finalize()" << std::endl;
}