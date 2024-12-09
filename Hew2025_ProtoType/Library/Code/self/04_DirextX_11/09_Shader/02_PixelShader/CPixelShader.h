#pragma once
#include"../00_CShader/CShader.h"
//D3D�ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CPixelShader	:public	CShader
{
public:
	//�R���X�g���N�^
	CPixelShader();
	//�f�X�g���N�^
	~CPixelShader();

	/**	@brief 	�s�N�Z���V�F�[�_�[�̍쐬
	*	@param	ID3D11ClassLinkage* p_classLinkage	�N���X�����P�[�W�C���^�[�t�F�C�X�ւ̃|�C���^�[
	*	@return	HRESULT
	*	@date	2024/04/24
	*/
	HRESULT	Create(ID3D11ClassLinkage* p_classLinkage);

	/**	@brief 	���_�s�N�Z���V�F�[�_�[�̃Z�b�g
	*	@param	ID3D11ClassInstance* const* pp_classInstances	�N���X�C���X�^���X�z��̃|�C���^
	*	@param	UINT	numClassInstances	�N���X�C���X�^���X�z��̐�
	*	@date	2024/04/24
	*/
	void	SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances);


	/**	@brief 	���_�s�N�Z���V�F�[�_�[�̉��
	*	@date	2024/04/24
	*/
	void	Release(void);

private:
	ID3D11PixelShader* p_pixelShader;	//�s�N�Z���V�F�[�_�[
};