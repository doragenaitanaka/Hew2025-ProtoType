#include"CViewport.h"

/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11_Viewport::CD3D11_Viewport()
{
}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11_Viewport::~CD3D11_Viewport()
{
	this->Release();
}

/**	@brief 	�r���[�|�[�g�̐ݒ�
*	@param	ID3D11DeviceContext* p_ImmediateContext     �f�o�C�X�R���e�L�X�g
*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
*	@return HRESULT
*	@date 2024/03/29
*/
void    CD3D11_Viewport::Create(ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* pSwapChain)
{
	// �o�b�N�o�b�t�@�̎擾
	ID3D11Texture2D* backBuffer = NULL;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// �o�b�N�o�b�t�@����𑜓x���擾
	D3D11_TEXTURE2D_DESC	buckBufferDesc;
	backBuffer->GetDesc(&buckBufferDesc);

	// �r���[�|�[�g�̏�����
	this->viewport.TopLeftX = 0;
	this->viewport.TopLeftY = 0;
	this->viewport.Width = buckBufferDesc.Width;
	this->viewport.Height = buckBufferDesc.Height;
	this->viewport.MinDepth = 0.0f;
	this->viewport.MaxDepth = 1.0f;

	backBuffer->Release();									// �K�v�Ȃ��Ȃ����̂ŉ��
	p_ImmediateContext->RSSetViewports(1, &this->viewport);	// �r���[�|�[�g��ݒ�
}

/**	@brief 	�������
*	@date 2024/03/29
*/
void   CD3D11_Viewport::Release()
{
}