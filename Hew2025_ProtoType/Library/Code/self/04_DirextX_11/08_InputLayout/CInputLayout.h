#pragma once
//D3Dに必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../01_Initialize/CD3D11.h"

class CInputLayout
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/04/23
	*/
	CInputLayout();
	/**	@brief 	デストラクタ
	*	@date	2024/04/23
	*/
	~CInputLayout();

	/**	@brief 	入力レイアウトの作成
	*	@param	D3D11_INPUT_ELEMENT_DESC*	layout		頂点データポインタ
	*	@param	UINT numElements	要素数サイズ
	*	@param	ID3DBlob*	p_vsBlob	シェーダファイルポインタ
	*	@return	HRESULT
	*	@date	2024/04/23
	*/
	HRESULT	Create(D3D11_INPUT_ELEMENT_DESC* p_layout, UINT numElements, ID3DBlob* p_vsBlob);

	/**	@brief 	入力アセンブラに紐づけ
	*	@date	2024/04/23
	*/
	void	SetInputLayout(void);

	/**	@brief 	解放処理
	*	@date	2024/04/23
	*/
	void	Release(void);
private:
	ID3D11InputLayout* p_inputLayout;	//入力レイアウト
	CD3D11* cd3d11;
};
