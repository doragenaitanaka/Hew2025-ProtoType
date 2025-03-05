/**	@file 	SplashScreanScene.h
*	@brief	起動時にロゴとか出るシーン
*	@date	2024/12/19
*/
#pragma once
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../Library/Code/self/01_GameManager/GameManager.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
#include"../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../Library/Code/self/08_Timer/Timer.h"
#include"../../Library/Code/self/Ueda_FadeIn&FadeOut/FedaIn&FedaOut.h"

/**	@file	SplashScreanScene.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class SplashScreanScene :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	SplashScreanScene();
	/**	@brief 	デストラクタ
	*/
	~SplashScreanScene()override;
	/**	@brief 	シーン全体の初期化
	*/
	void	Initialize(void)override;

	/**	@brief 	シーン全体の更新
	*/
	void	Update(void)override;

	/**	@brief 	シーン全体の描画
	*/
	void	Draw(void)override;

	/**	@brief 	シーン全体の終了処理
	*/
	void	Finalize(void)override;
private:
	Camera* p_camera;		// カメラ
	float displayTime;		// 表示時間
	FedaInOut* feda;		// フェード

	Timer displayTimer;		// 表示させる時間
	Timer sceneChangeTimer;	// シーン遷移までの時間

	// 画面の状態
	enum ScreenState
	{
		FADE_IN,		// フェードイン
		DISPLAY_LOGO,	// ロゴ表示
		FADE_OUT,		// フェードアウト
		SCENE_CHANGE,	// シーン遷移する
	};
	ScreenState currentScreenState;

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------
	Object* p_background;	// 背景
	Object* p_logo;			// ロゴ

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
