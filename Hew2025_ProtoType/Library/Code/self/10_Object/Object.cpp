/**	@brief 	���_�o�b�t�@�̍쐬�֐�
*	@date	2024/05/23
*	@memo	extern �� Direxc3D.h����f�o�C�X�A�f�o�C�X�R���e�L�X�g���Q�Ƃ��Ă���
*/

#include"Object.h"
#include"../../other/01_WICTextureLoader/WICTextureLoader.h"
#include"../../self/04_DirextX_11/01_Initialize/CD3D11.h"
#include"../../self/SafePointers.h"

#include".././03_Windows/WindowSetup.h"	// �X�N���[���̑傫���Ⴄ�@(�����ɃT�C�Y�u���ׂ��łȂ��̂���)

Object::Object()
{
	this->pos = { 0.0f,0.0f,0.0f };
	this->angle = 0.0f;

	this->size = { 100.0f,100.0f,0.0f };
	this->color = { 1.0f,1.0f,1.0f,1.0f };

	this->p_coll = nullptr;

	this->splitX = 1;
	this->splitY = 1;

	this->numU = 0.0f;
	this->numV = 0.0f;

	this->frameCount = 0;
	this->changeFrame = 0;
	this->moveUPos = 0.0f;

	this->isSwitched = false;

	this->p_constantBuffer = nullptr;
	this->p_vertexBuffer = nullptr;
	this->p_textureView = nullptr;
}

Object::~Object()
{
	this->UnInit();
}
/**	@brief 	�I�u�W�F�N�g�̏�����
*	@param	const wchar_t* _p_fileName �t�@�C���p�X
*	@param	int	_splitX = 1		�^�e�ɉ���������̂�
*	@param	int	_splitY = 1		���R�ɉ���������̂�
*	@param	int	_changeFrame = 1	���t���[���Ő؂�ւ��邩
*	@param	float	_moveUPos = 0.0f	�؂�ւ�邲�Ƃɓ����e�N�X�`��U���W�̈ړ���
*	@return	HRESULT
*	@date	2024/06/06
*/
HRESULT	Object::Init(const wchar_t* _p_fileName, int	_splitX, int	_splitY, int	_changeFrame , float	_moveUPos)
{
	// �I�u�W�F�N�g�̍��W�Ɉʒu�����킹��
	this->p_coll = new Collider2D(this->pos, this->size);

	// �������ɉ�����UV���W�����߂�
	this->splitX = _splitX;
	this->splitY = _splitY;

	// �f���e�N�X�`���͈̔͂����߂�
	this->vertexList[1].u = 1.0f / this->splitX;
	this->vertexList[2].v = 1.0f / this->splitY;
	this->vertexList[3].u = 1.0f / this->splitX;
	this->vertexList[3].v = 1.0f / this->splitY;

	// �A�j���[�V�����̐؂�ւ����x�ƈړ��ʂ�ݒ�
	this->changeFrame = _changeFrame;
	this->moveUPos = _moveUPos;

	HRESULT hr;
	// �萔�o�b�t�@�̍쐬
	if (!this->p_constantBuffer)
	{
		this->p_constantBuffer = new	CConstantBuffer;
		hr = this->p_constantBuffer->Create(NULL, sizeof(ConstBuffer));
	}

	// ���_�o�b�t�@�̍쐬
	if (!this->p_vertexBuffer)
	{
		this->p_vertexBuffer = new  CVertexBuffer;
		hr = this->p_vertexBuffer->Create(this->vertexList, sizeof(this->vertexList) * 4);
	}

	// �e�N�X�`���ǂݍ���
	if (!this->p_textureView)
	{
		this->p_textureView = this->LoadTexture(_p_fileName);
	}
	return	hr;
}

/**	@brief 	�I�u�W�F�N�g�̍X�V
*	@date	2024/06/12
*/
void	Object::Update(void)
{
	// ����͓����蔻��͂����ƃI�u�W�F�N�g�Ɠ������W
	this->p_coll->SetPos(this->pos);

	// �A�j���[�V�����̍X�V
	//this->AnimUpdate();

	// �萔�o�b�t�@�̍X�V
	this->ConstantBufferUpdate();
}

/**	@brief 	�A�j���[�V�����̍X�V
*	@date	2024/06/12
*/
void	Object::AnimUpdate(void)
{
	// �A�j���[�V�����̍X�V
	this->frameCount = (this->frameCount + 1) % this->changeFrame;
	// �؂�ւ���t���[����������
	if (this->frameCount == 0)
	{
		if (!this->isSwitched)
		{
			// U���W���ړ�
			this->numU += this->moveUPos;

			// �Ō�܂œ��������猳�ɖ߂�
			if (this->numU >= this->splitX)
			{
				this->isSwitched = true;
				this->numU = this->splitX - 1.0f;
			}
		}
		if (this->isSwitched)
		{
			// U���W���ړ�  
			this->numU -= this->moveUPos;

			// �Ō�܂œ��������猳�ɖ߂�
			if (this->numU <= 0)
			{
				this->isSwitched = false;
				this->numU = 0.0f;
			}
		}
	}
}

/**	@brief	�萔�o�b�t�@�̍X�V
*	@date	2024/06/12
*/
void	Object::ConstantBufferUpdate(void)
{
	// �萔�o�b�t�@���X�V
	ConstBuffer	cb;
	// �v���W�F�N�V�����ϊ����W�̍쐬
	// ��ʂ̑傫������X�N���[���Ɠ����ɂ���
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	// ���I�u�W�F�N�g�̈ʒu�A�傫���A�������w��
	cb.matrixWorld = DirectX::XMMatrixScaling(this->size.x, this->size.y, this->size.z);	// �傫��
	float   radianAngle = DirectX::XMConvertToRadians(this->angle);							// ���W�A���ɕϊ�
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(radianAngle);								// �������w��
	cb.matrixWorld *= DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬
	float	u = (float)this->numU / this->splitX;
	float	v = (float)this->numV / this->splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	// ���_�J���[�s��̍쐬
	cb.color = this->color;

	// �萔�o�b�t�@�̍X�V
	this->p_constantBuffer->Update(&cb);
}

/**	@brief 	�`��֐�
*	@param	UINT strides
*	@date	2024/05/23
*/
void	Object::Draw()
{
	UINT offsets = 0;
	UINT strides = sizeof(Vertex);
	this->p_vertexBuffer->SetVertexBuffer(0, 1, &strides, &offsets);	// ���_�o�b�t�@��IA�ɓn��

	//�f�o�C�X�R���e�L�X�g�̎擾
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11DeviceContext* p_deviceContext = cd3d11->GetDeviceContext();
	p_deviceContext->PSSetShaderResources(0, 1, &this->p_textureView);	// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��

	// �V�F�[�_�ɓn��
	this->p_constantBuffer->SetConstantBuffer();

	p_deviceContext->Draw(4, 0); // �`�施��
}
void	Object::UnInit(void)
{
	if (this->p_coll) {
		delete this->p_coll;
		this->p_coll = nullptr;
	}

	SAFE_RELEASE(this->p_vertexBuffer);
	SAFE_RELEASE(this->p_textureView);
	SAFE_RELEASE(this->p_constantBuffer);
}

/**	@brief 	���W��ݒ�
*	@param	float x
*	@param	float y
*	@param	float z
*	@date	2024/05/30
*/
void	Object::SetPos(float x, float y, float z)
{
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;

	// ����͓����蔻��͂����ƃI�u�W�F�N�g�Ɠ������W
	this->p_coll->SetPos(this->pos);

	// �萔�o�b�t�@�̍X�V
	this->ConstantBufferUpdate();
}
/**	@brief 	���W��ݒ�
*	@retuen		DirectX::XMFLOAT3
*	@date	2024/09/19
*/
DirectX::XMFLOAT3	Object::GetPos(void)
{
	return this->pos;
}

/**	@brief 	�T�C�Y��ݒ�
*	@retuen		DirectX::XMFLOAT3
*	@date	2024/09/19
*/
DirectX::XMFLOAT3	Object::GetSize(void)
{
	return this->size;
}

/**	@brief 	�R���C�_�[�̎擾
*	@return	Collider2D&		�R���C�_�[2D
*	@date	2024/06/12
*/
Collider2D& Object::GetCollider2D(void)
{
	return *this->p_coll;
}

/**	@brief 	�傫����ݒ�
*	@param	float x
*	@param	float y
*	@param	float z
*	@date	2024/05/30
*/
void	Object::SetSize(float x, float y, float z)
{
	this->size.x = x;
	this->size.y = y;
	this->size.z = z;

	// �����蔻����X�V
	this->p_coll->SetSize(this->size);
}

/**	@brief 	�p�x��ݒ�
*	@param	float angle
*	@date	2024/05/30
*/
void	Object::SetAngle(float angle)
{
	this->angle = angle;
}

/**	@brief 	�e�N�X�`�����Z�b�g
*	@param	ID3D11ShaderResourceView* _p_texture	�e�N�X�`��
*	@date	2024/09/17
*/
void	Object::SetTexture(ID3D11ShaderResourceView* _p_texture)
{
	this->p_textureView = _p_texture;
}

/**	@brief 	�f���e�N�X�`���̃��R�̏ꏊ��ݒ�
*	@param	int	numU
*	@date	2024/06/06
*/
void	Object::SetTextureNumU(float	numU)
{
	this->numU = numU;
}

/**	@brief 	�f���e�N�X�`���̃^�e�̏ꏊ��ݒ�
*	@param	int	numV
*	@date	2024/06/06
*/
void	Object::SetTextureNumV(float	numV)
{
	this->numV = numV;
}

/**	@brief 	�f���e�N�X�`���̃��R��U���W���擾
*	@return	int	numU
*	@date	2024/06/07
*/
float	Object::GetTextureNumU(void)
{
	return	this->numU;
}

/**	@brief 	�f���e�N�X�`���̃^�e��V���W���擾
*	@return	int	numV
*	@date	2024/06/07
*/
float	Object::GetTextureNumV(void)
{
	return	this->numV;
}

/**	@brief 	�f���e�N�X�`���̒��_���W��ݒ�
*	@param	DirectX::XMFLOAT4	_color	���_�J���[
*	@date	2024/06/12
*/
void	Object::SetColor(DirectX::XMFLOAT4	_color)
{
	this->color = _color;
}

/**	@brief 	�f���e�N�X�`���̓����x��ݒ�
*	@param	float	_color	�����x�i�A���t�@�l�j
*	@date	2024/06/12
*/
void	Object::SetAlpha(float	_color)
{
	this->color.w = _color;
}

/**	@brief 	�e�N�X�`���̓ǂݍ��݊֐�
*	@param	const wchar_t* fileName �t�@�C���p�X
*	@return	ID3D11ShaderResourceView*	�e�N�X�`��
*	@date	2024/09/17
*/
ID3D11ShaderResourceView* Object::LoadTexture(const wchar_t* fileName)
{
	HRESULT hr;
	ID3D11ShaderResourceView* p_texture = nullptr;
	//�f�o�C�X�̎擾
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11Device* p_device = cd3d11->GetDevice();
	//�e�N�X�`���ǂݍ���
	hr = CreateWICTextureFromFile(p_device, fileName, NULL, &p_texture);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "error", MB_ICONERROR | MB_OK);
		return nullptr;
	}
	return p_texture;
}