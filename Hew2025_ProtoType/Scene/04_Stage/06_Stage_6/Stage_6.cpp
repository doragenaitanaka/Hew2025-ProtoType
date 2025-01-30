﻿/**	@file	Stage_6.cpp
*	@brief 	Stage_6
*	@date 2024/12/19
*/
#include"Stage_6.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_6::Stage_6()
{
    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->PushObject = nullptr;
    this->seesaw = nullptr;
    this->SeesawOption = nullptr;
    this->Connector = nullptr;
    this->BallObject = nullptr;
    this->grabbox = nullptr;
    this->SlopeObject = nullptr;

    for (n = 0; n < 2; n++)
    {
        this->SeesawHead[n] = nullptr;
    }

    for (n = 0; n < 3; n++)
    {
        this->hook[n] = nullptr;
    }

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
Stage_6::~Stage_6()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_6::Initialize(void)
{
    // BGM
    this->p_sound->Play(SOUND_LABEL::BGM_GAME);

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }

    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage6.csv");
    }

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------
        
    // 背景
    if (!this->background) { this->background = new Background(this->p_camera); }
    this->background->Init(L"Asset/background.png");
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);

    // プレイヤー
    if (!this->player) { this->player = new Player(this->p_camera); }
    this->player->Init(L"Asset/gumbody2.png");
    this->player->SetPos(this->playerPos.x, this->playerPos.y, 0.0f);
    this->player->SetSize(this->PlayerSize.x, this->PlayerSize.y, 0.0f);
    
    // プレイヤーをターゲットに設定
    this->p_camera->SetTarget(this->player);

    // ゴール
    if (!this->goal) { this->goal = new Object(this->p_camera); }
    this->goal->Init(L"Asset/Gimmick/goal.png");
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);
    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

    // 
    if (!this->PushObject) { this->PushObject = new Object(this->p_camera); }   
    this->PushObject->Init(L"Asset/Gimmick/pencase.png");
    this->PushObject->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);
    this->PushObject->SetSize(PushObjectSize00.x, PushObjectSize00.y, 0.0f);

    // シーソー
    if (!this->seesaw) { this->seesaw = new Seesaw(this->p_camera); }

    if (!this->Connector) { this->Connector = new Object(this->p_camera); }
    this->Connector->Init(L"Asset/Gimmick/seesaw.png");//当たり判定用ブロックのテクスチャ
    this->Connector->SetPos(SeesawConnectPos.x, SeesawConnectPos.y, 0.0f);
    this->Connector->SetSize(SeesawConnectSize.x, SeesawConnectSize.y, 0.0f);
    this->Connector->SetAngle(ConnectorAngle);//シーソーの角度

    //シーソーの支点
    if (!this->SeesawOption) { this->SeesawOption = new Object(this->p_camera); }
    this->SeesawOption->Init(L"Asset/Gimmick/seesaw_pedestal.png");//当たり判定用ブロックのテクスチャ
    this->SeesawOption->SetPos(SeesawConnectPos.x, SeesawConnectPos.y, 0.0f);
    this->SeesawOption->SetSize(SeesawOptionSize.x, SeesawOptionSize.y, 0.0f);

    for (int i = 0; i < 2; i++)
    {
        if (!this->SeesawHead[i]) { this->SeesawHead[i] = new Object(this->p_camera); }
        this->SeesawHead[i]->Init(L"Asset/darkwood2.png");
        this->SeesawHead[i]->SetPos(this->SeeSawHeadPos[i].x, this->SeeSawHeadPos[i].y, 0.0f);
        this->SeesawHead[i]->SetSize(this->SeeSawHeadSize[i].x, this->SeeSawHeadSize[i].y, 0.0f);
    }

    // ボール
    if (!this->BallObject) { this->BallObject = new Ball(this->p_camera); }
    this->BallObject->Init(L"Asset/Gimmick/ball_03.png");//当たり判定用の
    this->BallObject->SetPos(BallPos.x, BallPos.y, 0.0f);
    this->BallObject->SetSize(BallSize.x, BallSize.y, 0.0f);
    this->BallObject->SetFriction(0.95f); // 摩擦係数
    this->BallObject->SetState(Ball::STOP);

    // つかむオブジェクト
    if (!this->grabbox) { this->grabbox = new GrabBox(this->p_camera); }
    this->grabbox->Init(L"Asset/Gimmick/eraser.png");//当たり判定用のブロックテクスチャ
    this->grabbox->SetPos(GrabboxPos.x, GrabboxPos.y, 0.0f);//当たり判定用ブロックの座標設定
    this->grabbox->SetSize(GrabboxSize.x, GrabboxSize.y, 0.0f);//当たり判定用ブロックの大きさ設定

    //フックの初期化
    for (int i = 0; i < 3; i++)
    {
        if (!this->hook[i]) { this->hook[i] = new Object(this->p_camera); }
        this->hook[i]->Init(L"Asset/Gimmick/hook.png");
        this->hook[i]->SetPos(this->HookPos[i].x, this->HookPos[i].y, 0.0f);
        this->hook[i]->SetSize(this->HookSize[i].x, this->HookSize[i].y, 0.0f);
    }

    // 坂道
    if (!this->SlopeObject) { this->SlopeObject = new Object(this->p_camera); }
    this->SlopeObject->Init(L"Asset/lightwood2.png");
    this->SlopeObject->SetPos(this->slopePos.x, this->slopePos.y, 0.0f);
    this->SlopeObject->SetSize(this->slopeSize.x, this->slopeSize.y, 0.0f);
    this->SlopeObject->SetAngle(slopeAngle);

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
void	Stage_6::Update(void)
{
    this->p_input->Update();

    p_input->GetLeftAnalogStick();
    this->player->SetPos(playerPos.x, playerPos.y, 0.0f);
    //----------------------------------------------
    // Creative Mode
    //----------------------------------------------
    if (gamemode == 0)
    {
        if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
        {
            playerPos.x += 0.0f;
        }
        else
        {
            playerPos.x += p_input->GetLeftAnalogStick().x * 10.0f;
        }
        if (p_input->GetLeftAnalogStick().y * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().y * 10.0f >= -2.0f)
        {
            playerPos.y += 0.0f;
        }
        else
        {
            playerPos.y += p_input->GetLeftAnalogStick().y * 10.0f;
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

        if (this->p_input->Trigger("SPACE"))
        {
            //gamemode = 1;
            std::cout << "x:" << std::to_string(playerPos.x) << " y:" << std::to_string(playerPos.y) << std::endl;
        }
    }

    //----------------------------------------------
    // Player Mode
    //----------------------------------------------
    if (this->gamemode == 1)
    {
        if (this->GrabFlg == false)
        {
            if (this->StayGround == false && JumpState != 2)
            {
                playerPos.y -= 10.0f;
            }

            if (this->p_input->Press("LEFT"))
            {
                playerPos.x -= 10.0f;
            }

            if (this->p_input->Press("RIGHT"))
            {
                playerPos.x += 10.0f;
                if (ColliderState == 5)
                {
                    playerPos.y += 10.0f;
                }
            }

        }

        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            //オブジェクトを離す処理
            this->grabbox->Release();
            GrabFlg = false;
            JumpState = 1;
        }

        if (ColliderState == 7)
        {
            if (this->p_input->Press("UP"))
            {
                //掴まる処理
                this->grabbox->Grab(player);
                GrabFlg = true;
            }
        }

        if (this->p_input->Press("DOWN"))
        {
            //オブジェクトを離す処理
            this->grabbox->Release();
            GrabFlg = false;
        }

        if (ColliderState == 5)
        {
            playerPos.x -= 2.0f;
            playerPos.y -= 2.0f;
        }

        if (this->p_input->Press("SHIFT"))
        {
            gamemode = 0;
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
    if (BallState == 0)
    {
        BallPos.y -= BallSpeed * 2;
    }

    if (BallMoveFLG[0])
    {

        if (BallState == 2)//右下の坂道
        {
            BallPos.y -= BallSpeed;
            BallMoveFLG[1] = false;
        }
        if (BallState == 3)//右に向かう坂道
        {
            BallPos.y -= BallSpeed / 2;
            BallMoveFLG[1] = true;
        }
        this->BallObject->SetState(Ball::BallState::ROLL);
        if (BallMoveFLG[1])
        {
            BallPos.x += BallSpeed;
            BallAngle--;
        }
        else
        {
            BallPos.x -= BallSpeed;
            BallAngle++;
        }
    }
    // 座標、角度を適用
    this->BallObject->SetAngle(BallAngle);
    this->BallObject->SetPos(BallPos.x, BallPos.y, 0.0f);

    //-----------------------------------

    // ジャンプした時
    if (seesaw->CheckJump())
    {
        if (seesawcnt != 70)
        {
            GrabboxPos.y += 100.0f;
            seesawcnt++;
        }
    }

    if (grabState != 1)
    {
        GrabboxPos.y -= 25.0f;
    }

    if (GrabFlg)
    {
        this->grabbox->Move(grabbox->GetPos());
        playerPos.x = GrabboxPos.x;
        playerPos.y = GrabboxPos.y;
    }

    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));
    this->grabbox->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize.x - 100.0f, GrabboxSize.y, 0.0f));
    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize[0].x, HookSize[0].y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize[0].x, HookSize[0].y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize[0].x, HookSize[0].y, 0.0f));

    this->SeesawHead[0]->SetColliderSize(DirectX::XMFLOAT3(SeeSawHeadSize[0].x, SeeSawHeadSize[0].y, 0.0f));
    this->SeesawHead[1]->SetColliderSize(DirectX::XMFLOAT3(SeeSawHeadSize[1].x, SeeSawHeadSize[1].y, 0.0f));
    
    this->Connector->SetColliderSize(DirectX::XMFLOAT3(SeesawConnectSize.x, SeesawConnectSize.y, 0.0f));
    this->BallObject->SetColliderSize(DirectX::XMFLOAT3(BallSize.x, BallSize.y, 0.0f));
    this->PushObject->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize00.x - 100.0f, PushObjectSize00.y, 0.0f));
    this->SlopeObject->SetColliderSize(DirectX::XMFLOAT3(slopeSize.x, slopeSize.y, 0.0f));


    // コライダーの取得
    auto& playerColl = player->GetCollider();
    auto& goalColl = goal->GetCollider();
    auto& pushColl = PushObject->GetCollider();
    auto& ballColl = BallObject->GetCollider();
    auto& grabColl = grabbox->GetCollider();
    auto& seesawColl = Connector->GetCollider();
    auto& slopeColl = this->SlopeObject->GetCollider();
    auto& tiles = this->p_tileMap->GetTiles();

    auto& HookColl1 = this->hook[0]->GetCollider();
    auto& HookColl2 = this->hook[1]->GetCollider();
    auto& HookColl3 = this->hook[2]->GetCollider();

    auto& headColl1 = this->SeesawHead[0]->GetCollider();
    auto& headColl2 = this->SeesawHead[1]->GetCollider();

    // タイルマップとの衝突判定
    this->ColliderState = 0;
    StayGround = false;
    this->BallState = 0;
    this->grabState = 0;

    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            this->StayGround = true;
        }
        if (ballColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            BallState = 1;
        }
    }


    if (playerColl.CheckCollision(HookColl1) || playerColl.CheckCollision(HookColl2) || playerColl.CheckCollision(HookColl3))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 2;
    }

        if (playerColl.CheckCollision(headColl1) || playerColl.CheckCollision(headColl2))
        {
            this->StayGround = true;
        }

        if (ballColl.CheckCollision(headColl1) || ballColl.CheckCollision(headColl2))
        {
            this->BallState = 3;
            BallMoveFLG[0] = false;
            BallPos = SeeSawHeadPos[0];
            ConnectorAngle = -15.0f;
        }

        if (grabColl.CheckCollision(headColl1) ||grabColl.CheckCollision(headColl2))
        {
            this->grabState = 1;
        }

    if (playerColl.CheckCollision(pushColl))
    {
        this->ColliderState = 3;
    }

    if (playerColl.CheckCollision(goalColl))
    {
        this->ColliderState = 4;
    }

    if (playerColl.CheckCollision(slopeColl))
    {
        StayGround = true;
        this->ColliderState = 5;
    }

    if (playerColl.CheckCollision(ballColl))
    {
        this->ColliderState = 6;
        this->BallMoveFLG[0] = true;
    }
    
    if (playerColl.CheckCollision(grabColl))
    {
        this->ColliderState = 7;
    }

    if (ballColl.CheckCollision(slopeColl))
    {
        this->BallState = 2;
        this->BallMoveFLG[1] = false;
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
        else if (ColliderState == 3)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->ブルーベリー色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 7)//if ColliderState == 7 ->オレンジ色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
    if (gamemode == 1)//Player Mode
    {
        if (StayGround == true)//if ColliderState == 1 ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
            JumpState = 0;
        }
        else if (ColliderState == 2)//if ColliderState == 2 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->ブルーベリー色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f));
        }
        else if (ColliderState == 7)//if ColliderState == 7 ->オレンジ色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->background->Update();
    this->p_tileMap->Update();
    this->player->Update();
    this->goal->Update();
    this->PushObject->Update();
    this->Connector->Update();
    this->SeesawOption->Update();
    this->BallObject->Update();
    this->grabbox->Update();
    this->SlopeObject->Update();

    this->Connector->SetAngle(ConnectorAngle);

    this->seesaw->Update(Connector, SeesawHead[1], SeesawHead[0]);  // オフセット(元々cameraPosだった現pos)は値無しで
    this->seesaw->CheckCollision(grabbox, BallObject,SeesawHead[1],SeesawHead[0]);
    
    for (n = 0; n < 3; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->SeesawHead[n]->Update();
    }

    // カメラの更新
    this->p_camera->Update();

    this->grabbox->SetPos(GrabboxPos.x, GrabboxPos.y, GrabboxPos.z);
}

/**	@brief 	シーン全体の描画
*/
void	Stage_6::Draw(void)
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
    this->SlopeObject->Draw();

    this->p_tileMap->Draw();

    this->goal->Draw();
    this->PushObject->Draw();
    this->Connector->Draw();
    this->SeesawOption->Draw();
    this->grabbox->Draw();
    
    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->SeesawHead[n]->Draw();
    }

    for (n = 0; n < 3; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }

    this->BallObject->Draw();
    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_6::Finalize(void)
{
    // BGM
    this->p_sound->Stop(SOUND_LABEL::BGM_GAME);

    SAFE_DELETE(this->p_camera);    // カメラ
    SAFE_DELETE(this->p_tileMap);   // タイルマップ

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
    SAFE_DELETE(this->goal);
    SAFE_DELETE(this->PushObject);
    SAFE_DELETE(this->Connector);
    SAFE_DELETE(this->BallObject);
    SAFE_DELETE(this->grabbox);
    SAFE_DELETE(this->SlopeObject);
    SAFE_DELETE(this->SeesawOption);
        ;

    for (n = 0; n < 3; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->SeesawHead[n]);
    }
    SAFE_DELETE(this->player);
}