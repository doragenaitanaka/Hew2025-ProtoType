#pragma once
#include"../00_CBuffer/CBuffer.h"

class CIndexBuffer	:protected	CBuffer
{
public:
	//コンストラクタ
	CIndexBuffer();
	//デストラクタ
	~CIndexBuffer();

	/**	@brief 	バッファの作成
	*	@param	const void*	p_SysMem		初期化データへのポインター
	*	@param	UINT	byteWidth			作成するインデックスバッファのサイズ
	*	@param	UINT	nothing = NULL		頂点インデックスバッファの作成では使わない
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo
	*/
	HRESULT	Create(const void* p_SysMem, UINT byteWidth, UINT nothing = NULL, D3D11_USAGE _usage = D3D11_USAGE_DEFAULT, UINT _cpuAccessFlags = 0)override;

	/**	@brief 	入力アセンブラステージに紐づける
	*	@param	DXGI_FORMAT	format	インデックスの形式
	*	@param	UINT	ofset	バイト単位オフセット
	*	@return	void
	*	@date	2024/04/29
	*	@memo
	*/
	void	SetIndexBuffer(DXGI_FORMAT	format, UINT	ofset);
};
