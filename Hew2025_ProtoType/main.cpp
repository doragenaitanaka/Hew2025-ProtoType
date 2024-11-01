#include<Windows.h>
#include"Library/Code/self/04_GameManager/GameManager.h"
#include"Library/Code/self/01_Windows/WindowSetup.h"
#include"main.h"

//  ウィンドウ画面を出すのに必要な情報をとる関数
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,			//  アプリの情報を格納したメモリ領域ポインタ(実行する各アプリ、OSのハンドル)
	_In_opt_ HINSTANCE hPrevInstance,	//  今は使われていないのでnullが入る
	_In_ LPWSTR    lpCmdLine,			//  アプリケーション起動時にコマンドラインで指定された引数が入る
	_In_ int       nCmdShow)			//  表示方法,ウィンドウが表示される時の状態
{
#ifdef DEBUG
    // コンソールウィンドウの初期化
    if (InitConsole() != 0) {
        return 1; 
    }
#endif // DEBUG

    GameManager::CreateInstance();							// インスタンスの生成
    GameManager* gameManager = GameManager::GetInstance();	// インスタンスの取得
    int msg = 0;

    msg = gameManager->Run(hInstance, nCmdShow);
    return msg;		// ウィンドウプロシージャに渡す
}

/**	@brief 	コンソールウィンドウの初期化
*	@date	2024/11/02
*/
int InitConsole()
{
    // コンソールウィンドウの初期化
    if (!AllocConsole()) {
        MessageBox(NULL, L"Failed to allocate console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // std入出力のリダイレクト先をコンソール画面にする
    FILE* fp = nullptr;
    errno_t err = freopen_s(&fp, "CONOUT$", "w", stdout);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stdout to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    err = freopen_s(&fp, "CONIN$", "r", stdin);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stdin to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    err = freopen_s(&fp, "CONOUT$", "w", stderr);
    if (err != 0) {
        MessageBox(NULL, L"Failed to redirect stderr to console.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 標準入出力ストリームの同期を有効
    std::ios::sync_with_stdio();
    // 標準ストリームのクリア
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();

    // ファイルポインタを閉じる
    if (fp)fclose(fp);
    fp = nullptr;
}