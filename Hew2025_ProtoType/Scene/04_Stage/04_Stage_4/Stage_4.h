/**	@file 	Stage_4.h
*	@brief 	Stage_4
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
#include"../../../Library/Code/self/16_Background/Background.h"
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

private:
	//座標
	XMFLOAT3 playerPos = { 2500.0f,-4200.0f,0.0f };

	XMFLOAT2 BlockPos00 = { 3800.0f,-700.0f }; //右床
	XMFLOAT2 BlockPos01 = { -1000.0f,-700.0f }; //左床
	XMFLOAT2 BlockPos02 = { -1800.0f,1800.0f };	//左壁
	XMFLOAT2 BlockPos03 = { 2150.0f,1600.0f }; //空中左床
	XMFLOAT2 BlockPos04 = { 4250.0f,1600.0f }; //空中右床(下)
	XMFLOAT2 BlockPos05 = { 3700.0f,1800.0f }; //空中壁1
	XMFLOAT2 BlockPos06 = { 3700.0f,2800.0f }; //空中壁2
	XMFLOAT2 BlockPos07 = { 3000.0f,3500.0f }; //空中右床上

	XMFLOAT2 PushObjectPos00 = { 3600.0f,-3750.0f }; //倒れるオブジェクト(下)
	XMFLOAT2 PushObjectPos01 = { 5300.0f,-1750.0f }; //倒れるオブジェクト(上)

	XMFLOAT2 HookPos00 = { 6250.0f,-4000.0f };	//地上右フック
	XMFLOAT2 HookPos01 = { 7800, -1950 };		//空中右フック
	XMFLOAT2 HookPos02 = { 4500.0f,-1850.0f };	//空中左フック(下)
	XMFLOAT2 HookPos03 = { 4500.0f,-1050.0f };	//空中左フック(中)
	XMFLOAT2 HookPos04 = { 4500.0f,-150.0f };	//空中左フック(上)
	XMFLOAT2 HookPos05 = { 3000.0f,-3850.0f };	//地上左フック(追加)

	XMFLOAT2 RailPos00 = { 6250.0f,-2800.0f }; //地上右フック用
	XMFLOAT2 RailPos01 = { 7800.0f,-1050.0f }; //空中右フック用
	XMFLOAT2 RailPos02 = { 5200.0f,-150.0f };	//空中左フック(上)用

	XMFLOAT2 GoalPos = { 6300,-100.0f }; //ゴール

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

	XMFLOAT2 PushObjectSize = { 300.0f,800.0f };

	XMFLOAT2 HookSize = { 200.0f,200.0f };

	XMFLOAT2 RailSize00 = { 100.0f,2600.0f };
	XMFLOAT2 RailSize01 = { 100.0f,2000.0f };
	XMFLOAT2 RailSize02 = { 100.0f,1500.0f };

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

	Input input;
	Background* background;
	Player* player;
	Object* hook[6];
	Object* PushObject[2];
	Object* rail[3];
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
