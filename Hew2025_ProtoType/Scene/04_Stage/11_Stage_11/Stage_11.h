/**	@file 	Stage_11.h
*	@brief 	Stage_11
*	@date	2024/12/19
*/
#pragma once

//インクルード
#include"../../00_BaseScene/BaseScene.h"
#include"../../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/12_GrabBox/GrabBox.h"
#include"../../../Library/Code/self/15_Pendulum/Pendulum.h"
#include"../../../Library/Code/self/imagawa_Input/input.h"
#include"../../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
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

	XMFLOAT3 CameraPos = { -900.0f, 300.0f,0.0f };

	XMFLOAT2 BlockPos00 = { 0.0f,0.0f };//基底床
	XMFLOAT2 BlockPos01 = { -1500.0f,3000.0f };//空中左壁
	XMFLOAT2 BlockPos02 = { 1500.0f,4150.0f };//空中右壁
	XMFLOAT2 BlockPos03 = { 950.0f,3025.0f };//階段右
	XMFLOAT2 BlockPos04 = { -500.0f,3075.0f };//階段左の乗るほう
	XMFLOAT2 BlockPos05 = { 50.0f,3900.0f };//ゴール床

	XMFLOAT2 HookPos00 = { -600.0f,400.0f };//左フック
	XMFLOAT2 HookPos01 = { 1500.0f, 1500.0f };//空中右フック
	XMFLOAT2 HookPos02 = { -200.0f, 2400.0f };//空中動く左フック
	XMFLOAT2 HookPos03 = { -1000.0f, 3700.0f };//ゴール左フック

	XMFLOAT2 YoyoPos00 = { 1050.0f,2200.0f };//ヨーヨー左の本体
	XMFLOAT2 YoyoPos01 = { 1250.0f,1400.0f };//ヨーヨー右の本体

	XMFLOAT2 RailPos00 = { -950.0f,2400.0f };//空中動くフックのレール

	XMFLOAT3 GrabboxPos00 = { 1050.0f,2200.0f,0.0f };//振り子左の当たり判定用
	XMFLOAT3 GrabboxPos01 = { 1250.0f,1400.0f,0.0f };//振り子右の当たり判定用

	XMFLOAT2 GoalPos = { 50.0f,4550.0f }; //ゴール
	//サイズ

	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 BlockSize00 = { 3500.0f,300.0f };//基底床
	XMFLOAT2 BlockSize01 = { 500.0f,800.0f };//空中左壁
	XMFLOAT2 BlockSize02 = { 300.0f,3100.0f };//空中右壁
	XMFLOAT2 BlockSize03 = { 1100.0f,100.0f };//階段右
	XMFLOAT2 BlockSize04 = { 500.0f,650.0f };//階段左の乗るほう
	XMFLOAT2 BlockSize05 = { 600.0f,1000.0f };//ゴール床

	XMFLOAT2 HookSize00 = { 200.0f, 200.0f };//左フック
	XMFLOAT2 HookSize01 = { 200.0f, 200.0f };//右フック
	XMFLOAT2 HookSize02 = { 200.0f, 200.0f };//ゴール横
	XMFLOAT2 HookSize03 = { 200.0f, 200.0f };//ゴール横

	XMFLOAT2 YoyoSize00 = { 400.0f,400.0f };//ヨーヨー左の本体
	XMFLOAT2 YoyoSize01 = { 400.0f,400.0f };//ヨーヨー右の本体

	XMFLOAT2 RailSize00 = { 1500.0f,100.0f };//レール

	XMFLOAT2 GrabboxSize00 = { 400.0f,400.0f };
	XMFLOAT2 GrabboxSize01 = { 400.0f,400.0f };
	XMFLOAT2 GoalSize = { 200.0f,300.0f }; //ゴール

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float slopeAngle = -45.0f;
	float HookMoveSpeed = 5.0f;
	float YoyoMoveSpeed = 10.0f;
	bool GrabFlg = false;
	bool TurnBackFLG = true;
	bool YoyoTurnFLG[4] = { true,true,true,true };//0 1 = ヨーヨー左の縦横　2 3 = ヨーヨー右の縦横
	bool StayGround = false;//地面に触れているかの判定
	int JumpState = 0;
	int cnt = 0;
	int drawnum = 0;//描画用のブロックの番号
	int n = 0;	//当たり判定用のブロックの番号
	int BlockNumber = 0;
	int YoyoNumber = 0;
	int BoxNumber = 0;
	int HookNumber = 0;
	int HookCnt = 0;
	int YoyoCntX[2] = { 0,0 };
	int YoyoCntY[2] = { 0,0 };
	int grabState = 0;
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* block[100];
	Object* blockdraw[10000];
	Object* hook[4];
	Object* rail;
	GrabBox* grabbox[2];
	Pendulum* pendulum[2]; // 振り子オブジェクト
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
