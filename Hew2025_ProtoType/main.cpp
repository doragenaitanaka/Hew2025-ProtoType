#include<Windows.h>
#include"Library/Code/self/04_GameManager/GameManager.h"
#include"Library/Code/self/01_Windows/WindowSetup.h"

//  ウィンドウ画面を出すのに必要な情報をとる関数
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,			//  アプリの情報を格納したメモリ領域ポインタ(実行する各アプリ、OSのハンドル)
	_In_opt_ HINSTANCE hPrevInstance,	//  今は使われていないのでnullが入る
	_In_ LPWSTR    lpCmdLine,			//  アプリケーション起動時にコマンドラインで指定された引数が入る
	_In_ int       nCmdShow)			//  表示方法,ウィンドウが表示される時の状態
{

	GameManager::CreateInstance();							// インスタンスの生成
	GameManager* gameManager = GameManager::GetInstance();	// インスタンスの取得
	int msg = 0;

	msg = gameManager->Run(hInstance, nCmdShow);

	return msg;		// ウィンドウプロシージャに渡す

}