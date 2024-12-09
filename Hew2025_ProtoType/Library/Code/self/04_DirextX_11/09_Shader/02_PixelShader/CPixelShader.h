#pragma once
#include"../00_CShader/CShader.h"
//D3Dに必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CPixelShader	:public	CShader
{
public:
	//コンストラクタ
	CPixelShader();
	//デストラクタ
	~CPixelShader();

	/**	@brief 	ピクセルシェーダーの作成
	*	@param	ID3D11ClassLinkage* p_classLinkage	クラスリンケージインターフェイスへのポインター
	*	@return	HRESULT
	*	@date	2024/04/24
	*/
	HRESULT	Create(ID3D11ClassLinkage* p_classLinkage);

	/**	@brief 	頂点ピクセルシェーダーのセット
	*	@param	ID3D11ClassInstance* const* pp_classInstances	クラスインスタンス配列のポインタ
	*	@param	UINT	numClassInstances	クラスインスタンス配列の数
	*	@date	2024/04/24
	*/
	void	SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances);


	/**	@brief 	頂点ピクセルシェーダーの解放
	*	@date	2024/04/24
	*/
	void	Release(void);

private:
	ID3D11PixelShader* p_pixelShader;	//ピクセルシェーダー
};