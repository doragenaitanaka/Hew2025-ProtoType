/**	@file	Test_Ueda.cpp
*	@brief 	植田用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Ueda.h"


/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Ueda::Test_Ueda()
{
	this->Initialize();
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Ueda::~Test_Ueda()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Ueda::Initialize(void)
{
	//サウンドの初期化
    
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10 
*/
void	Test_Ueda::Update(void)
{
    
    if (GetAsyncKeyState(VK_SPACE))
    {
        
        return;
    }
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Ueda::Draw(void)
{
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Ueda::Finalize(void)
{
  //サウンドの終了
	
}