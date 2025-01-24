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
#include<array>

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
	float space = 250.0f;			// 幅
	float stageUISize = 270.0f;			// UIサイズ
	float stageUISizeSelect = 350.0f;	// 選択時のUIサイズ
	BaseCollider* p_leftUI;			// UIの左端
	BaseCollider* p_rightUI;		// UIの右端

	DirectX::XMFLOAT3 leftUIPos;	// UIの左端
	DirectX::XMFLOAT3 rightUIPos;	// UIの右端

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

	enum class SelectUI
	{
		FRAME,
		LEFT_ARROW,
		RIGHT_ARROW,
		L1,
		R1,
		STAGE_LOGO,
		BIYOND,

		NUM = BIYOND,
		MAX,
	};

	Camera* p_camera;		// カメラ
	PointCollider* p_point;	// ポインター

	//--------------------------------------------------------------------------
	//		オブジェクト
	//--------------------------------------------------------------------------
	Object* p_background;								// 背景
	Object* p_stageUI[static_cast<int>(Stage::MAX)];	// ステージUI
	Object* p_UI[static_cast<int>(SelectUI::MAX)];		// セレクト画面のUI

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
	
	// ステージセレクトUIのファイルパス
	std::wstring UIPath[static_cast<int>(SelectUI::MAX)] = {
				L"Asset/UI/waku.png",
				L"Asset/UI/hidari.png",
				L"Asset/UI/migi.png",
				L"Asset/UI/l1.png",
				L"Asset/UI/r1.png",
				L"Asset/UI/stage select.png",
				L"Asset/UI/biyond.png",
	};

	// ステージセレクトUIの座標
	std::array<DirectX::XMFLOAT3, static_cast<int>(SelectUI::MAX)>UIPos = {
		DirectX::XMFLOAT3(0.0f,0.0f,0.0f),

		DirectX::XMFLOAT3(-750.0f,-380.0f,0.0f),
		DirectX::XMFLOAT3(750.0f,-380.0f,0.0f),

		DirectX::XMFLOAT3(-400.0f,-380.0f,0.0f),
		DirectX::XMFLOAT3(400.0f,-380.0f,0.0f),

		DirectX::XMFLOAT3(0.0f,300.0f,0.0f),

		DirectX::XMFLOAT3(-810.0f,450.0f,0.0f),
	};

	// ステージセレクトUIのサイズ
	std::array<DirectX::XMFLOAT3, static_cast<int>(SelectUI::MAX)>UISize = {
		DirectX::XMFLOAT3(1920.0f, 1080.0f,0.0f),

		DirectX::XMFLOAT3(125.0f,150.0f,0.0f),
		DirectX::XMFLOAT3(125.0f,150.0f,0.0f),

		DirectX::XMFLOAT3(150.0f,175.0f,0.0f),
		DirectX::XMFLOAT3(150.0f,175.0f,0.0f),

		DirectX::XMFLOAT3(1100.0f,200.0f,0.0f),

		DirectX::XMFLOAT3(900.0f,500.0f,0.0f),
	};

	//--------------------------------------------------------------------------
	//		描画関連
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  入力レイアウト
	CVertexShader* p_vertexShader;		//  頂点シェーダ
	CPixelShader* p_pixelShader;		//  ピクセルシェーダ
	CSampler* p_sampler;				// サンプラー
	ID3D11BlendState* p_brendState;		// アルファブレンディング用ステート
};