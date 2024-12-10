/**	@file 	SceneManager.cpp
*	@brief 	�V�[���Ǘ��N���X
*	@date	2024/05/11
*/

#include"SceneManager.h"
#include"../../../../Scene/01_TitleScene/TitleScene.h"
#include"../../../../Scene/02_GameScene/GameScene.h"
#include"../../../../Scene/03_ResultScene/ResultScene.h"

#include"../../../../Scene/95_Test_Ri/Test_Ri.h"
#include"../../../../Scene/96_Test_Imagawa/Test_Imagawa.h"
#include"../../../../Scene/97_Test_Ueda/Test_Ueda.h"
#include"../../../../Scene/98_Test_Uryu/Test_Uryu.h"
#include"../../../../Scene/99_TestScene/TestScene.h"

#include"../03_Windows/WindowSetup.h"
#include"../04_DirextX_11/01_Initialize/CD3D11.h"

#include<iostream>

//�ÓI�����o�ϐ��̏�����
SceneManager* SceneManager::sceneManager = nullptr;

//	private----------------------------------------------------------------------------------------------

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/11
*	@memo	�O�ł̐�����h��
*/
SceneManager::SceneManager()
{
	this->isInitialized = false;	//���������Ă��Ȃ���Ԃɂ��Ă���
	this->isChangedScene = false;	//�V�[���J�ڂ��Ă��Ȃ���Ԃɂ��Ă���
	this->nowScene = nullptr;
}

/**	@brief 	�f�X�g���N�^
*	@date	2024/05/11
*/
SceneManager::~SceneManager()
{
	//���݂̃V�[���̉��
	if (this->nowScene)
	{
		delete	this->nowScene;
		this->nowScene = nullptr;
	}
}

/**	@brief 	�V�[���̐���
*	@param	Scene	sceneName	���̃V�[����
*	@date	2024/05/11
*	@memo	�񓯊��̎��͂�����߂�lBaseScene*�ɂ��ĕ�������悤�ɂ���\��͖���I�I�I�I�I
*/
void	SceneManager::CreateScene(Scene sceneName)
{
	//���݂̃V�[�����������Ă����
	if (!this->nowScene) 
	{
		//�����ɍ��킹�ăV�[���𐶐�����
		switch (sceneName)
		{
		case Scene::TITLE:
			//cout << "TitleScene�𐶐�" << endl;
			this->nowScene = new	TitleScene;
			break;
		case Scene::GAME:
			//cout << "GameScene�𐶐�" << endl;
			this->nowScene = new	GameScene;
			break;
		case Scene::RESULT:
			//cout << "ResultScene�𐶐�" << endl;
			this->nowScene = new	ResultScene;
			break;
		case Scene::TEST:
			//cout << "TestScene�𐶐�" << endl;
			this->nowScene = new	TestScene;
			break;

		case Scene::TEST_IMAGAWA:
			//cout << "TestScene�𐶐�" << endl;
			this->nowScene = new	Test_Imagawa;
			break;
		case Scene::TEST_UEDA:
			//cout << "TestScene�𐶐�" << endl;
			this->nowScene = new	Test_Ueda;
			break;
		case Scene::TEST_URYU:
			//cout << "TestScene�𐶐�" << endl;
			this->nowScene = new	Test_Uryu;
			break;
		case Scene::TEST_RI:
			//cout << "TestScene�𐶐�" << endl;
			this->nowScene = new	Test_Ri;
			break;
		//case Scene::TAKAHASHI_TEST:
		//	//cout << "TestScene�𐶐�" << endl;
		//	this->nowScene = new	TestScene;
		//	break;
		default:
			break;
		}
	}
	//�V�[���������ł��Ă��Ȃ����
	if (!this->nowScene)
	{
		std::cerr << "�V�[�������Ɏ��s���܂���" << std::endl;
	}
}
 
//	public----------------------------------------------------------------------------------------------

/**	@brief 	�V�[���S�̂̎��s�֐�
*	@date	2024/05/11
*	@memo	�V�[���S�̂̏����̗���(�������A�X�V�A�`��)�������ɏ���
*/
void	SceneManager::Run(void)
{
	//�V�[�����������
	if (!this->nowScene)
	{
		std::cerr << "�V�[�������݂��܂���" << std::endl;
	}

	//�܂�����������Ă��Ȃ����
	if (!this->isInitialized)
	{	
 		this->nowScene->Initialize();	//	����������
		this->isChangedScene = false;	//�@�V�[���J�ڂ��Ă��Ȃ�
		this->isInitialized = true;		//	������

	}

	this->nowScene->Update();			//	�X�V����

	//�V�[���J�ڂ���Ă��Ȃ����
	if (!this->isChangedScene)
	{
		// cd3d11�N���X�̎擾
		CD3D11* cd3d11 = CD3D11::GetInstance();

		// �`��ɕK�v�ȃ��m���擾
		ID3D11DeviceContext* context = cd3d11->GetDeviceContext();
		ID3D11RenderTargetView* renderTargetView = cd3d11->GetRenderTargetView();
		IDXGISwapChain* swapChain = cd3d11->GetSwapChain();
		ID3D11DepthStencilView* depthStencilView = cd3d11->GetDepthStencilView();

		//��ʃN���A
		float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha							// ��ʓh��Ԃ��F
		context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);								// �`���̃L�����o�X�Ǝg�p����[�x�o�b�t�@���w�肷��
		context->ClearRenderTargetView(renderTargetView, clearColor);										// �`���L�����o�X��h��Ԃ�
		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);	// �[�x�o�b�t�@�����Z�b�g����

		this->nowScene->Draw();			// �`�揈��

		swapChain->Present(0, 0);		// �o�b�t�@�̐؂�ւ�
	}
}
/**	@brief 	�V�[���J�ڊ֐�
*	@param	Scene	sceneName	���̃V�[����
*	@date	2024/05/11
*/
void	SceneManager::ChangeScene(Scene	sceneName)
{
	if (this->nowScene)					//	���݂̃V�[���̃����������
	{
		delete	this->nowScene;
		this->nowScene = nullptr;
	}
	this->CreateScene(sceneName);		//	���̃V�[������

	this->isInitialized = false;		//	�������t���O���Z�b�g
	this->isChangedScene = true;		//�@�V�[���J�ڂ���
}
//	public (static)----------------------------------------------------------------------------------------------

/**	@brief 	�V�[���}�l�[�W���[�̐���
*	@date	2024/05/11
*	@memo	���̊֐����n�߂Ɏ��s����
*/
void	SceneManager::CreateInstance(void)
{
	//��������Ă��Ȃ���΃V�[���}�l�[�W���[�𐶐�����
	if (!SceneManager::sceneManager)
	{
		//cout << "�V�[���}�l�[�W���[�𐶐����܂�" << endl;
		SceneManager::sceneManager = new	SceneManager;
	}
}
/**	@brief 	�V�[���}�l�[�W���[�̍폜
*	@date	2024/05/11
*/
void	SceneManager::DestroyInstance(void)
{
	if (SceneManager::sceneManager)
	{
		//cout << "�V�[���}�l�[�W���[���������܂�" << endl;
		delete	SceneManager::sceneManager;
		SceneManager::sceneManager = nullptr;
	}
}
/**	@brief 	�V�[���}�l�[�W���[�̎擾
*	@return	SceneManager*	�V�[���}�l�[�W���[
*	@date	2024/05/11
*	@memo	���̊֐����g���Ċe�t�@�C���Ő����σV�[���}�l�[�W���[���擾����
*/
SceneManager* SceneManager::GetInstance(void)
{
	return	SceneManager::sceneManager;
}