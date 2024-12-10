#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")

#include"../02_Device/CDevice.h"
#include"../03_SwapChain/CSwapChain.h"
#include"../04_RenderTargetView/CRenderTargetView.h"
#include"../05_DepthStencil/CDepthStencil.h"
#include"../06_Viewport/CViewport.h"

class CD3D11 {
public:
    /**	@brief 	クラスインスタンスの生成
    *	@date	2024/05/16
    *	@memo	この関数を始めに実行する
    */
    static  void    CrerateIntance(void);

    /**	@brief 	クラスインスタンスの取得
    *	@return	CD3D11*	CD3D11クラス
    *	@date	2024/05/14
    *	@memo	この関数を使って各ファイルで生成済CD3D11クラスを取得する
    */
    static	CD3D11* GetInstance(void);
    /**	@brief 	クラスインスタンスの削除
    *	@return	CD3D11*	CD3D11クラス
    *	@date	2024/05/14
    */
    void    DestroyInstance(void);
    /**	@brief 	D3D11の初期化
    *   @param  HWND hwnd   windousハンドル
    *   @return HRESULT
    *	@date	2024/05/18
    */
    HRESULT Initialize(HWND hwnd);
    /**	@brief 	全体の解放
    *	@date	2024/05/14
    */
    void    Release();
    //ゲッター関数------------------------------------------------------------------------------

    /**	@brief 	Direct3Dデバイスの取得
    *	@return	CD3D11_Device*
    *	@date	2024/05/16
    */
    ID3D11Device* GetDevice(void);
    /**	@brief  デバイスコンテキストの取得
    *	@return	CD3D11_Device*
    *	@date	2024/05/16
    */
    ID3D11DeviceContext* GetDeviceContext(void);

    /**	@brief 	スワップチェインの取得
    *	@return	CD3D11_SwapChain*
    *	@date	2024/05/16
    */
    IDXGISwapChain* GetSwapChain(void);
    /**	@brief 	レンダーターゲットビューの取得
    *	@return	ID3D11RenderTargetView*
    *	@date	2024/05/16
    */
    ID3D11RenderTargetView* GetRenderTargetView(void);
    /**	@brief 	ビューポートの取得
    *	@return	D3D11_VIEWPORT
    *	@date	2024/05/16
    */
    D3D11_VIEWPORT* GetViewport(void);
    /**	@brief 	深度ステンシルの取得
    *	@return	ID3D11DepthStencilView
    *	@date	2024/05/16
    */
    ID3D11DepthStencilView* GetDepthStencilView(void);

private:
    CD3D11();
    ~CD3D11();

private:
    CD3D11_Device  deviceSetup;                        //グラフィックデバイスの設定
    CD3D11_SwapChain   swapChainSetup;                 //スワップチェインセットアップの設定
    CD3D11_RenderTargetView  renderTargetViewSetup;    //レンダーターゲットビューセットアップの設定
    CD3D11_Viewport    viewportSetup;                  //ビューポートの設定
    CD3D11_DepthStencil    depthStencilSetup;          //深度ステンシルの設定

    static  CD3D11* cd3d11;
};