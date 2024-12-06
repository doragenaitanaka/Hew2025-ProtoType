/**	@file 	GameManager.cpp
*	@brief 	�v���W�F�N�g�S�̂̊Ǘ��N���X
*	@date	2024/05/20
*/
#include<Windows.h>
#include"GameManager.h"
//public static	--------------------------------------------------------------------------------
/**	@brief 	�N���X�C���X�^���X�̐����֐�
*	@date	2024/05/20
*	@memo	���̊֐����n�߂Ɏ��s����
*/
void	GameManager::CreateInstance(void)
{
	if (!GameManager::gameManager)
	{
		GameManager::gameManager = new	GameManager;
	}
}

/**	@brief 	�N���X�C���X�^���X�̎擾�֐�
*	@return	GameManager*	GameManager�N���X
*	@date	2024/05/20
*/
GameManager* GameManager::GetInstance(void)
{
	return	GameManager::gameManager;
}
//public	------------------------------------------------------------------------------------

/**	@brief 	�N���X�C���X�^���X�̍폜�֐�
*	@return	GameManager*	GameManager�N���X
*	@date	2024/05/20
*/
void    GameManager::DestroyInstance(void)
{
	//���݂��Ă�������
	if (GameManager::gameManager)
	{
		delete	GameManager::gameManager;
		GameManager::gameManager = nullptr;
	}
}

/**	@brief 	�v���W�F�N�g�S�̂̎��s�֐�
*	@param	_In_ HINSTANCE hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
*	@param	 _In_ int       nCmdShow		�E�B���h�E���\������鎞�̏��
*	@date	2024/05/20
*/
int	GameManager::Run(_In_ HINSTANCE hInstance, _In_ int       nCmdShow)
{
	this->windowSetup->Initialize(hInstance, nCmdShow);				// windows�̏�����
	//this->cd3d11->Initialize(this->windowSetup->GetHWnd());		// d3d11�̏�����
	MSG msg = { 0 };



	
	// ==========================================================================================================
	
	this->sceneManager->ChangeScene(Scene::TEST);		// �ŏ��̃V�[��

	// ==========================================================================================================
	


	// fps�Œ�p
	LARGE_INTEGER	liWork;		// ��Ɨp�ϐ�								
	QueryPerformanceFrequency(&liWork);
	this->frequency = liWork.QuadPart;

	// ����(�P�ʁF�J�E���g)���擾		
	QueryPerformanceCounter(&liWork);
	this->oldCount = liWork.QuadPart;
	this->nowCount = this->oldCount;

	//�Q�[�����[�v
	while (this->isRunning)
	{
		// windows�֘A
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {		//  ���b�Z�[�W�������
			TranslateMessage(&msg);
			DispatchMessage(&msg);							//  �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}
		if (WM_QUIT == msg.message) return 0;				//  �~�����ƏI������
		else
		{
			// ���݂̎��Ԃ��擾
			QueryPerformanceCounter(&liWork);
			this->nowCount = liWork.QuadPart;

			// �w�肵���t���[�����[�g���o�߂�����
			if (this->nowCount >= this->oldCount + this->frequency / FPS)
			{
				this->sceneManager->Run();				// �V�[���̎��s

				// FPS�֘A
				this->fpsCounter++;						// �Q�[�����������s������+1
				this->oldCount = this->nowCount;		
			}


			// FPS�֘A
			this->nowTick = GetTickCount64();	// ���ݎ��Ԃ��擾		
			if (this->nowTick >= this->oldTick + 1000)
			{
				// FPS��\��
				char	str[32];
				wsprintfA(str, "FPS=%d", this->fpsCounter);				// ���l�𕶎���ɕϊ�
				SetWindowTextA(this->windowSetup->GetHWnd(), str);		// �E�B���h�E�^�C�g���ɕ\��

				// �J�E���^�[���Z�b�g
				this->fpsCounter = 0;
				this->oldTick = nowTick;
			}
		}
	}
	this->sceneManager->DestroyInstance();					// �V�[���Ǘ��N���X�̍폜
	//this->cd3d11->DestroyInstance();						// CD3D11�N���X�̍폜
	this->windowSetup->DestroyInstance(hInstance);			// �E�B���h�E�N���X�̍폜
	return (int)msg.wParam;									// �E�B���h�E�v���V�[�W���ɓn��
}

/**	@brief 	�v���W�F�N�g���I������֐�
*	@date	2024/05/20
*	@memo	�Q�[�����[�v���t���O��false�ɂ���
*/
void	GameManager::EndGame(void)
{
	//�Q�[�����[�v�𔲂���
	if (this->isRunning)
	{
		this->isRunning = false;
	}
}
//private	------------------------------------------------------------------------------------

GameManager::GameManager()
{
	// �N���X�C���X�^���X�̍쐬
	WindowSetup::CreateInstance();	// windows�������N���X
	//CD3D11::CrerateIntance();		// D3D11�������N���X
	SceneManager::CreateInstance();	// �V�[���Ǘ��N���X

	//�N���X�C���X�^���X�̎擾
	this->windowSetup = WindowSetup::GetInstance();		// windows�������N���X
	//this->cd3d11 = CD3D11::GetInstance();				// D3D11�������N���X
	this->sceneManager = SceneManager::GetInstance();	// �V�[���Ǘ��N���X

	this->isRunning = true;								// �Q�[�����[�v����

	// FPS�v���p�ϐ�
	this->fpsCounter = 0;
	this->oldTick = GetTickCount64();								// �O��v�����̎��Ԃ��擾
	this->nowTick = this->oldTick;									// ����v�����̎���

	// FPS�Œ�p�֐�
	this->frequency = 0.0f;
	// ����(�P�ʁF�J�E���g)
	this->oldCount = 0.0f;
	this->nowCount = this->oldCount;
}

GameManager::~GameManager()
{}
//	�ÓI�����o�ϐ�	---------------------------------------------------------------------------------------------------

GameManager* GameManager::gameManager = nullptr;	//�ÓI�����o�ϐ��̏�����