#pragma once
#include"../04_DirextX_11/07_Buffer/01_CVertexBuffer/CVertexBuffer.h"
#include"../04_DirextX_11/07_Buffer/03_CConstantBuffer/CConstantBuffer.h"
#include"../04_DirextX_11/08_InputLayout/CInputLayout.h"

#include "../05_Collider/00_BaseCollider/BaseCollider.h"
#include "../05_Collider/01_BoxCollider/BoxCollider.h"
#include "../05_Collider/02_CircleCollider/CircleCollider.h"
#include"../07_Camera/Camera.h"

#include<DirectXMath.h> //  DirectX::XMFLOAT3に必要

// 定数バッファの中身
struct ConstBuffer
{
	DirectX::XMMATRIX   matrixWorld;	// ワールド変換行列
	DirectX::XMMATRIX   matrixView;		// ビュー変換行列
	DirectX::XMMATRIX   matrixProj;		// プロジェクション変換行列 
	DirectX::XMMATRIX   matrixTex;		// UV座標移動行列 
	DirectX::XMFLOAT4	color;			// 頂点カラー行列
};

// 構造体の定義
// 頂点データを表す構造体
struct Vertex
{
	// 頂点の位置座標
	float x, y, z;
	//カラー値
	float	r, g, b, a;
	//テクスチャ座標(UV座標)
	float	u, v;
};

class Object
{
public:
	Object(Camera* _p_camera);
	virtual~Object();
	/**	@brief 	オブジェクトの初期化
	*	@param	const wchar_t* _p_fileName ファイルパス
	*	@param	int	_splitX = 1		タテに何分割するのか
	*	@param	int	_splitY = 1		ヨコに何分割するのか
	*	@param	int	_changeFrame = 1	何フレームで切り替えるか
	*	@param	float	_moveUPos = 0.0f	切り替わるごとに動くテクスチャU座標の移動量
	*	@return	HRESULT
	*	@date	2024/06/06
	*/
	virtual HRESULT	Init(const wchar_t* _p_fileName, int	_splitX = 1, int	_splitY = 1, int	_changeFrame = 1, float	_moveUPos = 0.0f);

	/**	@brief 	オブジェクトの更新
	*	@date	2024/06/12
	*/
	virtual void	Update(void);

	/**	@brief 	アニメーションの更新
	*	@date	2024/06/12
	*/
	void	AnimUpdate(void);

	/**	@brief	定数バッファの更新
	*	@date	2024/06/12
	*/
	void	ConstantBufferUpdate(void);

	/**	@brief 	描画関数
	*	@date	2024/05/23
	*/
	virtual void	Draw();
	/**	@brief 	終了処理
	*	@date  	2024/05/23
	*/
	virtual void	UnInit(void);

	/**	@brief 	座標を設定
	*	@param	float x
	*	@param	float y
	*	@param	float z
	*	@date	2024/05/30
	*/
	void	SetPos(float x, float y, float z);

	/**	@brief 	座標を取得
	*	@retuen		DirectX::XMFLOAT3
	*	@date	2024/09/19
	*/
	DirectX::XMFLOAT3	GetPos(void);

	/**	@brief 	サイズを取得
	*	@retuen		DirectX::XMFLOAT3
	*	@date	2024/09/19
	*/
	DirectX::XMFLOAT3	GetSize(void);	

	/**	@brief 	コライダーの座標を設定
	*	@param		DirectX::XMFLOAT3	_collPos	コライダーの座標
	*	@date	2024/12/20
	*/
	void SetColliderPos(DirectX::XMFLOAT3 _collPos);
	
	/**	@brief 	コライダーのサイズを設定
	*	@retuen		DirectX::XMFLOAT3	_collSize	コライダーの大きさ
	*	@date	2024/12/20
	*/
	void SetColliderSize(DirectX::XMFLOAT3 _collSize);

	/**	@brief 	大きさを設定
	*	@param	float x
	*	@param	float y
	*	@param	float z
	*	@date	2024/05/30
	*/
	void	SetSize(float x, float y, float z);

	/**	@brief 	角度を設定
	*	@param	float angle
	*	@date	2024/05/30
	*/
	void	SetAngle(float angle);

	/**	@brief 	映すテクスチャのヨコのU座標を設定
	*	@param	int	numU
	*	@date	2024/06/06
	*/
	void	SetTextureNumU(float	numU);

	/**	@brief 	映すテクスチャのタテのV座標を設定
	*	@param	int	numV
	*	@date	2024/06/06
	*/
	void	SetTextureNumV(float	numV);

	/**	@brief 	映すテクスチャのヨコのU座標を取得
	*	@return	int	numU
	*	@date	2024/06/07
	*/
	float	GetTextureNumU(void);

	/**	@brief 	映すテクスチャのタテのV座標を取得
	*	@return	int	numV
	*	@date	2024/06/07
	*/
	float	GetTextureNumV(void);

	/**	@brief 	コライダーの取得
	*	@return	BaseCollider&		コライダー
	*	@date	2024/06/12
	*/
	BaseCollider&	GetCollider(void);


	/**	@brief 	テクスチャをセット
	*	@param	DirectX::XMFLOAT4	_color	頂点カラー
	*	@date	2024/06/12
	*/
	void	SetTexture(ID3D11ShaderResourceView* _p_texture);

	/**	@brief 	映すテクスチャの頂点座標を設定
	*	@param	DirectX::XMFLOAT4	_color	頂点カラー
	*	@date	2024/06/12
	*/
	void	SetColor(DirectX::XMFLOAT4	_color);

	/**	@brief 	映すテクスチャの透明度を設定
	*	@param	float	_color	透明度（アルファ値）
	*	@date	2024/06/12
	*/
	void	SetAlpha(float	_color);

	/**	@brief 	テクスチャの読み込み関数
	*	@param	const wchar_t* fileName ファイルパス
	*	@return	ID3D11ShaderResourceView*	テクスチャ
	*	@date	2024/09/17
	*/
	static ID3D11ShaderResourceView* LoadTexture(const wchar_t* fileName);
protected:
	Camera* p_camera;	// カメラ

	// 表示テクスチャの頂点座標
	Vertex	vertexList[4]
	{
		{ -0.5f, 0.5f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.0f,0.0f},	// 0番目の頂点座標　{ x, y, z }{ r, g, b, a}{ u, v}
		{ 0.5f, 0.5f, 0.5f,		1.0f,1.0f,1.0f,1.0f,	1.0f,0.0f},	// 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.0f,1.0f},	// 2番目の頂点座標
		{ 0.5f, -0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,1.0f},	// 1番目の頂点座標
	}; 
	DirectX::XMFLOAT3	pos = {1.0f, 1.0f, 1.0f};	// 座標
	float	angle;									// 角度

	DirectX::XMFLOAT3	size = { 1.0f, 1.0f, 1.0f };// 大きさ
	DirectX::XMFLOAT4	color;						// 頂点カラー

	BaseCollider* p_coll;


	// テクスチャを何分割するのか
	int	splitX;
	int	splitY;
	// 左上から何段目を切り抜いて表示するのか
	float	numU;
	float	numV;

	int	frameCount;									// アニメーション用カウント変数
	int	changeFrame;								// 切り替えフレーム数
	float	moveUPos;								// U座標の移動量

	bool	isSwitched;								// アニメーション順番切り替えフラグ

	CConstantBuffer* p_constantBuffer;				// 定数バッファ
	CVertexBuffer* p_vertexBuffer;					// 頂点バッファ
	ID3D11ShaderResourceView* p_textureView;		// テクスチャリソース
};