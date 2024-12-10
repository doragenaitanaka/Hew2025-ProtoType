#pragma once
#include<DirectXMath.h> //  DirectX::XMFLOAT3�ɕK�v

// �l�p�`
class Collider2D
{
public:
	Collider2D();
	Collider2D(DirectX::XMFLOAT3& _pos, DirectX::XMFLOAT3& _size);
	~Collider2D();

	// �Q�b�^�[�Z�b�^�[
	void SetPos(DirectX::XMFLOAT3& _pos);	
	void SetSize(DirectX::XMFLOAT3& _size);
	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);

	// �����蔻��
	static bool OnCollisionSquare(Collider2D& _passive, Collider2D& _collision);

private:
	DirectX::XMFLOAT3 pos;	// ���W
	DirectX::XMFLOAT3 size;	// �����蔻��̑傫��
};