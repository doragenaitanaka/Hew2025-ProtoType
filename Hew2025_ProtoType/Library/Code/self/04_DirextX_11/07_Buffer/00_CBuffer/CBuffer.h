#pragma once
//D3Dに必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../../01_Initialize/CD3D11.h"

class CBuffer
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/04/29
	*/
	CBuffer();
	/**	@brief 	デストラクタ
	*	@date	2024/04/29
	*/
	~CBuffer();

	/**	@brief 	バッファの作成
	*	@param	const void*	p_SysMem		初期化データへのポインター
	*	@param	UINT
	*	@param	UINT
	*	@return	HRESULT
	*	@date	2024/05/23
	*	@memo	第二引数、第三引数は継承先によって役割が変わるので変数名決めないでおく
	*/
	virtual	HRESULT	Create(const void* p_SysMem, UINT, UINT, D3D11_USAGE _usage = D3D11_USAGE_DEFAULT, UINT _cpuAccessFlags = 0) = 0;

	/**	@brief 	バッファ情報のポインタアドレスを返す
	*	@return	ID3D11Buffer**
	*	@date	2024/04/29
	*/
	ID3D11Buffer** GetBuffer(void);

	/**	@brief 	解放処理
	*	@date	2024/04/29
	*/
	void	Release(void);

protected:
	ID3D11Buffer* p_buffer;	//バッファ
	CD3D11* cd3d11;         //CD3D11クラス
};