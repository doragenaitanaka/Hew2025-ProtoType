#include"CD3D11.h"
#include"../../SafePointers.h"

//	private	---------------------------------------------------------------------------------------------------

/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11::CD3D11()
{}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11::~CD3D11()
{
    //�������
    this->Release();
}
/**	@brief 	�S�̂̉��
*	@date	2024/05/14
*/
void CD3D11::Release()
{
    this->deviceSetup.Release();
    this->swapChainSetup.Release();
    this->renderTargetViewSetup.Release();
    this->viewportSetup.Release();
    this->depthStencilSetup.Release();
}

//	static(public)	---------------------------------------------------------------------------------------------------

/**	@brief 	�N���X�C���X�^���X�̐���
*	@date	2024/05/16
*	@memo	���̊֐����n�߂Ɏ��s����
*/
void   CD3D11::CrerateIntance(void)
{
    //��������Ă��Ȃ����CD3D11�N���X�𐶐�����
    if (!CD3D11::cd3d11)
    {
        CD3D11::cd3d11 = new	CD3D11;
    }
}

/**	@brief 	�N���X�C���X�^���X�̎擾
*	@return	CD3D11*	CD3D11�N���X
*	@date	2024/05/16
*	@memo	���̊֐����g���Ċe�t�@�C���Ő�����CD3D11�N���X���擾����
*/
CD3D11* CD3D11::GetInstance(void)
{
    return  CD3D11::cd3d11;
}
/**	@brief 	�N���X�C���X�^���X�̍폜
*	@date	2024/05/16
*/
void    CD3D11::DestroyInstance(void)
{
    //���݂��Ă�����
    if (CD3D11::cd3d11)
    {
        delete  CD3D11::cd3d11;
        CD3D11::cd3d11 = nullptr;
    }
}
/**	@brief 	D3D11�̏�����
*   @param  HWND hwnd   windous�n���h��
*   @return HRESULT
*	@date	2024/05/18
*/
HRESULT CD3D11::Initialize(HWND hwnd)
{
    HRESULT  hr;

    //�O���t�B�b�N�f�o�C�X�̏�����
    hr = this->deviceSetup.Create();
    if (FAILED(hr)) { return hr; }

    //�X���b�v�`�F�[���̍쐬
    hr = this->swapChainSetup.Create(hwnd, this->deviceSetup.m_pDevice);
    if (FAILED(hr)) { return hr; }

    //�����_�[�^�[�Q�b�g�r���[�̍쐬
    hr = this->renderTargetViewSetup.Create(this->deviceSetup.m_pDevice, this->swapChainSetup.m_pSwapChain);
    if (FAILED(hr)) { return hr; }

    //�[�x�X�e���V���r���[�̍쐬
    hr = this->depthStencilSetup.Create(this->deviceSetup.m_pDevice, this->deviceSetup.m_pImmediateContext, this->swapChainSetup.m_pSwapChain, this->renderTargetViewSetup.m_pRenderTargetView);
    if (FAILED(hr)) { return hr; }

    //�r���[�|�[�g�̐ݒ�
    this->viewportSetup.Create(this->deviceSetup.m_pImmediateContext, this->swapChainSetup.m_pSwapChain);
    return  hr;
}
//�Q�b�^�[-----------------------------------------------------------------------------------------------------------------
/**	@brief 	Direct3D�f�o�C�X�̎擾
*	@return	CD3D11_Device*
*	@date	2024/05/16
*/
ID3D11Device* CD3D11::GetDevice(void)
{
    return  this->deviceSetup.m_pDevice;
}
/**	@brief  �f�o�C�X�R���e�L�X�g�̎擾
*	@return	CD3D11_Device*
*	@date	2024/05/16
*/
ID3D11DeviceContext* CD3D11::GetDeviceContext(void)
{
    return  this->deviceSetup.m_pImmediateContext;
}

/**	@brief 	�X���b�v�`�F�C���̎擾
*	@return	CD3D11_SwapChain*
*	@date	2024/05/16
*/
IDXGISwapChain* CD3D11::GetSwapChain(void)
{
    return  this->swapChainSetup.m_pSwapChain;
}
/**	@brief 	�����_�[�^�[�Q�b�g�r���[�̎擾
*	@return	ID3D11RenderTargetView*
*	@date	2024/05/16
*/
ID3D11RenderTargetView* CD3D11::GetRenderTargetView(void)
{
    return  this->renderTargetViewSetup.m_pRenderTargetView;
}
/**	@brief 	�r���[�|�[�g�̎擾
*	@return	D3D11_VIEWPORT
*	@date	2024/05/16
*/
D3D11_VIEWPORT* CD3D11::GetViewport(void)
{   
    return  &this->viewportSetup.viewport;
}
/**	@brief 	�[�x�X�e���V���̎擾
*	@return	ID3D11DepthStencilView*
*	@date	2024/05/16
*/
ID3D11DepthStencilView* CD3D11::GetDepthStencilView(void)
{
    return this->depthStencilSetup.p_DepthStencilView;
}
//	�ÓI�����o�ϐ�	---------------------------------------------------------------------------------------------------

CD3D11* CD3D11::cd3d11 = nullptr;	//�ÓI�����o�ϐ��̏�����