/**	@file 	Stage_8.h
*	@brief 	Stage_8
*	@date	2024/12/19
*/
#pragma once

//インクルード
#include"../../00_BaseScene/BaseScene.h"
#include"../../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../../Library/Code/self/imagawa_Input/input.h"
#include"../../../Library/Code/self/06_TileMap/TileMap.h"
#include"../../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"

#include"../../../Library/Code/self/10_Object/Object.h"
#include"../../../Library/Code/self/11_Player/Player.h"
#include"../../../Library/Code/self/16_Background/Background.h"
#include"../../../Library/Code/self/18_Pen/Pen.h"

#include"../../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"

#include<array>
/**	@file	Stage_8.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_8 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_8();
	/**	@brief 	デストラクタ
	*/
	~Stage_8()override;
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

	XMFLOAT2 PlayerSize = { 200.0f,200.0f };//サイズ

	//ゴール
	XMFLOAT2 GoalPos = { 100.0f,-120.0f }; 
	XMFLOAT2 GoalSize = { 200.0f,300.0f };

	// フックの座標
	std::array<XMFLOAT2, 5>HookPos = {
		XMFLOAT2(800.0f,-3750.0f),	//左フック
		XMFLOAT2(3820.0f, -2750.0f),	//右フック
		XMFLOAT2(4580.0f,-1600.0f),	//ゴール横
		XMFLOAT2(2150.0f,-1250.0f),	//ゴール横
		XMFLOAT2(620.0f,-160.0f),	//ゴール横
	};
	// フックのサイズ
	std::array<XMFLOAT2, 5>HookSize = {
		XMFLOAT2(150.0f, 220.0f),
		XMFLOAT2(150.0f, 220.0f),
		XMFLOAT2(150.0f, 220.0f),
		XMFLOAT2(150.0f, 220.0f),
		XMFLOAT2(150.0f, 220.0f),
	};

	// 倒れるオブジェクトの座標
	std::array<XMFLOAT2, 2>PushObjectPos = {
		XMFLOAT2(3450.0f,-1120.0f),	
		XMFLOAT2(1300.0f, -3620.0f),	
	};
	
	// 倒れるオブジェトのサイズ
	std::array<XMFLOAT2, 2>PushObjectSize = {
		XMFLOAT2(500.0f,950.0f),
		XMFLOAT2(500.0f,950.0f)
	};

	// ペンの座標
	std::array<XMFLOAT2, 2>PenPos = {
		XMFLOAT2(3000.0f,-1520.0f),
		XMFLOAT2(1700.0f, -4020.0f),
	};

	// ペンのサイズ
	std::array<XMFLOAT2, 2>PenSize = {
		XMFLOAT2(900.0f,100.0f),
		XMFLOAT2(900.0f,100.0f)
	};
private:
	int gamemode = 0;
	int n = 0;
	int ColliderState = 0;
	int cnt = 0;
	int HookNumber = 0;
	int PushNumber = 0;
	int PenNumber = 0;
	int JumpState = 0;
	bool StayGround = false;//地面に触れているかの判定

	TrackingCamera* p_camera;	// カメラ
	TileMap* p_tileMap;			//タイルマップ
	//Input input;

	Object* background;
	Player* player;
	Object* hook[5];
	Object* PushObject[2];
	Object* Pen[2];
	Object* goal;

	//Object* block[100];
	//Object* blockdraw[10000];

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
