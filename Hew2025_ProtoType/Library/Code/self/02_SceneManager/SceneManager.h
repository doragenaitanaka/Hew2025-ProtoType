/**	@file 	SceneManager.h
*	@brief 	シーン管理クラス
*	@date	2024/05/11
*/

#pragma once
//シーンクラス
#include"../../../../Scene/00_BaseScene/BaseScene.h"
#include<iostream>

//シーン名
enum class Scene
{
	SplashScreanScene,

	TitleScene,
	
	StageSelectScene,

	// ステージ
	Stage_1,
	Stage_2,
	Stage_3,
	Stage_4,
	Stage_5,
	Stage_6,
	Stage_7,
	Stage_8,
	Stage_9,
	Stage_10,
	Stage_11,
	Stage_12,
	
	EndingScene,

	// テスト
	TEST,
	TEST_IMAGAWA,
	TEST_UEDA,
	TEST_URYU,
	TEST_RI,
	TEST_OTANI,
	TEST_TAKAHASHI,
};

// 前方宣言
class BaseScene;

/**	@brief 	シーン管理クラス
*	@date	2024/05/11
*	@memo	シーン自体の実行、シーン遷移を管理
*	@memo	今回は非同期処理を想定しないので管理するポインタは1つ
*	@memo	シングルトンパターン、sceneManagerを各ファイルで呼び出して使用する
*/
class SceneManager
{
private:
	/**	@brief 	コンストラクタ
	*	@date	2024/05/11
	*	@memo	外での生成を防ぐ
	*/
	SceneManager();
	/**	@brief 	デストラクタ
	*	@date	2024/05/11
	*/
	~SceneManager();
	/**	@brief 	シーンの生成
	*	@param	Scene	sceneName	次のシーン名
	*	@date	2024/05/11
	*	@memo	非同期の時はここを戻り値BaseScene*にして複数個作れるようにする予定は未定！！！！！
	*/
	void	CreateScene(Scene sceneName);

public:
	/**	@brief 	シーン全体の実行関数
	*	@date	2024/05/11
	*	@memo	シーン全体の処理の流れ(初期化、更新、描画)をここに書く
	*/
	void	Run(void);
	/**	@brief 	シーン遷移関数
	*	@param	Scene	sceneName	次のシーン名
	*	@date	2024/05/11
	*/
	void	ChangeScene(Scene	sceneName);

	/**	@brief 	シーンマネージャーの生成
	*	@date	2024/05/11
	*	@memo	この関数を始めに実行する
	*/
	static	void	CreateInstance(void);
	/**	@brief 	シーンマネージャーの削除
	*	@date	2024/05/11
	*/
	static	void	DestroyInstance(void);
	/**	@brief 	シーンマネージャーの取得
	*	@return	SceneManager*	シーンマネージャー
	*	@date	2024/05/11
	*	@memo	この関数を使って各ファイルで生成済シーンマネージャーを取得する
	*/
	static	SceneManager* GetInstance(void);
	
private:
	bool	isInitialized;					//true:初期化した
	bool	isChangedScene;					//true:シーン遷移が行われた
	BaseScene* nowScene;					//現在のシーンのアドレスを保持する
	static	SceneManager* sceneManager;		//シーンマネージャー
};