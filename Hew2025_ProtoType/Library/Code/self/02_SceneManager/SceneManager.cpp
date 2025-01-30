/**	@file 	SceneManager.cpp
*	@brief 	シーン管理クラス
*	@date	2024/05/11
*/

#include"SceneManager.h"
#include"../../../../Scene/01_SplashScreanScene/SplashScreanScene.h"
#include"../../../../Scene/02_TitleScene/TitleScene.h"
#include"../../../../Scene/03_StageSelectScene/StageSelectScene.h"

// ステージ
#include"../../../../Scene/04_Stage/01_Stage_1/Stage_1.h"
#include"../../../../Scene/04_Stage/02_Stage_2/Stage_2.h"
#include"../../../../Scene/04_Stage/03_Stage_3/Stage_3.h"
#include"../../../../Scene/04_Stage/04_Stage_4/Stage_4.h"
#include"../../../../Scene/04_Stage/05_Stage_5/Stage_5.h"
#include"../../../../Scene/04_Stage/06_Stage_6/Stage_6.h"
#include"../../../../Scene/04_Stage/07_Stage_7/Stage_7.h"
#include"../../../../Scene/04_Stage/08_Stage_8/Stage_8.h"
#include"../../../../Scene/04_Stage/09_Stage_9/Stage_9.h"
#include"../../../../Scene/04_Stage/10_Stage_10/Stage_10.h"
#include"../../../../Scene/04_Stage/11_Stage_11/Stage_11.h"
#include"../../../../Scene/04_Stage/12_Stage_12/Stage_12.h"

#include"../../../../Scene/05_EndingScene/EndingScene.h"

// テスト
#include"../../../../Scene/93_Test_Takahashi/Test_Takahashi.h"
#include"../../../../Scene/94_Test_Otani/Test_Otani.h"
#include"../../../../Scene/95_Test_Ri/Test_Ri.h"
#include"../../../../Scene/96_Test_Imagawa/Test_Imagawa.h"
#include"../../../../Scene/97_Test_Ueda/Test_Ueda.h"
#include"../../../../Scene/98_Test_Uryu/Test_Uryu.h"
#include"../../../../Scene/99_TestScene/TestScene.h"

#include"../03_Windows/WindowSetup.h"
#include"../04_DirextX_11/01_Initialize/CD3D11.h"

#include<iostream>

//静的メンバ変数の初期化
SceneManager* SceneManager::sceneManager = nullptr;

//	private----------------------------------------------------------------------------------------------

/**	@brief 	コンストラクタ
*	@date	2024/05/11
*	@memo	外での生成を防ぐ
*/
SceneManager::SceneManager()
{
	this->isInitialized = false;	//初期化していない状態にしておく
	this->isChangedScene = false;	//シーン遷移していない状態にしておく
	this->nowScene = nullptr;
}

/**	@brief 	デストラクタ
*	@date	2024/05/11
*/
SceneManager::~SceneManager()
{
	//現在のシーンの解放
	if (this->nowScene)
	{
		delete	this->nowScene;
		this->nowScene = nullptr;
	}
}

/**	@brief 	シーンの生成
*	@param	Scene	sceneName	次のシーン名
*	@date	2024/05/11
*	@memo	非同期の時はここを戻り値BaseScene*にして複数個作れるようにする予定は未定！！！！！
*/
void	SceneManager::CreateScene(Scene sceneName)
{
	//現在のシーンが解放されていれば
	if (!this->nowScene) 
	{
		//引数に合わせてシーンを生成する
		switch (sceneName)
		{
		//case Scene::SplashScreanScene:
		//	this->nowScene = new	SplashScreanScene;
		//	break;
		case Scene::TitleScene:
			this->nowScene = new	TitleScene;
			break;
		case Scene::StageSelectScene:
			this->nowScene = new	StageSelectScene;
			break;

		//=====================
		//		ステージ
		//=====================
		case Scene::Stage_1:
			this->nowScene = new	Stage_1;
			break;
		case Scene::Stage_2:
			this->nowScene = new	Stage_2;
			break;
		case Scene::Stage_3:
			this->nowScene = new	Stage_3;
			break;
		case Scene::Stage_4:
			this->nowScene = new	Stage_4;
			break;
		case Scene::Stage_5:
			this->nowScene = new	Stage_5;
			break;
		case Scene::Stage_6:
			this->nowScene = new	Stage_6;
			break;
		case Scene::Stage_7:
			this->nowScene = new	Stage_7;
			break;
		case Scene::Stage_8:
			this->nowScene = new	Stage_8;
			break;
		case Scene::Stage_9:
			this->nowScene = new	Stage_9;
			break;
		case Scene::Stage_10:
			this->nowScene = new	Stage_10;
			break;
		case Scene::Stage_11:
			this->nowScene = new	Stage_11;
			break;
		case Scene::Stage_12:
			this->nowScene = new	Stage_12;
			break;

		////=====================
		////		テスト
		////=====================
		//case Scene::TEST:
		//	this->nowScene = new	TestScene;
		//	break;

		//case Scene::TEST_IMAGAWA:
		//	this->nowScene = new	Test_Imagawa;
		//	break;
		//case Scene::TEST_UEDA:
		//	this->nowScene = new	Test_Ueda;
		//	break;
		//case Scene::TEST_URYU:
		//	this->nowScene = new	Test_Uryu;
		//	break;
		//case Scene::TEST_RI:
		//	this->nowScene = new	Test_Ri;
		//	break;	
		//case Scene::TEST_OTANI:
		//	this->nowScene = new	Test_Otani;
		//	break;
		//case Scene::TEST_TAKAHASHI:
		//	this->nowScene = new	Test_Takahashi;
		//	break;
		default:
			break;
		}
	}
	//シーンが生成できていなければ
	if (!this->nowScene)
	{
		std::cerr << "シーン生成に失敗しました" << std::endl;
	}
}
 
//	public----------------------------------------------------------------------------------------------

/**	@brief 	シーン全体の実行関数
*	@date	2024/05/11
*	@memo	シーン全体の処理の流れ(初期化、更新、描画)をここに書く
*/
void	SceneManager::Run(void)
{
	//シーンが無ければ
	if (!this->nowScene)
	{
		std::cerr << "シーンが存在しません" << std::endl;
	}

	//まだ初期化されていなければ
	if (!this->isInitialized)
	{	
 		this->nowScene->Initialize();	//	初期化処理
		this->isChangedScene = false;	//　シーン遷移していない
		this->isInitialized = true;		//	初期済
	}

	this->nowScene->Update();			//	更新処理

	//シーン遷移されていなければ
	if (!this->isChangedScene)
	{
		// cd3d11クラスの取得
		CD3D11* cd3d11 = CD3D11::GetInstance();

		// 描画に必要なモノを取得
		ID3D11DeviceContext* context = cd3d11->GetDeviceContext();
		ID3D11RenderTargetView* renderTargetView = cd3d11->GetRenderTargetView();
		IDXGISwapChain* swapChain = cd3d11->GetSwapChain();
		ID3D11DepthStencilView* depthStencilView = cd3d11->GetDepthStencilView();

		//画面クリア
		float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha							// 画面塗りつぶし色
		context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);								// 描画先のキャンバスと使用する深度バッファを指定する
		context->ClearRenderTargetView(renderTargetView, clearColor);										// 描画先キャンバスを塗りつぶす
		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);	// 深度バッファをリセットする

		this->nowScene->Draw();			// 描画処理

		swapChain->Present(0, 0);		// バッファの切り替え
	}
}
/**	@brief 	シーン遷移関数
*	@param	Scene	sceneName	次のシーン名
*	@date	2024/05/11
*/
void	SceneManager::ChangeScene(Scene	sceneName)
{
	if (this->nowScene)					//	現在のシーンのメモリを解放
	{
		delete	this->nowScene;
		this->nowScene = nullptr;
	}
	this->CreateScene(sceneName);		//	次のシーン生成

	this->isInitialized = false;		//	初期化フラグリセット
	this->isChangedScene = true;		//　シーン遷移した
}
//	public (static)----------------------------------------------------------------------------------------------

/**	@brief 	シーンマネージャーの生成
*	@date	2024/05/11
*	@memo	この関数を始めに実行する
*/
void	SceneManager::CreateInstance(void)
{
	//生成されていなければシーンマネージャーを生成する
	if (!SceneManager::sceneManager)
	{
		//cout << "シーンマネージャーを生成します" << endl;
		SceneManager::sceneManager = new	SceneManager;
	}
}
/**	@brief 	シーンマネージャーの削除
*	@date	2024/05/11
*/
void	SceneManager::DestroyInstance(void)
{
	if (SceneManager::sceneManager)
	{
		//cout << "シーンマネージャーを消去します" << endl;
		delete	SceneManager::sceneManager;
		SceneManager::sceneManager = nullptr;
	}
}
/**	@brief 	シーンマネージャーの取得
*	@return	SceneManager*	シーンマネージャー
*	@date	2024/05/11
*	@memo	この関数を使って各ファイルで生成済シーンマネージャーを取得する
*/
SceneManager* SceneManager::GetInstance(void)
{
	return	SceneManager::sceneManager;
}