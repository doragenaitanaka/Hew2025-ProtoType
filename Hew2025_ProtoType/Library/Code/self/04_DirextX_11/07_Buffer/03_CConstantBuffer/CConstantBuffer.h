#pragma once
#include"../00_CBuffer/CBuffer.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include<DirectXMath.h> //  DirectX::XMFLOAT3に必要
using   namespace DirectX;

class CConstantBuffer :public	CBuffer
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/05/24
	*/
	CConstantBuffer();
	/**	@brief 	デストラクタ
	*	@date	2024/05/24
	*/
	~CConstantBuffer();

	/**	@brief 	バッファの作成
	*	@param	const void*	p_SysMem		初期化データへのポインター
	*	@param	UINT	byteWidth			//コンスタントバッファのサイズ
	*	@param	UINT	nothing = NULL		//コンスタントバッファの作成では使わない
	*	@return	HRESULT
	*	@date	2024/05/24
	*/
	HRESULT	Create(const void* p_SysMem, UINT	byteWidth, UINT	nothing = NULL)override;

	/**	@brief 	バッファの更新
	*	@param	_In_  const void* pSrcData 反映データ
	*	@date	2024/05/24
	*/
	void	Update(_In_  const void* pSrcData);

	/**	@brief	使用するコンスタントバッファを設定
	*	@date	2024/05/24
	*/
	void	SetConstantBuffer(void);
};