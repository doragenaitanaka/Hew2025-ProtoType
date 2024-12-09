#pragma once
#include"../00_CBuffer/CBuffer.h"

#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CVertexBuffer	:public	CBuffer
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/04/29
	*/
	CVertexBuffer();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/04/29
	*/
	~CVertexBuffer();

	/**	@brief 	�o�b�t�@�̍쐬
	*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
	*	@param	UINT	byteWidth			�쐬���钸�_�o�b�t�@�̃T�C�Y
	*	@param	UINT	nothing = NULL		���_�o�b�t�@�̍쐬�ł͎g��Ȃ�
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo	
	*/
	HRESULT	Create(const void* p_SysMem, UINT byteWidth, UINT nothing = NULL)override;

	/**	@brief 	���̓A�Z���u���X�e�[�W�ɕR�Â���
	*	@param	UINT	StartSlot	���_�o�b�t�@�̐擪�X���b�g�ԍ�
	*	@param	UINT	NumBuffers	�g�p���钸�_�o�b�t�@�̑���
	*	@param	const	UINT*	p_stride	�e���_�o�b�t�@�̃X�g���C�h�̔z��|�C���^
	*	@param	const	UINT*	p_offset	�o�b�t�@�̊J�n�ʒu����ǂݍ��ݎn�߂�܂ł̃o�C�g���̃|�C���^
	*	@return	void
	*	@date	2024/04/22
	*	@memo
	*/
	void	SetVertexBuffer(UINT	StartSlot, UINT	NumBuffers, const UINT* p_stride, const	UINT* p_offset);
};
