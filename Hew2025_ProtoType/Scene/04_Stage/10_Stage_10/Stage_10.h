/**	@file 	Stage_10.h
*	@brief 	Stage_10
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

#include"../../../Library/Code/self/16_Background/Background.h"
#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
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

	XMFLOAT3 playerPos = { 7400.0f, -1650.0f,0.0f };

	XMFLOAT2 HookPos00 = { 3000.0f,-550.0f };//フック左から
	XMFLOAT2 HookPos01 = { 3750.0f,-650.0f };
	XMFLOAT2 HookPos02 = { 4450.0f,-1800.0f };
	XMFLOAT2 HookPos03 = { 5100.0f,-650.0f };
	XMFLOAT2 HookPos04 = { 5850.0f,-1700.0f };
	XMFLOAT2 HookPos05 = { 6600.0f,-1700.0f };

	XMFLOAT2 RailPos00 = { 3000.0f,-1700.0f };//レール左から順に
	XMFLOAT2 RailPos01 = { 3750.0f,-1700.0f };
	XMFLOAT2 RailPos02 = { 4450.0f,-1700.0f };
	XMFLOAT2 RailPos03 = { 5100.0f,-1700.0f };
	XMFLOAT2 RailPos04 = { 5850.0f,-1700.0f };
	XMFLOAT2 RailPos05 = { 6600.0f,-1700.0f };

	XMFLOAT2 PushObjectPos = { 1300.0f,-1400.0f };//倒れるオブジェクト

	XMFLOAT2 GoalPos = { 300.0f,-1750.0f }; //ゴール

	//サイズ
	XMFLOAT2 PlayerSize = { 200.0f,200.0f };

	XMFLOAT2 HookSize = { 150.0f,220.0f };

	XMFLOAT2 RailSize = { 100.0f,2100.0f };

	XMFLOAT2 PushObjectSize = { 400.0f,1000.0f };

	XMFLOAT2 GoalSize = { 200.0f,200.0f };

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float HookMoveSpeed[6] = { 10.0f,15.0f,20.0f,12.0f,17.0f,10.0f };//フックの速度右から
	bool StayGround = false;//地面に触れているかの判定
	bool MoveHookFLG = false;//フックが動き出すかのフラグ
	bool TurnBackFLG[6] = { true,true,false,true,false,true };//フックが往復するためのフラグ
	int JumpState = 0;//ジャンプの状態
	int cnt = 0;//ジャンプ等の判定用
	int n = 0;	//当たり判定用のブロックの番号
	int HookCnt[6] = { 0,0,100,0,100,100 }; //右から順
	int ColliderState = 0;
private:
	Input input;
	Background* background;
	Player* player;
	Object* hook[6];
	Object* rail[6];
	Object* PushObject;
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
