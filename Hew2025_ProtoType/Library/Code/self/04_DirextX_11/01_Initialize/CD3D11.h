#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")

#include"../02_Device/CDevice.h"
#include"../03_SwapChain/CSwapChain.h"
#include"../04_RenderTargetView/CRenderTargetView.h"
#include"../05_DepthStencil/CDepthStencil.h"
#include"../06_Viewport/CViewport.h"

class CD3D11 {
public:
    /**	@brief 	�N���X�C���X�^���X�̐���
    *	@date	2024/05/16
    *	@memo	���̊֐����n�߂Ɏ��s����
    */
    static  void    CrerateIntance(void);

    /**	@brief 	�N���X�C���X�^���X�̎擾
    *	@return	CD3D11*	CD3D11�N���X
    *	@date	2024/05/14
    *	@memo	���̊֐����g���Ċe�t�@�C���Ő�����CD3D11�N���X���擾����
    */
    static	CD3D11* GetInstance(void);
    /**	@brief 	�N���X�C���X�^���X�̍폜
    *	@return	CD3D11*	CD3D11�N���X
    *	@date	2024/05/14
    */
    void    DestroyInstance(void);
    /**	@brief 	D3D11�̏�����
    *   @param  HWND hwnd   windous�n���h��
    *   @return HRESULT
    *	@date	2024/05/18
    */
    HRESULT Initialize(HWND hwnd);
    /**	@brief 	�S�̂̉��
    *	@date	2024/05/14
    */
    void    Release();
    //�Q�b�^�[�֐�------------------------------------------------------------------------------

    /**	@brief 	Direct3D�f�o�C�X�̎擾
    *	@return	CD3D11_Device*
    *	@date	2024/05/16
    */
    ID3D11Device* GetDevice(void);
    /**	@brief  �f�o�C�X�R���e�L�X�g�̎擾
    *	@return	CD3D11_Device*
    *	@date	2024/05/16
    */
    ID3D11DeviceContext* GetDeviceContext(void);

    /**	@brief 	�X���b�v�`�F�C���̎擾
    *	@return	CD3D11_SwapChain*
    *	@date	2024/05/16
    */
    IDXGISwapChain* GetSwapChain(void);
    /**	@brief 	�����_�[�^�[�Q�b�g�r���[�̎擾
    *	@return	ID3D11RenderTargetView*
    *	@date	2024/05/16
    */
    ID3D11RenderTargetView* GetRenderTargetView(void);
    /**	@brief 	�r���[�|�[�g�̎擾
    *	@return	D3D11_VIEWPORT
    *	@date	2024/05/16
    */
    D3D11_VIEWPORT* GetViewport(void);
    /**	@brief 	�[�x�X�e���V���̎擾
    *	@return	ID3D11DepthStencilView
    *	@date	2024/05/16
    */
    ID3D11DepthStencilView* GetDepthStencilView(void);

private:
    CD3D11();
    ~CD3D11();

private:
    CD3D11_Device  deviceSetup;                        //�O���t�B�b�N�f�o�C�X�̐ݒ�
    CD3D11_SwapChain   swapChainSetup;                 //�X���b�v�`�F�C���Z�b�g�A�b�v�̐ݒ�
    CD3D11_RenderTargetView  renderTargetViewSetup;    //�����_�[�^�[�Q�b�g�r���[�Z�b�g�A�b�v�̐ݒ�
    CD3D11_Viewport    viewportSetup;                  //�r���[�|�[�g�̐ݒ�
    CD3D11_DepthStencil    depthStencilSetup;          //�[�x�X�e���V���̐ݒ�

    static  CD3D11* cd3d11;
};