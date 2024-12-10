#pragma once
#include"../04_DirextX_11/07_Buffer/01_CVertexBuffer/CVertexBuffer.h"
#include"../04_DirextX_11/07_Buffer/03_CConstantBuffer/CConstantBuffer.h"
#include"../05_Collider2D/Collider2D.h"

#include<DirectXMath.h> //  DirectX::XMFLOAT3�ɕK�v

// �萔�o�b�t�@�̒��g
struct ConstBuffer
{
	DirectX::XMMATRIX   matrixWorld;	// ���[���h�ϊ��s��
	DirectX::XMMATRIX   matrixProj;		// �v���W�F�N�V�����ϊ��s�� 
	DirectX::XMMATRIX   matrixTex;		// UV���W�ړ��s�� 
	DirectX::XMFLOAT4	color;			// ���_�J���[�s��
};

// �\���̂̒�`
// ���_�f�[�^��\���\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;
	//�J���[�l
	float	r, g, b, a;
	//�e�N�X�`�����W(UV���W)
	float	u, v;
};

class Object
{
public:
	Object();
	virtual~Object();
	/**	@brief 	�I�u�W�F�N�g�̏�����
	*	@param	const wchar_t* _p_fileName �t�@�C���p�X
	*	@param	int	_splitX = 1		�^�e�ɉ���������̂�
	*	@param	int	_splitY = 1		���R�ɉ���������̂�
	*	@param	int	_changeFrame = 1	���t���[���Ő؂�ւ��邩
	*	@param	float	_moveUPos = 0.0f	�؂�ւ�邲�Ƃɓ����e�N�X�`��U���W�̈ړ���
	*	@return	HRESULT
	*	@date	2024/06/06
	*/
	virtual HRESULT	Init(const wchar_t* _p_fileName, int	_splitX = 1, int	_splitY = 1, int	_changeFrame = 1, float	_moveUPos = 0.0f);

	/**	@brief 	�I�u�W�F�N�g�̍X�V
	*	@date	2024/06/12
	*/
	virtual void	Update(void);

	/**	@brief 	�A�j���[�V�����̍X�V
	*	@date	2024/06/12
	*/
	void	AnimUpdate(void);

	/**	@brief	�萔�o�b�t�@�̍X�V
	*	@date	2024/06/12
	*/
	void	ConstantBufferUpdate(void);

	/**	@brief 	�`��֐�
	*	@date	2024/05/23
	*/
	virtual void	Draw();
	/**	@brief 	�I������
	*	@date  	2024/05/23
	*/
	virtual void	UnInit(void);

	/**	@brief 	���W��ݒ�
	*	@param	float x
	*	@param	float y
	*	@param	float z
	*	@date	2024/05/30
	*/
	void	SetPos(float x, float y, float z);

	/**	@brief 	���W���擾
	*	@retuen		DirectX::XMFLOAT3
	*	@date	2024/09/19
	*/
	DirectX::XMFLOAT3	GetPos(void);

	/**	@brief 	�T�C�Y���擾
	*	@retuen		DirectX::XMFLOAT3
	*	@date	2024/09/19
	*/
	DirectX::XMFLOAT3	GetSize(void);

	/**	@brief 	�傫����ݒ�
	*	@param	float x
	*	@param	float y
	*	@param	float z
	*	@date	2024/05/30
	*/
	void	SetSize(float x, float y, float z);

	/**	@brief 	�p�x��ݒ�
	*	@param	float angle
	*	@date	2024/05/30
	*/
	void	SetAngle(float angle);

	/**	@brief 	�f���e�N�X�`���̃��R��U���W��ݒ�
	*	@param	int	numU
	*	@date	2024/06/06
	*/
	void	SetTextureNumU(float	numU);

	/**	@brief 	�f���e�N�X�`���̃^�e��V���W��ݒ�
	*	@param	int	numV
	*	@date	2024/06/06
	*/
	void	SetTextureNumV(float	numV);

	/**	@brief 	�f���e�N�X�`���̃��R��U���W���擾
	*	@return	int	numU
	*	@date	2024/06/07
	*/
	float	GetTextureNumU(void);

	/**	@brief 	�f���e�N�X�`���̃^�e��V���W���擾
	*	@return	int	numV
	*	@date	2024/06/07
	*/
	float	GetTextureNumV(void);

	/**	@brief 	�R���C�_�[�̎擾
	*	@return	Collider2D&		�R���C�_�[2D
	*	@date	2024/06/12
	*/
	Collider2D&	GetCollider2D(void);

	/**	@brief 	�e�N�X�`�����Z�b�g
	*	@param	DirectX::XMFLOAT4	_color	���_�J���[
	*	@date	2024/06/12
	*/
	void	SetTexture(ID3D11ShaderResourceView* _p_texture);

	/**	@brief 	�f���e�N�X�`���̒��_���W��ݒ�
	*	@param	DirectX::XMFLOAT4	_color	���_�J���[
	*	@date	2024/06/12
	*/
	void	SetColor(DirectX::XMFLOAT4	_color);

	/**	@brief 	�f���e�N�X�`���̓����x��ݒ�
	*	@param	float	_color	�����x�i�A���t�@�l�j
	*	@date	2024/06/12
	*/
	void	SetAlpha(float	_color);

private:
	/**	@brief 	�e�N�X�`���̓ǂݍ��݊֐�
	*	@param	const wchar_t* fileName �t�@�C���p�X
	*	@return	ID3D11ShaderResourceView*	�e�N�X�`��
	*	@date	2024/09/17
	*/
	static ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);
protected:
	// �\���e�N�X�`���̒��_���W
	Vertex	vertexList[4]
	{
		{ -0.5f, 0.5f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.0f,0.0f},	// 0�Ԗڂ̒��_���W�@{ x, y, z }{ r, g, b, a}{ u, v}
		{ 0.5f, 0.5f, 0.5f,		1.0f,1.0f,1.0f,1.0f,	1.0f,0.0f},	// 1�Ԗڂ̒��_���W
		{ -0.5f, -0.5f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.0f,1.0f},	// 2�Ԗڂ̒��_���W
		{ 0.5f, -0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,1.0f},	// 1�Ԗڂ̒��_���W
	}; 
	DirectX::XMFLOAT3	pos;						// ���W
	float	angle;									// �p�x

	DirectX::XMFLOAT3	size;						// �傫��
	DirectX::XMFLOAT4	color;						// ���_�J���[

	Collider2D* p_coll;	// �����蔻��

	// �e�N�X�`��������������̂�
	int	splitX;
	int	splitY;
	// ���ォ�牽�i�ڂ�؂蔲���ĕ\������̂�
	float	numU;
	float	numV;

	int	frameCount;									// �A�j���[�V�����p�J�E���g�ϐ�
	int	changeFrame;								// �؂�ւ��t���[����
	float	moveUPos;								// U���W�̈ړ���

	bool	isSwitched;								// �A�j���[�V�������Ԑ؂�ւ��t���O

	CConstantBuffer* p_constantBuffer;				// �萔�o�b�t�@
	CVertexBuffer* p_vertexBuffer;					// ���_�o�b�t�@
	ID3D11ShaderResourceView* p_textureView;		// �e�N�X�`�����\�[�X
};