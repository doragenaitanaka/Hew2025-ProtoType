#pragma once
#include"../00_CBuffer/CBuffer.h"

class CIndexBuffer	:protected	CBuffer
{
public:
	//�R���X�g���N�^
	CIndexBuffer();
	//�f�X�g���N�^
	~CIndexBuffer();

	/**	@brief 	�o�b�t�@�̍쐬
	*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
	*	@param	UINT	byteWidth			�쐬����C���f�b�N�X�o�b�t�@�̃T�C�Y
	*	@param	UINT	nothing = NULL		���_�C���f�b�N�X�o�b�t�@�̍쐬�ł͎g��Ȃ�
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo
	*/
	HRESULT	Create(const void* p_SysMem, UINT byteWidth, UINT nothing = NULL)override;

	/**	@brief 	���̓A�Z���u���X�e�[�W�ɕR�Â���
	*	@param	DXGI_FORMAT	format	�C���f�b�N�X�̌`��
	*	@param	UINT	ofset	�o�C�g�P�ʃI�t�Z�b�g
	*	@return	void
	*	@date	2024/04/29
	*	@memo
	*/
	void	SetIndexBuffer(DXGI_FORMAT	format, UINT	ofset);
};
