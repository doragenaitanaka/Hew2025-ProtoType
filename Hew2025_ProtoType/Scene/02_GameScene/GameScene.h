/**	@file	GameScene.h
*	@brief 	ゲームシーンクラス
*	@date	2024/05/10
*/

#pragma once
#include"../00_BaseScene/BaseScene.h"
#include<iostream>

/**	@brief 	ゲームシーンクラス
*	@date	2024/05/10
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class GameScene :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*	@date	2024/05/10
	*/
	GameScene();
	/**	@brief 	デストラクタ
	*	@date	2024/05/10
	*/
	~GameScene()override;
	/**	@brief 	シーン全体の初期化
	*	@date	2024/05/10
	*/
	void	Initialize(void)override;

	/**	@brief 	シーン全体の更新
	*	@date	2024/05/10
	*/
	void	Update(void)override;

	/**	@brief 	シーン全体の描画
	*	@date	2024/05/10
	*/
	void	Draw(void)override;

	/**	@brief 	シーン全体の終了処理
	*	@date	2024/05/10
	*/
	void	Finalize(void)override;
private:

};