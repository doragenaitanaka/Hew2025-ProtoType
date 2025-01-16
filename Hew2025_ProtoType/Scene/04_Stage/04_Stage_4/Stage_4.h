/**	@file 	Stage_4.h
*	@brief 	Stage_4
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
/**	@file	Stage_4.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_4 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_4();
	/**	@brief 	デストラクタ
	*/
	~Stage_4()override;
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

	XMFLOAT2 CameraPos = { -100.0f, -150.0f };

	XMFLOAT2 BlockPos00 = { 3800.0f,-700.0f }; //右床
	XMFLOAT2 BlockPos01 = { -1000.0f,-700.0f }; //左床
	XMFLOAT2 BlockPos02 = { -1800.0f,1800.0f };	//左壁
	XMFLOAT2 BlockPos03 = { 2150.0f,1600.0f }; //空中左床
	XMFLOAT2 BlockPos04 = { 4250.0f,1600.0f }; //空中右床(下)
	XMFLOAT2 BlockPos05 = { 3700.0f,1800.0f }; //空中壁1
	XMFLOAT2 BlockPos06 = { 3700.0f,2800.0f }; //空中壁2
	XMFLOAT2 BlockPos07 = { 3000.0f,3500.0f }; //空中右床上

	XMFLOAT2 PushObjectPos00 = { 850.0f,200.0f }; //倒れるオブジェクト(下)
	XMFLOAT2 PushObjectPos01 = { 2650.0f,2200.0f }; //倒れるオブジェクト(上)

	XMFLOAT2 HookPos00 = { 3250.0f,100.0f }; //地上右フック
	XMFLOAT2 HookPos01 = { 4150.0f,2000.0f }; //空中右フック
	XMFLOAT2 HookPos02 = { 1900.0f,2100.0f };	//空中左フック(下)
	XMFLOAT2 HookPos03 = { 1900.0f,2950.0f }; //空中左フック(中)
	XMFLOAT2 HookPos04 = { 1900.0f,3800.0f }; //空中左フック(上)
	XMFLOAT2 HookPos05 = { 250.0f,100.0f }; //地上左フック(追加)

	XMFLOAT2 RailPos00 = { 3250.0f,1300.0f }; //地上右フック用
	XMFLOAT2 RailPos01 = { 4150.0f,2900.0f }; //空中右フック用
	XMFLOAT2 RailPos02 = { 2200.0f,3800.0f };	//空中左フック(上)用

	XMFLOAT2 GoalPos = { 3000.0f,3750.0f }; //ゴール

	//サイズ

	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 BlockSize00 = { 4000.0f,800.0f };
	XMFLOAT2 BlockSize01 = { 4000.0f,800.0f };
	XMFLOAT2 BlockSize02 = { 2400.0f,4200.0f };
	XMFLOAT2 BlockSize03 = { 1300.0f,200.0f };
	XMFLOAT2 BlockSize04 = { 1300.0f,200.0f };
	XMFLOAT2 BlockSize05 = { 200.0f,200.0f };
	XMFLOAT2 BlockSize06 = { 200.0f,1200.0f };
	XMFLOAT2 BlockSize07 = { 1600.0f,200.0f };

	XMFLOAT2 PushObjectSize00 = { 300.0f,1000.0f };
	XMFLOAT2 PushObjectSize01 = { 300.0f,1000.0f };

	XMFLOAT2 HookSize00 = { 200.0f,200.0f };
	XMFLOAT2 HookSize01 = { 200.0f,200.0f };
	XMFLOAT2 HookSize02 = { 200.0f,200.0f };
	XMFLOAT2 HookSize03 = { 200.0f,200.0f };
	XMFLOAT2 HookSize04 = { 200.0f,200.0f };
	XMFLOAT2 HookSize05 = { 200.0f,200.0f };

	XMFLOAT2 RailSize00 = { 100.0f,2600.0f };
	XMFLOAT2 RailSize01 = { 100.0f,2000.0f };
	XMFLOAT2 RailSize02 = { 800.0f,100.0f };

	XMFLOAT2 GoalSize = { 200.0f,300.0f };

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	float HookMoveSpeed = 5.0f;
	bool StayGround = false;//地面に触れているかの判定
	bool MoveHookFLG[3] = { false,false,false };//フックが動き出すかのフラグ
	bool TurnBackFLG[3] = { true,true,true };//フックが往復するためのフラグ
	int JumpState = 0;
	int cnt = 0;
	int drawnum = 0;//描画用のブロックの番号
	int n = 0;	//当たり判定用のブロックの番号
	int BlockNumber = 0;
	int PushNumber = 0;
	int HookNumber = 0;
	int HookCnt[3] = { 0,0,0 };
	int RailNumber = 0;
	int RailCnt[3] = { 0,0,0 };
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* block[100];
	Object* blockdraw[10000];
	Object* hook[6];
	Object* PushObject[2];
	Object* rail[3];
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
