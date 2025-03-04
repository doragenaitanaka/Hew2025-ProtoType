/**	@file 	Stage_12.h
*	@brief 	Stage_12
*	@date	2024/12/19
*/
#pragma once

//インクルード
#include"../../00_BaseScene/BaseScene.h"
#include"../../../Library/Code/self/02_SceneManager/SceneManager.h"

#include"../../../Library/Code/self/imagawa_Input/input.h"
#include"../../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"

#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/13_Seesaw/Seesaw.h"
#include"../../../Library/Code/self/14_Ball/Ball.h"
#include"../../../Library/Code/self/17_FallObject/FallObject.h"
#include"../../../Library/Code/self/15_Pendulum/Pendulum.h"
#include"../../../Library/Code/self/18_Pen/Pen.h"

#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../../Library/Code/self/08_Timer/Timer.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/16_Background/Background.h"
#include"../../../Library/Code/other/03_sound/sound.h"
#include <memory> 
#include<array>
/**	@file	Stage_12.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_12 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_12();
	/**	@brief 	デストラクタ
	*/
	~Stage_12()override;
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


	float PlayerAngle = 0.0f;
	int idletime = 0;
	float u = 0.0f;
	float eyesy = 90.0f;
	float eyesx = 0.0f;
	float lefthandx = -62.0f;
	float lefthandy = 14.0f;
	float leftlegx = -39.0f;
	float leftlegy = -29.0f;
	float righthandx = 66.0f;
	float righthandy = 15.0f;
	float rightlegx = 50.0f;
	float rightlegy = -30.0f;
	int jumpkeystate = 0;
	float Vx2 = 0.0f;
	float Camera2xdelta = 0.0f;
	float Camera2ydelta = 0.0f;
	int t3 = 0;
	int pullstate = 0;
	float Vx4 = 7.0f;
	int superjumpstate = 0;
	float t2 = 0.0f;
	float a = 90.0f;
	float Vypower = 0.0f;
	float Vxpower = 0.0f;
	double radians = 0.0f;
	int powerstate = 0;
	float g = 5.2f;
	float power = -0.1f;
	float z = 0.0f;
	int movestate = 0;
	int movestate2 = 0;
	int PlayerColState = 0;
	int PlayerColState3 = 0;
	int PlayerColState2 = 1;
	int grabstate = 0;
	int jumpstate = 0;
	float Vdown = 0.0f;
	float Vdown2 = 0.0f;
	float Vnew = 0;
	float Vdelta = 0;
	float Vx = 0.0f;
	float Vy = 0.0f;
	float t = 0;
	float posx = 0.0f;
	float posy = 0.0f;
	int drawnum = 0;
	int n = 0;
	int m = 0;
	int ustate = 0;
	int BlockNumber = 0;
	int deadstate = 0;
	int HookCameraState = 0;
	int HookNumber = 0;
	int NewColState = 0;
	int StartState = 0;
	int HookColliderState = -1;
	bool ScenechangeState = false;
	int ScenechangeState2 = 0;
	int deathstate = 0;
	int t5 = 0;
	int t6 = 0;
	int PenAngle0 = 0;
	int PenAngle1 = 0;
	int PenAngle2 = 0;
	float movex = 0;
	float movey = 0;
	int  TestPenState2 = 0;
	int  TestPenState3 = 0;
	int  TestPen2State = 0;
	int superkeystate = 0;
	int  TestPen2State2 = 0;
	int  TestPen2State3 = 0;
	int PenColState = 0;
	int PenColState2 = 0;
	int  PenCol2State = 0;
	int TestPenState = 0;
	int PenNumber = 0;
	int TestPen3State = 0;
	int TestPen3State2 = 0;
	int TestPen3State3 = 0;
	int PenColState3 = 0;
	int  PenCol3State = 0;
	int grabState = 0;
	int YoyoStage = 0;
	std::shared_ptr<Object>death2;
	std::shared_ptr<Object>playercol;
	std::shared_ptr<Object>playercol2;
	std::shared_ptr<Object>playercol3;
	std::shared_ptr<Player>playerdraw;
	std::shared_ptr<Object>eyes;
	std::shared_ptr<Object>lefthand;
	std::shared_ptr<Object>righthand;
	std::shared_ptr<Object>leftleg;
	std::shared_ptr<Object>rightleg;
	std::shared_ptr<Object>idle;
	std::shared_ptr<Object>walking;
	std::shared_ptr<Object>walking2;
	std::shared_ptr<Object>goal;
	std::shared_ptr<Object>hook[8];
	std::shared_ptr<Object> hookdraw[5];
	std::shared_ptr<Object>PenCol[3];
	// ボール
	float BallSpeed = 10.0f;
	float BallAngle = 0.0f;
	int superpressstate = 0;

	float slopeAngle00 = -29.0f;//シーソーと左
	float slopeAngle01 = 45.0f;//右下
	float slopeAngle02 = -10.0f;//普通の坂道
	float seesawangle = -15.0f;
	bool GrabfallFlg = false;
	bool GrabFlg = false;
	bool StayGround = false;//地面に触れているかの判定
	bool BallMoveFLG[2] = { false,true };	//ボールが動いているかの判定
	bool CheckBall = true;//ボールがステージ内にあるか
	int JumpState = 0;
	int ballState = 0;//ボールの動き処理用 //1 = 地面に触れている 2 = 坂道に触れている 3 = シーソーヘッドに触れている
	int cnt = 0;//ジャンプ等の判定用
	int seesawcnt = 0;
	int BallStopState = 0;
	int  PenStopState0 = 0;
	int  PenStopState1 = 0;
	int SlopeState1 = 0;
	std::array<XMFLOAT2, 3>PenPos = {

	XMFLOAT2(4000.0f,-2125.0f),//1700.0f, -2475.0f		XMFLOAT2(2800.0f,-1520.0f),
	XMFLOAT2(4000.0f,-2075.0f),
		XMFLOAT2(2600.0f,-5820.0f)
	};

	float  SlopeVx = 0.0f;
	float  SlopeVy = 0.0f;
	XMFLOAT2 PenColSize = { 60.0f,60.0f };
	//	XMFLOAT2 PenPos00 = { 2600.0f,-5800.0f };//ペン スタート右
		//XMFLOAT2 PenPos01 = { 4000.0f,-2125.0f };//ペン 上1
	//	XMFLOAT2 PenPos02 = { 4000.0f,-2075.0f };//ペン 上2

	XMFLOAT2 SlopePos00 = { 5473.0f,-6773.0f };//右下坂道
	XMFLOAT2 SlopePos01 = { 585.0f,-3740.0f };//シーソー左坂道
	XMFLOAT2 SlopePos02 = { 4885.0f,-2230.0f };//普通の坂道

	XMFLOAT2 PipePos00 = { 300.0f,-2000.0f };//土管シーソーのほう
	XMFLOAT2 PipePos01 = { 4750.0f,-350.0f };//土管ゴール横のほう

	XMFLOAT2 SeesawPos = { 1950.0f,-4250.0f };//シーソー

	XMFLOAT2 SeesawOpPos00 = { 1200.0f,-4050.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpPos01 = { 2500.0f,-4400.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpPos02 = { 1950.0f,-4260.0f };//支点

	XMFLOAT2 BallPos = { 4750.0f,-5600.0f };//ボール
	XMFLOAT3 GrabboxPos = { 2500.0f,-4050.0f ,0.0f };//消しゴム

	// 倒れるオブジェクトの座標
	std::array<XMFLOAT2, 2>PushObjectPos = {
		XMFLOAT2(2000.0f,-5740.0f),
		XMFLOAT2(3400.0f,-2040.0f),
	};

	// 倒れるオブジェトのサイズ
	std::array<XMFLOAT2, 2>PushObjectSize = {
		XMFLOAT2(500.0f,950.0f),
		XMFLOAT2(500.0f,950.0f)
	};
	XMFLOAT2 PenSize = { 900.0f,100.0f };

	XMFLOAT2 SlopeSize00 = { 1200.0f,100.0f };//右下
	XMFLOAT2 SlopeSize01 = { 1050.0f,123.0f };//シーソー左
	XMFLOAT2 SlopeSize02 = { 350.0f,100.0f };//普通の坂道

	XMFLOAT2 SeesawSize = { 1400.0f,800.0f };
	XMFLOAT2 PipeSize = { 800.0f,1600.0f };
	XMFLOAT2 BallSize = { 500.0f,500.0f };
	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };

	XMFLOAT2 SeesawOpSize00 = { 300.0f,100.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpSize01 = { 300.0f,100.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpSize02 = { 500.0f,500.0f };//支点

	//XMFLOAT2 PushObjectSize = { 900.0f,1200.0f };


	XMFLOAT2 PlayerGrabPos = { 0.0f, 0.0f };

	XMFLOAT2 HookPos01 = { 1200.0f,-5500.0f };
	XMFLOAT2 HookPos02 = { 3100.0f,-5600.0f };
	XMFLOAT2 HookPos03 = { 2500.0f,-1800.0f };
	XMFLOAT2 HookPos04 = { 4900.0f,-1900.0f };
	XMFLOAT2 HookPos05 = { 6000.0f,-500.0f };
	XMFLOAT2 HookPos06 = { 112500.0f,-1800.0f };
	XMFLOAT2 HookPos07 = { 114900.0f,-1900.0f };
	XMFLOAT2 HookPos08 = { 116000.0f,-500.0f };

	XMFLOAT2 HookSize01 = { 100.0f, 100.0f };
	XMFLOAT2 HookSize02 = { 150.0f, 220.0f };


	XMFLOAT2 PlayerDrawPos = { 0.0f, 40.0f };
	XMFLOAT2 PlayerDrawSize = { 140.0f,140.0f };

	XMFLOAT2 EyesPos = { 0.5f, +90.0f };
	XMFLOAT2 EyesSize = { 120.0f,120.0f };

	XMFLOAT2 LefthandPos = { -62.0f,14.0f };
	XMFLOAT2 LefthandSize = { 105.0f,105.0f };

	XMFLOAT2 LeftlegPos = { -39.0f, -29.0f };
	XMFLOAT2 LeftlegSize = { 125.0f,125.0f };

	XMFLOAT2 RighthandPos = { 66.0f, 15.0f };
	XMFLOAT2 RighthandSize = { 105.0f,105.0f };

	XMFLOAT2 RightlegPos = { 50.0f, -30.0f };
	XMFLOAT2 RightlegSize = { 125.0f,125.0f };


	XMFLOAT2 PlayerColPos = { 25.0f, 25.0f };
	XMFLOAT2 PlayerColSize = { 110.0f,110.0f };

	XMFLOAT2 PlayerColPos3 = { -25.0f, 25.0f };
	XMFLOAT2 PlayerColSize3 = { 110.0f,110.0f };

	XMFLOAT2 PlayerColPos2 = { 0.0f, 80.0f };
	XMFLOAT2 PlayerColSize2 = { 120.0f,40.0f };


	XMFLOAT2 GoalPos = { 7000.0f,-500.0f };
	XMFLOAT2 GoalSize = { 1200.0f, 1200.0f };

	XMFLOAT2 IdlePos = { 0.0f,0.0f };
	XMFLOAT2 IdleSize = { 160.0f,160.0f };
	XMFLOAT2 DeathSize = { 230.0f,230.0f };
	XMFLOAT2 HookColSize01 = { 80.0f, 80.0f };

private:
	// テクスチャ
	std::array<ID3D11ShaderResourceView*, 2> textureList;

	// タイマー
	Timer failedTimer;	// 失敗時
	bool isFailed;		// true:失敗した

	int gamemode = 1;							// ゲームモード
	int ColliderState = 0;						// 当たった状態
	XMFLOAT2 PlayerSize = { 110.0f,110.0f };	// プレイヤーのサイズ

	TrackingCamera* p_camera;	// カメラ
	TileMap* p_tileMap;			//タイルマップ
	//Input input;

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------
	Background* background;
	Player* player;
	Background* keyConfigUI;
	Object* pen[3];
	Ball* ball;
	Object* PushObject[2];
	Object* Pipe[2];
	Seesaw* seesaw;
	Object* slope[3];
	GrabBox* grabbox;
	Object* SeesawOption[3];//0 = 左側の判定 1 = 右側の判定 2 = 支点
	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
