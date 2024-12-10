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
	//当たり判定の大きさ
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

// 当たり判定
bool Collider2D::OnCollisionSquare(Collider2D& _passive, Collider2D& _collision) 
{
	DirectX::XMFLOAT3	collDetection = {};	//passiveとcollision間の当たり判定距離を入れる
	DirectX::XMFLOAT3 distance = {};		//passiveとcollision間の距離を入れる

	// passiveとcollision間の距離（中心点から中心点まで）をx,y,zそれぞれ求める
  	distance.x = fabsf(_passive.pos.x - _collision.pos.x);		//x
	distance.y = fabsf(_passive.pos.y - _collision.pos.y);		//y
	distance.z = fabsf(_passive.pos.z - _collision.pos.z);		//z

	// passiveとcollisionの当たり判定距離をx,yそれぞれ求める
	collDetection.x = _passive.size.x + _collision.size.x;	//x
	collDetection.y = _passive.size.y + _collision.size.y;	//y
	collDetection.z = _passive.size.z + _collision.size.z;	//z

	// 中心点から中心点までの距離がそれぞれ当たり判定距離より小さかったら
	// 当たっている
	if (collDetection.x >= distance.x && collDetection.y >= distance.y && collDetection.z >= distance.z)
	{
		return true;
	}
	else { return false; }
}