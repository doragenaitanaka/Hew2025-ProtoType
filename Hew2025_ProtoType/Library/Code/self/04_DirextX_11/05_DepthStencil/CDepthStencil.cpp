#include"CDepthStencil.h"
#include"../../SafePointers.h"
/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11_DepthStencil::CD3D11_DepthStencil()
{
    this->p_DepthStencilView = nullptr;
}

/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11_DepthStencil::~CD3D11_DepthStencil()
{
    this->Release();
}
/**	@brief 	深度ステンシルの初期化
*	@param	ID3D11Device* p_Device                      Direct3Dデバイス
*	@param	ID3D11DeviceContext* p_ImmediateContext     デバイスコンテキスト
*   @param  IDXGISwapChain* p_SwapChain                 スワップチェーン
*   @param  ID3D11RenderTargetView* m_pRenderTargetView レンダーターゲットビューs
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_DepthStencil::Create(ID3D11Device* p_Device, ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* p_SwapChain, ID3D11RenderTargetView* m_pRenderTargetView)
{
    // 作成するテクスチャ
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    
    ID3D11Texture2D* p_depthStencilBufer = nullptr; // 深度ステンシルバッファ

    // バックバッファの取得
    ID3D11Texture2D* p_backBuffer = nullptr;        
    p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_backBuffer);

    // バックバッファから解像度を取得
    D3D11_TEXTURE2D_DESC buckBufferDesc;
    p_backBuffer->GetDesc(&buckBufferDesc);

    // テクスチャリソースの初期化
    descDepth.Width = buckBufferDesc.Width;             // バックバッファと同じ幅
    descDepth.Height = buckBufferDesc.Height;           // バックバッファと同じ高さ
    descDepth.MipLevels = 1;                            // ミップマップレベルは1
    descDepth.ArraySize = 1;                            // テクスチャ配列のサイズは1
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;   // 深度値に24bitのfloat型を、ステンシル値に8ビットのuintを確保
    descDepth.SampleDesc.Count = 1;                     // マルチサンプリングは使用しない
    descDepth.SampleDesc.Quality = 0;                   // マルチサンプリングの品質は最低
    descDepth.Usage = D3D11_USAGE_DEFAULT;              // GPUが読み書きする
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;     // 深度ステンシルターゲットとしてバインド
    descDepth.CPUAccessFlags = 0;                       // CPUからはアクセスしない
    descDepth.MiscFlags = 0;                            // その他のフラグは設定しない
    
    SAFE_RELEASE(p_backBuffer);         // 必要なくなったので解放

    HRESULT hr;
    hr = p_Device->CreateTexture2D(&descDepth, nullptr, &p_depthStencilBufer);  // 深度ステンシルバッファのテクスチャを作成    
    if (FAILED(hr)) { return hr; }                                              // 成功したかチェック

    // 作成するビューのタイプを指定
    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.Format = descDepth.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;

    // 深度ステンシルビューを作成
    hr = p_Device->CreateDepthStencilView(p_depthStencilBufer, &dsDesc, &this->p_DepthStencilView);
   
    if (FAILED(hr)) { return hr; }      // 成功したかチェック
    SAFE_RELEASE(p_depthStencilBufer);  // 深度ステンシルバッファの解放

    // レンダーターゲットにセット
    p_ImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, this->p_DepthStencilView);
    // クリアしておく
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // red, green, blue, alpha
    p_ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    p_ImmediateContext->ClearDepthStencilView(this->p_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    return S_OK;    // 成功を返す
}

/**	@brief 	解放処理
*	@date 2024/03/29
*/
void   CD3D11_DepthStencil::Release()
{
    SAFE_RELEASE(this->p_DepthStencilView);
}