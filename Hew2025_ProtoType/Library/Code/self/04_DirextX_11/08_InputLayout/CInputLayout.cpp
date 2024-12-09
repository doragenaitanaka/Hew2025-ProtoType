#include"CInputLayout.h"
#include"../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/23
*/
CInputLayout::CInputLayout()
{
    this->p_inputLayout = NULL;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/23
*/
CInputLayout::~CInputLayout()
{
	this->Release();
}

/**	@brief 	���̓��C�A�E�g�̍쐬
*	@param	D3D11_INPUT_ELEMENT_DESC*	layout	���_�f�[�^�|�C���^
*	@param	UINT numElements	                �v�f���T�C�Y
*	@param	ID3DBlob*	p_vsBlob	            �V�F�[�_�t�@�C���|�C���^
*	@return	HRESULT
*	@date	2024/04/23
*/
HRESULT	CInputLayout::Create(D3D11_INPUT_ELEMENT_DESC*	p_layout, UINT numElements, ID3DBlob* p_vsBlob)
{
    if (!this->p_inputLayout)
    {
        // ���_�V�F�[�_�[�̃o�C�g�R�[�h���擾
        LPVOID pShaderBytecode = p_vsBlob->GetBufferPointer();
        SIZE_T bytecodeLength = p_vsBlob->GetBufferSize();


        HRESULT hr;
        //CD3D11�N���X�̎擾
        if (!this->cd3d11)
        {
            this->cd3d11 = CD3D11::GetInstance();
        }
        //�f�o�C�X�̎擾
        ID3D11Device* device = cd3d11->GetDevice();
        // ���̓��C�A�E�g�̍쐬
        hr = device->CreateInputLayout(
            p_layout,               //���͗v�f�L�q�q�̔z��ւ̃|�C���^�[
            numElements,            //�z����̗v�f�̐�
            pShaderBytecode,        //�R���p�C�����ꂽ�V�F�[�_�[�̃o�C�g�R�[�h�ւ̃|�C���^�[
            bytecodeLength,         //�R���p�C�����ꂽ�V�F�[�_�[�̃o�C�g�R�[�h�̃T�C�Y
            &this->p_inputLayout    //�쐬���ꂽ���̓��C�A�E�g�I�u�W�F�N�g�ւ̃|�C���^�[���󂯎�邽�߂̓�d�|�C���^�[
        );
        if (FAILED(hr))
        {
            this->Release();
        }
        return  hr;
    }
    return  S_OK;
}

/**	@brief 	���̓A�Z���u���ɕR�Â�
*	@date	2024/04/23
*/
void	CInputLayout::SetInputLayout(void)
{
    if (this->p_inputLayout)
    {
        if (this->cd3d11)
        {
            ID3D11DeviceContext* context = cd3d11->GetDeviceContext();	//	�f�o�C�X�R���e�L�X�g�̎擾		
            context->IASetInputLayout(this->p_inputLayout);             //  ���̓��C�A�E�g�̐ݒ�
        }
    }
}

/**	@brief 	�������
*	@date	2024/04/23
*/
void	CInputLayout::Release(void)
{
    SAFE_RELEASE(this->p_inputLayout);
    this->cd3d11 = nullptr;
}