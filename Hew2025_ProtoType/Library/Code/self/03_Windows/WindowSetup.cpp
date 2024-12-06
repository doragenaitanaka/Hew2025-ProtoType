#include"WindowSetup.h"
#include"../SafePointers.h"
//	public (static)----------------------------------------------------------------------------------------------

/**	@brief 	windows�N���X�̐���
*	@date	2024/05/14
*	@memo	���̊֐����n�߂Ɏ��s����
*/
void	WindowSetup::CreateInstance(void)
{
	//��������Ă��Ȃ����windows�N���X�𐶐�����
	if (!WindowSetup::appWindow)
	{
		WindowSetup::appWindow = new	WindowSetup;
	}
}
/**	@brief 	windows�N���X�̎擾
*	@return	WindowSetup*	windows�N���X
*	@date	2024/05/14
*	@memo	���̊֐����g���Ċe�t�@�C���Ő�����windows�N���X���擾����
*/
WindowSetup* WindowSetup::GetInstance(void)
{
	return	WindowSetup::appWindow;
}
//	public -----------------------------------------------------------------------------------------------

/**	@brief	�S�̂̏�����
*	@param	_In_ HINSTANCE hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
*	@param	 _In_ int       nCmdShow		�E�B���h�E���\������鎞�̏��
*	@date	2024/05/14
*/
int	WindowSetup::Initialize(_In_ HINSTANCE hInstance, _In_ int       nCmdShow)
{
	int	er;
	if (er = this->RegisterWindowClass(hInstance) == E_FAIL) { return	er; }
	if (er = this->CreateWindowScreen() == E_FAIL) { return	er; }
	if (er = this->ShowWindowScreen(nCmdShow) == E_FAIL) { return	er; }

	return	er;
}
/**	@brief 	windows�N���X�̍폜
*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
*	@date	2024/05/14
*/
void	WindowSetup::DestroyInstance(_In_ HINSTANCE hInstance)
{
	//���݂��Ă�����
	if (WindowSetup::appWindow)
	{
		this->UnregisterWindowClass(hInstance);	//�E�B���h�E�N���X�̓o�^����
		delete	WindowSetup::appWindow;
		WindowSetup::appWindow = nullptr;
	}
}
/**	@brief	�n���h�����擾
*	@return	HWND	windows�n���h��
*	@date	2024/05/14
*/
HWND	WindowSetup::GetHWnd(void)
{
	return	this->hWnd;
}
//	private ----------------------------------------------------------------------------------------------
/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
WindowSetup::WindowSetup()
{
	isInit = false;		//true:wcex������������
}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
WindowSetup::~WindowSetup()
{}
/**	@brief 	�E�B���h�E�N���X�̓o�^�֐�
*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
*	@return
*	@date 2024/03/29
*	@memo	�E�B���h�E�N���X�̒�`�A�o�^���s��
*/
int	WindowSetup::RegisterWindowClass(_In_ HINSTANCE hInstance)
{
	//�E�B���h�E�N���X
	this->wcex.cbSize = sizeof(WNDCLASSEX);		//�\���̂̃T�C�Y
	this->wcex.style = CS_CLASSDC;				//�N���X�X�^�C��
	this->wcex.lpfnWndProc = WndProc;			//�E�B���h�E�v���V�[�W���ւ̃|�C���^�[
	this->wcex.cbClsExtra = 0L;					//�N���X�f�[�^�\���̂̌�Ɋ��蓖�Ă�ǉ��̃o�C�g��
	this->wcex.cbWndExtra = 0L;					//�E�B���h�E�C���X�^���X�̌�Ɋ��蓖�Ă�ǉ��̃o�C�g��
	this->wcex.hInstance = hInstance;			//�A�v���P�[�V�����C���X�^���X�̃n���h��
	this->wcex.hIcon = NULL;					//�E�B���h�E�N���X�̃A�C�R���ւ̃n���h��
	this->wcex.hCursor = NULL;					//�E�B���h�E�N���X�̃J�[�\���ւ̃n���h��
	this->wcex.hbrBackground = (HBRUSH)GetStockObject(BackColorBrush::DKGRAY);	// �E�B���h�E�̔w�i�u���V�ւ̃n���h��
	this->wcex.lpszMenuName = NULL;				//���j���[���\�[�X�̖��O
	this->wcex.lpszClassName = CLASS_NAME;		//�E�B���h�E�N���X�̖��O
	this->wcex.hIconSm = NULL;					//�������A�C�R���ւ̃n���h��

	//RegisterClassEx�֐��ɓn�������`�F�b�N
	if (!RegisterClassEx(&this->wcex))
	{
		return	E_FAIL;
	}
	//����������
	isInit = true;

	return	S_OK;
}
/**	@brief 	�E�B���h�E�N���X�̓o�^����������֐�
*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
*	@return
*	@date 2024/05/14
*/
void	WindowSetup::UnregisterWindowClass(_In_ HINSTANCE hInstance)
{
	if (this->hWnd)
	{
		UnregisterClass(CLASS_NAME, hInstance);
	}
}
/**	@brief 	�E�B���h�E�̍쐬
*	@return
*	@date 2024/03/29
*/
int	WindowSetup::CreateWindowScreen(void)
{
	//�������������̂ݎ��s����
	if (isInit)
	{
		//windows�n���h�����擾
		this->hWnd = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,		//�g���E�B���h�E�X�^�C��
			this->wcex.lpszClassName,	//�E�B���h�E�N���X��
			WINDOW_NAME,				//�E�B���h�E�̃^�C�g���o�[�ɕ\������閼�O
			WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��(����〈���ڂɊւ���I�v�V����)
			CW_USEDEFAULT,				//�E�B���h�E�̍������X���W
			CW_USEDEFAULT,				//�E�B���h�E�̍������Y���W
			SCREEN_WIDTH,						//�E�B���h�E�̕�
			SCREEN_HEIGHT,					//�E�B���h�E�̍���
			NULL,						//�e�E�B���h�E�̃n���h��(�Ɨ������E�B���h�E�̏ꍇ�� NULL)
			NULL,						//�E�B���h�E���g�p���郁�j���[�̃n���h��,�q�E�B���h�E��ID(���j���[���Ȃ��ꍇ�� NULL)
			this->wcex.hInstance,		//�E�B���h�E���쐬����v���O�����̃C���X�^���X�n���h��
			NULL						//�E�B���h�E�쐬���ɃE�B���h�E�v���V�[�W���ɓn�����ǉ��f�[�^
		);

		// �E�B���h�E�̃T�C�Y����ʂ̑傫�� + �g�̑����ɏC��
		RECT	rc1, rc2;
		GetWindowRect(this->hWnd, &rc1);	// �E�B���h�E�̒Z�a�̈���擾
		GetClientRect(this->hWnd, &rc2);	// �N���C�A���g�̒Z�a�̈���擾

		// �E�B���h�E�T�C�Y
		int	sx = SCREEN_WIDTH;
		int	sy = SCREEN_HEIGHT;

		// �g���̑傫�������Z
		sx += ((rc1.right - rc1.left) - (rc2.right- rc2.left));
		sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));

		// �E�B���h�E�T�C�Y��ύX
		SetWindowPos(this->hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));
	}
	//�n���h���������Ǝ擾�ł��Ă��邩�`�F�b�N
	if (!this->hWnd) {
		return E_FAIL;
	}
	return S_OK;
}
/**	@brief 	�E�B���h�E�̕\���A�X�V
*	@param	_In_ int			nCmdShow	�E�B���h�E���\������鎞�̏��
*	@return
*	@date 2024/05/15
*/
int	WindowSetup::ShowWindowScreen(_In_ int       nCmdShow)
{
	//�n���h�����擾���Ă��邩�`�F�b�N
	if (!this->hWnd) {
		return E_FAIL;
	}
	//�E�B���h�E��\��
	ShowWindow(this->hWnd, nCmdShow);	//�߂�l 0:�\������Ă����@1:��\��������
	//�E�B���h�E�̃N���C�A���g�̈���X�V
	UpdateWindow(this->hWnd);
	return S_OK;
}
//	�ÓI�����o�ϐ�	---------------------------------------------------------------------------------------------------

WindowSetup* WindowSetup::appWindow = nullptr;	//�ÓI�����o�ϐ��̏�����

//	���̑��֐�	-------------------------------------------------------------------------------------------------------

//�u�I�����܂����H�v�̉�ʏo�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//wParam�@���L�[���͑�����
		if (wParam == VK_ESCAPE)
		{													//���b�Z�[�W�{�b�N�X�́uok�v�u�L�����Z���v
			if (MessageBox(hWnd, L"�I��", L"�I�����܂����H", MB_OKCANCEL) == IDOK)
				PostQuitMessage(0);	//���b�Z�[�W�I������
		}
		break;
	case WM_CLOSE:  // �ux�v�{�^���������ꂽ��
	{
		int res = MessageBoxA(NULL, "�I�����܂����H", "�m�F", MB_OKCANCEL);
		if (res == IDOK) {
			DestroyWindow(hWnd);  // �uWM_DESTROY�v���b�Z�[�W�𑗂�
		}
	}
	break;
	default:
		// �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}