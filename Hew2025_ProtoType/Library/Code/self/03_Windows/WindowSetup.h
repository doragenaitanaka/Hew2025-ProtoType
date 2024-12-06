#pragma once
#include <windows.h>	

#define CLASS_NAME   L"DirectX11 Template"	// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  L"windows create test"	// �E�B���h�E�̖��O

#define	SCREEN_WIDTH	(640)
#define	SCREEN_HEIGHT	(480)

//�u�I�����܂����H�v�̉�ʏo�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//�E�B���h�E�̏����w�i�F
enum BackColorBrush
{
	WHITE	=	WHITE_BRUSH,	//0
	LTGRAY= LTGRAY_BRUSH,		//1
	GRAY= GRAY_BRUSH,			//2
	DKGRAY= DKGRAY_BRUSH,		//3
	BLACK= BLACK_BRUSH,			//4
	NOTHING	= NULL_BRUSH,		//5
	HOLLOW=HOLLOW_BRUSH,        //=NULL_BRUSH
};

//�E�B���h�E�\���ɕK�v�Ȃ��̂��܂Ƃ߂��N���X
class WindowSetup
{
public:
	/**	@brief 	windows�N���X�̐���
	*	@date	2024/05/14
	*	@memo	���̊֐����n�߂Ɏ��s����
	*/
	static	void	CreateInstance(void);
	/**	@brief 	windows�N���X�̎擾
	*	@return	WindowSetup*	windows�N���X
	*	@date	2024/05/14
	*	@memo	���̊֐����g���Ċe�t�@�C���Ő�����windows�N���X���擾����
	*/
	static	WindowSetup* GetInstance(void);
	/**	@brief	�S�̂̏�����
	*	@param	_In_ HINSTANCE hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
	*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
	*	@param	 _In_ int       nCmdShow		�E�B���h�E���\������鎞�̏��
	*	@date	2024/05/14
	*/
	int	Initialize(_In_ HINSTANCE hInstance, _In_ int       nCmdShow);
	/**	@brief 	windows�N���X�̍폜
	*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
	*	@date	2024/05/14
	*/
	void	DestroyInstance(HINSTANCE hInstance);
	/**	@brief	�n���h�����擾
	*	@return	HWND	windows�n���h��
	*	@date	2024/05/14
	*/
	HWND	GetHWnd(void);
private:	
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/
	WindowSetup();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~WindowSetup();
	/**	@brief 	�E�B���h�E�N���X�̓o�^�֐�
	*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
	*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
	*	@return
	*	@date 2024/03/29
	*	@memo	�E�B���h�E�N���X�̒�`�A�o�^���s��
	*/
	int	RegisterWindowClass(_In_ HINSTANCE hInstance);
	/**	@brief 	�E�B���h�E�N���X�̓o�^����������֐�
	*	@param	_In_ HINSTANCE	hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
	*	@return
	*	@date 2024/05/14
	*/
	void	UnregisterWindowClass(_In_ HINSTANCE hInstance);
	/**	@brief 	�E�B���h�E�̍쐬
	*	@return
	*	@date 2024/03/29
	*/
	int	CreateWindowScreen(void);

	/**	@brief 	�E�B���h�E�̕\���A�X�V
	*	@param	_In_ int			nCmdShow	�E�B���h�E���\������鎞�̏��
	*	@return
	*	@date 2024/05/15
	*/
	int	ShowWindowScreen(_In_ int       nCmdShow);
private:
	WNDCLASSEX wcex;	//windows�Ɋւ�����
	HWND hWnd;			//window�n���h��
	bool	isInit;		//true:wcex������������

	static	WindowSetup* appWindow;	
};
