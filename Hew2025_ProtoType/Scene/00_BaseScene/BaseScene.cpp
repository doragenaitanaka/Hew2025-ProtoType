/**	@file 	BaseScene.cpp
*	@brief 	シーン基底クラス
*	@date	2024/05/10
*/

#include"BaseScene.h"
/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
BaseScene::BaseScene() :p_sceneManager(nullptr), p_cd3d11(nullptr)
{
	// マネージャーの取得
	if (!this->p_sceneManager) { this->p_sceneManager = SceneManager::GetInstance(); }
	if (!this->p_cd3d11) { this->p_cd3d11 = CD3D11::GetInstance(); }
	//std::cout << "BaseScene::BaseScene()" << std::endl;
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
BaseScene::~BaseScene()
{
	// マネージャーの参照をなくす
	if (this->p_sceneManager) { this->p_sceneManager = nullptr; }  
	if (this->p_cd3d11) { this->p_cd3d11 = nullptr; }
	//std::cout << "BaseScene::~BaseScene()" << std::endl;
}