﻿/**	@file 	Stage_1.h
*	@brief 	Stage_1
*	@date	2024/12/19
*/
#pragma once
#include"../../00_BaseScene/BaseScene.h"

/**	@file	Stage_1.h
*	@brief	起動時にロゴとか出るシーン
*	@memo	基底クラスの純粋仮想関数を継承している裏付け(誤った継承動作を防ぐため)に継承したメンバ関数にoverride指定子を使用している
*/
class Stage_1 :public BaseScene
{
public:
	/**	@brief 	コンストラクタ
	*/
	Stage_1();
	/**	@brief 	デストラクタ
	*/
	~Stage_1()override;
	/**	@brief 	シーン全体の初期化
	*/
	void	Initialize(void)override;

	/**	@brief 	シーン全体の更新
	*/
	void	Update(void)override;

	/**	@brief 	シーン全体の描画
	*/
	void	Draw(void)override;

	/**	@brief 	シーン全体の終了処理
	*/
	void	Finalize(void)override;
private:
};