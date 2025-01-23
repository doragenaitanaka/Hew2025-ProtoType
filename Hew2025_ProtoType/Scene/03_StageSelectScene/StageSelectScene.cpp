/**	@file	StageSelectScene.cpp
/**	@file	StageSelectScene.cpp
*	@brief	ステージセレクト
*	@date	2024/12/19
*/
#include"StageSelectScene.h"
/**	@brief 	コンストラクタ
*/
StageSelectScene::StageSelectScene()
{
    // カメラ
    this->p_camera = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	
    this->p_background = nullptr;
    this->p_obj = nullptr;
    this->p_point = nullptr;
    this->p_leftUI = nullptr;
    this->p_rightUI = nullptr;

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
StageSelectScene::~StageSelectScene()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	StageSelectScene::Initialize(void)
{    
    // カメラ
    if (!this->p_camera) { this->p_camera = new Camera; }
    this->p_camera->SetPosition(0.0f, 0.0f);

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	

    // 背景
    if (!this->p_background) { this->p_background = new Object(this->p_camera); }
    this->p_background->Init(L"Asset/UI/stageselect_artbord.png");
    this->p_background->SetPos(0.0f, 0.0f, 0.0f);
    this->p_background->SetSize(1920.0f, 1080.0f, 0.0f);

    // ステージUI
	int half = static_cast<int>(Stage::MAX) / 2;

    // 最初だけ真ん中
	this->p_stageUI[static_cast<int>(Stage::STAGE_1)] = new Object(this->p_camera);
    this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->Init(this->stageUIPath[static_cast<int>(Stage::STAGE_1)].c_str());
	this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetPos(0.0f, -50.0f, 0.0f);
    this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetSize(UISize, UISize, 0.0f);

    // 前半（右側）
	for (int i = static_cast<int>(Stage::STAGE_2); i <= half; i++)
	{
		this->p_stageUI[i] = new Object(this->p_camera);
        this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
		// 均等に配置
        this->p_stageUI[i]->SetPos(i * (UISize + space), -50.0f, 0.0f);
        this->p_stageUI[i]->SetSize(UISize, UISize, 0.0f);
	}

    // 後半（左側）
    for (int i = half + 1; i < static_cast<int>(Stage::MAX); ++i)
    {
        int index = static_cast<int>(Stage::MAX) - i; // 逆順に配置
        this->p_stageUI[i] = new Object(this->p_camera);
        this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
        // 均等に配置
        this->p_stageUI[i]->SetPos(-index * (UISize + space), -50.0f, 0.0f);
        this->p_stageUI[i]->SetSize(UISize, UISize, 0.0f);
    }

    // 左端と右端を保持
    this->leftUIPos = DirectX::XMFLOAT3(-(half - 1) * (UISize + space), -50.0f, 0.0f);
    this->rightUIPos = DirectX::XMFLOAT3((half - 1) * (UISize + space), -50.0f, 0.0f);
    this->p_leftUI = new PointCollider(DirectX::XMFLOAT3(-(half + 1) * (UISize + space), -50.0f, 0.0f));
    this->p_rightUI = new PointCollider(DirectX::XMFLOAT3((half + 1) * (UISize + space), -50.0f, 0.0f));

    // ポインター
    if (!this->p_point) { this->p_point = new PointCollider(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)); }

    // テストオブジェクト
    if (!this->p_obj) { this->p_obj = new Object(this->p_camera); }
    this->p_obj->Init(L"Asset/UI/bangou1.png");
    this->p_obj->SetPos(0.0f, -50.0f, 0.0f);
    this->p_obj->SetSize(400.0f, 400.0f, 0.0f);
    this->p_obj->SetIsActive(false);

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
void	StageSelectScene::Update(void)
{
    this->p_input->Update();

    // 当たっていたら色変る
    int sceneNum = 0;
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        auto& coll = this->p_stageUI[i]->GetCollider();

        if (this->p_point->CheckCollision(coll))
        {
            std::cout << std::to_string(i+1) << "ステージ" << std::endl;
            this->p_stageUI[i]->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
            sceneNum = i;
        }
        else {
            this->p_stageUI[i]->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    if (this->p_input->Press("SPACE"))
    {
        //this->p_point->SetPosition(DirectX::XMFLOAT3(300.0f, 300.0f, 0.0f));
        switch (static_cast<StageSelectScene::Stage>(sceneNum))
        {
        case StageSelectScene::Stage::STAGE_1:
            this->p_sceneManager->ChangeScene(Scene::Stage_1);
            return;
            break;
        case StageSelectScene::Stage::STAGE_2:
            this->p_sceneManager->ChangeScene(Scene::Stage_2);
            return;
            break;
        case StageSelectScene::Stage::STAGE_3:
            this->p_sceneManager->ChangeScene(Scene::Stage_3);
            return;
            break;
        case StageSelectScene::Stage::STAGE_4:
            this->p_sceneManager->ChangeScene(Scene::Stage_4);
            return;
            break;
        case StageSelectScene::Stage::STAGE_5:
            this->p_sceneManager->ChangeScene(Scene::Stage_5);
            return;
            break;
        case StageSelectScene::Stage::STAGE_6:
            this->p_sceneManager->ChangeScene(Scene::Stage_6);
            return;
            break;
        case StageSelectScene::Stage::STAGE_7:
            this->p_sceneManager->ChangeScene(Scene::Stage_7);
            return;
            break;
        case StageSelectScene::Stage::STAGE_8:
            this->p_sceneManager->ChangeScene(Scene::Stage_8);
            return;
            break;
        case StageSelectScene::Stage::STAGE_9:
            this->p_sceneManager->ChangeScene(Scene::Stage_9);
            return;
            break;
        case StageSelectScene::Stage::STAGE_10:
            this->p_sceneManager->ChangeScene(Scene::Stage_10);
            return;
            break;
        case StageSelectScene::Stage::STAGE_11:
            this->p_sceneManager->ChangeScene(Scene::Stage_11);
            return;
            break;
        case StageSelectScene::Stage::STAGE_12:
            this->p_sceneManager->ChangeScene(Scene::Stage_12);
            return;
            break;
        default:
            break;
        }
    }
    else
    {
        this->p_point->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
    }

    // 移動
    float movePos = 0.0f;
    if (this->p_input->Trigger("LEFT"))
    {
        movePos = this->UISize + this->space;
    }
    else if (this->p_input->Trigger("RIGHT"))
    {
        movePos = -this->UISize - this->space;
    }
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        auto pos = this->p_stageUI[i]->GetPos();
        this->p_stageUI[i]->SetPos(pos.x + movePos, pos.y, pos.z);

        auto& coll = this->p_stageUI[i]->GetCollider();
        // 左端なら右端に
        if(coll.CheckCollision(*this->p_leftUI))
        { 
            this->p_stageUI[i]->SetPos(rightUIPos.x, rightUIPos.y, rightUIPos.z);
        }
        // 右端なら左端に
        else if (coll.CheckCollision(*this->p_rightUI))
        {
            this->p_stageUI[i]->SetPos(leftUIPos.x, leftUIPos.y, leftUIPos.z);
        }
    }

    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->p_background->Update();
    this->p_obj->Update();
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        this->p_stageUI[i]->Update();
    }

    // カメラの更新
    this->p_camera->Update();
}

/**	@brief 	シーン全体の描画
*/
void	StageSelectScene::Draw(void)
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
    this->p_obj->Draw();

    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        this->p_stageUI[i]->Draw();
    }
}

/**	@brief 	シーン全体の終了処理
*/
void	StageSelectScene::Finalize(void)
{
    SAFE_DELETE(this->p_camera);    // カメラ

    //--------------------------------------------------------------------------
    //		オブジェクト
    //--------------------------------------------------------------------------
    SAFE_DELETE(this->p_background);
    SAFE_DELETE(this->p_obj);
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++) { SAFE_DELETE(this->p_stageUI[i]); }
    SAFE_DELETE(this->p_point);

    //--------------------------------------------------------------------------
    //		描画関連
    //--------------------------------------------------------------------------	
    SAFE_DELETE(this->p_vertexShader);  // 頂点シェーダ
    SAFE_DELETE(this->p_pixelShader);   // ピクセルシェーダ
    SAFE_DELETE(this->p_inputLayout);   // 入力レイアウト
    SAFE_DELETE(this->p_sampler);       // サンプラー

    SAFE_RELEASE(this->p_brendState);   // ブレンドステート
}