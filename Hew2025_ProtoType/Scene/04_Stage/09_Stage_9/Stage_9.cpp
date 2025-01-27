/**	@file	Stage_9.cpp
*	@brief 	Stage_9
*	@date 2024/12/19
*/
#include"Stage_9.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_9::Stage_9()
{
    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->PushObject = nullptr;
    this->BallObject = nullptr;
    
    for (n = 0; n < 4; n++)
    {
        this->Slope[n] = nullptr;
    }

    for (n = 0; n < 2; n++)
    {
        this->hook[n] = nullptr;
    }

    for (n = 0; n < 2; n++)
    {
        this->Pen[n] = nullptr;
    }

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*/
Stage_9::~Stage_9()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_9::Initialize(void)
{

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }


    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage9.csv");
    }


    if (!this->background) { this->background = new Object(this->p_camera); }
    this->background->Init(L"Asset/back_img_01.png");
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->background->SetPos(0.0f, 0.0f, 0.0f);

    if (!this->player) { this->player = new Player(this->p_camera); }
    this->player->Init(L"Asset/gumbody2.png");
    this->player->SetSize(100.0f, 100.0f, 0.0f);
    this->player->SetPos(playerPos.x, playerPos.y, 0.0f);
    
    if (!this->goal) { this->goal = new Object(this->p_camera); }
    this->goal->Init(L"Asset/block.png");
    this->goal->SetSize(200.0f, 300.0f, 0.0f);
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);

    if (!this->PushObject) { this->PushObject = new Object(this->p_camera); }
    this->PushObject->Init(L"Asset/block.png");
    this->PushObject->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    this->PushObject->SetPos(PushObjectPos.x, PushObjectPos.y, 0.0f);
    this->PushObject->SetAngle(PushAngle);

    if (!this->BallObject) { this->BallObject = new Object(this->p_camera); }
    this->BallObject->Init(L"Asset/block.png");
    this->BallObject->SetSize(BallSize.x, BallSize.y, 0.0f);
    this->BallObject->SetPos(BallPos.x, BallPos.y, 0.0f);


    for (n = 0; n < 2; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object(this->p_camera); }
        this->hook[n]->Init(L"Asset/block.png");
        this->hook[n]->SetSize(HookSize.x, HookSize.y, 0.0f);
    }

    for (n = 0; n < 2; n++)
    {
        if (!this->Pen[n]) { this->Pen[n] = new Object(this->p_camera); }
        this->Pen[n]->Init(L"Asset/block.png");
        this->Pen[n]->SetSize(PenSize.x, PenSize.y, 0.0f);
    }

    for (n = 0; n < 4; n++)
    {
        if (!this->Slope[n]) { this->Slope[n] = new Object(this->p_camera); }
        this->Slope[n]->Init(L"Asset/block.png");
    }

    this->Slope[0]->SetPos(SlopePos00.x, SlopePos00.y, 0.0f);
    this->Slope[1]->SetPos(SlopePos01.x, SlopePos01.y, 0.0f);
    this->Slope[2]->SetPos(SlopePos02.x, SlopePos02.y, 0.0f);
    this->Slope[3]->SetPos(SlopePos03.x, SlopePos03.y, 0.0f);

    this->Slope[0]->SetSize(SlopeSize00.x, SlopeSize00.y, 0.0f);
    this->Slope[1]->SetSize(SlopeSize01.x, SlopeSize01.y, 0.0f);
    this->Slope[2]->SetSize(SlopeSize02.x, SlopeSize02.y, 0.0f);
    this->Slope[3]->SetSize(SlopeSize03.x, SlopeSize03.y, 0.0f);

    this->Slope[0]->SetAngle(SlopeAngle[0]);
    this->Slope[1]->SetAngle(SlopeAngle[1]);
    this->Slope[2]->SetAngle(SlopeAngle[2]);
    this->Slope[3]->SetAngle(SlopeAngle[3]);

    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);

    this->Pen[0]->SetPos(PenPos00.x, PenPos00.y, 0.0f);
    this->Pen[1]->SetPos(PenPos01.x, PenPos01.y, 0.0f);

    // プレイヤーをターゲットに設定
    this->p_camera->SetTarget(this->player);

    //--------------------------------------------------------------------------
    //		描画関連の初期化
    //--------------------------------------------------------------------------
    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー


    //--------------------------------------------------------------------------
    //		描画関連の初期化
    //--------------------------------------------------------------------------	

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
void	Stage_9::Update(void)
{
    this->p_input->Update();

    p_input->GetLeftAnalogStick();
    this->player->SetPos(playerPos.x, playerPos.y, playerPos.z);
    this->BallObject->SetPos(BallPos.x, BallPos.y, 0.0f);
    this->BallObject->SetAngle(BallAngle);


    //----------------------------------------------
    // Creative Mode
    //----------------------------------------------
    if (gamemode == 0)
    {

        if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
        {
            this->player->SetPos(playerPos.x + 0.0f, playerPos.y, playerPos.z);
        }
        else
        {
            float movePosX = this->p_input->GetLeftAnalogStick().x * 10.0f;
            this->player->SetPos(playerPos.x + movePosX, playerPos.y, playerPos.z);

        }
        if (p_input->GetLeftAnalogStick().y * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().y * 10.0f >= -2.0f)
        {
            this->player->SetPos(playerPos.x, playerPos.y + 0.0f, playerPos.z);
        }
        else
        {
            float movePosX = this->p_input->GetLeftAnalogStick().y * 10.0f;
            this->player->SetPos(playerPos.x, playerPos.y + movePosX, playerPos.z);
        }

        if (this->p_input->Press("LEFT"))
        {
            playerPos.x -= 20.0f;
        }
        if (this->p_input->Press("RIGHT"))
        {
            playerPos.x += 20.0f;
        }
        if (this->p_input->Press("UP"))
        {
            playerPos.y += 20.0f;
        }
        if (this->p_input->Press("DOWN"))
        {
            playerPos.y -= 20.0f;
        }

        if (this->p_input->Press("SPACE"))
        {
            gamemode = 1;
        }
    }

    //----------------------------------------------
    // Player Mode
    //----------------------------------------------
    if (gamemode == 1)
    {

        if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
        {
            this->player->SetPos(playerPos.x + 0.0f, playerPos.y, playerPos.z);
        }
        else
        {
            float movePosX = this->p_input->GetLeftAnalogStick().x * 10.0f;
            this->player->SetPos(playerPos.x + movePosX, playerPos.y, playerPos.z);

        }
        if (p_input->GetLeftAnalogStick().y * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().y * 10.0f >= -2.0f)
        {
            this->player->SetPos(playerPos.x, playerPos.y + 0.0f, playerPos.z);
        }
        else
        {
            float movePosX = this->p_input->GetLeftAnalogStick().y * 10.0f;
            this->player->SetPos(playerPos.x, playerPos.y + movePosX, playerPos.z);
        }

        if (this->p_input->Press("LEFT"))
        {
            playerPos.x -= 10.0f;
            if (ColliderState == 5 && SlopeState)
            {
                playerPos.y += 10.0f;
            }
        }
        if (this->p_input->Press("RIGHT"))
        {
            playerPos.x += 10.0f;
            if (ColliderState == 5 && !SlopeState)
            {
                playerPos.y += 5.0f;
            }
        }

        if (ColliderState == 5)
        {
            if (SlopeState)
            {
                playerPos.x += 2.0f;
                playerPos.y -= 2.0f;
            }
            else if (!SlopeState)
            {
                playerPos.x -= 15.0f;
                playerPos.y -= 10.0f;
            }
        }

        if (StayGround == false && JumpState != 2 )
        {
            playerPos.y -= 10.0f;
        }

        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
        }

    }



    //-----------------------------------------------------
    if (JumpState == 1)
    {
        if (cnt != 25)
        {
            playerPos.y += 25.0f;
            cnt++;
        }
        else
        {
            cnt = 0;
            JumpState = 2;
        }
    }

    if (JumpState == 2)
    {
        if (cnt != 7)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
            JumpState = 3;
        }
    }
    //-----------------------------------
    //ボール処理
    //-----------------------------------
    if (BallMoveFLG)
    {
        if (BallState != 3)
        {
            if (BallState == 1)
            {
                BallPos.x -= BallSpeed;
                BallAngle++;
            }

            if (BallState == 2)
            {
                BallPos.x -= BallSpeed * 1.7;
                BallAngle += 2;
            }

            if (BallState != 1)
            {
                BallPos.y -= 10.0f;
            }
        }
    }

    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));

    this->BallObject->SetColliderSize(DirectX::XMFLOAT3(BallSize.x, BallSize.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));

    this->Pen[0]->SetColliderSize(DirectX::XMFLOAT3(PenSize.x, PenSize.y, 0.0f));
    this->Pen[1]->SetColliderSize(DirectX::XMFLOAT3(PenSize.x, PenSize.y, 0.0f));


    this->Slope[0]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize00.x, SlopeSize00.y, 0.0f));
    this->Slope[1]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize01.x, SlopeSize01.y, 0.0f));
    this->Slope[2]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize02.x, SlopeSize02.y, 0.0f));
    this->Slope[3]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize03.x, SlopeSize03.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(200.0f, 300.0f, 0.0f));

    // タイルマップとの衝突判定
    ColliderState = 0;
    StayGround = false;
    auto& playerColl = this->player->GetCollider();
    auto& goalColl = this->goal->GetCollider();
    auto& tiles = this->p_tileMap->GetTiles();

    auto& ballColl = this->BallObject->GetCollider();

    auto& HookColl1 = this->hook[0]->GetCollider();
    auto& HookColl2 = this->hook[1]->GetCollider();

    auto& PenColl1 = this->Pen[0]->GetCollider();
    auto& PenColl2 = this->Pen[1]->GetCollider();

    auto& SlopeColl1 = this->Slope[0]->GetCollider();
    auto& SlopeColl2 = this->Slope[1]->GetCollider();
    auto& SlopeColl3 = this->Slope[2]->GetCollider();
    auto& SlopeColl4 = this->Slope[3]->GetCollider();


    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            StayGround = true;
        }

        if (ballColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            BallState = 1;
        }
    }

    if (playerColl.CheckCollision(HookColl1) || playerColl.CheckCollision(HookColl2))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 2;
    }

    if (playerColl.CheckCollision(PenColl1) || playerColl.CheckCollision(PenColl2))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 3;
    }
    
    if (playerColl.CheckCollision(ballColl))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 4;
        BallMoveFLG = true;
    }

    if (playerColl.CheckCollision(SlopeColl1) || playerColl.CheckCollision(SlopeColl3))
    {
        //std::cout << "当たった" << std::endl;
        SlopeState = true;
        ColliderState = 5;
        StayGround = true;
    }

    if (playerColl.CheckCollision(SlopeColl2) || playerColl.CheckCollision(SlopeColl4))
    {
        //std::cout << "当たった" << std::endl;
        SlopeState = false;
        ColliderState = 5;
        StayGround = true;
    }

    if (playerColl.CheckCollision(goalColl))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 6;
    }

   
    if (ballColl.CheckCollision(SlopeColl4))
    {
        BallState = 2;
    }

    if (ballColl.CheckCollision(SlopeColl3))
    {
        BallState = 3;
    }

    if (gamemode == 0)//Creative Mode
    {
        if (StayGround == 1)//if StayGround == true ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
            JumpState = 0;
        }
        else if (ColliderState == 2)//if ColliderState == 2 ->緑になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->青になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
    if (gamemode == 1)//Player Mode
    {
        if (StayGround == 1)//if StayGround == true ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
            JumpState = 0;
        }
        else if (ColliderState == 2)//if ColliderState == 2 ->緑になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->青になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    this->background->Update();
    this->p_tileMap->Update();
    this->BallObject->Update();
    this->PushObject->Update();
    this->player->Update();
    this->goal->Update();

    // カメラの更新
    this->p_camera->Update();

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->hook[n]->Update();
    }
    for (n = 0; n < 2; n++)//Updateの数
    {
        this->Pen[n]->Update();
    }
    for (n = 0; n < 4; n++)//Updateの数
    {
        this->Slope[n]->Update();
    }

    if (ColliderState == 6)
    {
        p_sceneManager->ChangeScene(Scene::Stage_10);
    }
}

/**	@brief 	シーン全体の描画
*/
void	Stage_9::Draw(void)
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
    this->p_tileMap->Draw();
    this->goal->Draw();
    this->PushObject->Draw();
    this->BallObject->Draw();

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->Pen[n]->Draw();
    }

    for (n = 0; n < 4; n++)//当たり判定用ブロック描画
    {
        this->Slope[n]->Draw();
    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_9::Finalize(void)
{
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
    SAFE_DELETE(this->background);//Delete Object
    SAFE_DELETE(this->PushObject);
    SAFE_DELETE(this->BallObject);


    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->Pen[n]);
    }

    for (n = 0; n < 4; n++)
    {
        SAFE_DELETE(this->Slope[n]);
    }

    SAFE_DELETE(this->goal);

    SAFE_DELETE(this->player);

}