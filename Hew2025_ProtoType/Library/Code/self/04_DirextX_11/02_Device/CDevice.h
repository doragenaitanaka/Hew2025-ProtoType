#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_Device
{
public:
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/
	CD3D11_Device();
	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~CD3D11_Device();
	/**	@brief 	グラフィックデバイスの初期化
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(void);
	/**	@brief 	解放処理
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11Device* m_pDevice;                        //Direct3Dデバイス
	ID3D11DeviceContext* m_pImmediateContext;       //デバイスコンテキスト
};
