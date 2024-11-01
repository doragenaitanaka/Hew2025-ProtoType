#include<Windows.h>
#include"Library/Code/self/04_GameManager/GameManager.h"
#include"Library/Code/self/01_Windows/WindowSetup.h"

//  �E�B���h�E��ʂ��o���̂ɕK�v�ȏ����Ƃ�֐�
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,			//  �A�v���̏����i�[�����������̈�|�C���^(���s����e�A�v���AOS�̃n���h��)
	_In_opt_ HINSTANCE hPrevInstance,	//  ���͎g���Ă��Ȃ��̂�null������
	_In_ LPWSTR    lpCmdLine,			//  �A�v���P�[�V�����N�����ɃR�}���h���C���Ŏw�肳�ꂽ����������
	_In_ int       nCmdShow)			//  �\�����@,�E�B���h�E���\������鎞�̏��
{

	GameManager::CreateInstance();							// �C���X�^���X�̐���
	GameManager* gameManager = GameManager::GetInstance();	// �C���X�^���X�̎擾
	int msg = 0;

	msg = gameManager->Run(hInstance, nCmdShow);

	return msg;		// �E�B���h�E�v���V�[�W���ɓn��

}