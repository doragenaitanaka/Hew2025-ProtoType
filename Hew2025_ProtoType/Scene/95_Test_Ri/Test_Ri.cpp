/**	@file	Test_Ri.cpp
*	@brief 	���p�̃Q�[���V�[���N���X
*	@date	2024/05/10
*/
#include"Test_Ri.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
Test_Ri::Test_Ri()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
Test_Ri::~Test_Ri()
{
	this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	Test_Ri::Initialize(void)
{
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	Test_Ri::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_RI);
        return;
    }
    std::cout << "Test_Ri::Update()" << std::endl;
}

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	Test_Ri::Draw(void)
{
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	Test_Ri::Finalize(void)
{
}