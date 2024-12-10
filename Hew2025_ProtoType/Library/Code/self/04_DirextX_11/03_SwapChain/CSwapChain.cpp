#include"CSwapChain.h"
#include<atltypes.h>
#include"../../SafePointers.h"
//CreateDXGIFactory 関数を使うのに必要
#include<dxgi.h>
#pragma comment(lib, "dxgi.lib")

/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11_SwapChain::CD3D11_SwapChain()
{
    this->m_pSwapChain = nullptr;
    this->pFactory = nullptr;
}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11_SwapChain::~CD3D11_SwapChain()
{
    this->Release();
}

/**	@brief 	レンダーターゲットビューの作成
*	@param	ID3D11Device* p_Device Direct3Dデバイス
*   @param  HWND hwnd              windowsハンドル
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_SwapChain::Create(HWND hwnd, ID3D11Device* m_pDevice)
{
    HRESULT  hr;

    //スワップチェーンの設定
    CRect                rect;
    DXGI_SWAP_CHAIN_DESC scDesc;

    //指定のウィンドウの中身を全て初期化
    ::GetClientRect(hwnd, &rect);
    ::ZeroMemory(&scDesc, sizeof(scDesc));

    //バックバッファの表示モード
    scDesc.BufferDesc.Width = rect.Width();
    scDesc.BufferDesc.Height = rect.Height();
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //マルチサンプリングのパラメータ
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;

    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      // 新しいフレームが描画されるたびに、前のフレームバッファの内容が破棄される
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferCount = 2;                                 //スワップチェーン内のバッファの数
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //バックバッファの使用方法
    scDesc.OutputWindow = hwnd;                             //出力するウィンドウのハンドル
    scDesc.Windowed = TRUE;                                 //ウィンドウモードかどうか

    //DXGIファクトリオブジェクトの作成
    //古い？
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&this->pFactory);
    //成功したかチェック
    if (FAILED(hr)) { return hr; }

    //スワップチェーンの初期化
    //11.1以降ではIDXGIFactory2::CreateSwapChainForHwndがいいっぽいが
    //今は11.0なのでこれで行く
    hr = this->pFactory->CreateSwapChain(m_pDevice,         //スワップチェーンを作成するDirect3Dデバイスへのポインター
        &scDesc,                                            //スワップチェーンの設定を含むDXGI_SWAP_CHAIN_DESC構造体へのポインター
        &this->m_pSwapChain);                               //作成されたスワップチェーンのインターフェースへのポインターを受け取る変数へのポインター

    //成功したかチェック
    if (FAILED(hr)) { return hr; }
    return hr;
}

/**	@brief 	解放処理
*	@date 2024/03/29
*/
void    CD3D11_SwapChain::Release()
{
    SAFE_RELEASE(this->m_pSwapChain);
    SAFE_RELEASE(this->pFactory);
}