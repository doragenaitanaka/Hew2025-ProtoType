#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_DepthStencil
{
public:
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/	
	CD3D11_DepthStencil();
	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~CD3D11_DepthStencil();
	/**	@brief 	深度ステンシルの初期化
	*	@param	ID3D11Device* p_Device                      Direct3Dデバイス
	*	@param	ID3D11DeviceContext* p_ImmediateContext     デバイスコンテキスト
	*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
	*   @param  ID3D11RenderTargetView* m_pRenderTargetView レンダーターゲットビューs
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(ID3D11Device* p_Device, ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* p_SwapChain, ID3D11RenderTargetView* m_pRenderTargetView);
	/**	@brief 	解放処理
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11DepthStencilView* p_DepthStencilView;	//深度ステンシルビュー
};

