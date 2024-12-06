#include"WindowSetup.h"
#include"../SafePointers.h"
//	public (static)----------------------------------------------------------------------------------------------

/**	@brief 	windowsクラスの生成
*	@date	2024/05/14
*	@memo	この関数を始めに実行する
*/
void	WindowSetup::CreateInstance(void)
{
	//生成されていなければwindowsクラスを生成する
	if (!WindowSetup::appWindow)
	{
		WindowSetup::appWindow = new	WindowSetup;
	}
}
/**	@brief 	windowsクラスの取得
*	@return	WindowSetup*	windowsクラス
*	@date	2024/05/14
*	@memo	この関数を使って各ファイルで生成済windowsクラスを取得する
*/
WindowSetup* WindowSetup::GetInstance(void)
{
	return	WindowSetup::appWindow;
}
//	public -----------------------------------------------------------------------------------------------

/**	@brief	全体の初期化
*	@param	_In_ HINSTANCE hInstance		現在のアプリケーションインスタンスへのハンドル
*	@param	BackColorBrush      backColor	ウィンドウの背景色
*	@param	 _In_ int       nCmdShow		ウィンドウが表示される時の状態
*	@date	2024/05/14
*/
int	WindowSetup::Initialize(_In_ HINSTANCE hInstance, _In_ int       nCmdShow)
{
	int	er;
	if (er = this->RegisterWindowClass(hInstance) == E_FAIL) { return	er; }
	if (er = this->CreateWindowScreen() == E_FAIL) { return	er; }
	if (er = this->ShowWindowScreen(nCmdShow) == E_FAIL) { return	er; }

	return	er;
}
/**	@brief 	windowsクラスの削除
*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
*	@date	2024/05/14
*/
void	WindowSetup::DestroyInstance(_In_ HINSTANCE hInstance)
{
	//存在していたら
	if (WindowSetup::appWindow)
	{
		this->UnregisterWindowClass(hInstance);	//ウィンドウクラスの登録解除
		delete	WindowSetup::appWindow;
		WindowSetup::appWindow = nullptr;
	}
}
/**	@brief	ハンドルを取得
*	@return	HWND	windowsハンドル
*	@date	2024/05/14
*/
HWND	WindowSetup::GetHWnd(void)
{
	return	this->hWnd;
}
//	private ----------------------------------------------------------------------------------------------
/**	@brief 	コンストラクタ
*	@date 2024/03/29
*/
WindowSetup::WindowSetup()
{
	isInit = false;		//true:wcexを初期化した
}
/**	@brief 	デストラクタ
*	@date 2024/03/29
*/
WindowSetup::~WindowSetup()
{}
/**	@brief 	ウィンドウクラスの登録関数
*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
*	@param	BackColorBrush      backColor	ウィンドウの背景色
*	@return
*	@date 2024/03/29
*	@memo	ウィンドウクラスの定義、登録を行う
*/
int	WindowSetup::RegisterWindowClass(_In_ HINSTANCE hInstance)
{
	//ウィンドウクラス
	this->wcex.cbSize = sizeof(WNDCLASSEX);		//構造体のサイズ
	this->wcex.style = CS_CLASSDC;				//クラススタイル
	this->wcex.lpfnWndProc = WndProc;			//ウィンドウプロシージャへのポインター
	this->wcex.cbClsExtra = 0L;					//クラスデータ構造体の後に割り当てる追加のバイト数
	this->wcex.cbWndExtra = 0L;					//ウィンドウインスタンスの後に割り当てる追加のバイト数
	this->wcex.hInstance = hInstance;			//アプリケーションインスタンスのハンドル
	this->wcex.hIcon = NULL;					//ウィンドウクラスのアイコンへのハンドル
	this->wcex.hCursor = NULL;					//ウィンドウクラスのカーソルへのハンドル
	this->wcex.hbrBackground = (HBRUSH)GetStockObject(BackColorBrush::DKGRAY);	// ウィンドウの背景ブラシへのハンドル
	this->wcex.lpszMenuName = NULL;				//メニューリソースの名前
	this->wcex.lpszClassName = CLASS_NAME;		//ウィンドウクラスの名前
	this->wcex.hIconSm = NULL;					//小さいアイコンへのハンドル

	//RegisterClassEx関数に渡せたかチェック
	if (!RegisterClassEx(&this->wcex))
	{
		return	E_FAIL;
	}
	//初期化した
	isInit = true;

	return	S_OK;
}
/**	@brief 	ウィンドウクラスの登録を解除する関数
*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
*	@return
*	@date 2024/05/14
*/
void	WindowSetup::UnregisterWindowClass(_In_ HINSTANCE hInstance)
{
	if (this->hWnd)
	{
		UnregisterClass(CLASS_NAME, hInstance);
	}
}
/**	@brief 	ウィンドウの作成
*	@return
*	@date 2024/03/29
*/
int	WindowSetup::CreateWindowScreen(void)
{
	//初期化した時のみ実行する
	if (isInit)
	{
		//windowsハンドルを取得
		this->hWnd = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,		//拡張ウィンドウスタイル
			this->wcex.lpszClassName,	//ウィンドウクラス名
			WINDOW_NAME,				//ウィンドウのタイトルバーに表示される名前
			WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル(動作や見た目に関するオプション)
			CW_USEDEFAULT,				//ウィンドウの左上隅のX座標
			CW_USEDEFAULT,				//ウィンドウの左上隅のY座標
			SCREEN_WIDTH,						//ウィンドウの幅
			SCREEN_HEIGHT,					//ウィンドウの高さ
			NULL,						//親ウィンドウのハンドル(独立したウィンドウの場合は NULL)
			NULL,						//ウィンドウが使用するメニューのハンドル,子ウィンドウのID(メニューがない場合は NULL)
			this->wcex.hInstance,		//ウィンドウを作成するプログラムのインスタンスハンドル
			NULL						//ウィンドウ作成時にウィンドウプロシージャに渡される追加データ
		);

		// ウィンドウのサイズを画面の大きさ + 枠の太さに修正
		RECT	rc1, rc2;
		GetWindowRect(this->hWnd, &rc1);	// ウィンドウの短径領域を取得
		GetClientRect(this->hWnd, &rc2);	// クライアントの短径領域を取得

		// ウィンドウサイズ
		int	sx = SCREEN_WIDTH;
		int	sy = SCREEN_HEIGHT;

		// 枠分の大きさを加算
		sx += ((rc1.right - rc1.left) - (rc2.right- rc2.left));
		sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));

		// ウィンドウサイズを変更
		SetWindowPos(this->hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));
	}
	//ハンドルがちゃんと取得できているかチェック
	if (!this->hWnd) {
		return E_FAIL;
	}
	return S_OK;
}
/**	@brief 	ウィンドウの表示、更新
*	@param	_In_ int			nCmdShow	ウィンドウが表示される時の状態
*	@return
*	@date 2024/05/15
*/
int	WindowSetup::ShowWindowScreen(_In_ int       nCmdShow)
{
	//ハンドルを取得しているかチェック
	if (!this->hWnd) {
		return E_FAIL;
	}
	//ウィンドウを表示
	ShowWindow(this->hWnd, nCmdShow);	//戻り値 0:表示されていた　1:非表示だった
	//ウィンドウのクライアント領域を更新
	UpdateWindow(this->hWnd);
	return S_OK;
}
//	静的メンバ変数	---------------------------------------------------------------------------------------------------

WindowSetup* WindowSetup::appWindow = nullptr;	//静的メンバ変数の初期化

//	その他関数	-------------------------------------------------------------------------------------------------------

//「終了しますか？」の画面出すやつ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//wParam　がキー入力送るやつ
		if (wParam == VK_ESCAPE)
		{													//メッセージボックスの「ok」「キャンセル」
			if (MessageBox(hWnd, L"終了", L"終了しますか？", MB_OKCANCEL) == IDOK)
				PostQuitMessage(0);	//メッセージ終了送る
		}
		break;
	case WM_CLOSE:  // 「x」ボタンが押されたら
	{
		int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
		if (res == IDOK) {
			DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
		}
	}
	break;
	default:
		// 受け取ったメッセージに対してデフォルトの処理を実行
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}