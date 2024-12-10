#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_RenderTargetView
{
public:
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/
	CD3D11_RenderTargetView();
	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~CD3D11_RenderTargetView();
	/**	@brief 	レンダーターゲットビューの作成
	*	@param	ID3D11Device* p_Device                      Direct3Dデバイス
	*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(ID3D11Device* p_Device, IDXGISwapChain* p_SwapChain);
	/**	@brief 	解放処理
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11RenderTargetView* m_pRenderTargetView;    //レンダーターゲットビュー
};