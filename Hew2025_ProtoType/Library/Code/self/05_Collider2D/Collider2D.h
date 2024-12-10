#pragma once
#include<DirectXMath.h> //  DirectX::XMFLOAT3に必要

// 四角形
class Collider2D
{
public:
	Collider2D();
	Collider2D(DirectX::XMFLOAT3& _pos, DirectX::XMFLOAT3& _size);
	~Collider2D();

	// ゲッターセッター
	void SetPos(DirectX::XMFLOAT3& _pos);	
	void SetSize(DirectX::XMFLOAT3& _size);
	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);

	// 当たり判定
	static bool OnCollisionSquare(Collider2D& _passive, Collider2D& _collision);

private:
	DirectX::XMFLOAT3 pos;	// 座標
	DirectX::XMFLOAT3 size;	// 当たり判定の大きさ
};