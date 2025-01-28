/**	@file 	Stage_6.h
*	@brief 	Stage_6
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

/**	@brief	Stage_6
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_6 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_6();
	/**	@brief 	デストラクタ
	*/
	~Stage_6()override;
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

	// オブジェくトの座標
	std::array<XMFLOAT2, 12> BlockPos = {
		XMFLOAT2(2700.0f,-350.0f),	//基底床
		XMFLOAT2(100.0f,950.0f),	//左壁
		XMFLOAT2(2200.0f,150.0f),	//中間柱
		XMFLOAT2(4700.0f,-150.0f),	//右床正
		XMFLOAT2(5400.0f,700.0f),	//右壁
		XMFLOAT2(3800.0f,1850.0f),	//ゴール床
		XMFLOAT2(550.0f,1100.0f),	//本棚左
		XMFLOAT2(950.0f,900.0f),	//本棚右
		XMFLOAT2(3500.0f,800.0f),	//ボール床

		XMFLOAT2(550.0f,1700.0f),	//本棚左
		XMFLOAT2(950.0f,1500.0f),	//本棚右
	};

	// オブジェくトのサイズ
	std::array<XMFLOAT2, 12> BlockSize = {
		XMFLOAT2(5800.0f,100.0f),//基底床
		XMFLOAT2(600.0f,2500.0f),//左壁
		XMFLOAT2(800.0f,900.0f),//中間柱
		XMFLOAT2(1000.0f,300.0f),//右床正
		XMFLOAT2(400.0f,2000.0f),//右壁
		XMFLOAT2(1400.0f,200.0f),//ゴール床
		XMFLOAT2(300.0f,200.0f),//本棚左
		XMFLOAT2(300.0f,200.0f),//本棚右
		XMFLOAT2(1000.0f,200.0f),//ボール床

		XMFLOAT2(300.0f,1000.0f),//本棚左
		XMFLOAT2(300.0f,1000.0f),//本棚右
	};

	// フックの座標
	std::array<XMFLOAT2, 3>HookPos = {
		XMFLOAT2(590.0f,200.0f),	//左フック
		XMFLOAT2(2500.0f, 1100.0f),	//右フック
		XMFLOAT2(2800.0f, 2100.0f),	//ゴール横
	};
	// フックのサイズ
	std::array<XMFLOAT2, 3>HookSize = {
		XMFLOAT2(200.0f,200.0f),
		XMFLOAT2(200.0f,200.0f),
		XMFLOAT2(200.0f,200.0f),
	};

	//倒れるオブジェクト
	XMFLOAT2 PushObjectPos00 = { 1100.0f, 200.0f }; 
	XMFLOAT2 PushObjectSize00 = { 300.0f,1000.0f };

	//ボールオブジェクト
	XMFLOAT2 BallPos = { 3200.0f, 1100.0f };		
	XMFLOAT2 BallSize = { 400.0f,400.0f };

	//ゴール
	XMFLOAT2 GoalPos = { 3840.0f,100.0f }; 
	XMFLOAT2 GoalSize = { 200.0f,300.0f };

	// シーソー
	std::array<XMFLOAT2, 2>SeeSawHeadPos = {
		XMFLOAT2(2800.0f,-200.0f),	//左
		XMFLOAT2(4000.0f,0.0f),		//右
	};
	std::array<XMFLOAT2, 2>SeeSawHeadSize = {
	XMFLOAT2(300.0f,100.0f),	//左
	XMFLOAT2(300.0f,100.0f),	//右
	};

	//シーソーの繋ぎ部分
	XMFLOAT2 SeesawConnectPos = { 3350.0f, -150.0f };
	XMFLOAT2 SeesawConnectSize = { 1400.0f, 100.0f };
	float ConnectorAngle = 10.0f;

	// プレイヤー
	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	//消しゴム
	XMFLOAT2 GrabboxSize = { 300.0f,500.0f };
	XMFLOAT3 GrabboxPos = { 2800.0f,200.0f,0.0f };

	// スロープ
	XMFLOAT2 slopePos{ 400.0f, 1400.0f };
	XMFLOAT2 slopeSize{ 4800.0f, 350.0f };
	float slopeAngle = -45.0f;

	int gamemode = 0;

	// プレイヤー
	float posx = 700.0f;
	float posy = 4200.0f;

	// ボール
	float BallSpeed = 5.0f;
	float BallAngle = 0.0f;

	bool GrabFlg = false;
	bool StayGround = false;				//地面に触れているかの判定
	bool BallMoveFLG[2] = { false,true };	//ボールが動いているかの判定
	int JumpState = 0;
	int cnt = 0;
	int drawnum = 0;	//描画用のブロックの番号
	int n = 0;			//当たり判定用のブロックの番号
	int BlockNumber = 0;
	int HookNumber = 0;
	int HeadNumber = 0;
	int ColliderState = 0;
	int BallState = 0;
	int grabState = 0;
	int seesawcnt = 0;

	TrackingCamera* p_camera;	// カメラ
	TileMap* p_tileMap;			//タイルマップ
	Input input;

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------	
	Background* background;
	Player* player;
	Object* hook[3];
	Object* PushObject;
	Object* goal;
	Object* SeesawHead[2];
	Object* Connector;
	Ball* BallObject;	
	GrabBox* grabbox;
	Seesaw* seesaw;

	Object* SlopeObject;

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};