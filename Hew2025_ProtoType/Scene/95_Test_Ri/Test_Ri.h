﻿/**	@file 	Test_Ri.h
*	@brief 	李用のテストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#pragma once

// インクルード
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/10_Object/Object.h"

#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"


/**	@file	Test_Ri.h
*	@brief 	李用のテストシーンクラス
*	@date	2024/05/21
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Test_Ri :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*	* @date 2024/05/21
	*/
	Test_Ri();
	/**	@brief 	デストラクタ
	*	@date 2024/05/21
	*/
	~Test_Ri()override;
	/**	@brief 	シーン全体の初期化
	*	@date 2024/05/21
	*/
	void	Initialize(void)override;

	/**	@brief 	シーン全体の更新
	*	@date 2024/05/21
	*/
	void	Update(void)override;

	/**	@brief 	シーン全体の描画
	*	@date 2024/05/21
	*/
	void	Draw(void)override;

	/**	@brief 	シーン全体の終了処理
	*	@date 2024/05/21
	*/
	void	Finalize(void)override;

	//テスト用の座標変数
	XMFLOAT2 TestPos = { -200.0f, 0.0f };
	XMFLOAT2 TestPos2 = { 200.0f, 0.0f };
	XMFLOAT2 TestPos3 = { -100.0f, 180.0f };
	//サイズ
	XMFLOAT2 TestSize = { 100.0f,100.0f };
	XMFLOAT2 TestSize2 = { 100.0f,100.0f };
	int state = 0;
	int state2 = 0;
	bool cstate = false;
private:
	Object* p_object;
	/** @brief 二つ目のオブジェクト用
	*   @date  2024/12/11
	*/
	Object* p_object2;
	Object* p_object3;
	Object* p_object4;
	Object* p_player;
	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};