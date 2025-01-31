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
    this->isSelect = false;

    // カメラ
    this->p_camera = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------
    this->p_background = nullptr;
    this->p_point = nullptr;
    this->p_leftUI = nullptr;
    this->p_rightUI = nullptr;
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
StageSelectScene::~StageSelectScene()
{
	this->Finalize();
}

/**	@brief 	シーン全体の初期化
*/
void	StageSelectScene::Initialize(void)
{    

    // 時刻の設定
    this->lastUpdateTime = std::chrono::steady_clock::now();

    // カメラ
    if (!this->p_camera) { this->p_camera = new Camera; }
    this->p_camera->SetPosition(0.0f, 0.0f);

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------

    // 背景
    if (!this->p_background) { this->p_background = new Object(this->p_camera); }
    this->p_background->Init(L"Asset/background.png");
    this->p_background->SetPos(-200.0f, 0.0f, 0.0f);
    this->p_background->SetSize(1920.0f*2, 1080.0f*2, 0.0f);

    //フェード
	if (!this->feda) { this->feda = new FedaInOut(this->p_camera); }
	this->feda->Init(L"Asset/FedaIn&FedaOut.png");
	this->feda->SetPos(0.0f, 0.0f, 0.0f);
	this->feda->SetSize(1920.0f, 1080.0f, 0.0f);
    this->feda->SetAlpha(1.0f);

    // ステージUI
    bool isOdd = static_cast<int>(Stage::MAX) % 2 != 0;

    // 奇数の場合
    if (isOdd) {
        int half = (static_cast<int>(Stage::MAX) + 1) / 2;

        // 最初だけ真ん中
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)] = new Object(this->p_camera);
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->Init(this->stageUIPath[static_cast<int>(Stage::STAGE_1)].c_str());
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetPos(0.0f, -50.0f, 0.0f);
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetSize(stageUISize, stageUISize, 0.0f);

        // 前半（右側）
        for (int i = static_cast<int>(Stage::STAGE_2); i <= half; ++i)
        {
            this->p_stageUI[i] = new Object(this->p_camera);
            this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
            // 均等に配置
            this->p_stageUI[i]->SetPos(i * (stageUISize + space), -50.0f, 0.0f);
            this->p_stageUI[i]->SetSize(stageUISize, stageUISize, 0.0f);
        }

        // 後半（左側）
        for (int i = half + 1; i < static_cast<int>(Stage::MAX); ++i)
        {
            int index = static_cast<int>(Stage::MAX) - i; // 逆順に配置
            this->p_stageUI[i] = new Object(this->p_camera);
            this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
            // 均等に配置
            this->p_stageUI[i]->SetPos(-index * (stageUISize + space), -50.0f, 0.0f);
            this->p_stageUI[i]->SetSize(stageUISize, stageUISize, 0.0f);
        }

        // 左端と右端の座標を当たり判定として保持
        this->leftUIPos = DirectX::XMFLOAT3(-(half - 2) * (stageUISize + space), -50.0f, 0.0f);
        this->rightUIPos = DirectX::XMFLOAT3((half - 2) * (stageUISize + space), -50.0f, 0.0f);
        this->p_leftUI = new PointCollider(DirectX::XMFLOAT3(-(half + 1) * (stageUISize + space), -50.0f, 0.0f));
        this->p_rightUI = new PointCollider(DirectX::XMFLOAT3((half + 1) * (stageUISize + space), -50.0f, 0.0f));
    }
    // 偶数の場合
    else {
        int half = static_cast<int>(Stage::MAX) / 2;

        // 最初だけ真ん中
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)] = new Object(this->p_camera);
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->Init(this->stageUIPath[static_cast<int>(Stage::STAGE_1)].c_str());
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetPos(0.0f, -50.0f, 0.0f);
        this->p_stageUI[static_cast<int>(Stage::STAGE_1)]->SetSize(stageUISize, stageUISize, 0.0f);

        // 前半（右側）
        for (int i = static_cast<int>(Stage::STAGE_2); i <= half; ++i)
        {
            this->p_stageUI[i] = new Object(this->p_camera);
            this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
            // 均等に配置
            this->p_stageUI[i]->SetPos(i * (stageUISize + space), -50.0f, 0.0f);
            this->p_stageUI[i]->SetSize(stageUISize, stageUISize, 0.0f);
        }
        // 後半（左側）
        for (int i = half + 1; i < static_cast<int>(Stage::MAX); ++i)
        {
            int index = static_cast<int>(Stage::MAX) - i; // 逆順に配置
            this->p_stageUI[i] = new Object(this->p_camera);
            this->p_stageUI[i]->Init(this->stageUIPath[i].c_str());
            // 均等に配置
            this->p_stageUI[i]->SetPos(-index * (stageUISize + space), -50.0f, 0.0f);
            this->p_stageUI[i]->SetSize(stageUISize, stageUISize, 0.0f);
        }

        // 左端と右端の座標を当たり判定として保持
        this->leftUIPos = DirectX::XMFLOAT3(-(half - 1) * (stageUISize + space), -50.0f, 0.0f);
        this->rightUIPos = DirectX::XMFLOAT3((half - 1) * (stageUISize + space), -50.0f, 0.0f);
        this->p_leftUI = new PointCollider(DirectX::XMFLOAT3(-(half + 1) * (stageUISize + space), -50.0f, 0.0f));
        this->p_rightUI = new PointCollider(DirectX::XMFLOAT3((half + 1) * (stageUISize + space), -50.0f, 0.0f));
    }

    // 初期化時に選択中のステージの設定
    this->stageNum = static_cast<int>(Stage::STAGE_1); // 初期選択ステージ
    this->isSelect = true; // 初期選択状態に設定

    // 初期選択状態でのサイズ設定
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        if (i == this->stageNum)
        {
            this->p_stageUI[i]->SetSize(this->stageUISizeSelect, this->stageUISizeSelect, 0.0f);
            this->p_stageUI[i]->SetPos(0.0f, (this->stageUISizeSelect - this->stageUISize) / 2.0f - 50.0f, 0.0f);
        }
        else
        {
            this->p_stageUI[i]->SetSize(this->stageUISize, this->stageUISize, 0.0f);
            this->p_stageUI[i]->SetPos(this->p_stageUI[i]->GetPos().x, -50.0f, 0.0f);
        }
    }

    this->isSelect = false;
    this->isStretch = false;
    this->lastUpdateTime = std::chrono::steady_clock::now();

    // UI
    for (int i = static_cast<int>(SelectUI::FRAME); i < static_cast<int>(SelectUI::MAX); ++i)
    {
        this->p_UI[i] = new Object(this->p_camera);
        this->p_UI[i]->Init(this->UIPath[i].c_str());
        auto pos = this->UIPos[i];
        auto size = this->UISize[i];
        this->p_UI[i]->SetPos(pos.x, pos.y, pos.z);
        this->p_UI[i]->SetSize(size.x, size.y, size.z);
    }

    // ビヨンド君傾ける
    this->p_UI[static_cast<int>(SelectUI::BIYOND)]->SetAngle(-35.0f);

    // ポインター
    if (!this->p_point) { this->p_point = new PointCollider(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)); }

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

/** @brief  シーン全体の更新
*/
void StageSelectScene::Update(void)
{
	//フェードイン
    if (!this->isChange) { this->feda->FedaIn(); }

	// 入力待ち
    if (this->inputTimer.Elapsed() > 0.4f)
    {
        // タイトルに戻る
        if (this->p_input->Trigger("TITLE"))
        {
            this->p_sceneManager->ChangeScene(Scene::TitleScene);
            return;
        }

        // 経過時間の計測
        auto currentTime = std::chrono::steady_clock::now();
        this->elapsedTime = currentTime - this->lastUpdateTime;

        this->p_input->Update();

        // ステージUIの移動
        float movePos = 0.0f;
        if (this->p_input->Trigger("L1"))
        {
            // SE
            this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);
            movePos = this->stageUISize + this->space;
            this->isSelect = true;
            this->isPushL1 = true;
        }
        else if (this->p_input->Trigger("R1"))
        {
            // SE
            this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);
            movePos = -this->stageUISize - this->space;
            this->isSelect = true;
            this->isPushR1 = true;
        }
        this->ButtonUpdate();

        // ステージがループするように処理
        for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
        {
            auto pos = this->p_stageUI[i]->GetPos();
            this->p_stageUI[i]->SetPos(pos.x + movePos, pos.y, pos.z);

            auto& coll = this->p_stageUI[i]->GetCollider();
            // 左端なら右端に
            if (coll.CheckCollision(*this->p_leftUI))
            {
                this->p_stageUI[i]->SetPos(rightUIPos.x, rightUIPos.y, rightUIPos.z);
            }
            // 右端なら左端に
            else if (coll.CheckCollision(*this->p_rightUI))
            {
                this->p_stageUI[i]->SetPos(leftUIPos.x, leftUIPos.y, leftUIPos.z);
            }
        }

        // 選択中のステージを保持
        if (this->isSelect)
        {
            for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
            {
                auto& coll = this->p_stageUI[i]->GetCollider();

                if (this->p_point->CheckCollision(coll))
                {
                    // 選択中のステージを大きくする
                    this->p_stageUI[i]->SetSize(this->stageUISizeSelect, this->stageUISizeSelect, 0.0f);
                    this->p_stageUI[i]->SetPos(0.0f, (this->stageUISizeSelect - this->stageUISize) / 2.0f - 50.0f, 0.0f);
                    this->stageNum = i;
                }
                // サイズリセット
                else
                {
                    this->p_stageUI[i]->SetSize(this->stageUISize, this->stageUISize, 0.0f);
                    this->p_stageUI[i]->SetPos(this->p_stageUI[i]->GetPos().x, -50.0f, 0.0f);
                }
            }
            this->isSelect = false;
            this->isStretch = false;
            this->lastUpdateTime = std::chrono::steady_clock::now();

            // ビヨンド君のリサイズ
            auto sizeBiyond = this->UISize[static_cast<int>(SelectUI::BIYOND)];
            this->p_UI[static_cast<int>(SelectUI::BIYOND)]->SetSize(sizeBiyond.x, sizeBiyond.y, sizeBiyond.z);
        }

        // 選択中のステージに飛ぶ
        if (this->p_input->Trigger("SELECT"))
        {
            // SE
            this->p_sound->Play(SOUND_LABEL::SE_UI_CLICK);
            this->isChange = true;
        }
    }
    // フェードアウト
    this->feda->FedaOut(this->isChange);

    // フェードアウト仕切ったらシーン遷移
    if (this->isChange && this->feda->GetAlpha() >= 1.0f)
    {
        this->SelectStage(this->stageNum);
        return;
    }

    // アニメーション
    this->AnimateUI();

    //--------------------------------------------------------------------------
    //      オブジェクトの更新
    //--------------------------------------------------------------------------    
    this->p_background->Update();
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        this->p_stageUI[i]->Update();
    }
    for (int i = static_cast<int>(SelectUI::FRAME); i < static_cast<int>(SelectUI::MAX); ++i)
    {
        this->p_UI[i]->Update();
    }

    // カメラの更新
    this->p_camera->Update();
    this->feda->Update();
}

/** @brief UIのアニメーション処理 
*/
void StageSelectScene::AnimateUI()
{
    // 伸ばす
    if (!this->isStretch)
    {
        auto sizeStage = this->p_stageUI[this->stageNum]->GetSize();
        auto sizeBiyond = this->p_UI[static_cast<int>(SelectUI::BIYOND)]->GetSize();

        this->p_stageUI[stageNum]->SetSize(sizeStage.x + 2.5f, sizeStage.y + 2.5f, sizeStage.z);
        this->p_UI[static_cast<int>(SelectUI::BIYOND)]->SetSize(sizeBiyond.x + 4.0f, sizeBiyond.y + 2.0f, sizeBiyond.z);

    }

    // 縮める
    else
    {
        auto sizeStage = this->p_stageUI[stageNum]->GetSize();
        auto sizeBiyond = this->p_UI[static_cast<int>(SelectUI::BIYOND)]->GetSize();

        this->p_stageUI[stageNum]->SetSize(sizeStage.x - 2.5f, sizeStage.y - 2.5f, sizeStage.z);
        this->p_UI[static_cast<int>(SelectUI::BIYOND)]->SetSize(sizeBiyond.x - 4.0f, sizeBiyond.y - 2.0f, sizeBiyond.z);

    }

    // 経過時間のリセット
    if (this->elapsedTime > this->interval)
    {
        this->isStretch = !this->isStretch;
        this->lastUpdateTime = std::chrono::steady_clock::now();
    }
}

/**	@brief 	ボタンを押したときのアニメーション
*/
void StageSelectScene::ButtonUpdate()
{
    // L1を押したとき
    auto pushSize = this->p_UI[static_cast<int>(SelectUI::L1)]->GetSize();
    // 縮小
    if (this->isPushL1)
    {
        if (pushSize.x > this->UISize[static_cast<int>(SelectUI::L1)].x * 0.9f)
        {
            this->p_UI[static_cast<int>(SelectUI::L1)]->SetSize(pushSize.x - 2.0f, pushSize.y - 2.0f, pushSize.z);
        }
        else { this->isPushL1 = false; }

        // 矢印の色変更
        this->p_UI[static_cast<int>(SelectUI::LEFT_ARROW)]->SetColor(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
    }
    // 拡大(元の大きさにする)
    else
    {
        if (pushSize.x < this->UISize[static_cast<int>(SelectUI::L1)].x)
        {
            this->p_UI[static_cast<int>(SelectUI::L1)]->SetSize(pushSize.x + 2.0f, pushSize.y + 2.0f, pushSize.z);
        }

        // 矢印の色変更
        this->p_UI[static_cast<int>(SelectUI::LEFT_ARROW)]->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // R1を押したとき
    pushSize = this->p_UI[static_cast<int>(SelectUI::R1)]->GetSize();
    // 縮小
    if (this->isPushR1)
    {
        if (pushSize.x > this->UISize[static_cast<int>(SelectUI::R1)].x * 0.9f)
        {
            this->p_UI[static_cast<int>(SelectUI::R1)]->SetSize(pushSize.x - 2.0f, pushSize.y - 2.0f, pushSize.z);
        }
        else { this->isPushR1 = false; }

        // 矢印の色変更
        this->p_UI[static_cast<int>(SelectUI::RIGHT_ARROW)]->SetColor(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
    }
    // 拡大(元の大きさにする)
    else
    {
        if (pushSize.x < this->UISize[static_cast<int>(SelectUI::R1)].x)
        {
            this->p_UI[static_cast<int>(SelectUI::R1)]->SetSize(pushSize.x + 2.0f, pushSize.y + 2.0f, pushSize.z);
        }

        // 矢印の色変更
        this->p_UI[static_cast<int>(SelectUI::RIGHT_ARROW)]->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    }
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

    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++)
    {
        this->p_stageUI[i]->Draw();
    }

    for (int i = static_cast<int>(SelectUI::FRAME); i < static_cast<int>(SelectUI::MAX); ++i)
    {
        this->p_UI[i]->Draw();
    }
	this->feda->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	StageSelectScene::Finalize(void)
{
    // BGM
    this->p_sound->Stop(SOUND_LABEL::BGM_TITLE);

    SAFE_DELETE(this->p_camera);    // カメラ

    //--------------------------------------------------------------------------
    //		オブジェクト
    //--------------------------------------------------------------------------
    SAFE_DELETE(this->p_background);
    for (int i = static_cast<int>(Stage::STAGE_1); i < static_cast<int>(Stage::MAX); i++) { SAFE_DELETE(this->p_stageUI[i]); }
    for (int i = static_cast<int>(SelectUI::LEFT_ARROW); i < static_cast<int>(SelectUI::MAX); ++i) { SAFE_DELETE(this->p_UI[i]); }
    SAFE_DELETE(this->p_point);
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

/**	@brief 	ステージの選択
*	@param	in&t _stageNum
*/
void StageSelectScene::SelectStage(int& _stageNum)
{
    switch (static_cast<StageSelectScene::Stage>(_stageNum))
    {
    case StageSelectScene::Stage::STAGE_1:
        this->p_sceneManager->ChangeScene(Scene::Stage_1);
        break;
    case StageSelectScene::Stage::STAGE_2:
        this->p_sceneManager->ChangeScene(Scene::Stage_2);
        break;
    case StageSelectScene::Stage::STAGE_3:
        this->p_sceneManager->ChangeScene(Scene::Stage_3);
        break;
    case StageSelectScene::Stage::STAGE_4:
        this->p_sceneManager->ChangeScene(Scene::Stage_4);
        break;
    case StageSelectScene::Stage::STAGE_5:
    this->p_sceneManager->ChangeScene(Scene::Stage_10); // Stage5に10をあてがう
    break;
    //case StageSelectScene::Stage::STAGE_6:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_10);// Stage6に10をあてがう
    //    break;
    //case StageSelectScene::Stage::STAGE_6:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_6);
    //    break;
    //case StageSelectScene::Stage::STAGE_7:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_7);
    //    break;
    //case StageSelectScene::Stage::STAGE_8:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_8);
    //    break;
    //case StageSelectScene::Stage::STAGE_9:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_9);
    //    break;
    //case StageSelectScene::Stage::STAGE_10:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_10);
    //    break;
    //case StageSelectScene::Stage::STAGE_11:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_11);
    //    break;
    //case StageSelectScene::Stage::STAGE_12:
    //    this->p_sceneManager->ChangeScene(Scene::Stage_12);
    //    break;
    default:
        break;
    }
    return;
}