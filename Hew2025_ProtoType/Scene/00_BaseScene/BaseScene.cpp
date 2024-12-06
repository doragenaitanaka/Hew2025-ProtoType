/**	@file 	BaseScene.cpp
*	@brief 	シーン基底クラス
*	@date	2024/05/10
*/

#include"BaseScene.h"
/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
BaseScene::BaseScene():p_sceneManager(nullptr)
{
	// マネージャーの取得
	if (!this->p_sceneManager) { this->p_sceneManager = SceneManager::GetInstance(); }
	std::cout << "BaseScene::BaseScene()" << std::endl;
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
BaseScene::~BaseScene()
{
	// マネージャーの参照をなくす
	if (this->p_sceneManager) { this->p_sceneManager = nullptr; }  
	std::cout << "BaseScene::~BaseScene()" << std::endl;
}