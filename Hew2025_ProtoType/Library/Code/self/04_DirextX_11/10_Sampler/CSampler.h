/**	@file 	CSampler.h
*	@brief 	サンプラークラス
*	@date	2024/05/30
*/
#pragma once
#include"../01_Initialize/CD3D11.h"
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CSampler
{
public:
	CSampler();
	~CSampler();
	/**	@brief 	サンプラーの作成
	*	@param	D3D11_FILTER filter
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressU
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressV
	*	@param	D3D11_TEXTURE_ADDRESS_MODE	addressW
	*	@return HRESULT
	*	@date 2024/05/30
	*/
	HRESULT	Create(D3D11_FILTER filter,
		D3D11_TEXTURE_ADDRESS_MODE	addressU,
		D3D11_TEXTURE_ADDRESS_MODE	addressV,
		D3D11_TEXTURE_ADDRESS_MODE	addressW);
	/**	@brief 	サンプラーを頂点シェーダに渡す
	*	@param	UINT StartSlot		サンプラーのインデックス(デバイスの配列のどこに置くのか)指定
	*	@param	UINT NumSamplers	配列内で使うサンプラー数(デバイスの配列でどのくらいの大きさなのか)
	*	@date 2024/05/30
	*/
	void	SetSamplerVS(UINT StartSlot, UINT NumSamplers);
	/**	@brief 	サンプラーをピクセルシェーダに渡す
	*	@param	UINT StartSlot		サンプラーのインデックス(デバイスの配列のどこに置くのか)指定
	*	@param	UINT NumSamplers	配列内で使うサンプラー数(デバイスの配列でどのくらいの大きさなのか)
	*	@date 2024/05/30
	*/
	void	SetSamplerPS(UINT StartSlot, UINT NumSamplers);
	/**	@brief 	メモリの解放処理
	*	@date 2024/05/30
	*/
	void	Release(void);
private:
	ID3D11SamplerState* p_samplerState;	// サンプラー情報
};