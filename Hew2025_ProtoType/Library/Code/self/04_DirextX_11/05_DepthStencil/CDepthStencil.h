#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_DepthStencil
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/	
	CD3D11_DepthStencil();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~CD3D11_DepthStencil();
	/**	@brief 	�[�x�X�e���V���̏�����
	*	@param	ID3D11Device* p_Device                      Direct3D�f�o�C�X
	*	@param	ID3D11DeviceContext* p_ImmediateContext     �f�o�C�X�R���e�L�X�g
	*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
	*   @param  ID3D11RenderTargetView* m_pRenderTargetView �����_�[�^�[�Q�b�g�r���[s
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(ID3D11Device* p_Device, ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* p_SwapChain, ID3D11RenderTargetView* m_pRenderTargetView);
	/**	@brief 	�������
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11DepthStencilView* p_DepthStencilView;	//�[�x�X�e���V���r���[
};

