#pragma once
//D3D�ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../../01_Initialize/CD3D11.h"

class CBuffer
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date	2024/04/29
	*/
	CBuffer();
	/**	@brief 	�f�X�g���N�^
	*	@date	2024/04/29
	*/
	~CBuffer();

	/**	@brief 	�o�b�t�@�̍쐬
	*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
	*	@param	UINT
	*	@param	UINT
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo	�������A��O�����͌p����ɂ���Ė������ς��̂ŕϐ������߂Ȃ��ł���
	*/
	virtual	HRESULT	Create(const void* p_SysMem, UINT, UINT, D3D11_USAGE _usage = D3D11_USAGE_DEFAULT, UINT _cpuAccessFlags = 0) = 0;

	/**	@brief 	�o�b�t�@���̃|�C���^�A�h���X��Ԃ�
	*	@return	ID3D11Buffer**
	*	@date	2024/04/29
	*/
	ID3D11Buffer** GetBuffer(void);

	/**	@brief 	�������
	*	@date	2024/04/29
	*/
	void	Release(void);

protected:
	ID3D11Buffer* p_buffer;	//�o�b�t�@
	CD3D11* cd3d11;         //CD3D11�N���X
};