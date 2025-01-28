/**	@file 	Stage_5.h
*	@brief 	Stage_5
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

	XMFLOAT2 CameraPos = { -700.0f, -150.0f };

	XMFLOAT2 BlockPos00 = { 0.0f,-350.0f };

	//サイズ

	XMFLOAT2 PlayerSize = { 100.0f,100.0f };

	XMFLOAT2 BlockSize00 = { 8000.0f,100.0f };

	int gamemode = 0;

	float posx = 0.0f;
	float posy = 0.0f;
	int drawnum = 0;//描画用のブロックの番号
	int n = 0;	//当たり判定用のブロックの番号
	int BlockNumber = 0;
	int ColliderState = 0;
private:
	Input input;
	Object* background;
	Player* player;
	Object* block[100];
	Object* blockdraw[10000];

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};
