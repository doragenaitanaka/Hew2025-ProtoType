/**	@file 	Stage_10.h
*	@brief 	Stage_10
*	@date	2024/12/19
*/
#pragma once

//インクルード
#include"../../00_BaseScene/BaseScene.h"
#include"../../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/imagawa_Input/input.h"
#include"../../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
/**	@file	Stage_10.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_10 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_10();
	/**	@brief 	デストラクタ
	*/
	~Stage_10()override;
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

	XMFLOAT2 CameraPos = { 3700.0f, 1200.0f };

	XMFLOAT2 BlockPos00 = { 3750.0f,0.0f };//右床
	XMFLOAT2 BlockPos01 = { -1100.0f,0.0f };//ゴール床
	XMFLOAT2 BlockPos02 = { -600.0f,2550.0f };//ゴール上床
	XMFLOAT2 BlockPos03 = { 5000.0f,900.0f };//右壁

	XMFLOAT2 HookPos00 = {  350.0f,2250.0f };//フック左から
	XMFLOAT2 HookPos01 = {  850.0f,200.0f };
	XMFLOAT2 HookPos02 = { 1350.0f,2250.0f };
	XMFLOAT2 HookPos03 = { 1850.0f,450.0f };
	XMFLOAT2 HookPos04 = { 2350.0f,2250.0f };
	XMFLOAT2 HookPos05 = { 2850.0f,1150.0f };

	XMFLOAT2 RailPos00 = {  350.0f,1150.0f };//レール左から順に
	XMFLOAT2 RailPos01 = {  850.0f,1150.0f };
	XMFLOAT2 RailPos02 = { 1350.0f,1150.0f };
	XMFLOAT2 RailPos03 = { 1850.0f,1150.0f };
	XMFLOAT2 RailPos04 = { 2350.0f,1150.0f };
	XMFLOAT2 RailPos05 = { 2850.0f,1150.0f };

	XMFLOAT2 PushObjectPos00 = { -600.0f,1500.0f };//倒れるオブジェクト

	XMFLOAT2 GoalPos = { -1600.0f,1150.0f }; //ゴール

	//サイズ
	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 BlockSize00 = { 1500.0f,2100.0f };
	XMFLOAT2 BlockSize01 = { 1500.0f,2000.0f };
	XMFLOAT2 BlockSize02 = { 400.0f,900.0f };
	XMFLOAT2 BlockSize03 = { 1000.0f,3900.0f };

	XMFLOAT2 HookSize00 = { 200.0f,200.0f };
	XMFLOAT2 HookSize01 = { 200.0f,200.0f };
	XMFLOAT2 HookSize02 = { 200.0f,200.0f };
	XMFLOAT2 HookSize03 = { 200.0f,200.0f };
	XMFLOAT2 HookSize04 = { 200.0f,200.0f };
	XMFLOAT2 HookSize05 = { 200.0f,200.0f };

	XMFLOAT2 RailSize00 = { 100.0f,2200.0f };
	XMFLOAT2 RailSize01 = { 100.0f,2200.0f };
	XMFLOAT2 RailSize02 = { 100.0f,2200.0f };
	XMFLOAT2 RailSize03 = { 100.0f,2200.0f };
	XMFLOAT2 RailSize04 = { 100.0f,2200.0f };
	XMFLOAT2 RailSize05 = { 100.0f,2200.0f };

	XMFLOAT2 PushObjectSize00 = { 300.0f,1000.0f };

	XMFLOAT2 GoalSize = { 200.0f,300.0f };

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float HookMoveSpeed[6] = { 10.0f,15.0f,20.0f,12.0f,17.0f,10.0f };//フックの速度右から
	bool StayGround = false;//地面に触れているかの判定
	bool MoveHookFLG = false;//フックが動き出すかのフラグ
	bool TurnBackFLG[6] = { true,false,true,false,true,true };//フックが往復するためのフラグ
	int JumpState = 0;//ジャンプの状態
	int cnt = 0;//ジャンプ等の判定用
	int drawnum = 0;//描画用のブロックの番号
	int n = 0;	//当たり判定用のブロックの番号
	int HookCnt[6] = { 0,100,0,100,0,100 }; //右から順
	int BlockNumber = 0;
	int HookNumber = 0;
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* block[100];
	Object* hook[6];
	Object* rail[6];
	Object* blockdraw[10000];
	Object* PushObject;
	Object* goal;

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
