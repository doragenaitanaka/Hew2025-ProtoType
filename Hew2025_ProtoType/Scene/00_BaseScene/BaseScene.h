/**	@file 	BaseScene.h
*	@brief 	シーン基底クラス
*	@date	2024/05/10
*/

#pragma once
#include<iostream>
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../Library/Code/self/04_DirextX_11/01_Initialize/CD3D11.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include"../../Library/Code/self/SafePointers.h"
#include"../../Library/Code/other/03_sound/sound.h"

// 前方宣言
class SceneManager;

/**	@brief 	シーン基底クラス
*	@date	2024/05/10
*	@memo	抽象クラスなのでコンストラクタ以純粋仮想関数にしている
*/
class BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/05/10
	*/
	BaseScene();
	
	/**	@brief 	デストラクタ
	*	@date	2024/05/10
	*/
	virtual ~BaseScene();

	/**	@brief 	シーン全体の初期化
	*	@date	2024/05/10
	*/
	virtual	void	Initialize(void) = 0;

	/**	@brief 	シーン全体の更新
	*	@date	2024/05/10
	*/
	virtual	void	Update(void) = 0;

	/**	@brief 	シーン全体の描画
	*	@date	2024/05/10
	*/
	virtual	void	Draw(void) = 0;

	/**	@brief 	シーン全体の終了処理
	*	@date	2024/05/10
	*/
	virtual	void	Finalize(void) = 0;

protected:
	SceneManager* p_sceneManager;	// シーンマネージャー
	CD3D11* p_cd3d11;				// d3d11クラス
	Input* p_input;					// 入力
	Sound* p_sound;					// サウンド
};