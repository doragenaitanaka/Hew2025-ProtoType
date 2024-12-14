/**	@file	Test_Otani.cpp
*	@brief 	大谷用のゲームシーンクラス
*	@date	2024/12/14
*/
#include"Test_Otani.h"

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Otani::Test_Otani()
{
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Otani::~Test_Otani()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Otani::Initialize(void)
{
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Otani::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_UEDA);
        return;
    }
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Otani::Draw(void)
{
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Otani::Finalize(void)
{
}