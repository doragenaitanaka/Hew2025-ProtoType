#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_RenderTargetView
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/
	CD3D11_RenderTargetView();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~CD3D11_RenderTargetView();
	/**	@brief 	�����_�[�^�[�Q�b�g�r���[�̍쐬
	*	@param	ID3D11Device* p_Device                      Direct3D�f�o�C�X
	*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(ID3D11Device* p_Device, IDXGISwapChain* p_SwapChain);
	/**	@brief 	�������
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11RenderTargetView* m_pRenderTargetView;    //�����_�[�^�[�Q�b�g�r���[
};