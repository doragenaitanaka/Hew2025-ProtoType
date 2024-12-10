#include"CRenderTargetView.h"
#include"../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11_RenderTargetView::CD3D11_RenderTargetView()
{
	this->m_pRenderTargetView = nullptr;
}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11_RenderTargetView::~CD3D11_RenderTargetView()
{
    this->Release();
}
/**	@brief 	レンダーターゲットビューの作成
*	@param	ID3D11Device* p_Device                      Direct3Dデバイス
*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_RenderTargetView::Create(ID3D11Device* p_Device, IDXGISwapChain* p_SwapChain)
{
    HRESULT  hr;

    
    ID3D11Texture2D* pBackBuffer;                                                       //  バックバッファ
    hr = p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);   //  スワップチェーンの最初のバックバッファ(0番目)を取得している 
    if (FAILED(hr)) { return hr; }                                                      //  取得できたかチェック

    
    hr = p_Device->CreateRenderTargetView(pBackBuffer, NULL, &this->m_pRenderTargetView);   //レンダーターゲットビューの作成(バッファの色を初期化)  
    SAFE_RELEASE(pBackBuffer);                                                              //  バックバッファはもう使わないので解放する
    if (FAILED(hr)) { return hr; }                                                          //  作成出来たかチェック
    return hr;
}
/**	@brief 	解放処理
*	@date 2024/03/29
*/
void    CD3D11_RenderTargetView::Release()
{
    SAFE_RELEASE(this->m_pRenderTargetView);
}