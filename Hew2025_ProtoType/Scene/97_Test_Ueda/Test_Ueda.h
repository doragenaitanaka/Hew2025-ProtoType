﻿/**	@file 	Test_Ueda.h
*	@brief 	植田用のテストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#pragma once

// インクルード
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include"../../Library/Code/self/14_Ball/Ball.h"
#include"../../Library/Code/self/15_Pendulum/Pendulum.h"
#include"../../Library/Code/self/17_FallObject/FallObject.h"
#include"../../Library/Code/self/07_Camera/Camera.h"
#include<iostream>


/**	@file	Test_Ueda.h
*	@brief 	植田用のテストシーンクラス
*	@date	2024/05/21
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Test_Ueda :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*	* @date 2024/05/21
	*/
	Test_Ueda();
	/**	@brief 	デストラクタ
	*	@date 2024/05/21
	*/
	~Test_Ueda()override;
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

	// 変数の定義
	int flame = 0;
	float power = 0;
	float gravity = 0.1f; // 重力の強さ
	float velocityY = 0.0f; // Y方向の速度（初期速度は0）
	float maxVelocityY = 10.0f; // 最大速度（任意設定）
	float f_objangle = 0.0f; // オブジェクトの角度
	

	//テスト用の座標変数
	XMFLOAT2 TestPos = { -200.0f, 0.0f };
	XMFLOAT2 TestPos2 = { 400.0f, 0.0f };

	//サイズ
	XMFLOAT2 TestSize = { 100.0f,100.0f };
	XMFLOAT2 TestSize2 = { 100.0f,600.0f };

private:
	Input input;
	Object* p_object;
    FallObject* p_fallobject;
	Ball* ball;
	Pendulum* pendulum; // 振り子オブジェクト
	
	Camera* p_camera;
	

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};