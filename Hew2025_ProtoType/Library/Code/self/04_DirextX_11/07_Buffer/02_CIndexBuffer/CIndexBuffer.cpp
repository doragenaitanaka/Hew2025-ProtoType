#include"CIndexBuffer.h"
#include"../../01_Initialize/CD3D11.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

//�R���X�g���N�^
CIndexBuffer::CIndexBuffer()
{
}
//�f�X�g���N�^
CIndexBuffer::~CIndexBuffer()
{
	this->Release();
}
/**	@brief 	�o�b�t�@�̍쐬
*	@param	const void*	p_SysMem		�������f�[�^�ւ̃|�C���^�[
*	@param	UINT	byteWidth			�쐬����C���f�b�N�X�o�b�t�@�̃o�C�g�T�C�Y
*	@param	UINT	nothing = NULL		���_�C���f�b�N�X�o�b�t�@�̍쐬�ł͎g��Ȃ�
*	@return	HRESULT
*	@date	2024/05/23
*	@memo
*/
HRESULT	CIndexBuffer::Create(const void* p_SysMem, UINT byteWidth, UINT nothing)
{
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;	    //  �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
	ibDesc.Usage = D3D11_USAGE_DEFAULT;				//  �쐬����o�b�t�@�̎g�p�@
	ibDesc.ByteWidth = byteWidth;					//  �쐬����o�b�t�@�̃o�C�g�T�C�Y
	ibDesc.MiscFlags = 0;							//  ���̑��̃t���O
	ibDesc.StructureByteStride = 0;		            //  �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
	ibDesc.CPUAccessFlags = 0;


	//�C���f�b�N�X�o�b�t�@���������
	if (!this->p_buffer)
	{
		//CD3D11�N���X�̎擾
		if (!this->cd3d11)
		{
			this->cd3d11 = CD3D11::GetInstance();
		}
		//�������ރf�[�^
		D3D11_SUBRESOURCE_DATA initData = { p_SysMem, 0, 0 };	//	1D���\�[�X�̏���������2,3�ڂ̂�g��Ȃ��i0�������j
		HRESULT	hr;
		ID3D11Device* device = this->cd3d11->GetDevice();				//	�f�o�C�X�̎擾
		hr = device->CreateBuffer(&ibDesc, &initData, &this->p_buffer);	// �C���f�b�N�X�o�b�t�@�̍쐬
		if (FAILED(hr))
		{
			//�������̉��
			if (this->p_buffer)
			{
				this->Release();
			}
		}
		return	hr;
	}
	return	S_OK;
}

/**	@brief 	���̓A�Z���u���X�e�[�W�ɕR�Â���
*	@param	DXGI_FORMAT	format	�C���f�b�N�X�̌`��
*	@param	UINT	ofset	�o�C�g�P�ʃI�t�Z�b�g
*	@return	void
*	@date	2024/04/29
*	@memo
*/
void	CIndexBuffer::SetIndexBuffer(DXGI_FORMAT	format, UINT	ofset)
{
	//�o�b�t�@���|�C���^�̃A�h���X���擾
	ID3D11Buffer** p_indexBuffer = this->GetBuffer();
	//�C���f�b�N�X�o�b�t�@������Ƃ�
	if (this->p_buffer)
	{
		ID3D11DeviceContext* deviceContext = this->cd3d11->GetDeviceContext();	//�f�o�C�X�R���e�L�X�g���擾
		deviceContext->IASetIndexBuffer(this->p_buffer, format, ofset);			//���̓A�Z���u���X�e�[�W�ɕR�Â�
	}
}