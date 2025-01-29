/**	@file	TitleScene.cpp
*	@brief 	タイトル
*	@date	2024/05/10
*/
#include"TitleScene.h"

#include"../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
TitleScene::TitleScene()
{
    this->p_camera = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	
    this->background = nullptr;
    this->logo = nullptr;
    this->start = nullptr;
    this->select = nullptr;
    this->gameend = nullptr;
    this->finger = nullptr;
    this->cloud1 = nullptr;
    this->cloud2 = nullptr;
    this->abutton = nullptr;

    //--------------------------------------------------------------------------
    //		描画関連
    //--------------------------------------------------------------------------
    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*/
TitleScene::~TitleScene()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	TitleScene::Initialize(void)
{
    //BGM 
    this->p_sound->Play(SOUND_LABEL::BGM_TITLE);

    // カメラ
    if (!this->p_camera) { this->p_camera = new Camera; }

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	

    // 背景
    if (!this->background) { this->background = new Object(this->p_camera); }
    this->background->Init(L"Asset/title/title scene_haikei.png");
    this->background->SetPos(0.0f, 0.0f, 0.0f);
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);

    // ロゴ
    if (!this->logo) { this->logo = new Object(this->p_camera); }
    this->logo->Init(L"Asset/title/beyond 1.png");
    this->logo->SetPos(0.0f, 300.0f, 0.0f);
    this->logo->SetSize(LogoSize.x, LogoSize.y, 0.0f);

    // ゲームスタート
    if (!this->start) { this->start = new Object(this->p_camera); }
    this->start->Init(L"Asset/title/title scene_sutrt.png");
    this->start->SetPos(-200.0f, -20.0f, 0.0f);
    this->start->SetSize(StartSize.x, StartSize.y, 0.0f);

    // ステージセレクト
    if (!this->select) { this->select = new Object(this->p_camera); }
    this->select->Init(L"Asset/title/title scene_stageselect.png");
    this->select->SetPos(110.0f, -220.0f, 0.0f);
    this->select->SetSize(SelectSize.x,SelectSize.y, 0.0f);

    // ゲーム終了
    if (!this->gameend) { this->gameend = new Object(this->p_camera); }
    this->gameend->Init(L"Asset/title/title scene_gameend.png");
    this->gameend->SetPos(-50.0f, -420.0f, 0.0f);
    this->gameend->SetSize(GameendSize.x,GameendSize.y, 0.0f);

    // 指
    if (!this->finger) { this->finger = new Object(this->p_camera); }
    this->finger->Init(L"Asset/title/title scene_hand.png");
    this->finger->SetPos(FingerPos.x, FingerPos.y, 0.0f);
    this->finger->SetSize(170.0f, 170.0f, 0.0f);

    // 雲(小)
    if (!this->cloud1) { this->cloud1 = new Object(this->p_camera); }
    this->cloud1->Init(L"Asset/title/title scene_kumo2.png");
    this->cloud1->SetPos(cloudPos00.x, cloudPos00.y, 0.0f);
    this->cloud1->SetSize(300, 300.0f, 0.0f);

    // 雲(大)
    if (!this->cloud2) { this->cloud2 = new Object(this->p_camera); }
    this->cloud2->Init(L"Asset/title/title scene_kumo1.png");
    this->cloud2->SetPos(cloudPos01.x, cloudPos01.y, 0.0f);
    this->cloud2->SetSize(700.0f, 600.0f, 0.0f);

    // Aボタン
    if (!this->abutton) { this->abutton = new Object(this->p_camera); }
    this->abutton->Init(L"Asset/title/title scene_a.png");
    this->abutton->SetPos(FingerPos.x + 75.0f, FingerPos.y - 50.0f, 0.0f);
    this->abutton->SetSize(50.0f, 50.0f, 0.0f);
    //--------------------------------------------------------------------------
    //		描画関連の初期化
    //--------------------------------------------------------------------------	

    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    HRESULT hr;
    // シェーダ
    {
        // 頂点シェーダコンパイル
        hr = this->p_vertexShader->CompileFromFile(
            L"Shader/VertexShader.hlsl",            // 使用したいシェーダファイルパス
            NULL,
            NULL,
            "vs_main",                              // シェーダファイル内で書いているエントリーポイント
            "vs_5_0",                               // シェーダのバージョン
            0,
            0
        );

        //  ピクセルシェーダーファイルコンパイル
        hr = this->p_pixelShader->CompileFromFile(
            L"Shader/PixelShader.hlsl",
            NULL,
            NULL,
            "ps_main",
            "ps_5_0",
            0,
            0
        );

        //  シェーダの生成
        hr = this->p_vertexShader->Create(NULL);     //  頂点シェーダ
        hr = this->p_pixelShader->Create(NULL);      //  ピクセルシェーダ
    }

    // インプットレイアウト作成
    D3D11_INPUT_ELEMENT_DESC layout[]
    {
        // 位置座標があるということを伝える
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        // 色情報があるということを伝える
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //UV座標(uv)
        {"TEX",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };

    // 入力レイアウトの作成
    unsigned int numElements = ARRAYSIZE(layout);                           // レイアウトのサイズ
    ID3DBlob* p_vsBlob = this->p_vertexShader->GetShaderFile();             // 頂点シェーダーファイルの取得
    hr = this->p_inputLayout->Create(layout, numElements, p_vsBlob);

    // サンプラーを作成
    hr = this->p_sampler->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
        D3D11_TEXTURE_ADDRESS_CLAMP,
        D3D11_TEXTURE_ADDRESS_CLAMP,
        D3D11_TEXTURE_ADDRESS_CLAMP);
    if (FAILED(hr)) { return; }

    // ブレンドステートの作成
    // →透過処理や加算合成を可能にする色の合成方法
    {
        D3D11_BLEND_DESC    brendState;

        ZeroMemory(&brendState, sizeof(D3D11_BLEND_DESC));
        brendState.AlphaToCoverageEnable = FALSE;
        brendState.IndependentBlendEnable = FALSE;
        brendState.RenderTarget[0].BlendEnable = TRUE;
        brendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        brendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        brendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        brendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        brendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        brendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        brendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        ID3D11Device* p_device = this->p_cd3d11->GetDevice();
        if (p_device)
        {
            hr = p_device->CreateBlendState(&brendState, &this->p_brendState);
            if (FAILED(hr)) { return; }
        }
        // 深度テストを無効にする
        ID3D11DepthStencilState* p_dSState;
        CD3D11_DEPTH_STENCIL_DESC   dsDesc;
        ZeroMemory(&dsDesc, sizeof(dsDesc));

        dsDesc.DepthEnable = FALSE;     // 深度テストを無効に設定
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
        if (p_device)
        {
            hr = p_device->CreateDepthStencilState(&dsDesc, &p_dSState);
            if (FAILED(hr)) { return; }

            // デバイスコンテキストの取得
            ID3D11DeviceContext* p_deviceContext = this->p_cd3d11->GetDeviceContext();
            if (p_deviceContext)
            {
                p_deviceContext->OMSetDepthStencilState(p_dSState, 1);
            }
        }
    }
}

/**	@brief 	シーン全体の更新
*/
void	TitleScene::Update(void)
{
    // 入力更新
    this->p_input->Update();
    this->p_input->GetLeftAnalogStick();

    //--------------------------------------------------------------------------
    //		ギミックの更新
    //--------------------------------------------------------------------------	

    //雲の動き
    if (cloudPos00.x >= -1100.0f)
    {
        cloudPos00.x -= CloudMoveSpeed * 2;
    }
    else if (cloudPos00.x <= -1100.0f)
    {
        cloudPos00.x = 1100.0f;
    }

    if (cloudPos01.x >= -1400.0f)
    {
        cloudPos01.x -= CloudMoveSpeed;
    }
    else if (cloudPos01.x <= -1400.0f)
    {
        cloudPos01.x = 1400.0f;
    }

    //Aボタンの動き
    if (Acnt != 50)
    {
        Acnt++;
    }
    else if (Acnt == 50)
    {
        if (AFlg)
        {
            this->abutton->SetColor({ 0.5f, 0.5f, 0.5f, 1.0f });
            AFlg = false;
        }
        else
        {
            this->abutton->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
            AFlg = true;
        }
        Acnt = 0;
    }

    //選択肢の動き
        if (UIcnt != 50)
        {
            UIcnt++;
            if (UIState)
            {
                switch (SelectState)
                {
                case 0:
                    StartSize.x+=1.1;
                    StartSize.y+=1.1;

                    SelectSize = { 1120.0f,160.0f };//サイズを初期化
                    GameendSize = { 800.0f,160.0f };//サイズを初期化
                    break;

                case 1:
                    SelectSize.x+= 1.1;
                    SelectSize.y+= 1.1;

                    StartSize = { 640.0f,160.0f };//サイズを初期化
                    GameendSize = { 800.0f,160.0f };//サイズを初期化
                    break;

                case 2:
                    GameendSize.x+= 1.1;
                    GameendSize.y+= 1.1;
                       
                    StartSize = { 640.0f,160.0f };//サイズを初期化
                    SelectSize = { 1120.0f,160.0f };//サイズを初期化
                    break;
                }
            }
            else
            {
                switch (SelectState)
                {
                case 0:
                    StartSize.x--;
                    StartSize.y--;
                    break;

                case 1:
                    SelectSize.x--;
                    SelectSize.y--;
                    break;

                case 2:
                    GameendSize.x--;
                    GameendSize.y--;
                    break;
                }
            }
            if (UIcnt <= 25)
            {
                UIState = true;
            }
            if (UIcnt >= 25)
            {
                UIState = false;
            }
        }
        else if (UIcnt == 50)
        {
            UIcnt = 0;
        }

        //タイトルロゴの動き
        if (Logocnt != 80)
        {
            Logocnt++;
            if (LogoState)
            {
                    LogoSize.x+=1.1;
                    LogoSize.y+=1.1;
            }
            else
            {
                    LogoSize.x--;
                    LogoSize.y--;
            }
            if (Logocnt <= 40)
            {
                LogoState = true;
            }
            if (Logocnt >= 40)
            {
                LogoState = false;
            }
        }
        else if (Logocnt == 80)
        {
            Logocnt = 0;
        }

        //選択中の指の動き
    if (this->p_input->Trigger("UP"))
    {
        // SE
        this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);

        switch (SelectState)
        {
        case 0://startに指
            FingerPos.y = -450.0f;
            SelectState = 2;
            break;

        case 1://ステージセレクトに指
            FingerPos.y = -50.0f;
            SelectState = 0;
            break;

        case 2://ゲーム終了に指
            FingerPos.y = -250.0f;
            SelectState = 1;
            break;
        }
    }
    if (this->p_input->Trigger("DOWN"))
    {        
        // SE
        this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);
        switch (SelectState)
        {
        case 0://startに指
            FingerPos.y = -250.0f;
            SelectState = 1;
            break;

        case 1://ステージセレクトに指
            FingerPos.y = -450.0f;
            SelectState = 2;
            break;

        case 2://ゲーム終了に指
            FingerPos.y = -50.0f;
            SelectState = 0;
            break;
        }
    }

    //シーンチェンジ
    if (this->p_input->Trigger("SELECT"))
    {
        // SE
        this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);
        switch (SelectState)
        {
        case 0://start
            this->p_sceneManager->ChangeScene(Scene::Stage_2);
            return;
            break;

        case 1://stage select
            this->p_sceneManager->ChangeScene(Scene::StageSelectScene);
            return;
            break;

        case 2://game end
            GameManager::GetInstance()->EndGame();
            return;
            break;
        }
    }
    //-----------------------------------------------------
    //  座標更新
    //-----------------------------------------------------
    this->finger->SetPos(FingerPos.x,FingerPos.y,0.0f);
    this->abutton->SetPos(FingerPos.x + 75.0f, FingerPos.y - 50.0f, 0.0f);
    this->cloud1->SetPos(cloudPos00.x,cloudPos00.y, 0.0f);
    this->cloud2->SetPos(cloudPos01.x, cloudPos01.y , 0.0f);

    //-----------------------------------------------------
    //  サイズ更新
    //-----------------------------------------------------
    this->logo->SetSize(LogoSize.x, LogoSize.y, 0.0f);
    this->start->SetSize(StartSize.x, StartSize.y, 0.0f);
    this->select->SetSize(SelectSize.x, SelectSize.y, 0.0f);
    this->gameend->SetSize(GameendSize.x, GameendSize.y, 0.0f);

    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->background->Update();
    this->logo->Update();
    this->start->Update();
    this->select->Update();
    this->gameend->Update();
    this->finger->Update();
    this->cloud1->Update();
    this->cloud2->Update();
    this->abutton->Update();

    // カメラの更新
    this->p_camera->Update();
}

/**	@brief 	シーン全体の描画
*/
void	TitleScene::Draw(void)
{
    //--------------------------------------------------------------------------
  //		描画関連(そんな頻繁に変えることはないと思う)
  //--------------------------------------------------------------------------	

  // 描画設定用にデバイスなどを取得
    CD3D11* cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* deviceContext = cd3d11->GetDeviceContext();
    ID3D11DepthStencilView* depthStencilView = cd3d11->GetDepthStencilView();
    ID3D11RenderTargetView* renderTargetView = cd3d11->GetRenderTargetView();
    D3D11_VIEWPORT* viewport = cd3d11->GetViewport();

    // 入力レイアウトの設定
    this->p_inputLayout->SetInputLayout();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // シェーダをセット
    this->p_vertexShader->SetShader(0, 0);
    this->p_pixelShader->SetShader(0, 0);

    // サンプラーをピクセルシェーダーに渡す
    this->p_sampler->SetSamplerPS(0, 1);

    // ブレンドステートをセット
    deviceContext->OMSetBlendState(this->p_brendState, NULL, 0xfffffffff);

    //--------------------------------------------------------------------------
    //		オブジェクトの描画
    //--------------------------------------------------------------------------
    this->background->Draw();
    this->cloud1->Draw();
    this->cloud2->Draw();
    this->logo->Draw();
    this->start->Draw();
    this->select->Draw();
    this->gameend->Draw();
    this->finger->Draw();
    this->abutton->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	TitleScene::Finalize(void)
{
    // BGM
    this->p_sound->Stop(SOUND_LABEL::BGM_TITLE);

    SAFE_DELETE(this->p_camera);    // カメラ

    //--------------------------------------------------------------------------
    //		描画関連
    //--------------------------------------------------------------------------	
    SAFE_DELETE(this->p_vertexShader);  // 頂点シェーダ
    SAFE_DELETE(this->p_pixelShader);   // ピクセルシェーダ
    SAFE_DELETE(this->p_inputLayout);   // 入力レイアウト
    SAFE_DELETE(this->p_sampler);       // サンプラー

    SAFE_RELEASE(this->p_brendState); // ブレンドステート

    //--------------------------------------------------------------------------
    //		オブジェクト
    //--------------------------------------------------------------------------
    SAFE_DELETE(this->background);
    SAFE_DELETE(this->logo);
    SAFE_DELETE(this->start);
    SAFE_DELETE(this->select);
    SAFE_DELETE(this->gameend);
    SAFE_DELETE(this->finger);
    SAFE_DELETE(this->cloud1);
    SAFE_DELETE(this->cloud2);
    SAFE_DELETE(this->abutton);
}