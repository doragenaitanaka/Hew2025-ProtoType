#pragma once
#include <windows.h>	

#define CLASS_NAME   L"DirectX11 Template"	// ウインドウクラスの名前
#define WINDOW_NAME  L"windows create test"	// ウィンドウの名前

#define	SCREEN_WIDTH	(640)
#define	SCREEN_HEIGHT	(480)

//「終了しますか？」の画面出すやつ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//ウィンドウの初期背景色
enum BackColorBrush
{
	WHITE	=	WHITE_BRUSH,	//0
	LTGRAY= LTGRAY_BRUSH,		//1
	GRAY= GRAY_BRUSH,			//2
	DKGRAY= DKGRAY_BRUSH,		//3
	BLACK= BLACK_BRUSH,			//4
	NOTHING	= NULL_BRUSH,		//5
	HOLLOW=HOLLOW_BRUSH,        //=NULL_BRUSH
};

//ウィンドウ表示に必要なものをまとめたクラス
class WindowSetup
{
public:
	/**	@brief 	windowsクラスの生成
	*	@date	2024/05/14
	*	@memo	この関数を始めに実行する
	*/
	static	void	CreateInstance(void);
	/**	@brief 	windowsクラスの取得
	*	@return	WindowSetup*	windowsクラス
	*	@date	2024/05/14
	*	@memo	この関数を使って各ファイルで生成済windowsクラスを取得する
	*/
	static	WindowSetup* GetInstance(void);
	/**	@brief	全体の初期化
	*	@param	_In_ HINSTANCE hInstance		現在のアプリケーションインスタンスへのハンドル
	*	@param	BackColorBrush      backColor	ウィンドウの背景色
	*	@param	 _In_ int       nCmdShow		ウィンドウが表示される時の状態
	*	@date	2024/05/14
	*/
	int	Initialize(_In_ HINSTANCE hInstance, _In_ int       nCmdShow);
	/**	@brief 	windowsクラスの削除
	*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
	*	@date	2024/05/14
	*/
	void	DestroyInstance(HINSTANCE hInstance);
	/**	@brief	ハンドルを取得
	*	@return	HWND	windowsハンドル
	*	@date	2024/05/14
	*/
	HWND	GetHWnd(void);
private:	
	/**	@brief 	コンストラクタ
	*	@date 2024/03/29
	*/
	WindowSetup();
	/**	@brief 	デストラクタ
	*	@date 2024/03/29
	*/
	~WindowSetup();
	/**	@brief 	ウィンドウクラスの登録関数
	*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
	*	@param	BackColorBrush      backColor	ウィンドウの背景色
	*	@return
	*	@date 2024/03/29
	*	@memo	ウィンドウクラスの定義、登録を行う
	*/
	int	RegisterWindowClass(_In_ HINSTANCE hInstance);
	/**	@brief 	ウィンドウクラスの登録を解除する関数
	*	@param	_In_ HINSTANCE	hInstance		現在のアプリケーションインスタンスへのハンドル
	*	@return
	*	@date 2024/05/14
	*/
	void	UnregisterWindowClass(_In_ HINSTANCE hInstance);
	/**	@brief 	ウィンドウの作成
	*	@return
	*	@date 2024/03/29
	*/
	int	CreateWindowScreen(void);

	/**	@brief 	ウィンドウの表示、更新
	*	@param	_In_ int			nCmdShow	ウィンドウが表示される時の状態
	*	@return
	*	@date 2024/05/15
	*/
	int	ShowWindowScreen(_In_ int       nCmdShow);
private:
	WNDCLASSEX wcex;	//windowsに関する情報
	HWND hWnd;			//windowハンドル
	bool	isInit;		//true:wcexを初期化した

	static	WindowSetup* appWindow;	
};
