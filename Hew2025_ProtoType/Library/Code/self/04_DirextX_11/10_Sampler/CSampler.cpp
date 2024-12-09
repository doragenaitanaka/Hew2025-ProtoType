#include"CSampler.h"
#include"../01_Initialize/CD3D11.h"
CSampler::CSampler()
{
    this->p_samplerState = nullptr;
}

CSampler::~CSampler()
{
    this->Release();
}

/**	@brief 	�T���v���[�̍쐬
*	@param	D3D11_FILTER filter
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressU
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressV
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressW
*	@return HRESULT
*	@date 2024/05/30
*   @memo   �e�N�X�`�����|���S���ɓ\��Ƃ��ɁA�g��k�������ۂ̃A���S���Y��
*/
HRESULT	CSampler::Create(D3D11_FILTER filter,
	D3D11_TEXTURE_ADDRESS_MODE	addressU,
	D3D11_TEXTURE_ADDRESS_MODE	addressV,
	D3D11_TEXTURE_ADDRESS_MODE	addressW)
{
    // ���e�N�X�`�����|���S���ɓ\��Ƃ��ɁA�g��k�������ۂ̃A���S���Y��
    D3D11_SAMPLER_DESC	smpDesc;
    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
    smpDesc.Filter = filter;
    smpDesc.AddressU = addressU;
    smpDesc.AddressV = addressV;
    smpDesc.AddressW = addressW;

    // �f�o�C�X�̎擾
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11Device* p_device = p_cd3d11->GetDevice();    
    // �T���v���[���쐬
    HRESULT hr;
    hr = p_device->CreateSamplerState(&smpDesc, &this->p_samplerState);
    if (FAILED(hr)) { return  hr; }
    return  hr;
}
/**	@brief 	�T���v���[�𒸓_�V�F�[�_�ɓn��
*	@param	UINT StartSlot		�T���v���[�̃C���f�b�N�X(�f�o�C�X�̔z��̂ǂ��ɒu���̂�)�w��
*	@param	UINT NumSamplers	�z����Ŏg���T���v���[��(�f�o�C�X�̔z��łǂ̂��炢�̑傫���Ȃ̂�)
*	@date 2024/05/30
*/
void	CSampler::SetSamplerVS(UINT StartSlot, UINT NumSamplers)
{
    // ������Ζ߂�
    if (!this->p_samplerState) { return; }

    // �f�o�C�X�R���e�L�X�g�̎擾
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* p_deviceContext = p_cd3d11->GetDeviceContext();
    // �T���v���[�𒸓_�V�F�[�_�ɃZ�b�g
    p_deviceContext->VSSetSamplers(StartSlot, NumSamplers, &this->p_samplerState);
}

/**	@brief 	�T���v���[���s�N�Z���V�F�[�_�ɓn��
*	@param	UINT StartSlot		�T���v���[�̃C���f�b�N�X(�f�o�C�X�̔z��̂ǂ��ɒu���̂�)�w��
*	@param	UINT NumSamplers	�z����Ŏg���T���v���[��(�f�o�C�X�̔z��łǂ̂��炢�̑傫���Ȃ̂�)
*	@date 2024/05/30
*/
void	CSampler::SetSamplerPS(UINT StartSlot, UINT NumSamplers)
{
    // ������Ζ߂�
    if (!this->p_samplerState) { return; }

    // �f�o�C�X�R���e�L�X�g�̎擾
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* p_deviceContext = p_cd3d11->GetDeviceContext();
    // �T���v���[���s�N�Z���V�F�[�_�ɃZ�b�g
    p_deviceContext->PSSetSamplers(StartSlot, NumSamplers, &this->p_samplerState);
}

/**	@brief 	�������̉������
*	@date 2024/05/30
*/
void	CSampler::Release(void)
{
    if (this->p_samplerState) { this->p_samplerState->Release(); }
}