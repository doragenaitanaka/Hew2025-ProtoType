#include"CVertexBuffer.h"
#include"../../01_Initialize/CD3D11.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/04/29
*/
CVertexBuffer::CVertexBuffer()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/04/29
*/
CVertexBuffer::~CVertexBuffer()
{
	this->Release();
}

/**	@brief 	�o�b�t�@�̍쐬
*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
*	@param	UINT	byteWidth			//���_�o�b�t�@�̃T�C�Y
*	@param	UINT	nothing = NULL		//���_�o�b�t�@�̍쐬�ł͎g��Ȃ�
*	@return	HRESULT
*	@date	2024/05/23
*	@memo
*/
HRESULT	CVertexBuffer::Create(const void* p_SysMem, UINT byteWidth, UINT nothing)
{
	// ���_�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//  �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
	vbDesc.Usage = D3D11_USAGE_DEFAULT;				//  �쐬����o�b�t�@�̎g�p�@
	vbDesc.ByteWidth = byteWidth;				    //  �쐬����o�b�t�@�̃o�C�g�T�C�Y
	vbDesc.MiscFlags = 0;							//  ���̑��̃t���O
	vbDesc.StructureByteStride = 0;					//  �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
	vbDesc.CPUAccessFlags = 0;

	//���_�o�b�t�@���Ȃ����
	if (!this->p_buffer)
	{
		//�������ރf�[�^
		D3D11_SUBRESOURCE_DATA initData = { p_SysMem, 0, 0 };	//1D���\�[�X�̏���������2,3�ڂ̂�g��Ȃ��i0�������j
		//�f�o�C�X�̎擾
		ID3D11Device* device = this->cd3d11->GetDevice();
		// ���_�o�b�t�@�̍쐬
		HRESULT	hr;
		hr = device->CreateBuffer(&vbDesc, &initData, &this->p_buffer);
		if (FAILED(hr))
		{
			//�������̉��
			if (this->p_buffer)
			{
				this->Release();
			}
		}
		return  hr;
	}
	return  S_OK;
}

/**	@brief 	���̓A�Z���u���X�e�[�W�ɕR�Â���
*	@param	UINT	StartSlot	���_�o�b�t�@�̐擪�X���b�g�ԍ�
*	@param	UINT	NumBuffers	�g�p���钸�_�o�b�t�@�̑���
*	@param	const	UINT*	p_stride	�e���_�o�b�t�@�̃X�g���C�h�̔z��|�C���^
*	@param	const	UINT*	p_offset	�o�b�t�@�̊J�n�ʒu����ǂݍ��ݎn�߂�܂ł̃o�C�g���̃|�C���^
*	@return	void
*	@date	2024/04/29
*/
void	CVertexBuffer::SetVertexBuffer(UINT	StartSlot, UINT	NumBuffers, const UINT* p_stride, const	UINT* p_offset)
{
	//���_�o�b�t�@����Ƃ�
	if (this->p_buffer)
	{
		if (this->cd3d11)
		{
			ID3D11DeviceContext* context = cd3d11->GetDeviceContext();									//	�f�o�C�X�R���e�L�X�g�̎擾		
			context->IASetVertexBuffers(StartSlot, NumBuffers, &this->p_buffer, p_stride, p_offset);	//	���̓A�Z���u���X�e�[�W�ɕR�Â�
		}
	}
}