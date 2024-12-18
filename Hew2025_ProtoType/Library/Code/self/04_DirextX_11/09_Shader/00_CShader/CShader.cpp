#include"CShader.h"
#include"../../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/24
*/
CShader::CShader()
{
	this->p_blob = nullptr;
	this->cd3d11 = nullptr;
}
/**	@brief 	デストラクタ
*	@date	2024/04/24
*/
CShader::~CShader()
{
	this->Release();
}

/**	@brief 	シェーダーファイルのコンパイル
*	@param	LPCWSTR	fileName				ファイルの名前
*	@param	D3D_SHADER_MACRO* p_defines		シェーダーマクロを定義するD3D_SHADER_MACRO構造体の配列へのオプショナルなポインター
*	@param	ID3DInclude* p_nclude			コンパイラがインクルードファイルの処理に使用するポインター
*	@param	LPCSTR	p_entrypoint			シェーダーの実行が開始されるシェーダーエントリポイント名
*	@param	LPCSTR	p_target				コンパイル対象のシェーダーターゲットまたはシェーダー機能のセットを指定
* 	@param	UINT	flags_1					シェーダーコンパイルオプションの組み合わせ
* 	@param	UINT	flags_2					効果コンパイルオプションの組み合わせ
*	@return	HRESULT
*	@date	2024/04/24
*/
HRESULT	CShader::CompileFromFile(
    LPCWSTR	fileName,
    D3D_SHADER_MACRO* p_defines,
    ID3DInclude* p_nclude,
    LPCSTR	p_entrypoint,
    LPCSTR	p_target,
    UINT	flags_1,
    UINT	flags_2
)
{
	if (!this->p_blob)
	{
		HRESULT hr;
		ID3DBlob* p_errorMsg;
		//コンパイル
		hr = D3DCompileFromFile(
			fileName,                   //ファイルの名前
			p_defines,                  //シェーダーマクロを定義するD3D_SHADER_MACRO構造体の配列へのオプショナルなポインター
			p_nclude,                   //コンパイラがインクルードファイルの処理に使用するポインター
			p_entrypoint,               //シェーダーの実行が開始されるシェーダーエントリポイント名
			p_target,                   //コンパイル対象のシェーダーターゲットまたはシェーダー機能のセットを指定
			flags_1,                    //シェーダーコンパイルオプションの組み合わせ
			flags_2,                    //効果コンパイルオプションの組み合わせ
			&this->p_blob,              //コンパイル済みコードへのアクセスに使用できるポインターアドレス
			&p_errorMsg                 //コンパイラエラーメッセージへのアクセスに使用
		);
		if (FAILED(hr))
		{
			// シェーダのエラー内容を表示
			MessageBox(NULL, (wchar_t*)p_errorMsg->GetBufferPointer(), L"Compile Error", MB_OK);
			//メモリの解放
			SAFE_RELEASE(this->p_blob);
			SAFE_RELEASE(p_errorMsg);
		}
		return  hr;
	}
	return  S_OK;
}

/**	@brief 	シェーダーファイルの取得
*	@return	ID3DBlob*	シェーダーファイル
*	@date	2024/04/24
*/
ID3DBlob* CShader::GetShaderFile(void)
{
	return	this->p_blob;
}

/**	@brief 	解放処理
*	@date	2024/04/24
*/
void	CShader::Release(void)
{
	SAFE_RELEASE(this->p_blob);
}
