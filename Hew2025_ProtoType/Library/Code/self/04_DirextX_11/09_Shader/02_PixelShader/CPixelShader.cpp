#include"CPixelShader.h"
#include"../../01_Initialize/CD3D11.h"
#include"../../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/24
*/

CPixelShader::CPixelShader()
{
	this->p_pixelShader = NULL;
}
/**	@brief 	デストラクタ
*	@date	2024/04/24
*/
CPixelShader::~CPixelShader()
{
	this->Release();
}

/**	@brief 	ピクセルシェーダーの作成
*	@param	ID3D11ClassLinkage* p_classLinkage	クラスリンケージインターフェイスへのポインター
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CPixelShader::Create(ID3D11ClassLinkage* p_classLinkage)
{
	if (!this->p_pixelShader)
	{
		HRESULT hr;
		ID3DBlob* p_vsCode = this->GetShaderFile();	//シェーダーファイルの取得
		//CD3D11クラスの取得
		if (!this->cd3d11)
		{
			this->cd3d11 = CD3D11::GetInstance();
		}
		//デバイスの取得
		ID3D11Device* device = cd3d11->GetDevice();
		//頂点シェーダの生成
		hr = device->CreatePixelShader(
			p_vsCode->GetBufferPointer(),       //コンパイルされたシェーダへのポインタ
			p_vsCode->GetBufferSize(),          //コンパイルされた頂点シェーダーのサイズ
			NULL,                               //クラスリンケージインターフェイスへのポインター
			&this->p_pixelShader				//作成されたID3D11VertexShaderインターフェイスへのポインターのアドレス
		);
		if (FAILED(hr))
		{
			this->Release();
		}
		return  hr;
	}
	return  S_OK;
}

/**	@brief 	頂点ピクセルシェーダーのセット
*	@param	ID3D11ClassInstance* const* pp_classInstances	クラスインスタンス配列のポインタ
*	@param	UINT	numClassInstances	クラスインスタンス配列の数
*	@date	2024/04/24
*/
void	CPixelShader::SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances)
{
	//存在していなければエラー
	if (!this->p_pixelShader)
	{
		// シェーダのエラー内容を表示
		MessageBox(NULL, L"ピクセルシェーダーがありません", L"Shader Error", MB_OK);
		return;
	}
	//CD3D11クラスの取得
	if (!this->cd3d11)
	{
		this->cd3d11 = CD3D11::GetInstance();
	}
	if (this->cd3d11)
	{
		ID3D11DeviceContext* context = cd3d11->GetDeviceContext();						//	デバイスコンテキストの取得		
		context->PSSetShader(this->p_pixelShader, pp_classInstances, numClassInstances);//	頂点シェーダをセット
	}
}

/**	@brief 	頂点ピクセルシェーダーの解放
*	@date	2024/04/24
*/
void	CPixelShader::Release(void)
{
	this->CShader::Release();			// ピクセルシェーダーファイルの解放
	SAFE_RELEASE(this->p_pixelShader);	// ピクセルシェーダーの解放
}
