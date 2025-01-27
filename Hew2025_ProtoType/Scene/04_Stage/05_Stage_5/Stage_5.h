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

#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/15_Pendulum/Pendulum.h"
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

	//座標
	XMFLOAT3 playerPos = { 300.0f,-5000.0f,0.0f };

	XMFLOAT2 HookPos00 = { 5850.0f,-4850.0f };//右フック下
	XMFLOAT2 HookPos01 = { 5850.0f,-4650.0f };//右フック上
	XMFLOAT2 HookPos02 = { 5850.0f,-2500.0f };//空中右フック左
	XMFLOAT2 HookPos03 = { 6050.0f,-2500.0f };//空中右フック右
	XMFLOAT2 HookPos04 = { 2150.0f,-2350.0f };//空中左フック上
	XMFLOAT2 HookPos05 = { 2150.0f,-2550.0f };//空中左フック下
	XMFLOAT2 HookPos06 = { 2150.0f,-200.0f };//空中ゴール左フック

	XMFLOAT2 RailPos00 = { 3050.0f,-500.0f };//右フック下
	XMFLOAT2 RailPos01 = { 3650.0f,1550.0f };//空中右フック右
	XMFLOAT2 RailPos02 = { 550.0f,1350.0f };//空中左フック下

	XMFLOAT2 YoyoPos = { 2600.0f,-3400.0f };//ヨーヨーの支点

	XMFLOAT3 GrabboxPos = { 4500.0f,-4800.0f,0.0f };//振り子の当たり判定用

	XMFLOAT2 GoalPos = { 3000.0f,-100.0f }; //ゴール

	//サイズ

	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 HookSize = { 200.0f,200.0f };

	XMFLOAT2 RailSize00 = { 100.0f,800.0f };
	XMFLOAT2 RailSize01 = { 800.0f,100.0f };
	XMFLOAT2 RailSize02 = { 100.0f,600.0f };

	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };

	XMFLOAT2 GoalSize = { 200.0f,300.0f };


	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float HookMoveSpeed = 5.0f;
	float YoyoMoveSpeed = 15.0f;
	bool GrabFlg = false;
	bool StayGround = false;//地面に触れているかの判定
	bool MoveHookFLG[4] = { false,false,false,false };//フックが動き出すかのフラグ
	bool TurnBackFLG[4] = { true,true,true,true };//フックが往復するためのフラグ
	bool YoyoTurnFLG[2] = { true,true };
	int JumpState = 0;
	int cnt = 0;
	int drawnum = 0;//描画用のブロックの番号
	int n = 0;	//当たり判定用のブロックの番号
	int BlockNumber = 0;
	int HookNumber = 0;
	int YoyoNumber = 0;
	int HookCnt[4] = { 0,0,0,0 };
	int YoyoCntX = 0;
	int YoyoCntY = 0;
	int grabState = 0;
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* hook[7];
	Object* rail[4];
	Object* YoyoObject[2]; //YoyObject[0] = ヨーヨーの支点 YoyoObject[1] = ヨーヨーの本体
	GrabBox* grabbox;
	Pendulum* pendulum; // 振り子オブジェクト
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
