/**	@file 	SceneManager.cpp
*	@brief 	シーン管理クラス
*	@date	2024/05/11
*/

#include"SceneManager.h"
#include"../../../../Scene/01_TitleScene/TitleScene.h"
#include"../../../../Scene/02_GameScene/GameScene.h"
#include"../../../../Scene/03_ResultScene/ResultScene.h"

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
		case Scene::TITLE:
			//cout << "TitleSceneを生成" << endl;
			this->nowScene = new	TitleScene;
			break;
		case Scene::GAME:
			//cout << "GameSceneを生成" << endl;
			this->nowScene = new	GameScene;
			break;
		case Scene::RESULT:
			//cout << "ResultSceneを生成" << endl;
			this->nowScene = new	ResultScene;
			break;
		case Scene::TEST:
			//cout << "TestSceneを生成" << endl;
			this->nowScene = new	TestScene;
			break;

		case Scene::TEST_IMAGAWA:
			//cout << "TestSceneを生成" << endl;
			this->nowScene = new	Test_Imagawa;
			break;
		case Scene::TEST_UEDA:
			//cout << "TestSceneを生成" << endl;
			this->nowScene = new	Test_Ueda;
			break;
		case Scene::TEST_URYU:
			//cout << "TestSceneを生成" << endl;
			this->nowScene = new	Test_Uryu;
			break;
		case Scene::TEST_RI:
			//cout << "TestSceneを生成" << endl;
			this->nowScene = new	Test_Ri;
			break;
		//case Scene::TAKAHASHI_TEST:
		//	//cout << "TestSceneを生成" << endl;
		//	this->nowScene = new	TestScene;
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