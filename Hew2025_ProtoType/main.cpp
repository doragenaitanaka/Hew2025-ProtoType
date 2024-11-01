#include<Windows.h>
#include"Library/Code/self/04_GameManager/GameManager.h"
#include"Library/Code/self/01_Windows/WindowSetup.h"
#include"main.h"

//  �E�B���h�E��ʂ��o���̂ɕK�v�ȏ����Ƃ�֐�
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,			//  �A�v���̏����i�[�����������̈�|�C���^(���s����e�A�v���AOS�̃n���h��)
	_In_opt_ HINSTANCE hPrevInstance,	//  ���͎g���Ă��Ȃ��̂�null������
	_In_ LPWSTR    lpCmdLine,			//  �A�v���P�[�V�����N�����ɃR�}���h���C���Ŏw�肳�ꂽ����������
	_In_ int       nCmdShow)			//  �\�����@,�E�B���h�E���\������鎞�̏��
{
#ifdef DEBUG
    // �R���\�[���E�B���h�E�̏�����
    if (InitConsole() != 0) {
        return 1; 
    }
#endif // DEBUG

    GameManager::CreateInstance();							// �C���X�^���X�̐���
    GameManager* gameManager = GameManager::GetInstance();	// �C���X�^���X�̎擾
    int msg = 0;

    msg = gameManager->Run(hInstance, nCmdShow);
    return msg;		// �E�B���h�E�v���V�[�W���ɓn��
}

/**	@brief 	�R���\�[���E�B���h�E�̏�����
*	@date	2024/11/02
*/
int InitConsole()
{
    // �R���\�[���E�B���h�E�̏�����
    if (!AllocConsole()) {
        MessageBox(NULL, L"Failed to allocate console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // std���o�͂̃��_�C���N�g����R���\�[����ʂɂ���
    FILE* fp = nullptr;
    errno_t err = freopen_s(&fp, "CONOUT$", "w", stdout);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stdout to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    err = freopen_s(&fp, "CONIN$", "r", stdin);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stdin to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    err = freopen_s(&fp, "CONOUT$", "w", stderr);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stderr to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // �W�����o�̓X�g���[���̓�����L��
    std::ios::sync_with_stdio();
    // �W���X�g���[���̃N���A
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();

    // �t�@�C���|�C���^�����
    if (fp)fclose(fp);
    fp = nullptr;
}