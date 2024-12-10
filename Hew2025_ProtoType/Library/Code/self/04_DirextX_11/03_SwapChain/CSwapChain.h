#pragma once
//D3D初期化に必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_SwapChain
{
public:
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/
	CD3D11_SwapChain();

	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~CD3D11_SwapChain();

	/**	@brief 	レンダーターゲットビューの作成
	*	@param	ID3D11Device* p_Device Direct3Dデバイス
	*   @param  HWND hwnd              windowsハンドル
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	virtual	HRESULT    Create(HWND hwnd, ID3D11Device* m_pDevice);
	/**	@brief 	解放処理
	*	@date 2024/03/29
	*/
	void    Release();
public:
	IDXGISwapChain* m_pSwapChain;                   //スワップチェーン
	IDXGIFactory* pFactory;                         //DXGIファクトリ
};

