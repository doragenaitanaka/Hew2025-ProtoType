/**	@file	TitleScene.cpp
*	@brief 	タイトルシーンクラス
*	@date	2024/05/10
*/
#include"TitleScene.h"
#include"../../Library/Code/self/03_SceneManager/SceneManager.h"

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
TitleScene::TitleScene()
{
	this->p_sceneManager = SceneManager::GetInstance();	
    //this->p_cd3d11 = CD3D11::GetInstance();

}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
TitleScene::~TitleScene()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	TitleScene::Initialize(void)
{
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10W
*/
void	TitleScene::Update(void)
{
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	TitleScene::Draw(void)
{
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	TitleScene::Finalize(void)
{
    // マネージャー   sss
    //this->p_cd3d11 = nullptr;
    this->p_sceneManager = nullptr;
}