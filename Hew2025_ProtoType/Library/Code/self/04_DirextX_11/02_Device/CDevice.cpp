#include"CDevice.h"
#include"../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11_Device::CD3D11_Device()
{
    this->m_pDevice = nullptr;
    this->m_pImmediateContext = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11_Device::~CD3D11_Device()
{
    this->Release();
}

/**	@brief 	�O���t�B�b�N�f�o�C�X�̏�����
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_Device::Create(void)
{
    HRESULT  hr;
    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    //�f�o�C�X�̎w��
    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;

    //�O���t�B�b�N�f�o�C�X�̏�����
    hr = D3D11CreateDevice(NULL,        //�f�o�C�X�̍쐬�Ɏg�p����r�f�I�A�_�v�^�[�ւ̃|�C���^�[
        D3D_DRIVER_TYPE_HARDWARE,       //�쐬����h���C�o�[�̎��
        NULL,                           // �\�t�g�E�F�A���X�^���C�U�[����������DLL�ւ̃n���h��
        flags,                          //�����^�C�����C���[��L���ɂ��邽�߂̃t���O
        pLevels,                        //�쐬���悤�Ƃ���������x���̏��������肷��D3D_FEATURE_LEVEL�̔z��ւ̃|�C���^�[
        1,                              //pFeatureLevels���̗v�f�̐�
        D3D11_SDK_VERSION,              //SDK�̃o�[�W����
        &this->m_pDevice,               //�쐬���ꂽ�f�o�C�X��\��ID3D11Device�I�u�W�F�N�g�ւ̃|�C���^�[�̃A�h���X��Ԃ�
        &level,                         //���������ꍇ�A��������pFeatureLevels�z�񂩂�ŏ���D3D_FEATURE_LEVEL��Ԃ�
        &this->m_pImmediateContext);    //�f�o�C�X�R���e�L�X�g��\��ID3D11DeviceContext�I�u�W�F�N�g�ւ̃|�C���^�[�̃A�h���X��Ԃ�

    //�����������`�F�b�N
    if (FAILED(hr)) { return hr; }
}
/**	@brief 	�������
*	@date 2024/03/29
*/
void    CD3D11_Device::Release()
{
    if (this->m_pImmediateContext) {
        this->m_pImmediateContext->ClearState();
    }
    SAFE_RELEASE(this->m_pImmediateContext);
    SAFE_RELEASE(this->m_pDevice);
}