#pragma once
/**	@file 	GameManager.h
*	@brief 	�v���W�F�N�g�S�̂̊Ǘ��N���X
*	@date	2024/05/20
*/

#include"../03_Windows/WindowSetup.h"
#include"../04_DirextX_11/01_Initialize/CD3D11.h"
#include"../02_SceneManager/SceneManager.h"

//define��`
#define	FPS (60)

class GameManager
{
public:
	/**	@brief 	�N���X�C���X�^���X�̐����֐�
	*	@date	2024/05/20
	*	@memo	���̊֐����n�߂Ɏ��s����
	*/
	static	void	CreateInstance(void);
	/**	@brief 	�N���X�C���X�^���X�̎擾�֐�
	*	@return	CD3D11*	CD3D11�N���X
	*	@date	2024/05/20
	*	@memo	���̊֐����g���Ċe�t�@�C���Ő�����CD3D11�N���X���擾����
	*/
	static	GameManager* GetInstance(void);
	/**	@brief 	�N���X�C���X�^���X�̍폜�֐�
	*	@return	CD3D11*	CD3D11�N���X
	*	@date	2024/05/20
	*/
	void    DestroyInstance(void);
	/**	@brief 	�v���W�F�N�g�S�̂̎��s�֐�
	*	@param	_In_ HINSTANCE hInstance		���݂̃A�v���P�[�V�����C���X�^���X�ւ̃n���h��
	*	@param	BackColorBrush      backColor	�E�B���h�E�̔w�i�F
	*	@param	 _In_ int       nCmdShow		�E�B���h�E���\������鎞�̏��
	*	@param	int	�v���V�[�W���Ƀ��b�Z�[�W��Ԃ�
	*	@date	2024/05/20
	*/
	int	Run(_In_ HINSTANCE hInstance, _In_ int       nCmdShow);
	/**	@brief 	�v���W�F�N�g���I������֐�
	*	@date	2024/05/20
	*	@memo	�Q�[�����[�v���t���O��false�ɂ���
	*/
	void	EndGame(void);
private:
	GameManager();
	~GameManager();
private:
	CD3D11* cd3d11;							// d3d11�̏��������܂Ƃ߂��N���X
	WindowSetup* windowSetup;				// windows�̏��������܂Ƃ߂��N���X
	SceneManager* sceneManager;				// �V�[���Ǘ��N��
	
	bool	isRunning;						// true:�Q�[�����[�v���s��

	// FPS�v���p�ϐ�
	int	fpsCounter;		
	long	long	oldTick;				// �O��v�����̎���
	long	long	nowTick;				// ����v�����̎���

	// FPS�Œ�p�֐�
	long	long	frequency;				// �ǂꂭ�炢�ׂ������Ԃ��J�E���g�ł��邩
	// ����(�P�ʁF�J�E���g)
	long	long	oldCount;				// �O��v�����̎���
	long	long	nowCount;				// ����v�����̎���

	static	GameManager* gameManager;		// �v���W�F�N�g�Ǘ��N���X
};

