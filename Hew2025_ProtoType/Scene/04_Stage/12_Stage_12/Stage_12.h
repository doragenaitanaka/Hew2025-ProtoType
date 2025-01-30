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

#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/13_Seesaw/Seesaw.h"
#include"../../../Library/Code/self/14_Ball/Ball.h"
#include"../../../Library/Code/self/16_Background/Background.h"
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

	//座標

	XMFLOAT3 playerPos = { 400.0f, -5750.0f,0.0f };

	XMFLOAT2 HookPos00 = { 1200.0f,-5500.0f };//スタートすぐ
	XMFLOAT2 HookPos01 = { 3100.0f,-5700.0f };//ボール左
	XMFLOAT2 HookPos02 = { 2500.0f,-1800.0f };//シーソー上
	XMFLOAT2 HookPos03 = { 4900.0f,-1900.0f };//ペン二本のとこ
	XMFLOAT2 HookPos04 = { 6000.0f,-500.0f };//ゴールすぐ横

	XMFLOAT2 PenPos00 = { 2600.0f,-5800.0f };//ペン スタート右
	XMFLOAT2 PenPos01 = { 4000.0f,-2125.0f };//ペン 上1
	XMFLOAT2 PenPos02 = { 4000.0f,-2075.0f };//ペン 上2
	
	XMFLOAT2 SlopePos00 = { 5473.0f,-6773.0f };//右下坂道
	XMFLOAT2 SlopePos01 = { 600.0f,-3700.0f };//シーソー左坂道
	XMFLOAT2 SlopePos02 = { 4800.0f,-2210.0f };//普通の坂道

	XMFLOAT2 PipePos00 = { 300.0f,-2000.0f };//土管シーソーのほう
	XMFLOAT2 PipePos01 = { 4750.0f,-350.0f };//土管ゴール横のほう

	XMFLOAT2 SeesawPos = { 1950.0f,-4250.0f };//シーソー

	XMFLOAT2 SeesawOpPos00 = { 1200.0f,-4050.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpPos01 = { 2500.0f,-4400.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpPos02 = { 1950.0f,-4260.0f };//支点

	XMFLOAT2 BallPos = { 4750.0f,-5600.0f };//ボール
	XMFLOAT3 GrabboxPos = { 2500.0f,-4050.0f ,0.0f };//消しゴム

	XMFLOAT2 PushObjectPos00 = { 2000.0f,-5300.0f };//倒れるオブジェクト
	XMFLOAT2 PushObjectPos01 = { 3400.0f,-1600.0f };//倒れるオブジェクト

	XMFLOAT2 GoalPos = { 7000.0f,-500.0f }; //ゴール
	//サイズ
	XMFLOAT2 PlayerSize = { 200.0f,200.0f };

	XMFLOAT2 HookSize = { 150.0f,220.0f };
	XMFLOAT2 PenSize = { 900.0f,100.0f };

	XMFLOAT2 SlopeSize00 = { 1200.0f,100.0f };//右下
	XMFLOAT2 SlopeSize01 = { 1100.0f,100.0f };//シーソー左
	XMFLOAT2 SlopeSize02 = { 500.0f,100.0f };//普通の坂道

	XMFLOAT2 SeesawSize = { 1400.0f,800.0f };
	XMFLOAT2 PipeSize = { 800.0f,1600.0f };
	XMFLOAT2 BallSize = { 500.0f,500.0f };
	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };

	XMFLOAT2 SeesawOpSize00 = { 300.0f,100.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpSize01 = { 300.0f,100.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpSize02 = { 500.0f,500.0f };//支点

	XMFLOAT2 PushObjectSize = { 900.0f,1200.0f };

	XMFLOAT2 GoalSize = { 200.0f,2000.0f };

	int gamemode = 0;

	// ボール
	float BallSpeed = 10.0f;
	float BallAngle = 0.0f;

	float posx = 0.0f;
	float posy = 0.0f;
	float slopeAngle00 = -25.0f;//シーソーと左
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
	int grabState = 0;
	int n = 0;	//当たり判定用のブロックの番号
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Object* SeesawOption[3];//0 = 左側の判定 1 = 右側の判定 2 = 支点
	Player* player;
	Object* hook[5];
	Object* pen[3];
	Ball* ball;
	Object* PushObject[2];
	Object* Pipe[2];
	Seesaw* seesaw;
	Object* slope[3];
	GrabBox* grabbox;
	Object* goal;

	TrackingCamera* p_camera;	// カメラ
	TileMap* p_tileMap;			//タイルマップ

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
