/**	@file 	BaseScene.cpp
*	@brief 	�V�[�����N���X
*	@date	2024/05/10
*/

#include"BaseScene.h"
/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
BaseScene::BaseScene():p_sceneManager(nullptr)
{
	// �}�l�[�W���[�̎擾
	if (!this->p_sceneManager) { this->p_sceneManager = SceneManager::GetInstance(); }
	std::cout << "BaseScene::BaseScene()" << std::endl;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
BaseScene::~BaseScene()
{
	// �}�l�[�W���[�̎Q�Ƃ��Ȃ���
	if (this->p_sceneManager) { this->p_sceneManager = nullptr; }  
	std::cout << "BaseScene::~BaseScene()" << std::endl;
}