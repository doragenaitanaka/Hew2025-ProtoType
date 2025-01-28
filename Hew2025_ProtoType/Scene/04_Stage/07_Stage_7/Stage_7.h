/**	@file 	Stage_7.h
*	@brief 	Stage_7
*	@date	2024/12/19
*/
#pragma once

//インクルード
#include"../../00_BaseScene/BaseScene.h"
#include"../../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../../Library/Code/self/imagawa_Input/input.h"
#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"

#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/13_Seesaw/Seesaw.h"
#include"../../../Library/Code/self/14_Ball/Ball.h"
#include"../../../Library/Code/self/16_Background/Background.h"

#include"../../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"

#include<array>
/**	@file	Stage_7.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_7 :public BaseScene
{
public:
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_7();
	/**	@brief 	デストラクタ
	*/
	~Stage_7()override;
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

	XMFLOAT2 PushObjectPos00 =  { 4100.0f,-3300.0f };
	XMFLOAT2 GoalPos =			{ 4600.0f,-900.0f }; //ゴール
	XMFLOAT2 ClaypipePos =		{ 1800.0f,-1600.0f };
	XMFLOAT2 BallPos =			{ 1800.0f,-1600.0f };

	// フックの座標
	std::array<XMFLOAT2, 4>HookPos = {
		XMFLOAT2(2850.0f,-3200.0f),	//左フック
		XMFLOAT2(3500.0f, -3600.0f),	//右フック
		XMFLOAT2(5250.0f,-3350.0f),	//ゴール横
		XMFLOAT2(6000.0f,-1800.0f),	//ゴール横
	};
	// フックのサイズ
	std::array<XMFLOAT2, 4>HookSize = {
		XMFLOAT2(200.0f,200.0f),
		XMFLOAT2(200.0f,200.0f),
		XMFLOAT2(200.0f,200.0f),
		XMFLOAT2(200.0f,200.0f),
	};

	// スロープ
	XMFLOAT2 slopePos00{ 2200.0f, -2600.0f };
	XMFLOAT2 slopeSize00{ 1600.0f,  150.0f };
	float slopeAngle00 = -12.0f;

	// スロープ
	XMFLOAT2 slopePos01{ 3380.0f, -4000.0f };
	XMFLOAT2 slopeSize01{ 1350.0f,  150.0f };
	float slopeAngle01 = 15.0f;

	// スロープ
	XMFLOAT2 slopePos02{ 6500.0f, -2900.0f };
	XMFLOAT2 slopeSize02{ 1600.0f,  150.0f };
	float slopeAngle02 = 45.0f;

	XMFLOAT2 PlayerSize =		{ 100.0f,100.0f };	// プレイヤーのサイズ
	XMFLOAT2 BallSize =			{ 300.0f,300.0f };
	XMFLOAT2 ClaypipeSize =		{ 400.0f,900.0f };
	XMFLOAT2 PushObjectSize =	{ 600.0f,1200.0f };
	XMFLOAT2 GoalSize = { 200.0f,300.0f };

private:
	int gamemode = 0;		// ゲームモード
	int n;
	int cnt = 0;
	int ColliderState = 0;			// 当たった状態
	bool StayGround = false;//地面に触れているかの判定
	int JumpState = 0;
	int BallState = 0;
	int HookNumber = 0;
	float BallSpeed = 5.0f;
	float BallAngle = 0.0f;
	bool BallMoveFLG[2] = { false,true };//ボールが動いているかの判定
	

	TrackingCamera* p_camera;	// カメラ
	TileMap* p_tileMap;			//タイルマップ
	//Input input;

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------
	Background* background;
	Player* player;
	Object* hook[4];
	Object* PushObject;
	Object* goal;
	Object* claypipe;
	Ball* ball;
	Object* SlopeObject00;
	Object* SlopeObject01;
	Object* SlopeObject02;

	//Object* block[100];
	//Object* blockdraw[10000];

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};