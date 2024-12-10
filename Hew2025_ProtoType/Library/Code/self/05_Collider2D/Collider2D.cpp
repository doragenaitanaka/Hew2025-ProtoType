#include"Collider2D.h"

Collider2D::Collider2D():pos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)),size(DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f))
{}

Collider2D::Collider2D(DirectX::XMFLOAT3& _pos, DirectX::XMFLOAT3& _size) :pos(_pos)
{
	this->SetSize(_size);
}

Collider2D::~Collider2D()
{
}

void Collider2D::SetPos(DirectX::XMFLOAT3& _pos)
{
	this->pos = _pos;
}
void Collider2D::SetSize(DirectX::XMFLOAT3& _size)
{
	//�����蔻��̑傫��
	this->size.x = _size.x / 2.0f;
	this->size.y = _size.y / 2.0f;
	this->size.z = _size.z / 2.0f;
}
DirectX::XMFLOAT3 Collider2D::GetPos(void)
{
	return this->pos;
}
DirectX::XMFLOAT3 Collider2D::GetSize(void)
{
	return this->size;
}

// �����蔻��
bool Collider2D::OnCollisionSquare(Collider2D& _passive, Collider2D& _collision) 
{
	DirectX::XMFLOAT3	collDetection = {};	//passive��collision�Ԃ̓����蔻�苗��������
	DirectX::XMFLOAT3 distance = {};		//passive��collision�Ԃ̋���������

	// passive��collision�Ԃ̋����i���S�_���璆�S�_�܂Łj��x,y,z���ꂼ�ꋁ�߂�
  	distance.x = fabsf(_passive.pos.x - _collision.pos.x);		//x
	distance.y = fabsf(_passive.pos.y - _collision.pos.y);		//y
	distance.z = fabsf(_passive.pos.z - _collision.pos.z);		//z

	// passive��collision�̓����蔻�苗����x,y���ꂼ�ꋁ�߂�
	collDetection.x = _passive.size.x + _collision.size.x;	//x
	collDetection.y = _passive.size.y + _collision.size.y;	//y
	collDetection.z = _passive.size.z + _collision.size.z;	//z

	// ���S�_���璆�S�_�܂ł̋��������ꂼ�ꓖ���蔻�苗����菬����������
	// �������Ă���
	if (collDetection.x >= distance.x && collDetection.y >= distance.y && collDetection.z >= distance.z)
	{
		return true;
	}
	else { return false; }
}