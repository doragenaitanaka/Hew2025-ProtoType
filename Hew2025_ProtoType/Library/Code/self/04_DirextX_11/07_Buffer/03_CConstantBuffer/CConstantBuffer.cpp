#include"CConstantBuffer.h"
#include<iostream>
/**	@brief 	コンストラクタ
*	@date	2024/05/24
*/
CConstantBuffer::CConstantBuffer()
{
}
/**	@brief 	デストラクタ
*	@date	2024/05/24
*/
CConstantBuffer::~CConstantBuffer()
{
	this->Release();
}

/**	@brief 	バッファの作成
*	@param	const void*	p_SysMem		//初期化データへのポインター(ここでは使わないのでNULLを入れる)
*	@param	UINT	byteWidth			//コンスタントバッファのサイズ
*	@param	UINT	nothing = NULL		//コンスタントバッファの作成では使わない
*	@return	HRESULT
*	@date	2024/05/24
*/
HRESULT CConstantBuffer::Create(const void* p_SysMem, UINT  byteWidth, UINT nothing, D3D11_USAGE _usage, UINT _cpuAccessFlags)
{
    //バッファの作成
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = byteWidth;
    cbDesc.Usage = _usage;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = _cpuAccessFlags;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    //バッファ情報を取得
    ID3D11Device* device = cd3d11->GetDevice();
    if (!device) { std::cerr << "deviceがnullptrです。" << std::endl; }
    if (!this->p_buffer)
    {
        HRESULT hr = device->CreateBuffer(&cbDesc, NULL, &this->p_buffer);
        if (FAILED(hr))
        {
            this->Release();
            return hr;
        }
    }
    return S_OK;
}

/**	@brief 	バッファの更新
*	@param	_In_  const void* pSrcData 反映データ
*	@date	2024/05/24
*/
void CConstantBuffer::Update(_In_  const void* pSrcData)
{
    if (this->cd3d11 && this->p_buffer)
    {
        ID3D11DeviceContext* context = this->cd3d11->GetDeviceContext();
        context->UpdateSubresource(this->p_buffer, 0, NULL, pSrcData, 0, 0);
    }
}

/**	@brief	使用するコンスタントバッファを設定
*	@date	2024/05/24
*/
void	CConstantBuffer::SetConstantBuffer(void)
{
	//コンスタントバッファがあるとき
	if (this->p_buffer)
	{
		if (this->cd3d11)
		{
			ID3D11DeviceContext* context = cd3d11->GetDeviceContext();	// デバイスコンテキストの取得
			context->VSSetConstantBuffers(0, 1, &this->p_buffer);		// コンスタントバッファを設定
		}
	}
}