#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_Viewport
{
public:
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/
	CD3D11_Viewport();
	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~CD3D11_Viewport();

	/**	@brief 	ビューポートの設定
	*	@param	ID3D11DeviceContext* p_ImmediateContext     デバイスコンテキスト
	*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	void    Create(ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* pSwapChain);

	/**	@brief 	解放処理
	*	@date 2024/03/29
	*/
	void    Release();
public:
	D3D11_VIEWPORT viewport;	//ビューポート
	//一旦1画面想定
};