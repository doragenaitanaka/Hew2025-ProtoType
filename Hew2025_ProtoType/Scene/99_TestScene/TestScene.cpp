/**	@file	TestScene.cpp
*	@brief 	テストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#include<DirectXMath.h> 
#include<time.h>
#include<algorithm>

#include"TestScene.h"
#include"../../Library/Code/self/01_Windows/WindowSetup.h"
#include"../../Library/Code/self/03_SceneManager/SceneManager.h"

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
TestScene::TestScene()
{
    // クラスインスタンスの取得
    //this->p_cd3d11 = CD3D11::GetInstance();
    this->p_sceneManager = SceneManager::GetInstance();
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
TestScene::~TestScene()
{
    this->Finalize();
}

/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	TestScene::Initialize(void)
{
    //std::cout << "Initialize" << std::endl;
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	TestScene::Update(void)
{
    //std::cout << "Update" << std::endl;
}// Update()    end

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	TestScene::Draw(void)
{    
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	TestScene::Finalize(void)
{
    // シングルトンインスタンス
    if (this->p_sceneManager) { this->p_sceneManager = nullptr; }   // シーンマネージャー
    //if (this->p_cd3d11) { this->p_cd3d11 = nullptr; }               // cd3d11クラス
}