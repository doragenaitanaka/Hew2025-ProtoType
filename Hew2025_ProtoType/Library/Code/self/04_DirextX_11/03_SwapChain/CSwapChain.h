#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_SwapChain
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/
	CD3D11_SwapChain();

	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~CD3D11_SwapChain();

	/**	@brief 	�����_�[�^�[�Q�b�g�r���[�̍쐬
	*	@param	ID3D11Device* p_Device Direct3D�f�o�C�X
	*   @param  HWND hwnd              windows�n���h��
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	virtual	HRESULT    Create(HWND hwnd, ID3D11Device* m_pDevice);
	/**	@brief 	�������
	*	@date 2024/03/29
	*/
	void    Release();
public:
	IDXGISwapChain* m_pSwapChain;                   //�X���b�v�`�F�[��
	IDXGIFactory* pFactory;                         //DXGI�t�@�N�g��
};

