﻿/**	@file 	Test_Uryu.h
*	@brief 	瓜生用のテストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#pragma once

// インクルード
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../Library/Code/self/13_Seesaw/Seesaw.h"

#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"

/**	@file	Test_Uryu.h
*	@brief 	瓜生用のテストシーンクラス
*	@date	2024/05/21
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Test_Uryu :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*	* @date 2024/05/21
	*/
	Test_Uryu();
	/**	@brief 	デストラクタ
	*	@date 2024/05/21
	*/
	~Test_Uryu()override;
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
	XMFLOAT2 TestPos2 = { 200.0f, -50.0f };
	XMFLOAT2 TestPos3 = { 200.0f, 1000.0f };
	XMFLOAT2 TestPos4 = { -200.0f, -50.0f };
	XMFLOAT2 TestPos5 = { 0.0f, -50.0f };
	//サイズ
	XMFLOAT2 TestSize = { 100.0f,100.0f };
	XMFLOAT2 TestSize2 = { 125.0f,125.0f };
	XMFLOAT2 TestSize3 = { 125.0f,125.0f };
	XMFLOAT2 TestSize4 = { 125.0f,125.0f };
	XMFLOAT2 TestSize5 = { 500.0f,50.0f };
	
	bool TestMoveFlg = true;
	bool TestProcessing = false;
	bool GravityFlg = true;
	bool TouchFlg = false;
	bool SeesawMoveFlg = false;
	bool SeesawDirection = false; //falseなら左が下がる、trueなら右が下がる
	bool PlayerOnSeesawL = false; //シーソーの左に乗っているか
	bool PlayerOnSeesawR = false; //シーソーの右に乗っているか
	bool BoundFlg = false;
	bool OneBoundFlg = true;
	int TestMoveCnt = 0;
	int TestGrabState = 0;
	int TestCnt = 0;
	float MoveSpeed = 20.0f;
private:
	Object* p_TestObject;
	/** @brief 二つ目のオブジェクト/シーソーのオブジェクトが乗るほう
	*   @date  2024/12/11
	*/
	Object* p_TestObject2;
	/** @brief 三つ目のオブジェクト/シーソーに乗せるオブジェクト
	*	@date  2024/12/21
	*/
	Object* p_TestObject3;
	/** @brief 四つ目のオブジェクト/シーソーのプレイヤーが乗るほう
	*	@date  2024/12/26
	*/
	Object* p_TestObject4;
	/** @brief 五つ目のオブジェクト/シーソーの見た目を繋ぐ用
	*	@date  2024/12/27
	*/
	Object* p_TestObject5;
	/** @brief シーソーのインスタンス
*	@date  2024/12/27
*/
	Seesaw* seesaw;
	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};