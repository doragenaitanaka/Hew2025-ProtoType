/**	@file	Test_Otani.cpp
*	@brief 	��J�p�̃Q�[���V�[���N���X
*	@date	2024/12/14
*/
#include"Test_Otani.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
Test_Otani::Test_Otani()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
Test_Otani::~Test_Otani()
{
    this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	Test_Otani::Initialize(void)
{
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	Test_Otani::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_UEDA);
        return;
    }
}

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	Test_Otani::Draw(void)
{
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	Test_Otani::Finalize(void)
{
}