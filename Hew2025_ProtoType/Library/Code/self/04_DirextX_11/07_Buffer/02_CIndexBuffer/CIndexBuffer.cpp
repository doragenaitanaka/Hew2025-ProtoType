#include"CIndexBuffer.h"
#include"../../01_Initialize/CD3D11.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

//コンストラクタ
CIndexBuffer::CIndexBuffer()
{
}
//デストラクタ
CIndexBuffer::~CIndexBuffer()
{
	this->Release();
}
/**	@brief 	バッファの作成
*	@param	const void*	p_SysMem		初期化データへのポインター
*	@param	UINT	byteWidth			作成するインデックスバッファのバイトサイズ
*	@param	UINT	nothing = NULL		頂点インデックスバッファの作成では使わない
*	@return	HRESULT
*	@date	2024/05/23
*	@memo
*/
HRESULT	CIndexBuffer::Create(const void* p_SysMem, UINT byteWidth, UINT nothing, D3D11_USAGE _usage, UINT _cpuAccessFlags)
{
	// インデックスバッファの設定
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;	    //  デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
	ibDesc.Usage = _usage;							//  作成するバッファの使用法
	ibDesc.ByteWidth = byteWidth;					//  作成するバッファのバイトサイズ
	ibDesc.MiscFlags = 0;							//  その他のフラグ
	ibDesc.StructureByteStride = 0;		            //  構造化バッファの場合、その構造体のサイズ
	ibDesc.CPUAccessFlags = _cpuAccessFlags;


	//インデックスバッファが無ければ
	if (!this->p_buffer)
	{
		//CD3D11クラスの取得
		if (!this->cd3d11)
		{
			this->cd3d11 = CD3D11::GetInstance();
		}
		//書き込むデータ
		D3D11_SUBRESOURCE_DATA initData = { p_SysMem, 0, 0 };	//	1Dリソースの初期化時は2,3個目のやつ使わない（0をいれる）
		HRESULT	hr;
		ID3D11Device* device = this->cd3d11->GetDevice();				//	デバイスの取得
		hr = device->CreateBuffer(&ibDesc, &initData, &this->p_buffer);	// インデックスバッファの作成
		if (FAILED(hr))
		{
			//メモリの解放
			if (this->p_buffer)
			{
				this->Release();
			}
		}
		return	hr;
	}
	return	S_OK;
}

/**	@brief 	入力アセンブラステージに紐づける
*	@param	DXGI_FORMAT	format	インデックスの形式
*	@param	UINT	ofset	バイト単位オフセット
*	@return	void
*	@date	2024/04/29
*	@memo
*/
void	CIndexBuffer::SetIndexBuffer(DXGI_FORMAT	format, UINT	ofset)
{
	//バッファ情報ポインタのアドレスを取得
	ID3D11Buffer** p_indexBuffer = this->GetBuffer();
	//インデックスバッファがあるとき
	if (this->p_buffer)
	{
		ID3D11DeviceContext* deviceContext = this->cd3d11->GetDeviceContext();	//デバイスコンテキストを取得
		deviceContext->IASetIndexBuffer(this->p_buffer, format, ofset);			//入力アセンブラステージに紐づけ
	}
}