/**	@file 	Stage_1.h
*	@brief 	Stage_1
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
#include <memory> 
/**	@file	Stage_1.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_1 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_1();
	/**	@brief 	デストラクタ
	*/
	~Stage_1()override;
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

	XMFLOAT2 CameraPos = { -700.0f, -50.0f };
	XMFLOAT2 CameraPos2 = { 0.0f, 0.0f };
	XMFLOAT2 PlayerPos = { 0.0f, -150.0f };
	XMFLOAT2 PlayerSize = { 120.0f,120.0f };
	float PlayerAngle = 0.0f;

	XMFLOAT2 PlayerDrawPos = { 0.0f, 40.0f };
	XMFLOAT2 PlayerDrawSize = { 140.0f,140.0f };


	XMFLOAT2 EyesPos = { 0.5f, +90.0f };
	XMFLOAT2 EyesSize = { 120.0f,120.0f };



	XMFLOAT2 PlayerColPos = { 30.0f, -135.0f };
	XMFLOAT2 PlayerColSize = { 110.0f,110.0f };

	XMFLOAT2 PlayerColPos3 = { -30.0f, -135.0f };
	XMFLOAT2 PlayerColSize3 = { 110.0f,110.0f };

	XMFLOAT2 PlayerColPos2 = { 0.0f, -80.0f };
	XMFLOAT2 PlayerColSize2 = { 120.0f,40.0f };

	XMFLOAT2 PlayerGrabPos = { 0.0f, 0.0f };

	XMFLOAT2 NewColPos = { 0.0f,-150.0f };
	XMFLOAT2 NewColSize = { 140.0f,20.0f };


	XMFLOAT2 BlockPos01 = { 0.0f,-350.0f };
	XMFLOAT2 BlockPos02 = { 100.0f, -200.0f };
	XMFLOAT2 BlockPos03 = { 2200.0f, -100.0f };
	XMFLOAT2 BlockPos04 = { 2600.0f, 300.0f };
	XMFLOAT2 BlockPos05 = { 2900.0f, 550.0f };
	XMFLOAT2 BlockPos06 = { 3100.0f, 700.0f };
	XMFLOAT2 BlockPos07 = { 3400.0f, 1800.0f };
	XMFLOAT2 BlockPos08 = { 800.0f, 1250.0f };

	XMFLOAT2 BlockDrawPos01 = { 000.0f,-200.0f };

	XMFLOAT2 HookPos01 = { 700.0f,0.0f };
	XMFLOAT2 HookPos02 = { 1300.0f, 300.0f };
	XMFLOAT2 HookPos03 = { 2250.0f, 800.0f };
	XMFLOAT2 HookPos04 = { 1800.0f, 1300.0f };

	XMFLOAT2 GoalPos = { 600.0f, 1400.0f };

	//サイズ
	XMFLOAT2 TestSize = { 100.0f,100.0f };



	XMFLOAT2 BlockDrawSize = { 0.0f,0.0f };
	XMFLOAT2 BlockSize01 = { 8000.0f,100.0f };
	XMFLOAT2 BlockSize02 = { 800.0f,200.0f };
	XMFLOAT2 BlockSize03 = { 2000.0f,400.0f };
	XMFLOAT2 BlockSize04 = { 2000.0f,400.0f };
	XMFLOAT2 BlockSize05 = { 1000.0f,100.0f };
	XMFLOAT2 BlockSize06 = { 1000.0f,200.0f };
	XMFLOAT2 BlockSize07 = { 1000.0f,2000.0f };
	XMFLOAT2 BlockSize08 = { 800.0f,100.0f };

	XMFLOAT2 HookSize01 = { 100.0f, 100.0f };
	XMFLOAT2 HookSize02 = { 100.0f, 100.0f };
	XMFLOAT2 HookSize03 = { 100.0f, 100.0f };
	XMFLOAT2 HookColSize01 = { 80.0f, 80.0f };

	XMFLOAT2 GoalSize = { 200.0f, 200.0f };

	XMFLOAT2 LefthandPos = { -62.0f,14.0f };
	XMFLOAT2 LefthandSize = { 105.0f,105.0f };

	XMFLOAT2 LeftlegPos = { -39.0f, -29.0f };
	XMFLOAT2 LeftlegSize = { 125.0f,125.0f };

	XMFLOAT2 RighthandPos = { 66.0f, 15.0f };
	XMFLOAT2 RighthandSize = { 105.0f,105.0f };

	XMFLOAT2 RightlegPos = { 50.0f, -30.0f };
	XMFLOAT2 RightlegSize = { 125.0f,125.0f };

	XMFLOAT2 IdlePos = { 0.0f,0.0f };
	XMFLOAT2 IdleSize = { 140.0f,140.0f };

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
	int gamemode = 1;
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
	int BlockNumber = 0;
	int HookCameraState = 0;
	int HookNumber = 0;
	int NewColState = 0;
	int ColliderState = 0;
	int HookColliderState = -1;
	bool ScenechangeState = false;
	std::shared_ptr<Object> blockdraw[768];
	std::shared_ptr<Object> block[8];
	std::shared_ptr<Object> hook[4];
private:
	Input input;
	Object* background;
	Object* playercol;
	Object* playercol2;
	Object* playercol3;
	Object* newcol;
	Player* player;
	Player* playerdraw;
	Object* eyes;
	Object* lefthand;
	Object* righthand;
	Object* leftleg;
	Object* rightleg;

	Object* idle;
	Object* walking;

	//Object* block[8];
	////Object* blockdraw[1000];
	//
	//Object* hook[4];
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
