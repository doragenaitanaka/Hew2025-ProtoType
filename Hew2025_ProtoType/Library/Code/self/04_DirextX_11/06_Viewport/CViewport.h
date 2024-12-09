#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_Viewport
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/
	CD3D11_Viewport();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~CD3D11_Viewport();

	/**	@brief 	�r���[�|�[�g�̐ݒ�
	*	@param	ID3D11DeviceContext* p_ImmediateContext     �f�o�C�X�R���e�L�X�g
	*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	void    Create(ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* pSwapChain);

	/**	@brief 	�������
	*	@date 2024/03/29
	*/
	void    Release();
public:
	D3D11_VIEWPORT viewport;	//�r���[�|�[�g
	//��U1��ʑz��
};