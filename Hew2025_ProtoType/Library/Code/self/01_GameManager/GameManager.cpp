/**	@file 	GameManager.cpp
*	@brief 	プロジェクト全体の管理クラス
*	@date	2024/05/20
*/
#include<Windows.h>
#include"GameManager.h"

//==================最初に実行されるシーン(ここしかいじっちゃダメ！！！！！！)========================

Scene GameManager::startScene = Scene::TEST_UEDA;

//====================================================================================================
GameManager* GameManager::gameManager = nullptr;

/**	@brief 	クラスインスタンスの生成関数
*	@date	2024/05/20
*	@memo	この関数を始めに実行する
*/
void	GameManager::CreateInstance(void)
{
	if (!GameManager::gameManager)
	{
		GameManager::gameManager = new	GameManager;
	}
}

/**	@brief 	クラスインスタンスの取得関数
*	@return	GameManager*	GameManagerクラス
*	@date	2024/05/20
*/
GameManager* GameManager::GetInstance(void)
{
	return	GameManager::gameManager;
}
//public	------------------------------------------------------------------------------------

/**	@brief 	クラスインスタンスの削除関数
*	@return	GameManager*	GameManagerクラス
*	@date	2024/05/20
*/
void    GameManager::DestroyInstance(void)
{
	//存在していたら解放
	if (GameManager::gameManager)
	{
		delete	GameManager::gameManager;
		GameManager::gameManager = nullptr;
	}
}

/**	@brief 	プロジェクト全体の実行関数
*	@param	_In_ HINSTANCE hInstance		現在のアプリケーションインスタンスへのハンドル
*	@param	BackColorBrush      backColor	ウィンドウの背景色
*	@param	 _In_ int       nCmdShow		ウィンドウが表示される時の状態
*	@date	2024/05/20
*/
int	GameManager::Run(_In_ HINSTANCE hInstance, _In_ int       nCmdShow)
{
	this->windowSetup->Initialize(hInstance, nCmdShow);			// windowsの初期化
	this->cd3d11->Initialize(this->windowSetup->GetHWnd());		// d3d11の初期化
	MSG msg = { 0 };	

	// 最初のシーンを生成
	this->sceneManager->ChangeScene(GameManager::startScene);		

	// fps固定用
	LARGE_INTEGER	liWork;	// 作業用変数								
	QueryPerformanceFrequency(&liWork);
	this->frequency = liWork.QuadPart;

	// 時間(単位：カウント)を取得		
	QueryPerformanceCounter(&liWork);
	this->oldCount = liWork.QuadPart;
	this->nowCount = this->oldCount;

	//ゲームループ
	while (this->isRunning)
	{
		// windows関連
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {		//  メッセージがあれば
			TranslateMessage(&msg);
			DispatchMessage(&msg);							//  ウィンドウプロシージャにメッセージを送る
		}
		if (WM_QUIT == msg.message) return 0;				//  ×押すと終了する
		else
		{
			// 現在の時間を取得
			QueryPerformanceCounter(&liWork);
			this->nowCount = liWork.QuadPart;

			// 指定したフレームレートが経過したら
			if (this->nowCount >= this->oldCount + this->frequency / FPS)
			{
				this->sceneManager->Run();				// シーンの実行

				// FPS関連
				this->fpsCounter++;						// ゲーム処理を実行したら+1
				this->oldCount = this->nowCount;		
			}


			// FPS関連
			this->nowTick = GetTickCount64();	// 現在時間を取得		
			if (this->nowTick >= this->oldTick + 1000)
			{
				// FPSを表示
				char	str[32];
				wsprintfA(str, "FPS=%d", this->fpsCounter);				// 数値を文字列に変換
				SetWindowTextA(this->windowSetup->GetHWnd(), str);		// ウィンドウタイトルに表示

				// カウンターリセット
				this->fpsCounter = 0;
				this->oldTick = nowTick;
			}
		}
	}
	this->sceneManager->DestroyInstance();					// シーン管理クラスの削除
	this->cd3d11->DestroyInstance();						// CD3D11クラスの削除
	this->windowSetup->DestroyInstance(hInstance);			// ウィンドウクラスの削除
	return (int)msg.wParam;									// ウィンドウプロシージャに渡す
}

/**	@brief 	プロジェクトを終了する関数
*	@date	2024/05/20
*	@memo	ゲームループ可動フラグをfalseにする
*/
void	GameManager::EndGame(void)
{
	//ゲームループを抜ける
	if (this->isRunning)
	{
		this->isRunning = false;
	}
}

GameManager::GameManager()
{
	// クラスインスタンスの作成
	WindowSetup::CreateInstance();	// windows初期化クラス
	CD3D11::CrerateIntance();		// D3D11初期化クラス
	SceneManager::CreateInstance();	// シーン管理クラス

	//クラスインスタンスの取得
	this->windowSetup = WindowSetup::GetInstance();		// windows初期化クラス
	this->cd3d11 = CD3D11::GetInstance();				// D3D11初期化クラス
	this->sceneManager = SceneManager::GetInstance();	// シーン管理クラス

	this->isRunning = true;								// ゲームループ可動中

	// FPS計測用変数
	this->fpsCounter = 0;
	this->oldTick = GetTickCount64();								// 前回計測時の時間を取得
	this->nowTick = this->oldTick;									// 今回計測時の時間

	// FPS固定用関数
	this->frequency = 0.0f;
	// 時間(単位：カウント)
	this->oldCount = 0.0f;
	this->nowCount = this->oldCount;
}

GameManager::~GameManager()
{}

