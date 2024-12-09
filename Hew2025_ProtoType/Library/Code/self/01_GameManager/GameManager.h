#pragma once
/**	@file 	GameManager.h
*	@brief 	プロジェクト全体の管理クラス
*	@date	2024/05/20
*/

#include"../03_Windows/WindowSetup.h"
#include"../04_DirextX_11/01_Initialize/CD3D11.h"
#include"../02_SceneManager/SceneManager.h"

//define定義
#define	FPS (60)

class GameManager
{
public:
	/**	@brief 	クラスインスタンスの生成関数
	*	@date	2024/05/20
	*	@memo	この関数を始めに実行する
	*/
	static	void	CreateInstance(void);
	/**	@brief 	クラスインスタンスの取得関数
	*	@return	CD3D11*	CD3D11クラス
	*	@date	2024/05/20
	*	@memo	この関数を使って各ファイルで生成済CD3D11クラスを取得する
	*/
	static	GameManager* GetInstance(void);
	/**	@brief 	クラスインスタンスの削除関数
	*	@return	CD3D11*	CD3D11クラス
	*	@date	2024/05/20
	*/
	void    DestroyInstance(void);
	/**	@brief 	プロジェクト全体の実行関数
	*	@param	_In_ HINSTANCE hInstance		現在のアプリケーションインスタンスへのハンドル
	*	@param	BackColorBrush      backColor	ウィンドウの背景色
	*	@param	 _In_ int       nCmdShow		ウィンドウが表示される時の状態
	*	@param	int	プロシージャにメッセージを返す
	*	@date	2024/05/20
	*/
	int	Run(_In_ HINSTANCE hInstance, _In_ int       nCmdShow);
	/**	@brief 	プロジェクトを終了する関数
	*	@date	2024/05/20
	*	@memo	ゲームループ可動フラグをfalseにする
	*/
	void	EndGame(void);
private:
	GameManager();
	~GameManager();
private:
	CD3D11* cd3d11;							// d3d11の初期化をまとめたクラス
	WindowSetup* windowSetup;				// windowsの初期化をまとめたクラス
	SceneManager* sceneManager;				// シーン管理クラ
	
	bool	isRunning;						// true:ゲームループ実行中

	// FPS計測用変数
	int	fpsCounter;		
	long	long	oldTick;				// 前回計測時の時間
	long	long	nowTick;				// 今回計測時の時間

	// FPS固定用関数
	long	long	frequency;				// どれくらい細かく時間をカウントできるか
	// 時間(単位：カウント)
	long	long	oldCount;				// 前回計測時の時間
	long	long	nowCount;				// 今回計測時の時間

	static	GameManager* gameManager;		// プロジェクト管理クラス
};

