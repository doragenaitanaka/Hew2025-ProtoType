/**	@file	Test_Ri.cpp
*	@brief 	李用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Ri.h"

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Ri::Test_Ri()
{
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Ri::~Test_Ri()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Ri::Initialize(void)
{
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Ri::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_RI);
        return;
    }
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Ri::Draw(void)
{
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Ri::Finalize(void)
{
}