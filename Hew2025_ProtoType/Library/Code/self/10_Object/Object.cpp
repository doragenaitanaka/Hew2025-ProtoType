/**	@brief 	頂点バッファの作成関数
*	@date	2024/05/23
*	@memo	extern で Direxc3D.hからデバイス、デバイスコンテキストを参照している
*/

#include"Object.h"
#include"../../other/01_WICTextureLoader/WICTextureLoader.h"
#include"../../self/04_DirextX_11/01_Initialize/CD3D11.h"
#include"../../self/SafePointers.h"

#include".././03_Windows/WindowSetup.h"	// スクリーンの大きさ貰う　(ここにサイズ置くべきでないのかも)

Object::Object(Camera* _p_camera):p_camera{_p_camera }
{
	this->isActive = true;

	this->istextureShared = false;

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
/**	@brief 	オブジェクトの初期化
*	@param	const wchar_t* _p_fileName ファイルパス
*	@param	int	_splitX = 1		タテに何分割するのか
*	@param	int	_splitY = 1		ヨコに何分割するのか
*	@param	int	_changeFrame = 1	何フレームで切り替えるか
*	@param	float	_moveUPos = 0.0f	切り替わるごとに動くテクスチャU座標の移動量
*	@return	HRESULT
*	@date	2024/06/06
*/
HRESULT	Object::Init(const wchar_t* _p_fileName, int	_splitX, int	_splitY, int	_changeFrame , float	_moveUPos)
{
	// コライダーをオブジェクトの座標、サイズと合わせる
	this->p_coll = new BoxCollider(DirectX::XMFLOAT3(this->pos.x, this->pos.y, this->pos.z), DirectX::XMFLOAT3(this->size.x, this->size.y, this->size.z));

	// 分割数に応じてUV座標を決める
	this->splitX = _splitX;
	this->splitY = _splitY;

	// 映すテクスチャの範囲を決める
	this->vertexList[1].u = 1.0f / this->splitX;
	this->vertexList[2].v = 1.0f / this->splitY;
	this->vertexList[3].u = 1.0f / this->splitX;
	this->vertexList[3].v = 1.0f / this->splitY;

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
		this->p_vertexBuffer = new CVertexBuffer;
		// 頂点リストのサイズを取得
		UINT vertexListSize = sizeof(this->vertexList) / sizeof(Vertex); // Vertexは頂点の型
		HRESULT hr = this->p_vertexBuffer->Create(this->vertexList, vertexListSize * sizeof(Vertex));
		if (FAILED(hr))
		{
			// エラー処理
			delete this->p_vertexBuffer;
			this->p_vertexBuffer = nullptr;
		}
	}

	// テクスチャ読み込み
	if (!this->p_textureView)
	{
		this->p_textureView = this->LoadTexture(_p_fileName);
	}
	return	hr;
}

/**	@brief 	オブジェクトの更新
*	@date	2024/06/12
*/
void	Object::Update(void)
{
	if (!this->isActive) { return; }

	// アニメーションの更新
	//this->AnimUpdate();

	// 定数バッファの更新
	this->ConstantBufferUpdate();
}

/**	@brief 	アニメーションの更新
*	@date	2024/06/12
*/
void	Object::AnimUpdate(void)
{
	// アニメーションの更新
	this->frameCount = (this->frameCount + 1) % this->changeFrame;
	// 切り替えるフレームが来たら
	if (this->frameCount == 0)
	{
		if (!this->isSwitched)
		{
			// U座標を移動
			this->numU += this->moveUPos;

			// 最後まで動かせたら元に戻す
			if (this->numU >= this->splitX)
			{
				this->isSwitched = true;
				this->numU = this->splitX - 1.0f;
			}
		}
		if (this->isSwitched)
		{
			// U座標を移動  
			this->numU -= this->moveUPos;

			// 最後まで動かせたら元に戻す
			if (this->numU <= 0)
			{
				this->isSwitched = false;
				this->numU = 0.0f;
			}
		}
	}
}

/**	@brief	定数バッファの更新
*	@date	2024/06/12
*/
void	Object::ConstantBufferUpdate(void)
{
	ConstBuffer	cb;

	// ビュー変換行列の作成
	cb.matrixView = this->p_camera->GetViewMat();

	// プロジェクション変換行列の作成
	cb.matrixProj = this->p_camera->GetProjectionMat();

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

/**	@brief 	描画関数
*	@param	UINT strides
*	@date	2024/05/23
*/
void	Object::Draw()
{
	if (!this->isActive) { return; }

	UINT offsets = 0;
	UINT strides = sizeof(Vertex);
	this->p_vertexBuffer->SetVertexBuffer(0, 1, &strides, &offsets);	// 頂点バッファをIAに渡す

	//デバイスコンテキストの取得
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11DeviceContext* p_deviceContext = cd3d11->GetDeviceContext();
	p_deviceContext->PSSetShaderResources(0, 1, &this->p_textureView);	// テクスチャをピクセルシェーダーに渡す

	// シェーダに渡す
	this->p_constantBuffer->SetConstantBuffer();

	p_deviceContext->Draw(4, 0); // 描画命令
}
void	Object::UnInit(void)
{
	if (this->p_coll) {
		delete this->p_coll;
		this->p_coll = nullptr;
	}

	SAFE_RELEASE(this->p_vertexBuffer);
	SAFE_RELEASE(this->p_constantBuffer);

	// テクスチャが共有されていなければ解放処理を行う
	if (!this->istextureShared) { SAFE_RELEASE(this->p_textureView); }
}

/**	@brief 	オブジェクトが有効かどうか
*	@param	bool _isActive
*/
void	Object::SetIsActive(bool _isActive)
{
	this->isActive = _isActive;
}

/**	@brief 	オブジェクトが有効かどうか返す
*	@return	bool _isActive
*/
bool	Object::GetIsActive(void)
{
	return this->isActive;
}

/**	@brief 	座標を設定
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

	// 今回は当たり判定はずっとオブジェクトと同じ座標
	this->p_coll->SetPosition(this->pos);

	// 定数バッファの更新
	this->ConstantBufferUpdate();
}
/**	@brief 	座標を設定
*	@return		DirectX::XMFLOAT3
*	@date	2024/09/19
*/
DirectX::XMFLOAT3	Object::GetPos(void)
{
	return this->pos;
}

/**	@brief 	サイズを設定
*	@return		DirectX::XMFLOAT3
*	@date	2024/09/19
*/
DirectX::XMFLOAT3	Object::GetSize(void)
{
	return this->size;
}

/**	@brief 	コライダーの座標を設定
*	@param		DirectX::XMFLOAT3	_collPos	コライダーの座標
*	@date	2024/12/20
*/
void Object::SetColliderPos(DirectX::XMFLOAT3 _collPos)
{
	this->p_coll->SetPosition(_collPos);
}

/**	@brief 	コライダーのサイズを設定
*	@return		DirectX::XMFLOAT3
*	@date	2024/12/20
*/
void Object::SetColliderSize(DirectX::XMFLOAT3 _collSize)
{
	// Boxの場合大きさを設定する
	if (typeid(*this->p_coll) == typeid(BoxCollider))
	{
		static_cast<BoxCollider*>(this->p_coll)->SetSize(_collSize);
	}
}

/**	@brief 	大きさを設定
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
}

/**	@brief 	角度を設定
*	@param	float angle
*	@date	2024/05/30
*/
void	Object::SetAngle(float angle)
{
	this->angle = angle;

	// Boxの場合角度を設定する
	if (typeid(*this->p_coll) == typeid(BoxCollider))
	{
		static_cast<BoxCollider*>(this->p_coll)->SetAngle(angle);
	}
}

/**	@brief 	テクスチャをセット
*	@param	ID3D11ShaderResourceView* _p_texture	テクスチャ
*	@date	2024/09/17
*/
void	Object::SetTexture(ID3D11ShaderResourceView* _p_texture)
{
	this->p_textureView = _p_texture;

	// テクスチャを外部から読み込んで共有している
	this->istextureShared = true;
}

/**	@brief 	映すテクスチャのヨコの場所を設定
*	@param	int	numU
*	@date	2024/06/06
*/
void	Object::SetTextureNumU(float	numU)
{
	this->numU = numU;
}

/**	@brief 	映すテクスチャのタテの場所を設定
*	@param	int	numV
*	@date	2024/06/06
*/
void	Object::SetTextureNumV(float	numV)
{
	this->numV = numV;
}

/**	@brief 	映すテクスチャのヨコのU座標を取得
*	@return	int	numU
*	@date	2024/06/07
*/
float	Object::GetTextureNumU(void)
{
	return	this->numU;
}

/**	@brief 	映すテクスチャのタテのV座標を取得
*	@return	int	numV
*	@date	2024/06/07
*/
float	Object::GetTextureNumV(void)
{
	return	this->numV;
}

/**	@brief 	コライダーの取得
*	@return	BaseCollider&		コライダー
*	@date	2024/06/12
*/
BaseCollider& Object::GetCollider(void)
{
	return *this->p_coll;
}

/**	@brief 	映すテクスチャの頂点座標を設定
*	@param	DirectX::XMFLOAT4	_color	頂点カラー
*	@date	2024/06/12
*/
void	Object::SetColor(DirectX::XMFLOAT4	_color)
{
	this->color = _color;
}

/**	@brief 	映すテクスチャの透明度を設定
*	@param	float	_color	透明度（アルファ値）
*	@date	2024/06/12
*/
void	Object::SetAlpha(float	_color)
{
	this->color.w = _color;
}


/**	@brief 	テクスチャの読み込み関数
*	@param	const wchar_t* fileName ファイルパス
*	@return	ID3D11ShaderResourceView*	テクスチャ
*	@date	2024/09/17
*/
ID3D11ShaderResourceView* Object::LoadTexture(const wchar_t* fileName)
{
	HRESULT hr;
	ID3D11ShaderResourceView* p_texture = nullptr;
	//デバイスの取得
	CD3D11* cd3d11 = CD3D11::GetInstance();
	ID3D11Device* p_device = cd3d11->GetDevice();
	//テクスチャ読み込み
	hr = CreateWICTextureFromFile(p_device, fileName, NULL, &p_texture);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "error", MB_ICONERROR | MB_OK);
		return nullptr;
	}
	return p_texture;
}