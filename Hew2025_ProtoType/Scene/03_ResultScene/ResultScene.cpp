/**	@file	ResultScene.cpp
*	@brief 	リザルトシーンクラス
*	@date	2024/05/10
*/

#include"ResultScene.h"

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
ResultScene::ResultScene()
{
	//this->p_cd3d11 = CD3D11::GetInstance();
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
ResultScene::~ResultScene()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	ResultScene::Initialize(void)
{
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	ResultScene::Update(void)
{
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	ResultScene::Draw(void)
{
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	ResultScene::Finalize(void)
{
    // マネージャー   
   // this->p_cd3d11 = nullptr;
}