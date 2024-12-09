/**	@file 	BaseScene.cpp
*	@brief 	�V�[�����N���X
*	@date	2024/05/10
*/

#include"BaseScene.h"
/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
BaseScene::BaseScene() :p_sceneManager(nullptr), p_cd3d11(nullptr)
{
	// �}�l�[�W���[�̎擾
	if (!this->p_sceneManager) { this->p_sceneManager = SceneManager::GetInstance(); }
	if (!this->p_cd3d11) { this->p_cd3d11 = CD3D11::GetInstance(); }
	std::cout << "BaseScene::BaseScene()" << std::endl;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
BaseScene::~BaseScene()
{
	// �}�l�[�W���[�̎Q�Ƃ��Ȃ���
	if (this->p_sceneManager) { this->p_sceneManager = nullptr; }  
	if (this->p_cd3d11) { this->p_cd3d11 = nullptr; }
	std::cout << "BaseScene::~BaseScene()" << std::endl;
}