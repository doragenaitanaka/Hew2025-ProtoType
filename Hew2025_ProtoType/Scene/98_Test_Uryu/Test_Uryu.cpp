/**	@file	Test_Uryu.cpp
*	@brief 	�Z���p�̃Q�[���V�[���N���X
*	@date	2024/05/10
*/
#include"Test_Uryu.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
Test_Uryu::Test_Uryu()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
Test_Uryu::~Test_Uryu()
{
	this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	Test_Uryu::Initialize(void)
{
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	Test_Uryu::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_URYU);
        return;
    }
    std::cout << "Test_Uryu::Update()" << std::endl;
}

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	Test_Uryu::Draw(void)
{
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	Test_Uryu::Finalize(void)
{
}