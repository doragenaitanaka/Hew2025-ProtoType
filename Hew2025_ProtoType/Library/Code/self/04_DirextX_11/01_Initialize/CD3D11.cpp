#include"CD3D11.h"
#include"../../SafePointers.h"

//	private	---------------------------------------------------------------------------------------------------

/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11::CD3D11()
{}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11::~CD3D11()
{
    //解放処理
    this->Release();
}
/**	@brief 	全体の解放
*	@date	2024/05/14
*/
void CD3D11::Release()
{
    this->deviceSetup.Release();
    this->swapChainSetup.Release();
    this->renderTargetViewSetup.Release();
    this->viewportSetup.Release();
    this->depthStencilSetup.Release();
}

//	static(public)	---------------------------------------------------------------------------------------------------

/**	@brief 	クラスインスタンスの生成
*	@date	2024/05/16
*	@memo	この関数を始めに実行する
*/
void   CD3D11::CrerateIntance(void)
{
    //生成されていなければCD3D11クラスを生成する
    if (!CD3D11::cd3d11)
    {
        CD3D11::cd3d11 = new	CD3D11;
    }
}

/**	@brief 	クラスインスタンスの取得
*	@return	CD3D11*	CD3D11クラス
*	@date	2024/05/16
*	@memo	この関数を使って各ファイルで生成済CD3D11クラスを取得する
*/
CD3D11* CD3D11::GetInstance(void)
{
    return  CD3D11::cd3d11;
}
/**	@brief 	クラスインスタンスの削除
*	@date	2024/05/16
*/
void    CD3D11::DestroyInstance(void)
{
    //存在していたら
    if (CD3D11::cd3d11)
    {
        delete  CD3D11::cd3d11;
        CD3D11::cd3d11 = nullptr;
    }
}
/**	@brief 	D3D11の初期化
*   @param  HWND hwnd   windousハンドル
*   @return HRESULT
*	@date	2024/05/18
*/
HRESULT CD3D11::Initialize(HWND hwnd)
{
    HRESULT  hr;

    //グラフィックデバイスの初期化
    hr = this->deviceSetup.Create();
    if (FAILED(hr)) { return hr; }

    //スワップチェーンの作成
    hr = this->swapChainSetup.Create(hwnd, this->deviceSetup.m_pDevice);
    if (FAILED(hr)) { return hr; }

    //レンダーターゲットビューの作成
    hr = this->renderTargetViewSetup.Create(this->deviceSetup.m_pDevice, this->swapChainSetup.m_pSwapChain);
    if (FAILED(hr)) { return hr; }

    //深度ステンシルビューの作成
    hr = this->depthStencilSetup.Create(this->deviceSetup.m_pDevice, this->deviceSetup.m_pImmediateContext, this->swapChainSetup.m_pSwapChain, this->renderTargetViewSetup.m_pRenderTargetView);
    if (FAILED(hr)) { return hr; }

    //ビューポートの設定
    this->viewportSetup.Create(this->deviceSetup.m_pImmediateContext, this->swapChainSetup.m_pSwapChain);
    return  hr;
}
//ゲッター-----------------------------------------------------------------------------------------------------------------
/**	@brief 	Direct3Dデバイスの取得
*	@return	CD3D11_Device*
*	@date	2024/05/16
*/
ID3D11Device* CD3D11::GetDevice(void)
{
    return  this->deviceSetup.m_pDevice;
}
/**	@brief  デバイスコンテキストの取得
*	@return	CD3D11_Device*
*	@date	2024/05/16
*/
ID3D11DeviceContext* CD3D11::GetDeviceContext(void)
{
    return  this->deviceSetup.m_pImmediateContext;
}

/**	@brief 	スワップチェインの取得
*	@return	CD3D11_SwapChain*
*	@date	2024/05/16
*/
IDXGISwapChain* CD3D11::GetSwapChain(void)
{
    return  this->swapChainSetup.m_pSwapChain;
}
/**	@brief 	レンダーターゲットビューの取得
*	@return	ID3D11RenderTargetView*
*	@date	2024/05/16
*/
ID3D11RenderTargetView* CD3D11::GetRenderTargetView(void)
{
    return  this->renderTargetViewSetup.m_pRenderTargetView;
}
/**	@brief 	ビューポートの取得
*	@return	D3D11_VIEWPORT
*	@date	2024/05/16
*/
D3D11_VIEWPORT* CD3D11::GetViewport(void)
{   
    return  &this->viewportSetup.viewport;
}
/**	@brief 	深度ステンシルの取得
*	@return	ID3D11DepthStencilView*
*	@date	2024/05/16
*/
ID3D11DepthStencilView* CD3D11::GetDepthStencilView(void)
{
    return this->depthStencilSetup.p_DepthStencilView;
}
//	静的メンバ変数	---------------------------------------------------------------------------------------------------

CD3D11* CD3D11::cd3d11 = nullptr;	//静的メンバ変数の初期化