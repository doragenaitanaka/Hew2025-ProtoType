#include"CShader.h"
#include"../../../SafePointers.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/24
*/
CShader::CShader()
{
	this->p_blob = nullptr;
	this->cd3d11 = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/24
*/
CShader::~CShader()
{
	this->Release();
}

/**	@brief 	�V�F�[�_�[�t�@�C���̃R���p�C��
*	@param	LPCWSTR	fileName				�t�@�C���̖��O
*	@param	D3D_SHADER_MACRO* p_defines		�V�F�[�_�[�}�N�����`����D3D_SHADER_MACRO�\���̂̔z��ւ̃I�v�V���i���ȃ|�C���^�[
*	@param	ID3DInclude* p_nclude			�R���p�C�����C���N���[�h�t�@�C���̏����Ɏg�p����|�C���^�[
*	@param	LPCSTR	p_entrypoint			�V�F�[�_�[�̎��s���J�n�����V�F�[�_�[�G���g���|�C���g��
*	@param	LPCSTR	p_target				�R���p�C���Ώۂ̃V�F�[�_�[�^�[�Q�b�g�܂��̓V�F�[�_�[�@�\�̃Z�b�g���w��
* 	@param	UINT	flags_1					�V�F�[�_�[�R���p�C���I�v�V�����̑g�ݍ��킹
* 	@param	UINT	flags_2					���ʃR���p�C���I�v�V�����̑g�ݍ��킹
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CShader::CompileFromFile(
    LPCWSTR	fileName,
    D3D_SHADER_MACRO* p_defines,
    ID3DInclude* p_nclude,
    LPCSTR	p_entrypoint,
    LPCSTR	p_target,
    UINT	flags_1,
    UINT	flags_2
)
{
	if (!this->p_blob)
	{
		HRESULT hr;
		ID3DBlob* p_errorMsg;
		//�R���p�C��
		hr = D3DCompileFromFile(
			fileName,                   //�t�@�C���̖��O
			p_defines,                  //�V�F�[�_�[�}�N�����`����D3D_SHADER_MACRO�\���̂̔z��ւ̃I�v�V���i���ȃ|�C���^�[
			p_nclude,                   //�R���p�C�����C���N���[�h�t�@�C���̏����Ɏg�p����|�C���^�[
			p_entrypoint,               //�V�F�[�_�[�̎��s���J�n�����V�F�[�_�[�G���g���|�C���g��
			p_target,                   //�R���p�C���Ώۂ̃V�F�[�_�[�^�[�Q�b�g�܂��̓V�F�[�_�[�@�\�̃Z�b�g���w��
			flags_1,                    //�V�F�[�_�[�R���p�C���I�v�V�����̑g�ݍ��킹
			flags_2,                    //���ʃR���p�C���I�v�V�����̑g�ݍ��킹
			&this->p_blob,              //�R���p�C���ς݃R�[�h�ւ̃A�N�Z�X�Ɏg�p�ł���|�C���^�[�A�h���X
			&p_errorMsg                 //�R���p�C���G���[���b�Z�[�W�ւ̃A�N�Z�X�Ɏg�p
		);
		if (FAILED(hr))
		{
			// �V�F�[�_�̃G���[���e��\��
			MessageBox(NULL, (wchar_t*)p_errorMsg->GetBufferPointer(), L"Compile Error", MB_OK);
			//�������̉��
			SAFE_RELEASE(this->p_blob);
			SAFE_RELEASE(p_errorMsg);
		}
		return  hr;
	}
	return  S_OK;
}

/**	@brief 	�V�F�[�_�[�t�@�C���̎擾
*	@return	ID3DBlob*	�V�F�[�_�[�t�@�C��
*	@date	2024/04/24
*/
ID3DBlob* CShader::GetShaderFile(void)
{
	return	this->p_blob;
}

/**	@brief 	�������
*	@date	2024/04/24
*/
void	CShader::Release(void)
{
	SAFE_RELEASE(this->p_blob);
}