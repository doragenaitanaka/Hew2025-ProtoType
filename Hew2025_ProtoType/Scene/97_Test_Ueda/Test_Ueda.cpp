/**	@file	Test_Ueda.cpp
*	@brief 	�A�c�p�̃Q�[���V�[���N���X
*	@date	2024/05/10
*/
#include"Test_Ueda.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
Test_Ueda::Test_Ueda()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
Test_Ueda::~Test_Ueda()
{
	this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	Test_Ueda::Initialize(void)
{
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	Test_Ueda::Update(void)
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
void	Test_Ueda::Draw(void)
{
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	Test_Ueda::Finalize(void)
{
}