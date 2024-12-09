#include"CSwapChain.h"
#include<atltypes.h>
#include"../../SafePointers.h"
//CreateDXGIFactory �֐����g���̂ɕK�v
#include<dxgi.h>
#pragma comment(lib, "dxgi.lib")

/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11_SwapChain::CD3D11_SwapChain()
{
    this->m_pSwapChain = nullptr;
    this->pFactory = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11_SwapChain::~CD3D11_SwapChain()
{
    this->Release();
}

/**	@brief 	�����_�[�^�[�Q�b�g�r���[�̍쐬
*	@param	ID3D11Device* p_Device Direct3D�f�o�C�X
*   @param  HWND hwnd              windows�n���h��
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_SwapChain::Create(HWND hwnd, ID3D11Device* m_pDevice)
{
    HRESULT  hr;

    //�X���b�v�`�F�[���̐ݒ�
    CRect                rect;
    DXGI_SWAP_CHAIN_DESC scDesc;

    //�w��̃E�B���h�E�̒��g��S�ď�����
    ::GetClientRect(hwnd, &rect);
    ::ZeroMemory(&scDesc, sizeof(scDesc));

    //�o�b�N�o�b�t�@�̕\�����[�h
    scDesc.BufferDesc.Width = rect.Width();
    scDesc.BufferDesc.Height = rect.Height();
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //�}���`�T���v�����O�̃p�����[�^
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;

    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      // �V�����t���[�����`�悳��邽�тɁA�O�̃t���[���o�b�t�@�̓��e���j�������
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferCount = 2;                                 //�X���b�v�`�F�[�����̃o�b�t�@�̐�
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //�o�b�N�o�b�t�@�̎g�p���@
    scDesc.OutputWindow = hwnd;                             //�o�͂���E�B���h�E�̃n���h��
    scDesc.Windowed = TRUE;                                 //�E�B���h�E���[�h���ǂ���

    //DXGI�t�@�N�g���I�u�W�F�N�g�̍쐬
    //�Â��H
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&this->pFactory);
    //�����������`�F�b�N
    if (FAILED(hr)) { return hr; }

    //�X���b�v�`�F�[���̏�����
    //11.1�ȍ~�ł�IDXGIFactory2::CreateSwapChainForHwnd���������ۂ���
    //����11.0�Ȃ̂ł���ōs��
    hr = this->pFactory->CreateSwapChain(m_pDevice,         //�X���b�v�`�F�[�����쐬����Direct3D�f�o�C�X�ւ̃|�C���^�[
        &scDesc,                                            //�X���b�v�`�F�[���̐ݒ���܂�DXGI_SWAP_CHAIN_DESC�\���̂ւ̃|�C���^�[
        &this->m_pSwapChain);                               //�쐬���ꂽ�X���b�v�`�F�[���̃C���^�[�t�F�[�X�ւ̃|�C���^�[���󂯎��ϐ��ւ̃|�C���^�[

    //�����������`�F�b�N
    if (FAILED(hr)) { return hr; }
    return hr;
}

/**	@brief 	�������
*	@date 2024/03/29
*/
void    CD3D11_SwapChain::Release()
{
    SAFE_RELEASE(this->m_pSwapChain);
    SAFE_RELEASE(this->pFactory);
}