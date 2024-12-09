/**	@file	TestScene.cpp
*	@brief 	テストシーンクラス
*	@date	2024/05/21
*	@memo	マネージャーは静的メンバ変数なので取得のみ
*/
#include"TestScene.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
TestScene::TestScene()
{
    std::cout << "TestScene::TestScene()" << std::endl;
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
TestScene::~TestScene()
{
    std::cout << "TestScene::~TestScene()" << std::endl;
    this->Finalize();
}

/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	TestScene::Initialize(void)
{
    std::cout << "TestScene::Initialize()" << std::endl;
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	TestScene::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST);
        return;
    }

    std::cout << "TestScene::Update()" << std::endl;
}// Update()    end

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	TestScene::Draw(void)
{    
    std::cout << "TestScene::Draw()" << std::endl;
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	TestScene::Finalize(void)
{
    std::cout << "TestScene::Finalize()" << std::endl;
}