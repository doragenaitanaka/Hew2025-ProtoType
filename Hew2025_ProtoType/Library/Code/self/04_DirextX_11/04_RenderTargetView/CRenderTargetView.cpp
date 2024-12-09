#include"CRenderTargetView.h"
#include"../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11_RenderTargetView::CD3D11_RenderTargetView()
{
	this->m_pRenderTargetView = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11_RenderTargetView::~CD3D11_RenderTargetView()
{
    this->Release();
}
/**	@brief 	�����_�[�^�[�Q�b�g�r���[�̍쐬
*	@param	ID3D11Device* p_Device                      Direct3D�f�o�C�X
*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_RenderTargetView::Create(ID3D11Device* p_Device, IDXGISwapChain* p_SwapChain)
{
    HRESULT  hr;

    
    ID3D11Texture2D* pBackBuffer;                                                       //  �o�b�N�o�b�t�@
    hr = p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);   //  �X���b�v�`�F�[���̍ŏ��̃o�b�N�o�b�t�@(0�Ԗ�)���擾���Ă��� 
    if (FAILED(hr)) { return hr; }                                                      //  �擾�ł������`�F�b�N

    
    hr = p_Device->CreateRenderTargetView(pBackBuffer, NULL, &this->m_pRenderTargetView);   //�����_�[�^�[�Q�b�g�r���[�̍쐬(�o�b�t�@�̐F��������)  
    SAFE_RELEASE(pBackBuffer);                                                              //  �o�b�N�o�b�t�@�͂����g��Ȃ��̂ŉ������
    if (FAILED(hr)) { return hr; }                                                          //  �쐬�o�������`�F�b�N
    return hr;
}
/**	@brief 	�������
*	@date 2024/03/29
*/
void    CD3D11_RenderTargetView::Release()
{
    SAFE_RELEASE(this->m_pRenderTargetView);
}