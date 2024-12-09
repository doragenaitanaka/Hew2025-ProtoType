#include"CBuffer.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/29
*/
CBuffer::CBuffer()
{
	this->cd3d11 = CD3D11::GetInstance();
	this->p_buffer = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/29
*/
CBuffer::~CBuffer()
{
	this->Release();
}
/**	@brief 	�������
*	@date	2024/04/29
*/
void	CBuffer::Release(void)
{
	//�쐬�ς̂Ƃ�
	if (this->p_buffer)
	{
		this->p_buffer->Release();
		this->p_buffer = nullptr;
	}
	this->cd3d11 = nullptr;
}

/**	@brief 	�o�b�t�@���̃|�C���^��Ԃ�
*	@return	ID3D11Buffer**
*	@date	2024/04/29
*/
ID3D11Buffer** CBuffer::GetBuffer(void)
{
	return	&this->p_buffer;
}