/**	@file 	Stage_11.h
*	@brief 	Stage_11
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
#include"../../../Library/Code/self/16_Background/Background.h"

/**	@file	Stage_11.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_11 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_11();
	/**	@brief 	デストラクタ
	*/
	~Stage_11()override;
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

	XMFLOAT3 playerPos = { 1000.0f, -7650.0f,0.0f };

	XMFLOAT2 slopePos = { 2425.0f,-2625.0f };//坂道

	XMFLOAT2 HookPos00 = { 2700.0f,-7400.0f };//左フック
	XMFLOAT2 HookPos01 = { 5150.0f, -5000.0f };//空中右フック
	XMFLOAT2 HookPos02 = { 1300.0f, -3500.0f };//空中動く左フック
	XMFLOAT2 HookPos03 = { 650.0f, -2000.0f };//ゴール左フック

	XMFLOAT2 RailPos = { 650.0f,-3500.0f };//空中動くフックのレール

	XMFLOAT3 GrabboxPos00 = { 4750.0f,-4000.0f,0.0f };//振り子左の当たり判定用
	XMFLOAT3 GrabboxPos01 = { 5350.0f,-5300.0f,0.0f };//振り子右の当たり判定用

	XMFLOAT2 GoalPos = { 1600.0f,-1150.0f }; //ゴール
	//サイズ

	XMFLOAT2 PlayerSize = { 200.0f,200.0f };

	XMFLOAT2 slopeSize = { 1000.0f,100.0f };//坂道

	XMFLOAT2 HookSize = { 150.0f, 220.0f };//左フック

	XMFLOAT2 RailSize = { 50.0f,1400.0f };//レール

	XMFLOAT2 GrabboxSize = { 400.0f,400.0f };

	XMFLOAT2 GoalSize = { 200.0f,200.0f }; //ゴール

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float slopeAngle = 45.0f;
	float HookMoveSpeed = 5.0f;
	float YoyoMoveSpeed = 10.0f;
	float YoyoAngle = 0;
	bool GrabFlg = false;
	bool TurnBackFLG = true;
	bool YoyoTurnFLG[4] = { true,true,true,true };//0 1 = ヨーヨー左の縦横　2 3 = ヨーヨー右の縦横
	bool StayGround = false;//地面に触れているかの判定
	int JumpState = 0;
	int cnt = 0;
	int n = 0;	//当たり判定用のブロックの番号
	int HookCnt = 0;
	int YoyoCntX[2] = { 0,0 };
	int YoyoCntY[2] = { 0,0 };
	int grabState = 0;
	int ColliderState = 0;
private:
	Input input;
	Background* background;
	Player* player;
	Object* slope;
	Object* hook[4];
	Object* rail;
	GrabBox* grabbox[2];
	Pendulum* pendulum[2]; // 振り子オブジェクト
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
