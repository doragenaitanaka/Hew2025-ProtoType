#pragma once
#include <d3dcompiler.h>				// シェーダコンパイル周りの機能をインクルード
#pragma comment(lib, "d3dcompiler.lib")	// シェーダコンパイル用の静的ライブラリをリンク
//D3Dに必要なの
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>
#include"../../01_Initialize/CD3D11.h"

//シェーダファイルのオンラインコンパイルをする設計
//オフラインでもできるようにしようと思ったらファイル読み込んだのを入れる為のSetCompileFile関数的なの…？

class CShader
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/04/24
	*/
	CShader();
	/**	@brief 	デストラクタ
	*	@date	2024/04/24
	*/
	~CShader();

	/**	@brief 	シェーダーファイルのコンパイル
	*	@param	LPCWSTR	fileName				ファイルの名前
	*	@param	D3D_SHADER_MACRO* p_defines		シェーダーマクロを定義するD3D_SHADER_MACRO構造体の配列へのオプショナルなポインター
	*	@param	ID3DInclude* p_nclude			コンパイラがインクルードファイルの処理に使用するポインター
	*	@param	LPCSTR	p_entrypoint			シェーダーの実行が開始されるシェーダーエントリポイント名
	*	@param	LPCSTR	p_target				コンパイル対象のシェーダーターゲットまたはシェーダー機能のセットを指定
	* 	@param	UINT	flags_1					シェーダーコンパイルオプションの組み合わせ
	* 	@param	UINT	flags_2					効果コンパイルオプションの組み合わせ
	*	@return	HRESULT
	*	@date	2024/04/24
	*/
	HRESULT	CompileFromFile(
		LPCWSTR	fileName,				
		D3D_SHADER_MACRO* p_defines,
		ID3DInclude* p_nclude,
		LPCSTR	p_entrypoint,
		LPCSTR	p_target,
		UINT	flags_1,
		UINT	flags_2
	);
	/**	@brief 	シェーダーファイルの取得
	*	@return	ID3DBlob*	シェーダーファイル
	*	@date	2024/04/24
	*/
	ID3DBlob* GetShaderFile(void);

	/**	@brief 	解放処理
	*	@date	2024/04/24
	*/
	virtual	void	Release(void);
	/**	@brief 	シェーダーの作成
	*	@param	ID3D11ClassLinkage* p_classLinkage	クラスリンケージインターフェイスへのポインター
	*	@return	HRESULT
	*	@date	2024/04/24
	*/
	virtual	HRESULT	Create(ID3D11ClassLinkage* p_classLinkage) = 0;
	/**	@brief 	シェーダーのセット
	*	@param	ID3D11ClassInstance* const* pp_classInstances	クラスインスタンス配列のポインタ
	*	@param	UINT	numClassInstances	クラスインスタンス配列の数
	*	@date	2024/04/24
	*/
	virtual	void	SetShader(ID3D11ClassInstance* const* pp_classInstances, UINT	numClassInstances) = 0;
private:
	ID3DBlob* p_blob;	//シェーダーファイル
protected:
	CD3D11* cd3d11;         //CD3D11クラス
};