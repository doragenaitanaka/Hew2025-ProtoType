#include"CVertexShader.h"
#include"../../01_Initialize/CD3D11.h"
#include"../../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/24
*/
CVertexShader::CVertexShader()
{
	this->p_vertexShader = NULL;
}
/**	@brief 	デストラクタ
*	@date	2024/04/24
*/
CVertexShader::~CVertexShader()
{
	//頂点シェーダーの解放
	this->Release();
}

/**	@brief 	頂点シェーダーの作成
*	@param	ID3D11ClassLinkage* p_classLinkage	クラスリンケージインターフェイスへのポインター
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CVertexShader::Create(ID3D11ClassLinkage* p_classLinkage)
{
    //生成済の場合は飛ばす
    if (!this->p_vertexShader)
    {
        
        ID3DBlob* p_vsCode = this->GetShaderFile();
        //CD3D11クラスの取得
        if (!this->cd3d11)
        {
            this->cd3d11 = CD3D11::GetInstance();
        }
        //デバイスの取得
        HRESULT hr;
        ID3D11Device* device = cd3d11->GetDevice();
        //頂点シェーダの生成
        hr = device->CreateVertexShader(
            p_vsCode->GetBufferPointer(),       //コンパイルされたシェーダへのポインタ
            p_vsCode->GetBufferSize(),          //コンパイルされた頂点シェーダーのサイズ
            NULL,                               //クラスリンケージインターフェイスへのポインター
            &this->p_vertexShader               //作成されたID3D11VertexShaderインターフェイスへのポインターのアドレス
        );
        if (FAILED(hr))
        {
            this->Release();
        }
        return  hr;
    }
    return  S_OK;
}

/**	@brief 	頂点シェーダーのセット
*	@param	ID3D11ClassInstance* const* pp_classInstances	クラスインスタンス配列のポインタ
*	@param	UINT	numClassInstances	クラスインスタンス配列の数
*	@date	2024/04/24
*/
void	CVertexShader::SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances)
{
    //存在していなければエラー
    if (!this->p_vertexShader)
    {
        // シェーダのエラー内容を表示
        MessageBox(NULL, L"頂点シェーダーがありません", L"Shader Error", MB_OK);
        return;
    }
    //CD3D11クラスの取得
    if (!this->cd3d11)
    {
        this->cd3d11 = CD3D11::GetInstance();
    }
    if (this->cd3d11)
    {
        ID3D11DeviceContext* context = cd3d11->GetDeviceContext();						    //	デバイスコンテキストの取得		
        context->VSSetShader(this->p_vertexShader, pp_classInstances, numClassInstances);   //   頂点シェーダをセット
    }
}

/**	@brief 	頂点シェーダーの解放
*	@date	2024/04/24
*/
void	CVertexShader::Release(void)
{
	this->CShader::Release();	        // 頂点シェーダーファイルの解放
    SAFE_RELEASE(this->p_vertexShader);	// 頂点シェーダの解放
}
