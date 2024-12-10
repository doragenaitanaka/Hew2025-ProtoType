#include"CSampler.h"
#include"../01_Initialize/CD3D11.h"
CSampler::CSampler()
{
    this->p_samplerState = nullptr;
}

CSampler::~CSampler()
{
    this->Release();
}

/**	@brief 	サンプラーの作成
*	@param	D3D11_FILTER filter
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressU
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressV
*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressW
*	@return HRESULT
*	@date 2024/05/30
*   @memo   テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
*/
HRESULT	CSampler::Create(D3D11_FILTER filter,
	D3D11_TEXTURE_ADDRESS_MODE	addressU,
	D3D11_TEXTURE_ADDRESS_MODE	addressV,
	D3D11_TEXTURE_ADDRESS_MODE	addressW)
{
    // →テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
    D3D11_SAMPLER_DESC	smpDesc;
    ::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
    smpDesc.Filter = filter;
    smpDesc.AddressU = addressU;
    smpDesc.AddressV = addressV;
    smpDesc.AddressW = addressW;

    // デバイスの取得
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11Device* p_device = p_cd3d11->GetDevice();    
    // サンプラーを作成
    HRESULT hr;
    hr = p_device->CreateSamplerState(&smpDesc, &this->p_samplerState);
    if (FAILED(hr)) { return  hr; }
    return  hr;
}
/**	@brief 	サンプラーを頂点シェーダに渡す
*	@param	UINT StartSlot		サンプラーのインデックス(デバイスの配列のどこに置くのか)指定
*	@param	UINT NumSamplers	配列内で使うサンプラー数(デバイスの配列でどのくらいの大きさなのか)
*	@date 2024/05/30
*/
void	CSampler::SetSamplerVS(UINT StartSlot, UINT NumSamplers)
{
    // 無ければ戻る
    if (!this->p_samplerState) { return; }

    // デバイスコンテキストの取得
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* p_deviceContext = p_cd3d11->GetDeviceContext();
    // サンプラーを頂点シェーダにセット
    p_deviceContext->VSSetSamplers(StartSlot, NumSamplers, &this->p_samplerState);
}

/**	@brief 	サンプラーをピクセルシェーダに渡す
*	@param	UINT StartSlot		サンプラーのインデックス(デバイスの配列のどこに置くのか)指定
*	@param	UINT NumSamplers	配列内で使うサンプラー数(デバイスの配列でどのくらいの大きさなのか)
*	@date 2024/05/30
*/
void	CSampler::SetSamplerPS(UINT StartSlot, UINT NumSamplers)
{
    // 無ければ戻る
    if (!this->p_samplerState) { return; }

    // デバイスコンテキストの取得
    CD3D11* p_cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* p_deviceContext = p_cd3d11->GetDeviceContext();
    // サンプラーをピクセルシェーダにセット
    p_deviceContext->PSSetSamplers(StartSlot, NumSamplers, &this->p_samplerState);
}

/**	@brief 	メモリの解放処理
*	@date 2024/05/30
*/
void	CSampler::Release(void)
{
    if (this->p_samplerState) { this->p_samplerState->Release(); }
}