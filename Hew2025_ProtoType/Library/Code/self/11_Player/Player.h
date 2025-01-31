#pragma once
#include"../10_Object/Object.h"

class Player :public Object
{
public:
	Player(Camera* _p_camera);
	~Player()override;

	// プレイヤー用の表示テクスチャの頂点座標
	Vertex	playerVertexList[16]
	{
		{ -0.5f, 0.5f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.0f,0.0f},	// 0番目の頂点座標　{ x, y, z }{ r, g, b, a}{ u, v}
		{ 0.0f, 0.5f, 0.5f,		1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f},	// 1番目の頂点座標
		{ -0.5f, -0.0f, 0.5f,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f},	// 2番目の頂点座標
		{ 0.0f, -0.0f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.5f},	// 3番目の頂点座標
		{ -0.5f, -0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,0.0f},	// 4番目の頂点座標
		{ 0.0f, -0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,0.5f},	// 5番目の頂点座標
		{ 0.5f, -0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,1.0f},	// 6番目の頂点座標
		{ 0.5f, 0.0f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,0.5f},	// 7番目の頂点座標
		{ 0.5f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,0.0f},	// 8番目の頂点座標
		{ 0.0f, 0.0f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.5f},	// 9番目の頂点座標
		{ 0.0f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f}, // 10番目の頂点座標
		{ 0.0f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f}, // 11番目の頂点座標
		{ 0.5f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	1.0f,0.0f},	// 12番目の頂点座標
		{ 0.0f, 0.0f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.5f},	// 13番目の頂点座標
		{ 0.0f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f}, // 14番目の頂点座標
		{ 0.0f, 0.5f, 0.5f ,	1.0f,1.0f,1.0f,1.0f,	0.5f,0.0f}, // 15番目の頂点座標
	};

	/**	@brief 	オブジェクトの初期化
	*	@param	const wchar_t* _p_fileName ファイルパス
	*	@param	int	_splitX = 1		タテに何分割するのか
	*	@param	int	_splitY = 1		ヨコに何分割するのか
	*	@param	int	_changeFrame = 1	何フレームで切り替えるか
	*	@param	float	_moveUPos = 0.0f	切り替わるごとに動くテクスチャU座標の移動量
	*	@return	HRESULT
	*	@date	2024/12/20
	*/
	HRESULT	Init(const wchar_t* _p_fileName = nullptr, int	_splitX = 1, int	_splitY = 1, int	_changeFrame = 1, float	_moveUPos = 0.0f)override;

	/**	@brief 	オブジェクトの更新
	*	@date	2024/12/20
	*/
	void	Update()override;

	/**	@brief 	描画関数
	*	@date	2024/12/20
	*/
	void	Draw()override;

	/**	@brief 	終了処理
*	@date  	2024/05/23
*/
	void	UnInit()override;

	bool GetIsDead()const;
	void SetIsDead(const bool _isDead);

	float x3, y3, x4, y4;
private:
	bool isDead;	// 死んだか
};