/**	@file 	StageSelectScene.h
*	@brief	ステージセレクト
*	@date	2024/12/19
*/
#pragma once
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/11_Player/Player.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
#include"../../Library/Code/self/07_Camera/Camera.h"
#include"../../Library/Code/self/05_Collider/03_PointCollider/PointCollider.h"

#include<string>

/**	@file	StageSelectScene.h
*	@brief	ステージセレクト
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class StageSelectScene :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	StageSelectScene();
	/**	@brief 	デストラクタ
	*/
	~StageSelectScene()override;
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
	float space = 200.0f;			// 幅
	float UISize = 330.0f;			// UIサイズ
	BaseCollider* p_leftUI;			// UIの左端
	BaseCollider* p_rightUI;		// UIの右端

	DirectX::XMFLOAT3 leftUIPos;	// UIの左端
	DirectX::XMFLOAT3 rightUIPos;  // UIの右端

	enum class Stage
	{
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_6,
		STAGE_7,
		STAGE_8,
		STAGE_9,
		STAGE_10,
		STAGE_11,
		STAGE_12,
		NUM = STAGE_12,
		MAX,
	};

	Camera* p_camera;	// カメラ

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------
	Object* p_background;	// 背景
	Object* p_obj;	
	Object* p_stageUI[static_cast<int>(Stage::MAX)];	// ステージUI

	// ステージUIファイルパス
	std::wstring stageUIPath[static_cast<int>(Stage::MAX)] = {
		L"Asset/UI/bangou1.png",
		L"Asset/UI/bangou2.png",
		L"Asset/UI/bangou3.png",
		L"Asset/UI/bangou4.png",
		L"Asset/UI/bangou5.png",
		L"Asset/UI/bangou6.png",
		L"Asset/UI/bangou7.png",
		L"Asset/UI/bangou8.png",
		L"Asset/UI/bangou9.png",
		L"Asset/UI/bangou10.png",
		L"Asset/UI/bangou11.png",
		L"Asset/UI/bangou12.png"
	};
	PointCollider* p_point;			// ポインター

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};