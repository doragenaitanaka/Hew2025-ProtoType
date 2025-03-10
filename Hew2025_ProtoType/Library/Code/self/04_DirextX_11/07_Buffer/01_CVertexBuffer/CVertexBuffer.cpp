﻿#include"CVertexBuffer.h"
#include"../../01_Initialize/CD3D11.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/29
*/
CVertexBuffer::CVertexBuffer()
{
}
/**	@brief 	デストラクタ
*	@date	2024/04/29
*/
CVertexBuffer::~CVertexBuffer()
{
	this->Release();
}

/**	@brief 	バッファの作成
*	@param	const void*	p_SysMem		初期化データへのポインター
*	@param	UINT	byteWidth			//頂点バッファのサイズ
*	@param	UINT	nothing = NULL		//頂点バッファの作成では使わない
*	@return	HRESULT
*	@date	2024/05/23
*	@memo
*/
HRESULT CVertexBuffer::Create(const void* p_SysMem, UINT byteWidth, UINT nothing, D3D11_USAGE _usage, UINT _cpuAccessFlags)
{
    // 頂点バッファの設定
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.Usage = _usage;
    vbDesc.ByteWidth = byteWidth;
    vbDesc.MiscFlags = 0;
    vbDesc.StructureByteStride = 0;
    vbDesc.CPUAccessFlags = _cpuAccessFlags;

    // デバイスの取得
    ID3D11Device* device = this->cd3d11->GetDevice();
    // エラーハンドリング
    if (!device) { return E_FAIL; }

    // 頂点バッファがなければ
    if (!this->p_buffer)
    {
        // 書き込むデータ
        D3D11_SUBRESOURCE_DATA initData = { p_SysMem, 0, 0 };

        // 頂点バッファの作成
         HRESULT hr = device->CreateBuffer(&vbDesc, &initData, &this->p_buffer);
        
        if (FAILED(hr))
        {
            // メモリの解放
            this->Release();
            return hr;
        }
    }
    return S_OK;
}

/**	@brief 	入力アセンブラステージに紐づける
*	@param	UINT	StartSlot	頂点バッファの先頭スロット番号
*	@param	UINT	NumBuffers	使用する頂点バッファの総数
*	@param	const	UINT*	p_stride	各頂点バッファのストライドの配列ポインタ
*	@param	const	UINT*	p_offset	バッファの開始位置から読み込み始めるまでのバイト数のポインタ
*	@return	void
*	@date	2024/04/29
*/
void	CVertexBuffer::SetVertexBuffer(UINT	StartSlot, UINT	NumBuffers, const UINT* p_stride, const	UINT* p_offset)
{
	//頂点バッファあるとき
	if (this->p_buffer)
	{
		if (this->cd3d11)
		{
			ID3D11DeviceContext* context = cd3d11->GetDeviceContext();									//	デバイスコンテキストの取得		
			context->IASetVertexBuffers(StartSlot, NumBuffers, &this->p_buffer, p_stride, p_offset);	//	入力アセンブラステージに紐づけ
		}
	}
}