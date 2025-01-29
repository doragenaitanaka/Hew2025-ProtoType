/**	@file	Stage_12.cpp
*	@brief 	Stage_12
*	@date 2024/12/19
*/
#include"Stage_12.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_12::Stage_12()
{
    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->seesaw = nullptr;
    this->ball = nullptr;
    this->Pipe[0] = nullptr;
    this->Pipe[1] = nullptr;
    this->grabbox = nullptr;

    for (n = 0; n < 3; n++)
    {
        this->slope[n] = nullptr;
    }

    for (n = 0; n < 3; n++)
    {
        this->pen[n] = nullptr;
    }

    for (n = 0; n < 5; n++)
    {
        this->hook[n] = nullptr;
    }

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*/
Stage_12::~Stage_12()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_12::Initialize(void)
{
    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }


    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage12.csv");
    }

    if (!this->background) { this->background = new Background(this->p_camera); }
    this->background->Init(L"Asset/background.png");
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->background->SetPos(0.0f, 0.0f, 0.0f);

    if (!this->player) { this->player = new Player(this->p_camera); }
    this->player->Init(L"Asset/gumbody2.png");
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);
    this->player->SetPos(playerPos.x, playerPos.y, 0.0f);
    DirectX::XMFLOAT3 playerPos = this->player->GetPos();

    if (!this->goal) { this->goal = new Object(this->p_camera); }
    this->goal->Init(L"Asset/Gimmick/goal.png");
    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);

    if (!this->grabbox) { this->grabbox = new GrabBox(this->p_camera); }
    this->grabbox->Init(L"Asset/Gimmick/eraser.png");
    this->grabbox->SetSize(GrabboxSize.x, GrabboxSize.y, 0.0f);
    this->grabbox->SetPos(GrabboxPos.x, GrabboxPos.y, 0.0f);

    if (!this->ball) { this->ball = new Ball(this->p_camera); }
    this->ball->Init(L"Asset/Gimmick/ball_03.png");
    this->ball->SetSize(BallSize.x, BallSize.y, 0.0f);
    this->ball->SetPos(BallPos.x, BallPos.y, 0.0f);

    if (!this->seesaw) { this->seesaw = new Seesaw(this->p_camera); }
    this->seesaw->Init(L"Asset/Gimmick/seesaw.png");
    this->seesaw->SetSize(SeesawSize.x, SeesawSize.y, 0.0f);
    this->seesaw->SetPos(SeesawPos.x, SeesawPos.y, 0.0f);

    for (n = 0; n < 3; n++)
    {
        if (!this->SeesawOption[n]) { this->SeesawOption[n] = new Object(this->p_camera); }
        this->SeesawOption[n]->Init(L"Asset/Gimmick/seesaw_pedestal.png");
    }
    this->SeesawOption[0]->SetPos(SeesawOpPos00.x, SeesawOpPos00.y, 0.0f);
    this->SeesawOption[1]->SetPos(SeesawOpPos01.x, SeesawOpPos01.y, 0.0f);
    this->SeesawOption[2]->SetPos(SeesawOpPos02.x, SeesawOpPos02.y, 0.0f);

    this->SeesawOption[0]->SetSize(SeesawOpSize00.x, SeesawOpSize00.y, 0.0f);
    this->SeesawOption[1]->SetSize(SeesawOpSize01.x, SeesawOpSize01.y, 0.0f);
    this->SeesawOption[2]->SetSize(SeesawOpSize02.x, SeesawOpSize02.y, 0.0f);

    for (n = 0; n < 3; n++)
    {
        if (!this->slope[n]) { this->slope[n] = new Object(this->p_camera); }
        this->slope[n]->Init(L"Asset/lightwood2.png");
    }
    this->slope[0]->SetPos(SlopePos00.x, SlopePos00.y, 0.0f);
    this->slope[1]->SetPos(SlopePos01.x, SlopePos01.y, 0.0f);
    this->slope[2]->SetPos(SlopePos02.x, SlopePos02.y, 0.0f);
    this->slope[0]->SetSize(SlopeSize00.x, SlopeSize00.y, 0.0f);
    this->slope[1]->SetSize(SlopeSize01.x, SlopeSize01.y, 0.0f);
    this->slope[2]->SetSize(SlopeSize02.x, SlopeSize02.y, 0.0f);

    this->slope[0]->SetAngle(slopeAngle01);
    this->slope[1]->SetAngle(slopeAngle00);
    this->slope[2]->SetAngle(slopeAngle01);



    for (n = 0; n < 5; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object(this->p_camera); }
        this->hook[n]->Init(L"Asset/Gimmick/hook.png");
        this->hook[n]->SetSize(HookSize.x, HookSize.y, 0.0f);
    }
    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);
    this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);
    this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);
    this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);

    for (n = 0; n < 3; n++)
    {
        if (!this->pen[n]) { this->pen[n] = new Object(this->p_camera); }
        this->pen[n]->Init(L"Asset/Gimmick/pen.png");
        this->pen[n]->SetSize(PenSize.x, PenSize.y, 0.0f);
    }
    this->pen[0]->SetPos(PenPos00.x, PenPos00.y, 0.0f);
    this->pen[1]->SetPos(PenPos01.x, PenPos01.y, 0.0f);
    this->pen[2]->SetPos(PenPos02.x, PenPos02.y, 0.0f);

    for (n = 0; n < 2; n++)
    {
        if (!this->Pipe[n]) { this->Pipe[n] = new Object(this->p_camera); }
        this->Pipe[n]->Init(L"Asset/Gimmick/Pipe.png");
        this->Pipe[n]->SetSize(PipeSize.x, PipeSize.y, 0.0f);
    }
    this->Pipe[0]->SetPos(PipePos00.x, PipePos00.y, 0.0f);
    this->Pipe[1]->SetPos(PipePos01.x, PipePos01.y, 0.0f);

    for (n = 0; n < 2; n++)
    {
        if (!this->PushObject[n]) { this->PushObject[n] = new Object(this->p_camera); }
        this->PushObject[n]->Init(L"Asset/Gimmick/pencase.png");
        this->PushObject[n]->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    }
    this->PushObject[0]->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);
    this->PushObject[1]->SetPos(PushObjectPos01.x, PushObjectPos01.y, 0.0f);

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
void	Stage_12::Update(void)
{
    this->p_input->Update();

    p_input->GetLeftAnalogStick();
    this->player->SetPos(playerPos.x, playerPos.y, playerPos.z);

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

        if (this->GrabFlg == false)
        {
            if (this->p_input->Press("LEFT"))
            {
                playerPos.x -= 10.0f;
            }
            if (this->p_input->Press("RIGHT"))
            {
                playerPos.x += 10.0f;
            }

            if (this->p_input->Press("UP"))
            {
                if (ColliderState == 5)
                {
                    //掴まる処理
                    this->grabbox->Grab(player);
                    GrabFlg = true;
                    JumpState = 0;
                }
            }

        }
        

        if (this->p_input->Press("DOWN"))
        {
            //オブジェクトを離す処理
            this->grabbox->Release();
            GrabFlg = false;
        }

        if (StayGround == false && JumpState != 2)
        {
            playerPos.y -= 10.0f;
        }

        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            //オブジェクトを離す処理
            this->grabbox->Release();
            GrabFlg = false;
            JumpState = 1;
        }

        if (this->p_input->Press("SHIFT"))
        {
            gamemode = 0;
        }

        if (ColliderState == 4)
        {
            playerPos.x -= 20.0f;
            playerPos.y -= 20.0f;
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
    if (GrabFlg)
    {
        this->grabbox->Move(grabbox->GetPos());
        playerPos = GrabboxPos;
    }


    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));

    this->slope[0]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize00.x, SlopeSize00.y, 0.0f));
    this->slope[1]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize01.x, SlopeSize01.y, 0.0f));
    this->slope[2]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize02.x, SlopeSize02.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[4]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));

    this->pen[0]->SetColliderSize(DirectX::XMFLOAT3(PenSize.x, PenSize.y, 0.0f));
    this->pen[1]->SetColliderSize(DirectX::XMFLOAT3(PenSize.x, PenSize.y, 0.0f));
    this->pen[2]->SetColliderSize(DirectX::XMFLOAT3(PenSize.x, PenSize.y, 0.0f));

    this->slope[0]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize00.x, SlopeSize00.y, 0.0f));
    this->slope[1]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize01.x, SlopeSize01.y, 0.0f));
    this->slope[2]->SetColliderSize(DirectX::XMFLOAT3(SlopeSize02.x, SlopeSize02.y, 0.0f));

    this->seesaw->SetColliderSize(DirectX::XMFLOAT3(SeesawSize.x, SeesawSize.y, 0.0f));

    this->ball->SetColliderSize(DirectX::XMFLOAT3(BallSize.x, BallSize.y, 0.0f));

    this->SeesawOption[0]->SetColliderSize(DirectX::XMFLOAT3(SeesawOpSize00.x, SeesawOpSize00.y, 0.0f));
    this->SeesawOption[1]->SetColliderSize(DirectX::XMFLOAT3(SeesawOpSize01.x, SeesawOpSize01.y, 0.0f));

    this->grabbox->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize.x, GrabboxSize.y, 0.0f));
    
    this->PushObject[0]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize.x -300.0f, PushObjectSize.y, 0.0f));
    this->PushObject[1]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize.x -300.0f, PushObjectSize.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    // タイルマップとの衝突判定
    ColliderState = 0;
    StayGround = false;
    auto& playerColl = this->player->GetCollider();
    auto& goalColl = this->goal->GetCollider();
    auto& grabColl = this->grabbox->GetCollider();
    auto& ballColl = this->ball->GetCollider();
    auto& seesawColl = this->seesaw->GetCollider();
    auto& tiles = this->p_tileMap->GetTiles();

    auto& OptionLColl = this->SeesawOption[0]->GetCollider();
    auto& OptionRColl = this->SeesawOption[1]->GetCollider();

    auto& PenColl1 = this->pen[0]->GetCollider();
    auto& PenColl2 = this->pen[1]->GetCollider();
    auto& PenColl3 = this->pen[2]->GetCollider();

    auto& slopeColl1 = this->slope[0]->GetCollider();
    auto& slopeColl2 = this->slope[1]->GetCollider();
    auto& slopeColl3 = this->slope[2]->GetCollider();

    auto& PushColl1 = this->PushObject[0]->GetCollider();
    auto& PushColl2 = this->PushObject[1]->GetCollider();

    auto& HookColl1 = this->hook[0]->GetCollider();
    auto& HookColl2 = this->hook[1]->GetCollider();
    auto& HookColl3 = this->hook[2]->GetCollider();
    auto& HookColl4 = this->hook[3]->GetCollider();
    auto& HookColl5 = this->hook[4]->GetCollider();

    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            StayGround = true;
        }
    }

    if (playerColl.CheckCollision(HookColl1) || playerColl.CheckCollision(HookColl2) || playerColl.CheckCollision(HookColl3) || playerColl.CheckCollision(HookColl4) || playerColl.CheckCollision(HookColl5))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 2;
    }

    if (playerColl.CheckCollision(PushColl1) || playerColl.CheckCollision(PushColl2))
    {
        ColliderState = 3;
    }

    if (playerColl.CheckCollision(grabColl))
    {
        ColliderState = 4;
    }

    if (playerColl.CheckCollision(ballColl))
    {
        ColliderState = 5;
    }

    if (playerColl.CheckCollision(slopeColl1) || playerColl.CheckCollision(slopeColl2) || playerColl.CheckCollision(slopeColl3))
    {
        ColliderState = 6;
    }

    if (playerColl.CheckCollision(PenColl1) || playerColl.CheckCollision(PenColl2) || playerColl.CheckCollision(PenColl3))
    {
        ColliderState = 7;
    }

    if (playerColl.CheckCollision(OptionLColl) || playerColl.CheckCollision(OptionRColl))
    {
        ColliderState = 8;
    }

    if (playerColl.CheckCollision(seesawColl))
    {
        ColliderState = 9;
    }

    if (playerColl.CheckCollision(goalColl))
    {
        ColliderState = 10;
    }

    if (gamemode == 0)//Creative Mode
    {
        if (StayGround == true)//if StayGround == true ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
            JumpState = 0;
        }
        else if (ColliderState == 2)//if ColliderState == 2 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->青色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->緑色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 7)//if ColliderState == 7 ->ピンク色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 8)//if ColliderState == 8 ->黄緑色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f));
        }
        else if (ColliderState == 9)//if ColliderState == 9 ->モスグリーン色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.2f, 0.5f, 0.2f, 1.0f));
        }
        else if (ColliderState == 10)//if ColliderState == 10 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
    if (gamemode == 1)//Player Mode
    {
        if (StayGround == true)//if StayGround == true ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
            JumpState = 0;
        }
        else if (ColliderState == 2)//if ColliderState == 2 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->青色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->緑色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 7)//if ColliderState == 7 ->ピンク色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 8)//if ColliderState == 8 ->黄緑色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f));
        }
        else if (ColliderState == 9)//if ColliderState == 9 ->モスグリーン色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.2f, 0.5f, 0.2f, 1.0f));
        }
        else if (ColliderState == 10)//if ColliderState == 10 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    this->background->Update();
    this->p_tileMap->Update();
    this->p_camera->Update();
    this->player->Update();
    this->seesaw->Update(seesaw,SeesawOption[1],SeesawOption[0]);
    this->goal->Update();
    this->grabbox->Update();
    this->ball->Update();

    for (n = 0; n < 3; n++)//Updateの数
    {
        this->slope[n]->Update();
    }

    for (n = 0; n < 5; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->PushObject[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->Pipe[n]->Update();
    }

    for (n = 0; n < 3; n++)//Updateの数
    {
        this->pen[n]->Update();
    }

    for (n = 0; n < 3; n++)//Updateの数
    {
        this->SeesawOption[n]->Update();
    }

    if (ColliderState == 10)
    {
//        p_sceneManager->ChangeScene(Scene::TitleScene);
    }

    //updateの後にsetposしないと動きがおかしくなる
    this->grabbox->SetPos(GrabboxPos.x, GrabboxPos.y, 0.0f);
}

/**	@brief 	シーン全体の描画
*/
void	Stage_12::Draw(void)
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
    this->seesaw->Draw();
    this->goal->Draw();
    this->grabbox->Draw();
    this->ball->Draw();

    for (n = 0; n < 3; n++)//Drawの数
    {
        this->slope[n]->Draw();
    }

    for (n = 0; n < 5; n++)//Drawの数
    {
        this->hook[n]->Draw();
    }

    for (n = 0; n < 2; n++)//Drawの数
    {
        this->PushObject[n]->Draw();
    }

    for (n = 0; n < 2; n++)//Drawの数
    {
        this->Pipe[n]->Draw();
    }

    for (n = 0; n < 3; n++)//Drawの数
    {
        this->pen[n]->Draw();
    }

    for (n = 0; n < 3; n++)//Drawの数
    {
        this->SeesawOption[n]->Draw();
    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_12::Finalize(void)
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
    SAFE_DELETE(this->background);
    SAFE_DELETE(this->p_tileMap);
    SAFE_DELETE(this->p_camera);
    SAFE_DELETE(this->player);
    SAFE_DELETE(this->seesaw);
    SAFE_DELETE(this->goal);
    SAFE_DELETE(this->grabbox);
    SAFE_DELETE(this->ball);

    for (n = 0; n < 3; n++) 
    {
        SAFE_DELETE(this->slope[n]);
    }

    for (n = 0; n < 5; n++) 
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 2; n++) 
    {
        SAFE_DELETE(this->PushObject[n]);
    }

    for (n = 0; n < 2; n++) 
    {
        SAFE_DELETE(this->Pipe[n]);
    }

    for (n = 0; n < 3; n++) 
    {
        SAFE_DELETE(this->pen[n]);
    }

    for (n = 0; n < 3; n++) 
    {
        SAFE_DELETE(this->SeesawOption[n]);
    }


}
