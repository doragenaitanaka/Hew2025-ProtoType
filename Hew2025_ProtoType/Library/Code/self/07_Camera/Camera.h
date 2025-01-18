/**	@file 	Camera.h
*	@brief 	カメラクラス
*	@date	2025/01/18
*/
#pragma once
#include<DirectXMath.h> //  DirectX::XMFLOAT3に必要
#include"../03_Windows/WindowSetup.h"

class Camera
{
public:
	Camera();
	~Camera();
	virtual void Update();

	DirectX::XMMATRIX GetViewMat();
	DirectX::XMMATRIX GetProjectionMat();

	// カメラの位置を設定するメソッド
	void SetPosition(float x, float y)
	{
		pos = DirectX::XMFLOAT3(x, y, -10.0f); // z座標を固定
		tgt = DirectX::XMFLOAT3(x, y, 0.0f);   // ターゲットのz座標も固定
	}

private:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 tgt;
	DirectX::XMFLOAT3 up;

	float nearPlane;	// ニアクリップ
	float farPlane;		// ファークリップ
};