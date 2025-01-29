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

	XMFLOAT3 playerPos = { 400.0f, -5800.0f,0.0f };

	XMFLOAT2 HookPos00 = { 3000.0f,-550.0f };//
	XMFLOAT2 HookPos01 = { 3750.0f,-650.0f };//
	XMFLOAT2 HookPos02 = { 4450.0f,-1800.0f };//
	XMFLOAT2 HookPos03 = { 5100.0f,-650.0f };//
	XMFLOAT2 HookPos04 = { 5850.0f,-1700.0f };//

	XMFLOAT2 PenPos00 = { 3000.0f,-550.0f };//ペン
	XMFLOAT2 PenPos01 = { 3000.0f,-550.0f };//ペン
	XMFLOAT2 PenPos02 = { 3000.0f,-550.0f };//ペン
	
	XMFLOAT2 SlopePos00 = { 3000.0f,-550.0f };//坂道
	XMFLOAT2 SlopePos01 = { 600.0f,-3700.0f };//坂道
	XMFLOAT2 SlopePos02 = { 3000.0f,-550.0f };//坂道

	XMFLOAT2 PipePos00 = { 3000.0f,-550.0f };//土管
	XMFLOAT2 PipePos01 = { 3000.0f,-550.0f };//土管

	XMFLOAT2 SeesawPos = { 3000.0f,-550.0f };//シーソー

	XMFLOAT2 SeesawOpPos00 = { 3000.0f,-550.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpPos01 = { 3000.0f,-550.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpPos02 = { 3000.0f,-550.0f };//支点


	XMFLOAT2 BallPos = { 3000.0f,-550.0f };//ボール
	XMFLOAT3 GrabboxPos = { 3000.0f,-550.0f ,0.0f };//消しゴム

	XMFLOAT2 PushObjectPos00 = { 2000.0f,-5300.0f };//倒れるオブジェクト
	XMFLOAT2 PushObjectPos01 = { 1300.0f,-1400.0f };//倒れるオブジェクト

	XMFLOAT2 GoalPos = { 300.0f,-1750.0f }; //ゴール
	//サイズ
	XMFLOAT2 PlayerSize = { 200.0f,200.0f };

	XMFLOAT2 HookSize = { 150.0f,220.0f };
	XMFLOAT2 PenSize = { 800.0f,50.0f };

	XMFLOAT2 SlopeSize00 = { 800.0f,100.0f };//右下
	XMFLOAT2 SlopeSize01 = { 1100.0f,100.0f };//シーソー左
	XMFLOAT2 SlopeSize02 = { 400.0f,100.0f };//普通の坂道

	XMFLOAT2 SeesawSize = { 1200.0f,100.0f };
	XMFLOAT2 PipeSize = { 400.0f,800.0f };
	XMFLOAT2 BallSize = { 500.0f,500.0f };
	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };

	XMFLOAT2 SeesawOpSize00 = { 3000.0f,-550.0f };//左側の当たり判定
	XMFLOAT2 SeesawOpSize01 = { 3000.0f,-550.0f };//右側の当たり判定
	XMFLOAT2 SeesawOpSize02 = { 3000.0f,-550.0f };//支点

	XMFLOAT2 PushObjectSize = { 900.0f,1200.0f };

	XMFLOAT2 GoalSize = { 200.0f,200.0f };

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float slopeAngle00 = -25.0f;//右下
	float slopeAngle01 = 45.0f;//シーソー左と普通の坂道
	bool GrabFlg = false;
	bool StayGround = false;//地面に触れているかの判定
	bool BallMoveFLG[2] = { false,true };	//ボールが動いているかの判定
	bool CheckBall = true;//ボールがステージ内にあるか
	int JumpState = 0;
	int cnt = 0;//ジャンプ等の判定用
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
