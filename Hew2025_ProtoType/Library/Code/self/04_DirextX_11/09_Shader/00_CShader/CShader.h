#pragma once
#include <d3dcompiler.h>				// �V�F�[�_�R���p�C������̋@�\���C���N���[�h
#pragma comment(lib, "d3dcompiler.lib")	// �V�F�[�_�R���p�C���p�̐ÓI���C�u�����������N
//D3D�ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../../01_Initialize/CD3D11.h"

//�V�F�[�_�t�@�C���̃I�����C���R���p�C��������݌v
//�I�t���C���ł��ł���悤�ɂ��悤�Ǝv������t�@�C���ǂݍ��񂾂̂�����ׂ�SetCompileFile�֐��I�Ȃ́c�H

class CShader
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/04/24
	*/
	CShader();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/04/24
	*/
	~CShader();

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
	HRESULT	CompileFromFile(
		LPCWSTR	fileName,				
		D3D_SHADER_MACRO* p_defines,
		ID3DInclude* p_nclude,
		LPCSTR	p_entrypoint,
		LPCSTR	p_target,
		UINT	flags_1,
		UINT	flags_2
	);
	/**	@brief 	�V�F�[�_�[�t�@�C���̎擾
	*	@return	ID3DBlob*	�V�F�[�_�[�t�@�C��
	*	@date	2024/04/24
	*/
	ID3DBlob* GetShaderFile(void);

	/**	@brief 	�������
	*	@date	2024/04/24
	*/
	virtual	void	Release(void);
	/**	@brief 	�V�F�[�_�[�̍쐬
	*	@param	ID3D11ClassLinkage* p_classLinkage	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
	*	@return	HRESULT
	*	@date	2024/04/24
	*/
	virtual	HRESULT	Create(ID3D11ClassLinkage* p_classLinkage) = 0;
	/**	@brief 	�V�F�[�_�[�̃Z�b�g
	*	@param	ID3D11ClassInstance* const* pp_classInstances	�N���X�C���X�^���X�z��̃|�C���^
	*	@param	UINT	numClassInstances	�N���X�C���X�^���X�z��̐�
	*	@date	2024/04/24
	*/
	virtual	void	SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances) = 0;
private:
	ID3DBlob* p_blob;	//�V�F�[�_�[�t�@�C��
protected:
	CD3D11* cd3d11;         //CD3D11�N���X
};