#include"CInputLayout.h"
#include"../../SafePointers.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/23
*/
CInputLayout::CInputLayout()
{
    this->p_inputLayout = NULL;
}
/**	@brief 	デストラクタ
*	@date	2024/04/23
*/
CInputLayout::~CInputLayout()
{
	this->Release();
}

/**	@brief 	入力レイアウトの作成
*	@param	D3D11_INPUT_ELEMENT_DESC*	layout	頂点データポインタ
*	@param	UINT numElements	                要素数サイズ
*	@param	ID3DBlob*	p_vsBlob	            シェーダファイルポインタ
*	@return	HRESULT
*	@date	2024/04/23
*/
HRESULT	CInputLayout::Create(D3D11_INPUT_ELEMENT_DESC*	p_layout, UINT numElements, ID3DBlob* p_vsBlob)
{
    if (!this->p_inputLayout)
    {
        // 頂点シェーダーのバイトコードを取得
        LPVOID pShaderBytecode = p_vsBlob->GetBufferPointer();
        SIZE_T bytecodeLength = p_vsBlob->GetBufferSize();


        HRESULT hr;
        //CD3D11クラスの取得
        if (!this->cd3d11)
        {
            this->cd3d11 = CD3D11::GetInstance();
        }
        //デバイスの取得
        ID3D11Device* device = cd3d11->GetDevice();
        // 入力レイアウトの作成
        hr = device->CreateInputLayout(
            p_layout,               //入力要素記述子の配列へのポインター
            numElements,            //配列内の要素の数
            pShaderBytecode,        //コンパイルされたシェーダーのバイトコードへのポインター
            bytecodeLength,         //コンパイルされたシェーダーのバイトコードのサイズ
            &this->p_inputLayout    //作成された入力レイアウトオブジェクトへのポインターを受け取るための二重ポインター
        );
        if (FAILED(hr))
        {
            this->Release();
        }
        return  hr;
    }
    return  S_OK;
}

/**	@brief 	入力アセンブラに紐づけ
*	@date	2024/04/23
*/
void	CInputLayout::SetInputLayout(void)
{
    if (this->p_inputLayout)
    {
        if (this->cd3d11)
        {
            ID3D11DeviceContext* context = cd3d11->GetDeviceContext();	//	デバイスコンテキストの取得		
            context->IASetInputLayout(this->p_inputLayout);             //  入力レイアウトの設定
        }
    }
}

/**	@brief 	解放処理
*	@date	2024/04/23
*/
void	CInputLayout::Release(void)
{
    SAFE_RELEASE(this->p_inputLayout);
    this->cd3d11 = nullptr;
}