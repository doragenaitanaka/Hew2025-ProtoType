#include"CVertexShader.h"
#include"../../01_Initialize/CD3D11.h"
#include"../../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/24
*/
CVertexShader::CVertexShader()
{
	this->p_vertexShader = NULL;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/24
*/
CVertexShader::~CVertexShader()
{
	//���_�V�F�[�_�[�̉��
	this->Release();
}

/**	@brief 	���_�V�F�[�_�[�̍쐬
*	@param	ID3D11ClassLinkage* p_classLinkage	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CVertexShader::Create(ID3D11ClassLinkage* p_classLinkage)
{
    //�����ς̏ꍇ�͔�΂�
    if (!this->p_vertexShader)
    {
        
        ID3DBlob* p_vsCode = this->GetShaderFile();
        //CD3D11�N���X�̎擾
        if (!this->cd3d11)
        {
            this->cd3d11 = CD3D11::GetInstance();
        }
        //�f�o�C�X�̎擾
        HRESULT hr;
        ID3D11Device* device = cd3d11->GetDevice();
        //���_�V�F�[�_�̐���
        hr = device->CreateVertexShader(
            p_vsCode->GetBufferPointer(),       //�R���p�C�����ꂽ�V�F�[�_�ւ̃|�C���^
            p_vsCode->GetBufferSize(),          //�R���p�C�����ꂽ���_�V�F�[�_�[�̃T�C�Y
            NULL,                               //�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
            &this->p_vertexShader               //�쐬���ꂽID3D11VertexShader�C���^�[�t�F�C�X�ւ̃|�C���^�[�̃A�h���X
        );
        if (FAILED(hr))
        {
            this->Release();
        }
        return  hr;
    }
    return  S_OK;
}

/**	@brief 	���_�V�F�[�_�[�̃Z�b�g
*	@param	ID3D11ClassInstance* const* pp_classInstances	�N���X�C���X�^���X�z��̃|�C���^
*	@param	UINT	numClassInstances	�N���X�C���X�^���X�z��̐�
*	@date	2024/04/24
*/
void	CVertexShader::SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances)
{
    //���݂��Ă��Ȃ���΃G���[
    if (!this->p_vertexShader)
    {
        // �V�F�[�_�̃G���[���e��\��
        MessageBox(NULL, L"���_�V�F�[�_�[������܂���", L"Shader Error", MB_OK);
        return;
    }
    //CD3D11�N���X�̎擾
    if (!this->cd3d11)
    {
        this->cd3d11 = CD3D11::GetInstance();
    }
    if (this->cd3d11)
    {
        ID3D11DeviceContext* context = cd3d11->GetDeviceContext();						    //	�f�o�C�X�R���e�L�X�g�̎擾		
        context->VSSetShader(this->p_vertexShader, pp_classInstances, numClassInstances);   //   ���_�V�F�[�_���Z�b�g
    }
}

/**	@brief 	���_�V�F�[�_�[�̉��
*	@date	2024/04/24
*/
void	CVertexShader::Release(void)
{
	this->CShader::Release();	        // ���_�V�F�[�_�[�t�@�C���̉��
    SAFE_RELEASE(this->p_vertexShader);	// ���_�V�F�[�_�̉��
}