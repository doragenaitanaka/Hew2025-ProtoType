/**	@file 	TitleScene.h
*	@brief 	タイトル
*	@date	2024/05/10
*/

#pragma once
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../Library/Code/self/01_GameManager/GameManager.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
#include"../../Library/Code/self/07_Camera/01_TrackingCamera/TrackingCamera.h"
#include"../../Library/Code/self/Ueda_FadeIn&FadeOut/FedaIn&FedaOut.h"
/**	@file	TitleScene.h
*	@brief 	タイトル
*	@date	2024/05/10
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class TitleScene:public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	TitleScene();
	/**	@brief 	デストラクタ
	*	@date	2024/05/10
	*/
	~TitleScene()override;
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

	XMFLOAT2 FingerPos = { -450.0f,-50.0f };//指
	XMFLOAT2 AbuttonPos = { FingerPos.x + 75.0f,FingerPos.y - 50.0f };//Aボタン
	XMFLOAT2 cloudPos00 = { -700.0f,-250.0f };//雲(小)
	XMFLOAT2 cloudPos01 = { 600.0f,250.0f };//雲(大)

	XMFLOAT2 LogoSize = {960.0f,540.0f};//タイトルロゴのサイズ
	XMFLOAT2 StartSize = { 640.0f,160.0f };//選択肢のサイズ
	XMFLOAT2 SelectSize = { 1120.0f,160.0f };//選択肢のサイズ
	XMFLOAT2 GameendSize = { 800.0f,160.0f };//選択肢のサイズ
private:
	float CloudMoveSpeed = 2.5f;//雲の移動速度
	int SelectState = 0;//選択のステート
	int Logocnt = 0;//タイトルロゴのcnt
	int UIcnt = 0;//選択肢用のcnt
	int Acnt = 0;//Aボタン用のcnt
	bool LogoState = true;//タイトルロゴのステート
	bool UIState = true;//選択肢用のステート
	bool AFlg = true;//Aボタン用のフラグ
	bool iflg = false;//フェードインフラグ

	Camera* p_camera;	// カメラ
	Input input;
	Object* background;//背景
	Object* logo;//タイトルロゴ
	Object* start;//ゲームスタート
	Object* select;//ステージセレクト
	Object* gameend;//ゲーム終了
	Object* finger;//指
	Object* cloud1;//雲(小)
	Object* cloud2;//雲(大)
	Object* abutton;//Aボタン
	FedaInOut* feda;//フェード
	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート

};