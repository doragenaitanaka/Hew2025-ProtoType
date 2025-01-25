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

	/**	@brief 	更新
	*/
	virtual void Update();

	/**	@brief 	ビュー変換行列の取得
	*   @return DirectX::XMMATRIX   ビュー変換行列
	*/
	DirectX::XMMATRIX GetViewMat();

	/**	@brief 	プロジェクション変換行列の取得
	*   @return DirectX::XMMATRIX   プロジェクション変換行列
	*/
	DirectX::XMMATRIX GetProjectionMat();

	/**	@brief 	カメラの位置を設定するメソッド
	*   @param float _x
	*   @param float _y
	*/
	inline void SetPosition(float _x, float _y)
	{
		pos = DirectX::XMFLOAT3(_x, _y, -10.0f);	// z座標を固定
		tgt = DirectX::XMFLOAT3(_x, _y, 10.0f);		// ターゲットのz座標も固定
	}

	/**	@brief 	カメラのズーム倍率の設定
	*   @param float _zoomFactor	ズームする倍率
	*/
	inline void SetZoom(float _zoomFactor)
	{
		this->zoomFactor = _zoomFactor;
	}

	/**	@brief 	画面シェイク
	*   @param float _intensity	揺れる強さ
	*/
	void Shake(float _intensity);

protected:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 tgt;
	DirectX::XMFLOAT3 up;

	float nearPlane;	// ニアクリップ
	float farPlane;		// ファークリップ

	float zoomFactor;	// ズーム倍率
};