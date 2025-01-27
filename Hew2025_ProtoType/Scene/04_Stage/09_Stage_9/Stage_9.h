/**	@file 	Stage_9.h
*	@brief 	Stage_9
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
/**	@file	Stage_9.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_9 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_9();
	/**	@brief 	デストラクタ
	*/
	~Stage_9()override;
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

	XMFLOAT3 playerPos = { 300.0f,-4700.0f,0.0f };

	XMFLOAT2 PushObjectPos = { 3500.0f,-4400.0f }; //ペンケース
	XMFLOAT2 BallPos = { 4300.0f, -1400.0f }; //ボールオブジェクト
	XMFLOAT2 HookPos00 = { 1500.0f,-5200.0f }; //地上フック
	XMFLOAT2 HookPos01 = { 5200, -1400.0f }; //空中フック

	XMFLOAT2 SlopePos00 = {1005.0f,-5095.0f }; //坂道左下
	XMFLOAT2 SlopePos01 = {2000.0f,-4955.0f }; //坂道右下
	XMFLOAT2 SlopePos02 = { 1425.0f,-3800.0f }; //坂道左上
	XMFLOAT2 SlopePos03 = { 2910.0f,-2900.0f }; //坂道右上

	XMFLOAT2 PenPos00 = { 4000.0f,-4525.0f }; //ペン1
	XMFLOAT2 PenPos01 = { 4100.0f, -4475.0f }; //ペン2

	XMFLOAT2 GoalPos = { 400,-3500.0f }; //ゴール

	//サイズ

	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 PushObjectSize = { 300.0f,1000.0f };
	XMFLOAT2 BallSize = { 500.0f,500.0f };
	XMFLOAT2 HookSize = { 200.0f,200.0f };

	XMFLOAT2 SlopeSize00 = { 100.0f,1100.0f }; //坂道左下
	XMFLOAT2 SlopeSize01 = { 100.0f,1200.0f }; //坂道右下
	XMFLOAT2 SlopeSize02 = { 100.0f,400.0f }; //坂道左上
	XMFLOAT2 SlopeSize03 = { 100.0f,3000.0f }; //坂道右上

	XMFLOAT2 PenSize = { 800.0f,50.0f };
	int gamemode = 0;

	
	float PushAngle = 90.0f;//ペンホルダーを横に
	float BallSpeed = 5.0f;
	float BallAngle = 0.0f;
	float SlopeAngle[4] = {45.0f,150.0f,45.0f,325.0f};
	bool SlopeState = true;//trueは登れる坂でfalseは登れない坂
	bool StayGround = false;//地面に触れているかの判定
	bool BallMoveFLG = false;//ボールが動いているかの判定
	int JumpState = 0;
	int BallState = 0;
	int cnt = 0;
	int n = 0;	//当たり判定用のブロックの番号
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Object* Slope[4];
	Player* player;
	Object* hook[2];
	Object* PushObject;
	Object* BallObject;
	Object* Pen[2];
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
