#include"CDevice.h"
#include"../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
CD3D11_Device::CD3D11_Device()
{
    this->m_pDevice = nullptr;
    this->m_pImmediateContext = nullptr;
}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
CD3D11_Device::~CD3D11_Device()
{
    this->Release();
}

/**	@brief 	グラフィックデバイスの初期化
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_Device::Create(void)
{
    HRESULT  hr;
    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    //デバイスの指定
    D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL level;

    //グラフィックデバイスの初期化
    hr = D3D11CreateDevice(NULL,        //デバイスの作成に使用するビデオアダプターへのポインター
        D3D_DRIVER_TYPE_HARDWARE,       //作成するドライバーの種類
        NULL,                           // ソフトウェアラスタライザーを実装するDLLへのハンドル
        flags,                          //ランタイムレイヤーを有効にするためのフラグ
        pLevels,                        //作成しようとする特徴レベルの順序を決定するD3D_FEATURE_LEVELの配列へのポインター
        1,                              //pFeatureLevels内の要素の数
        D3D11_SDK_VERSION,              //SDKのバージョン
        &this->m_pDevice,               //作成されたデバイスを表すID3D11Deviceオブジェクトへのポインターのアドレスを返す
        &level,                         //成功した場合、成功したpFeatureLevels配列から最初のD3D_FEATURE_LEVELを返す
        &this->m_pImmediateContext);    //デバイスコンテキストを表すID3D11DeviceContextオブジェクトへのポインターのアドレスを返す

    //成功したかチェック
    if (FAILED(hr)) { return hr; }
}
/**	@brief 	解放処理
*	@date 2024/03/29
*/
void    CD3D11_Device::Release()
{
    if (this->m_pImmediateContext) {
        this->m_pImmediateContext->ClearState();
    }
    SAFE_RELEASE(this->m_pImmediateContext);
    SAFE_RELEASE(this->m_pDevice);
}