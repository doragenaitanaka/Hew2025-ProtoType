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
    //サウンドの取得
	AudioManager& audioManager = AudioManager::getInstance();
	audioManager.init();//サウンドの初期化

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
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Ueda::Update(void)
{
    AudioManager& AudioManager = AudioManager::getInstance();
    IXAudio2SourceVoice* m_pSourceVoice = nullptr;
    AudioManager.loadsound("asset/BGM/Atelier Sophie OST 106 Scenery of the Town _ Morning_4.wav", &m_pSourceVoice);//サウンドを読み込み
    AudioManager.setMasterVolume(0.5f);//ボリュームを50%に設定
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_UEDA);
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
	AudioManager& audioManager = AudioManager::getInstance();
	audioManager.Uninit();
}