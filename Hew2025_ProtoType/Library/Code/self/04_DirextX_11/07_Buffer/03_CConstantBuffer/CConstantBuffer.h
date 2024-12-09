#pragma once
#include"../00_CBuffer/CBuffer.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include<DirectXMath.h> //  DirectX::XMFLOAT3�ɕK�v
using   namespace DirectX;

class CConstantBuffer :public	CBuffer
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/05/24
	*/
	CConstantBuffer();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/05/24
	*/
	~CConstantBuffer();

	/**	@brief 	�o�b�t�@�̍쐬
	*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
	*	@param	UINT	byteWidth			//�R���X�^���g�o�b�t�@�̃T�C�Y
	*	@param	UINT	nothing = NULL		//�R���X�^���g�o�b�t�@�̍쐬�ł͎g��Ȃ�
	*	@return	HRESULT
	*	@date	2024/05/24
	*/
	HRESULT	Create(const void* p_SysMem, UINT	byteWidth, UINT	nothing = NULL)override;

	/**	@brief 	�o�b�t�@�̍X�V
	*	@param	_In_  const void* pSrcData ���f�f�[�^
	*	@date	2024/05/24
	*/
	void	Update(_In_  const void* pSrcData);

	/**	@brief	�g�p����R���X�^���g�o�b�t�@��ݒ�
	*	@date	2024/05/24
	*/
	void	SetConstantBuffer(void);
};