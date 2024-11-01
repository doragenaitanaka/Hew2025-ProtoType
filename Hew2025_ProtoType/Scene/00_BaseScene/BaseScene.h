/**	@file 	BaseScene.h
*	@brief 	シーン基底クラス
*	@date	2024/05/10
*/

#pragma once
#include<iostream>

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
	virtual	~BaseScene();

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
};
