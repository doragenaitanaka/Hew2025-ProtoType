/**	@file 	Test_Ueda.h
*	@brief 	植田用のテストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#pragma once

// インクルード
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../Library/Code/self/13_Seesaw/Seesaw.h"
#include"../../Library/Code/self/16_Pen/Pen.h"

#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"


/**	@file	Test_Uryu.h
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

	//テスト用の座標変数
	XMFLOAT2 TestPos = { -200.0f, 0.0f };
	XMFLOAT2 TestPos2 = { 100.0f, -100.0f };
	XMFLOAT2 TestPos3 = { 200.0f, -100.0f };
	XMFLOAT2 TestPos4 = { 330.0f, -100.0f };
	XMFLOAT2 TestPos5 = { 200.0f, 0.0f };
	XMFLOAT2 TestPos6 = { 330.0f, 0.0f };
	//サイズ
	XMFLOAT2 TestSize = { 100.0f,100.0f };
	XMFLOAT2 TestSize2 = { 50.0f,200.0f };
	XMFLOAT2 TestSize3 = { 130.0f,100.0f };
	XMFLOAT2 TestSize4 = { 130.0f,100.0f };
	XMFLOAT2 TestSize5 = { 130.0f,100.0f };
	XMFLOAT2 TestSize6 = { 130.0f,100.0f };

	bool TestMoveFlg = true;
	bool TestProcessing = false;
	bool GravityFlg = true;
	bool TouchFlg = false;
	bool BoundFlg = false;
	bool OneBoundFlg = true;
	int TestMoveCnt = 0;
	int TestPenState = 0;
	int TestCnt = 0;
	float MoveSpeed = 20.0f;
	float PenAngle = 0.0f;
	float speed = 10.0f;
	float deltaTime = 1.0f;

	Vector2 PenPos = { TestPos2.x,TestPos2.y };

	
private:
	Object* p_TestObject;

	Object* p_TestObject2;

	Object* p_TestObject3;

	Object* p_TestObject4;

	Object* p_TestObject5;

	Object* p_TestObject6;


	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};