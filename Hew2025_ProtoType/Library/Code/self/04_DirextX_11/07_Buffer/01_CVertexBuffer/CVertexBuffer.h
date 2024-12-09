#pragma once
#include"../00_CBuffer/CBuffer.h"

#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CVertexBuffer	:public	CBuffer
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/04/29
	*/
	CVertexBuffer();
	/**	@brief 	デストラクタ
	*	@date	2024/04/29
	*/
	~CVertexBuffer();

	/**	@brief 	バッファの作成
	*	@param	const void*	p_SysMem		初期化データへのポインター
	*	@param	UINT	byteWidth			作成する頂点バッファのサイズ
	*	@param	UINT	nothing = NULL		頂点バッファの作成では使わない
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo	
	*/
	HRESULT	Create(const void* p_SysMem, UINT byteWidth, UINT nothing = NULL)override;

	/**	@brief 	入力アセンブラステージに紐づける
	*	@param	UINT	StartSlot	頂点バッファの先頭スロット番号
	*	@param	UINT	NumBuffers	使用する頂点バッファの総数
	*	@param	const	UINT*	p_stride	各頂点バッファのストライドの配列ポインタ
	*	@param	const	UINT*	p_offset	バッファの開始位置から読み込み始めるまでのバイト数のポインタ
	*	@return	void
	*	@date	2024/04/22
	*	@memo
	*/
	void	SetVertexBuffer(UINT	StartSlot, UINT	NumBuffers, const UINT* p_stride, const	UINT* p_offset);
};
