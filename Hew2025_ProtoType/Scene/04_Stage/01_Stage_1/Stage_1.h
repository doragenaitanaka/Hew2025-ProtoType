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

	XMFLOAT2 CameraPos = { -700.0f, -150.0f };

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
	XMFLOAT2 PlayerSize = { 100.0f,100.0f };
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

	XMFLOAT2 GoalSize = { 200.0f, 200.0f };

	int gamemode=0;

	float posx = 0.0f;
	float posy = 0.0f;
	int drawnum = 0;
	int n = 0;
	int m = 0;
	int BlockNumber = 0;
	int HookNumber = 0;
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* block[100];
	Object* blockdraw[10000];
	Object* hook[100];
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
