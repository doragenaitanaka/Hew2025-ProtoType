/**	@file 	CSampler.h
*	@brief 	�T���v���[�N���X
*	@date	2024/05/30
*/
#pragma once
#include"../01_Initialize/CD3D11.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CSampler
{
public:
	CSampler();
	~CSampler();
	/**	@brief 	�T���v���[�̍쐬
	*	@param	D3D11_FILTER filter
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressU
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressV
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressW
	*	@return HRESULT
	*	@date 2024/05/30
	*/
	HRESULT	Create(D3D11_FILTER filter,
		D3D11_TEXTURE_ADDRESS_MODE	addressU,
		D3D11_TEXTURE_ADDRESS_MODE	addressV,
		D3D11_TEXTURE_ADDRESS_MODE	addressW);
	/**	@brief 	�T���v���[�𒸓_�V�F�[�_�ɓn��
	*	@param	UINT StartSlot		�T���v���[�̃C���f�b�N�X(�f�o�C�X�̔z��̂ǂ��ɒu���̂�)�w��
	*	@param	UINT NumSamplers	�z����Ŏg���T���v���[��(�f�o�C�X�̔z��łǂ̂��炢�̑傫���Ȃ̂�)
	*	@date 2024/05/30
	*/
	void	SetSamplerVS(UINT StartSlot, UINT NumSamplers);
	/**	@brief 	�T���v���[���s�N�Z���V�F�[�_�ɓn��
	*	@param	UINT StartSlot		�T���v���[�̃C���f�b�N�X(�f�o�C�X�̔z��̂ǂ��ɒu���̂�)�w��
	*	@param	UINT NumSamplers	�z����Ŏg���T���v���[��(�f�o�C�X�̔z��łǂ̂��炢�̑傫���Ȃ̂�)
	*	@date 2024/05/30
	*/
	void	SetSamplerPS(UINT StartSlot, UINT NumSamplers);
	/**	@brief 	�������̉������
	*	@date 2024/05/30
	*/
	void	Release(void);
private:
	ID3D11SamplerState* p_samplerState;	// �T���v���[���
};