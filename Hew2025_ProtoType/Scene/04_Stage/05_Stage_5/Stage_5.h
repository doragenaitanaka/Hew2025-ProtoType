/**	@file 	Stage_5.h
*	@brief 	Stage_5
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
#include"../../../Library/Code/self/08_Timer/Timer.h"
#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/15_Pendulum/Pendulum.h"
#include"../../../Library/Code/self/16_Background/Background.h"
#include"../../../Library/Code/other/03_sound/sound.h"
#include <memory> 
/**	@file	Stage_5.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_5 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_5();
	/**	@brief 	デストラクタ
	*/
	~Stage_5()override;
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
	int HookCameraState = 0;
	int HookNumber = 0;
	int YoyoStage = 0;
	int NewColState = 0;
	int StartState = 0;
	int HookColliderState = -1;
	bool ScenechangeState = false;
	int ScenechangeState2 = 0;
	int deathstate = 0;
	int t5 = 0;
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
	std::shared_ptr<Object>hook[7];
	std::shared_ptr<Object> hookdraw[7];
	std::shared_ptr<Object>rail[4];
	std::shared_ptr<Object>YoyoObject[2]; //YoyObject[0] = ヨーヨーの支点 YoyoObject[1] = ヨーヨーの本体
	std::shared_ptr<GrabBox>grabbox;
	std::shared_ptr<Pendulum>pendulum;

	XMFLOAT2 PlayerGrabPos = { 0.0f, 0.0f };

	XMFLOAT2 HookPos00 = { 5850.0f,-4850.0f };//右フック下
	XMFLOAT2 HookPos01 = { 115850.0f,-4650.0f };//右フック上
	XMFLOAT2 HookPos02 = { 115850.0f,-2500.0f };//空中右フック左
	XMFLOAT2 HookPos03 = { 5920.0f,-2500.0f };//空中右フック右
	XMFLOAT2 HookPos04 = { 112150.0f,-2350.0f };//空中左フック上
	XMFLOAT2 HookPos05 = { 2150.0f,-2550.0f };//空中左フック下
	XMFLOAT2 HookPos06 = { 2150.0f,-200.0f };//空中ゴール左フック

	XMFLOAT2 HookSize01 = { 220.0f, 220.0f };
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

	XMFLOAT2 RailPos00 = { 5850,-5135.0f };//右フック下
	XMFLOAT2 RailPos01 = { 6250.0f,-2420.0f };//空中右フック右
	XMFLOAT2 RailPos02 = { 2150.0f,-2835.0f };//空中左フック下
	XMFLOAT2 RailSize00 = { 100.0f,700.0f };
	XMFLOAT2 RailSize01 = { 100.0f,700.0f };
	XMFLOAT2 RailSize02 = { 100.0f,700.0f };

	XMFLOAT2 YoyoPos = { 2600.0f,-3400.0f };//ヨーヨーの支点

	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };
	XMFLOAT3 GrabboxPos = { 4500.0f,-4800.0f,0.0f };//振り子の当たり判定用
	XMFLOAT2 GoalPos = { 3000.0f,-100.0f };
	XMFLOAT2 GoalSize = { 200.0f, 200.0f };

	XMFLOAT2 IdlePos = { 0.0f,0.0f };
	XMFLOAT2 IdleSize = { 160.0f,160.0f };
	XMFLOAT2 DeathSize = { 230.0f,230.0f };
	XMFLOAT2 HookColSize01 = { 80.0f, 80.0f };
	int YoyoNumber = 0;
	int HookCnt[4] = { 0,0,0,0 };
	int YoyoCntX = 0;
	int YoyoCntY = 0;
	int grabState = 0;
	float HookMoveSpeed = 5.0f;
	float YoyoMoveSpeed = 15.0f;
	bool GrabFlg = false;
	bool StayGround = false;//地面に触れているかの判定
	bool MoveHookFLG[4] = { false,false,false,false };//フックが動き出すかのフラグ
	bool TurnBackFLG[4] = { true,true,true,true };//フックが往復するためのフラグ
	bool YoyoTurnFLG[2] = { true,true };
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

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};

