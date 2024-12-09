#pragma once
//D3D�ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../01_Initialize/CD3D11.h"

class CInputLayout
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/04/23
	*/
	CInputLayout();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/04/23
	*/
	~CInputLayout();

	/**	@brief 	���̓��C�A�E�g�̍쐬
	*	@param	D3D11_INPUT_ELEMENT_DESC*	layout		���_�f�[�^�|�C���^
	*	@param	UINT numElements	�v�f���T�C�Y
	*	@param	ID3DBlob*	p_vsBlob	�V�F�[�_�t�@�C���|�C���^
	*	@return	HRESULT
	*	@date	2024/04/23
	*/
	HRESULT	Create(D3D11_INPUT_ELEMENT_DESC* p_layout, UINT numElements, ID3DBlob* p_vsBlob);

	/**	@brief 	���̓A�Z���u���ɕR�Â�
	*	@date	2024/04/23
	*/
	void	SetInputLayout(void);

	/**	@brief 	�������
	*	@date	2024/04/23
	*/
	void	Release(void);
private:
	ID3D11InputLayout* p_inputLayout;	//���̓��C�A�E�g
	CD3D11* cd3d11;
};
