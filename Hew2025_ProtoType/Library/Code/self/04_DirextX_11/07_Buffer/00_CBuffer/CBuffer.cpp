#include"CBuffer.h"

/**	@brief 	コンストラクタ
*	@date	2024/04/29
*/
CBuffer::CBuffer()
{
	this->cd3d11 = CD3D11::GetInstance();
	this->p_buffer = nullptr;
}
/**	@brief 	デストラクタ
*	@date	2024/04/29
*/
CBuffer::~CBuffer()
{
	this->Release();
}
/**	@brief 	解放処理
*	@date	2024/04/29
*/
void	CBuffer::Release(void)
{
	//作成済のとき
	if (this->p_buffer)
	{
		this->p_buffer->Release();
		this->p_buffer = nullptr;
	}
	this->cd3d11 = nullptr;
}

/**	@brief 	バッファ情報のポインタを返す
*	@return	ID3D11Buffer*
*	@date	2024/04/29
*/
ID3D11Buffer* CBuffer::GetBuffer(void)
{
	return	this->p_buffer;
}