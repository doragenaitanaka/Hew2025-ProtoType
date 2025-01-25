#include"Background.h"

Background::Background(Camera* _p_camera):Object(_p_camera)
{}
Background::~Background(){}

/**	@brief 	オブジェクトの更新
*/
void	Background::Update(void)
{
	if (!this->isActive) { return; }

	// アニメーションの更新
	//this->AnimUpdate();

	// 定数バッファの更新
	this->ConstantBufferUpdate();
}

/**	@brief	定数バッファの更新
*/
void	Background::ConstantBufferUpdate(void)
{
	if (!this->isActive) { return; }
	ConstBuffer	cb;

	// ビュー変換行列の作成
	cb.matrixView = DirectX::XMMatrixIdentity(); // カメラの影響を受けない

	// プロジェクション変換座標の作成
	// 画面の大きさ基準をスクリーンと同じにする
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	// ワールド変換行列の作成
	// →オブジェクトの位置、大きさ、向きを指定
	cb.matrixWorld = DirectX::XMMatrixScaling(this->size.x, this->size.y, this->size.z);	// 大きさ
	float   radianAngle = DirectX::XMConvertToRadians(this->angle);							// ラジアンに変換
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(radianAngle);								// 向きを指定
	cb.matrixWorld *= DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	float	u = (float)this->numU / this->splitX;
	float	v = (float)this->numV / this->splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	// 頂点カラー行列の作成
	cb.color = this->color;

	// 定数バッファの更新
	this->p_constantBuffer->Update(&cb);
}