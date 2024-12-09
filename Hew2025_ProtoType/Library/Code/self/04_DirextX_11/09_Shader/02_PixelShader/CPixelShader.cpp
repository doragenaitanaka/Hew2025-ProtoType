#include"CPixelShader.h"
#include"../../01_Initialize/CD3D11.h"
#include"../../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/24
*/

CPixelShader::CPixelShader()
{
	this->p_pixelShader = NULL;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/24
*/
CPixelShader::~CPixelShader()
{
	this->Release();
}

/**	@brief 	�s�N�Z���V�F�[�_�[�̍쐬
*	@param	ID3D11ClassLinkage* p_classLinkage	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CPixelShader::Create(ID3D11ClassLinkage* p_classLinkage)
{
	if (!this->p_pixelShader)
	{
		HRESULT hr;
		ID3DBlob* p_vsCode = this->GetShaderFile();	//�V�F�[�_�[�t�@�C���̎擾
		//CD3D11�N���X�̎擾
		if (!this->cd3d11)
		{
			this->cd3d11 = CD3D11::GetInstance();
		}
		//�f�o�C�X�̎擾
		ID3D11Device* device = cd3d11->GetDevice();
		//���_�V�F�[�_�̐���
		hr = device->CreatePixelShader(
			p_vsCode->GetBufferPointer(),       //�R���p�C�����ꂽ�V�F�[�_�ւ̃|�C���^
			p_vsCode->GetBufferSize(),          //�R���p�C�����ꂽ���_�V�F�[�_�[�̃T�C�Y
			NULL,                               //�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
			&this->p_pixelShader				//�쐬���ꂽID3D11VertexShader�C���^�[�t�F�C�X�ւ̃|�C���^�[�̃A�h���X
		);
		if (FAILED(hr))
		{
			this->Release();
		}
		return  hr;
	}
	return  S_OK;
}

/**	@brief 	���_�s�N�Z���V�F�[�_�[�̃Z�b�g
*	@param	ID3D11ClassInstance* const* pp_classInstances	�N���X�C���X�^���X�z��̃|�C���^
*	@param	UINT	numClassInstances	�N���X�C���X�^���X�z��̐�
*	@date	2024/04/24
*/
void	CPixelShader::SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances)
{
	//���݂��Ă��Ȃ���΃G���[
	if (!this->p_pixelShader)
	{
		// �V�F�[�_�̃G���[���e��\��
		MessageBox(NULL, L"�s�N�Z���V�F�[�_�[������܂���", L"Shader Error", MB_OK);
		return;
	}
	//CD3D11�N���X�̎擾
	if (!this->cd3d11)
	{
		this->cd3d11 = CD3D11::GetInstance();
	}
	if (this->cd3d11)
	{
		ID3D11DeviceContext* context = cd3d11->GetDeviceContext();						//	�f�o�C�X�R���e�L�X�g�̎擾		
		context->PSSetShader(this->p_pixelShader, pp_classInstances, numClassInstances);//	���_�V�F�[�_���Z�b�g
	}
}

/**	@brief 	���_�s�N�Z���V�F�[�_�[�̉��
*	@date	2024/04/24
*/
void	CPixelShader::Release(void)
{
	this->CShader::Release();			// �s�N�Z���V�F�[�_�[�t�@�C���̉��
	SAFE_RELEASE(this->p_pixelShader);	// �s�N�Z���V�F�[�_�[�̉��
}