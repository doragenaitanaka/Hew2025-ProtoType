#include"Player.h"

Player::Player():x3{ 0.0f }, x4{ 0.0f }, y3{ 0.0f }, y4{ 0.0f }
{}

Player::~Player()
{}

/**	@brief 	オブジェクトの初期化
*	@param	const wchar_t* _p_fileName ファイルパス
*	@param	int	_splitX = 1		タテに何分割するのか
*	@param	int	_splitY = 1		ヨコに何分割するのか
*	@param	int	_changeFrame = 1	何フレームで切り替えるか
*	@param	float	_moveUPos = 0.0f	切り替わるごとに動くテクスチャU座標の移動量
*	@return	HRESULT
*	@date	2024/12/20
*/
HRESULT	Player::Init(const wchar_t* _p_fileName, int	_splitX, int	_splitY, int	_changeFrame, float	_moveUPos)
{
	//=======================================
	//		テスト的に変えている
	

	this->x3 = 0.5f;
	this->y3 = 0.5f;


	//=======================================

	// コライダーをオブジェクトの座標、サイズと合わせる
	this->p_coll = new BoxCollider(DirectX::XMFLOAT3(this->pos.x, this->pos.y, this->pos.z), DirectX::XMFLOAT3(this->size.x, this->size.y, this->size.z));

	// 分割数に応じてUV座標を決める
	this->splitX = _splitX;
	this->splitY = _splitY;

	// フレームの幅と高さ
	float uvWidth = 1.0f / splitX;
	float uvHeight = 1.0f / splitY;

	// フレームの行と列を計算
	int frameX = static_cast<int>(numU) % splitX;
	int frameY = static_cast<int>(numV) / splitY;

	// UV座標の設定
	this->playerVertexList[0].u = frameX * uvWidth;
	this->playerVertexList[0].v = frameY * uvHeight;

	this->playerVertexList[1].u = (frameX + 1) * uvWidth;
	this->playerVertexList[1].v = frameY * uvHeight;

	this->playerVertexList[2].u = frameX * uvWidth;
	this->playerVertexList[2].v = (frameY + 1) * uvHeight;

	this->playerVertexList[3].u = (frameX + 1) * uvWidth;
	this->playerVertexList[3].v = (frameY + 1) * uvHeight;

	this->playerVertexList[4].u = frameX * uvWidth;
	this->playerVertexList[4].v = (frameY + 2) * uvHeight;

	this->playerVertexList[5].u = (frameX + 1) * uvWidth;
	this->playerVertexList[5].v = (frameY + 2) * uvHeight;

	this->playerVertexList[6].u = (frameX + 2) * uvWidth;
	this->playerVertexList[6].v = frameY * uvHeight;

	this->playerVertexList[7].u = (frameX + 2) * uvWidth;
	this->playerVertexList[7].v = (frameY + 1) * uvHeight;

	this->playerVertexList[8].u = (frameX + 2) * uvWidth;
	this->playerVertexList[8].v = (frameY + 2) * uvHeight;

	// アニメーションの切り替え速度と移動量を設定
	this->changeFrame = _changeFrame;
	this->moveUPos = _moveUPos;

	HRESULT hr;
	// 定数バッファの作成
	if (!this->p_constantBuffer)
	{
		this->p_constantBuffer = new	CConstantBuffer;
		hr = this->p_constantBuffer->Create(NULL, sizeof(ConstBuffer));
	}

	// 頂点バッファの作成
	if (!this->p_vertexBuffer)
	{
		this->p_vertexBuffer = new  CVertexBuffer;
		//																									↓ 動的に書き換え可能にしている
		hr = this->p_vertexBuffer->Create(this->playerVertexList, sizeof(this->playerVertexList) * 9,NULL, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
	}

	// テクスチャ読み込み
	if (!this->p_textureView)
	{
		this->p_textureView = this->LoadTexture(_p_fileName);
	}
	return	hr;
}

/**	@brief 	オブジェクトの更新
*	@date	2024/12/20
*/
void	Player::Update()
{
	// 頂点データの更新
	this->playerVertexList[0].x = -0.5f + 0.6f * x3 + 0.2f * x4;
	this->playerVertexList[2].x = -0.5f + x3 - 0.1f * x4;
	this->playerVertexList[4].x = -0.5f + 0.6f * x3 + 0.2f * x4;

	this->playerVertexList[2].y = 0.0f + y3;
	this->playerVertexList[0].y = 0.5f + 0.5f * y3;

	this->playerVertexList[4].y = -0.5f + 0.7f * y3;
	this->playerVertexList[3].y = 0.0f + y4;
	this->playerVertexList[1].y = 0.5f + 0.5f * y4;
	this->playerVertexList[5].y = -0.5f + 0.5f * y4;

	this->playerVertexList[1].x = 0.5f + 0.6f * x4 + 0.2f * x3;
	this->playerVertexList[3].x = 0.5f + x4 - 0.1f * x3;
	this->playerVertexList[5].x = 0.5f + 0.6f * x4 + 0.2f * x3;
	this->playerVertexList[8].x = 0.5f + 0.6f * x4 + 0.2f * x3;

	// デバイスコンテキストの取得
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11DeviceContext* p_deviceContext = cd3d11->GetDeviceContext();

	// 新しい頂点データを設定し直す
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// バッファをマップ
	HRESULT hr = p_deviceContext->Map(this->p_vertexBuffer->GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (SUCCEEDED(hr))
	{
		// データをコピー
		memcpy(mappedResource.pData, this->playerVertexList, sizeof(this->playerVertexList));

		// バッファをアンマップ
		p_deviceContext->Unmap(this->p_vertexBuffer->GetBuffer(), 0);
	}

	// 定数バッファの更新
	this->ConstantBufferUpdate();
}

/**	@brief 	描画関数
*	@date	2024/12/20
*/
void	Player::Draw()
{
	UINT offsets = 0;
	UINT strides = sizeof(Vertex);
	this->p_vertexBuffer->SetVertexBuffer(0, 1, &strides, &offsets);	// 頂点バッファをIAに渡す

	//デバイスコンテキストの取得
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11DeviceContext* p_deviceContext = cd3d11->GetDeviceContext();
	p_deviceContext->PSSetShaderResources(0, 1, &this->p_textureView);	// テクスチャをピクセルシェーダーに渡す

	// シェーダに渡す
	this->p_constantBuffer->SetConstantBuffer();

	p_deviceContext->Draw(9, 0); // 描画命令
}

/**	@brief 	終了処理
*	@date  	2024/12/20
*/
void	Player::UnInit()
{
}