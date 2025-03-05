/**	@file	SplashScreanScene.cpp
*	@brief	起動時にロゴとか出るシーン
*	@date	2024/12/19
*/
#include"SplashScreanScene.h"

/**	@brief 	コンストラクタ
*/
SplashScreanScene::SplashScreanScene()
{
    // カメラ
    this->p_camera = nullptr;

    this->currentScreenState = ScreenState::FADE_IN;
    this->displayTime = 3.0f;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------
    this->p_background = nullptr;
    this->p_logo = nullptr;
    this->feda = nullptr;

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
SplashScreanScene::~SplashScreanScene()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	SplashScreanScene::Initialize(void)
{    
    // カメラ
    if (!this->p_camera) { this->p_camera = new Camera; }
    this->p_camera->SetPosition(0.0f, 0.0f);

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------

    // 背景
    if (!this->p_background) { this->p_background = new Object(this->p_camera); }
    this->p_background->Init(L"Asset/UI/background.png");
    this->p_background->SetPos(0.0f, 0.0f, 0.0f);
    this->p_background->SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
    this->p_background->SetSize(1920.0f, 1080.0f, 0.0f);
    
    // ロゴ
    if (!this->p_logo) { this->p_logo = new Object(this->p_camera); }
    this->p_logo->Init(L"Asset/UI/controller_normal_1.png");
    this->p_logo->SetPos(0.0f, 0.0f, 0.0f);
    this->p_logo->SetSize(900.0f, 600.0f, 0.0f);

    //フェード
    if (!this->feda) { this->feda = new FedaInOut(this->p_camera); }
    this->feda->Init(L"Asset/FedaIn&FedaOut.png");
    this->feda->SetPos(0.0f, 0.0f, 0.0f);
    this->feda->SetSize(1920.0f, 1080.0f, 0.0f);
    this->feda->SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
    this->feda->SetFadaInDecrease(0.02f);
    this->feda->SetFadaOutDecrease(0.02f);

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
void	SplashScreanScene::Update(void)
{

    switch (this->currentScreenState)
    {    
    // フェードイン中
    case SplashScreanScene::FADE_IN:

        this->feda->FedaIn();

        // フェードインしきったらロゴ表示
        if (this->feda->GetAlpha() <= 0.0f)
        {
            this->currentScreenState = ScreenState::DISPLAY_LOGO;
            this->displayTimer.Reset();
        }
        break;
        
    // ロゴ表示中
    case SplashScreanScene::DISPLAY_LOGO:

        // 一定時間がたったらフェードアウトして遷移
        if (this->displayTimer.Elapsed() > this->displayTime)
        {
            this->currentScreenState = ScreenState::FADE_OUT;
        }
        break;

    // フェードアウト中
    case SplashScreanScene::FADE_OUT:
    {
        bool isFadeOut = true;
        this->feda->FedaOut(isFadeOut);

        // フェードアウトしたらタイトル遷移
        if (this->feda->GetAlpha() >= 1.0f)
        {
            // 計測開始
            this->sceneChangeTimer.Reset();
            this->currentScreenState = ScreenState::SCENE_CHANGE;
        }
    }
        break;
    // シーン遷移する
    case SplashScreanScene::SCENE_CHANGE:

        // 一定時間計測後シーン遷移
        if (this->sceneChangeTimer.Elapsed() >= 1.0f)
        {
            this->p_sceneManager->ChangeScene(Scene::TitleScene);
            return;
        }
        break;
    default:
        break;
    }

    // カメラの更新
    this->p_camera->Update();

    //--------------------------------------------------------------------------
    //		オブジェクト
    //--------------------------------------------------------------------------
    this->p_background->Update();
    this->p_logo->Update();
    this->feda->Update();
}

/**	@brief 	シーン全体の描画
*/
void	SplashScreanScene::Draw(void)
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
    //		オブジェクト
    //--------------------------------------------------------------------------
    this->p_background->Draw();
    this->p_logo->Draw();
    this->feda->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	SplashScreanScene::Finalize(void)
{
    SAFE_DELETE(this->p_camera);    // カメラ

    //--------------------------------------------------------------------------
    //		オブジェクト
    //--------------------------------------------------------------------------
    SAFE_DELETE(this->p_background);
    SAFE_DELETE(this->p_logo);
    SAFE_DELETE(this->feda);

    //--------------------------------------------------------------------------
    //		描画関連
    //--------------------------------------------------------------------------	
    SAFE_DELETE(this->p_vertexShader);  // 頂点シェーダ
    SAFE_DELETE(this->p_pixelShader);   // ピクセルシェーダ
    SAFE_DELETE(this->p_inputLayout);   // 入力レイアウト
    SAFE_DELETE(this->p_sampler);       // サンプラー

    SAFE_RELEASE(this->p_brendState);   // ブレンドステート
}
