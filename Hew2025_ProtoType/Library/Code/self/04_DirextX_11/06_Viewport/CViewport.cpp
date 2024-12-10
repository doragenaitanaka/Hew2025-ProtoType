#include"CViewport.h"

/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11_Viewport::CD3D11_Viewport()
{
}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11_Viewport::~CD3D11_Viewport()
{
	this->Release();
}

/**	@brief 	ビューポートの設定
*	@param	ID3D11DeviceContext* p_ImmediateContext     デバイスコンテキスト
*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
*	@return HRESULT
*	@date 2024/03/29
*/
void    CD3D11_Viewport::Create(ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* pSwapChain)
{
	// バックバッファの取得
	ID3D11Texture2D* backBuffer = NULL;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// バックバッファから解像度を取得
	D3D11_TEXTURE2D_DESC	buckBufferDesc;
	backBuffer->GetDesc(&buckBufferDesc);

	// ビューポートの初期化
	this->viewport.TopLeftX = 0;
	this->viewport.TopLeftY = 0;
	this->viewport.Width = buckBufferDesc.Width;
	this->viewport.Height = buckBufferDesc.Height;
	this->viewport.MinDepth = 0.0f;
	this->viewport.MaxDepth = 1.0f;

	backBuffer->Release();									// 必要なくなったので解放
	p_ImmediateContext->RSSetViewports(1, &this->viewport);	// ビューポートを設定
}

/**	@brief 	解放処理
*	@date 2024/03/29
*/
void   CD3D11_Viewport::Release()
{
}