#include"CConstantBuffer.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/24
*/
CConstantBuffer::CConstantBuffer()
{
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/24
*/
CConstantBuffer::~CConstantBuffer()
{
	this->Release();
}

/**	@brief 	�o�b�t�@�̍쐬
*	@param	const void*	p_SysMem		//�������f�[�^�ւ̃|�C���^�[(�����ł͎g��Ȃ��̂�NULL������)
*	@param	UINT	byteWidth			//�R���X�^���g�o�b�t�@�̃T�C�Y
*	@param	UINT	nothing = NULL		//�R���X�^���g�o�b�t�@�̍쐬�ł͎g��Ȃ�
*	@return	HRESULT
*	@date	2024/05/24
*/
HRESULT	CConstantBuffer::Create(const void* p_SysMem, UINT	byteWidth, UINT	nothing )
{
    //�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = byteWidth;
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    //�o�b�t�@�����擾
    ID3D11Buffer** p_vertexBuffer = this->GetBuffer();
    ID3D11Device* device = cd3d11->GetDevice();
	if (!this->p_buffer)
	{
		//�f�o�C�X�̎擾
		ID3D11Device* device = this->cd3d11->GetDevice();
		HRESULT	hr;
		//�R���X�^���g�o�b�t�@�̍쐬
		hr = device->CreateBuffer(&cbDesc, NULL, &p_buffer);
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

/**	@brief 	�o�b�t�@�̍X�V
*	@param	_In_  const void* pSrcData ���f�f�[�^
*	@date	2024/05/24
*/
void	CConstantBuffer::Update(_In_  const void* pSrcData)
{
	if (this->cd3d11)
	{
		ID3D11DeviceContext* context = this->cd3d11->GetDeviceContext();	// �R���e�L�X�g�擾
		context->UpdateSubresource(p_buffer, 0, NULL, pSrcData, 0, 0);			// �萔�o�b�t�@��GPU���ɓn��
	}
}

/**	@brief	�g�p����R���X�^���g�o�b�t�@��ݒ�
*	@date	2024/05/24
*/
void	CConstantBuffer::SetConstantBuffer(void)
{
	//�R���X�^���g�o�b�t�@������Ƃ�
	if (this->p_buffer)
	{
		if (this->cd3d11)
		{
			ID3D11DeviceContext* context = cd3d11->GetDeviceContext();	// �f�o�C�X�R���e�L�X�g�̎擾
			context->VSSetConstantBuffers(0, 1, &this->p_buffer);		// �R���X�^���g�o�b�t�@��ݒ�
		}
	}
}