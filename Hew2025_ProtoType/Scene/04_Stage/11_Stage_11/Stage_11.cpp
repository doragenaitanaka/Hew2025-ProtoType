﻿/**	@file	Stage_11.cpp
*	@brief 	Stage_11
*	@date 2024/12/19
*/
#include"Stage_11.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
#include <memory> 
/**	@brief 	コンストラクタ
*/
Stage_11::Stage_11()
{
    this->isFailed = false;

    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    // テクスチャの読み込み
    this->textureList[0] = Object::LoadTexture(L"Asset/block.png");         // ブロック
    this->textureList[1] = Object::LoadTexture(L"Asset/Gimmick/hook.png");  // フック

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	
    this->background = nullptr;
    this->player = nullptr;
    this->keyConfigUI = nullptr;
    this->rail = nullptr;
    this->slope = nullptr;
    this->grabbox[0] = nullptr;
    this->grabbox[1] = nullptr;
    this->pendulum[0] = nullptr;
    this->pendulum[1] = nullptr;


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
Stage_11::~Stage_11()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_11::Initialize(void)
{
    // BGM
    this->p_sound->Play(SOUND_LABEL::BGM_GAME);

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }

    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage11.csv");
    }

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	

    // 背景
    if (!this->background) { this->background = new Background(this->p_camera); }
    this->background->Init(L"Asset/background.png");
    this->background->SetPos(0.0f, 0.0f, 0.0f);
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);

    // プレイヤー
    if (!this->player) { this->player = new Player(this->p_camera); }
    this->player->SetTexture(this->textureList[0]);
    this->player->Init();
    this->player->SetPos(0.0f, -100.0f, 100.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

    //キーコンフィグUI
    if (!this->keyConfigUI) { this->keyConfigUI = new Background(this->p_camera); }
    this->keyConfigUI->Init(L"Asset/UI/KeyConfig.png");
    this->keyConfigUI->SetPos(0.0f, 0.0f, 0.0f);
    this->keyConfigUI->SetSize(1920.0f * 0.7f, 1080.0f * 0.7f, 0.0f);
    this->keyConfigUI->SetIsActive(true);

    if (!this->slope) { this->slope = new Object(this->p_camera); }
    this->slope->Init(L"Asset/wall.png");
    this->slope->SetSize(slopeSize.x, slopeSize.y, 0.0f);
    this->slope->SetPos(slopePos.x, slopePos.y, 0.0f);
    this->slope->SetAngle(slopeAngle);

    if (!this->rail) { this->rail = new Object(this->p_camera); }
    this->rail->Init(L"Asset/Gimmick/rail_02.png");
    this->rail->SetSize(RailSize.x, RailSize.y, 0.0f);
    this->rail->SetPos(RailPos.x, RailPos.y, 0.0f);
    this->rail->SetAngle(90.0f);

    for (m = 0; m < 4; m++)
    {
        if (!this->hook[m]) {
            this->hook[m] = std::make_shared<Object>(this->p_camera);
        }
        if (!this->hookdraw[m]) {
            this->hookdraw[m] = std::make_shared<Object>(this->p_camera);
        }
    }

    for (n = 0; n < 2; n++)
    {
        if (!this->pendulum[n]) { this->pendulum[n] = new Pendulum(this->p_camera); }
        this->pendulum[n]->Init(L"Asset/Gimmick/yo-yo.png");
        this->pendulum[n]->SetSize(GrabboxSize.x, GrabboxSize.y, 0.0f);
    }
    this->pendulum[0]->SetPos(GrabboxPos00.x, GrabboxPos00.y, 0.0f);
    this->pendulum[1]->SetPos(GrabboxPos01.x, GrabboxPos01.y, 0.0f);

    for (n = 0; n < 2; n++)
    {
        if (!this->grabbox[n]) { this->grabbox[n] = new GrabBox(this->p_camera); }
        this->grabbox[n]->Init(L"Asset/Gimmick/yo-yo.png");
        this->grabbox[n]->SetSize(GrabboxSize.x, GrabboxSize.y, 0.0f);
    }
    this->grabbox[0]->SetPos(GrabboxPos00.x, GrabboxPos00.y, 0.0f);
    this->grabbox[1]->SetPos(GrabboxPos01.x, GrabboxPos01.y, 0.0f);


    if (!this->playerdraw) { this->playerdraw = std::make_shared<Player>(this->p_camera); }
    if (!this->lefthand) {
        this->lefthand = std::make_shared<Object>(this->p_camera);
    }
    if (!this->righthand) {
        this->righthand = std::make_shared<Object>(this->p_camera);
    }
    if (!this->leftleg) {
        this->leftleg = std::make_shared<Object>(this->p_camera);
    }
    if (!this->rightleg) { this->rightleg = std::make_shared<Object>(this->p_camera); }

    if (!this->eyes) { this->eyes = std::make_shared<Object>(this->p_camera); }

    if (!this->death2) {
        this->death2 = std::make_shared<Object>(this->p_camera);
    }
    if (!this->idle) {
        this->idle = std::make_shared<Object>(this->p_camera);
    }
    if (!this->walking) {
        this->walking = std::make_shared<Object>(this->p_camera);
    }
    if (!this->walking2) {
        this->walking2 = std::make_shared<Object>(this->p_camera);
    }
    if (!this->playercol) {
        this->playercol = std::make_shared<Object>(this->p_camera);
    }
    if (!this->playercol2) {
        this->playercol2 = std::make_shared<Object>(this->p_camera);
    }
    if (!this->playercol3) {
        this->playercol3 = std::make_shared<Object>(this->p_camera);
    }

    if (!this->goal) { this->goal = std::make_shared<Object>(this->p_camera); }



    // プレイヤーをターゲットに設定
    this->p_camera->SetTarget(this->player);

    for (m = 0; m < 4; m++)
    {
        this->hook[m]->SetTexture(this->textureList[1]);
        this->hookdraw[m]->SetTexture(this->textureList[1]);
        this->hook[m]->Init();
        this->hookdraw[m]->Init();
    }


    this->playerdraw->Init(L"Asset/gumbody.png");
    this->eyes->Init(L"Asset/gum_eyes.png");
    this->lefthand->Init(L"Asset/left_hand.png");
    this->righthand->Init(L"Asset/right_hand.png");
    this->leftleg->Init(L"Asset/left_leg.png");
    this->rightleg->Init(L"Asset/right_leg.png");

    this->death2->Init(L"Asset/death.png", 4, 1);
    this->idle->Init(L"Asset/idle_3.png", 4, 1);
    this->walking->Init(L"Asset/walking_2.png", 4, 1);
    this->walking2->Init(L"Asset/walking_3.png", 4, 1);

    this->playercol->SetTexture(this->textureList[0]);
    this->playercol2->SetTexture(this->textureList[0]);
    this->playercol3->SetTexture(this->textureList[0]);
    this->playercol->Init();
    this->playercol2->Init();
    this->playercol3->Init();

    this->goal->Init(L"Asset/Gimmick/goal.png");

    this->playerdraw->SetSize(PlayerDrawSize.x, PlayerDrawSize.y, 0.0f);
    this->eyes->SetSize(EyesSize.x, EyesSize.y, 0.0f);
    this->lefthand->SetSize(LefthandSize.x, LefthandSize.y, 0.0f);
    this->leftleg->SetSize(LeftlegSize.x, LeftlegSize.y, 0.0f);
    this->righthand->SetSize(RighthandSize.x, RighthandSize.y, 0.0f);
    this->rightleg->SetSize(RightlegSize.x, RightlegSize.y, 0.0f);
    this->idle->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->death2->SetSize(DeathSize.x, DeathSize.y, 0.0f);
    this->walking->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->walking2->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->playercol->SetSize(PlayerColSize.x, PlayerColSize.y, 0.0f);
    this->playercol2->SetSize(PlayerColSize2.x, PlayerColSize2.y, 0.0f);
    this->playercol3->SetSize(PlayerColSize3.x, PlayerColSize3.y, 0.0f);

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

    this->hook[0]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[2]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[3]->SetSize(HookSize01.x, HookSize01.y, 0.0f);


    this->hookdraw[0]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[1]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[3]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
 player->SetPos(1000.0f, -7650.0f, 0.0f);
   // player->SetPos(1900.0f, -1160.0f, 0.0f);

    Vx = 0.0f;
    Vy = 0.0f;
    t = 0;
    t2 = 0;
    jumpstate = 0;
    HookColliderState = -1;


    //// カメラの倍率変更(1.0fがデフォ)
   // this->p_camera->SetZoom(1.0f);

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
void	Stage_11::Update(void)
{
    // 入力更新
    this->p_input->Update();
    this->p_input->GetLeftAnalogStick();

    // リスタート    
    if (this->p_input->Trigger("RETRY"))
    {
        this->p_sceneManager->ChangeScene(Scene::Stage_11);
        return;
    }
    // タイトルに戻る
    if (this->p_input->Trigger("TITLE"))
    {
        this->p_sceneManager->ChangeScene(Scene::TitleScene);
        return;
    }
    // キーコンフィグを確認
    if (this->p_input->Trigger("KEYCONFIG"))
    {
        //KeyConfigの表示切替
        this->keyConfigUI->SetIsActive(!this->keyConfigUI->GetIsActive());
    }

    //----------------------------------------------
    // Creative Mode
    //----------------------------------------------
    if (gamemode == 0)
    {
        if (this->p_input->Press("CHANGEMODE1"))
        {
            gamemode = 1;
        }
        DirectX::XMFLOAT3 playerPos = this->player->GetPos();

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
            this->player->SetPos(playerPos.x - 10.0f, playerPos.y, playerPos.z);
        }
        if (this->p_input->Press("RIGHT"))
        {
            this->player->SetPos(playerPos.x + 10.0f, playerPos.y, playerPos.z);
        }
        if (this->p_input->Press("UP"))
        {
            this->player->SetPos(playerPos.x, playerPos.y + 10.0f, playerPos.z);
        }
        if (this->p_input->Press("DOWN"))
        {
            this->player->SetPos(playerPos.x, playerPos.y - 10.0f, playerPos.z);
        }
    }

    //-----------------------------------
    //フックの移動処理
    if (TurnBackFLG)
    {
        HookPos03.x -= HookMoveSpeed;
        HookCnt++;

        if (HookCnt == 275)
        {
            TurnBackFLG = false;
        }

    }
    else
    {
        HookPos03.x += HookMoveSpeed;
        HookCnt--;

        if (HookCnt == 0)
        {
            TurnBackFLG = true;
        }
    }

    this->hook[2]->SetPos(HookPos03.x, HookPos03.y, 0.0f);

    //-----------------------------------
    //ヨーヨーの動き処理
    //横の動き
    if (YoyoTurnFLG[0])
    {
        GrabboxPos00.x -= YoyoMoveSpeed;
        YoyoCntX[0]++;
        if (YoyoCntX[0] == 400)
        {
            YoyoTurnFLG[0] = false;
        }
    }
    else
    {
        GrabboxPos00.x += YoyoMoveSpeed;
        YoyoCntX[0]--;
        if (YoyoCntX[0] == 0)
        {
            YoyoTurnFLG[0] = true;
        }
    }

    //縦の動き
    if (YoyoTurnFLG[1])
    {
        GrabboxPos00.y -= YoyoMoveSpeed;
        YoyoCntY[0]++;
        if (YoyoCntY[0] == 200)
        {
            YoyoTurnFLG[1] = false;
        }
    }
    else
    {
        GrabboxPos00.y += YoyoMoveSpeed;
        YoyoCntY[0]--;
        if (YoyoCntY[0] == 0)
        {
            YoyoTurnFLG[1] = true;
        }
    }

    //横の動き
    if (YoyoTurnFLG[2])
    {
        GrabboxPos01.x -= YoyoMoveSpeed;
        YoyoCntX[1]++;
        if (YoyoCntX[1] == 400)
        {
            YoyoTurnFLG[2] = false;
        }
    }
    else
    {
        GrabboxPos01.x += YoyoMoveSpeed;
        YoyoCntX[1]--;
        if (YoyoCntX[1] == 0)
        {
            YoyoTurnFLG[2] = true;
        }
    }

    //縦の動き
    if (YoyoTurnFLG[3])
    {
        GrabboxPos01.y -= YoyoMoveSpeed;
        YoyoCntY[1]++;
        if (YoyoCntY[1] == 200)
        {
            YoyoTurnFLG[3] = false;
        }
    }
    else
    {
        GrabboxPos01.y += YoyoMoveSpeed;
        YoyoCntY[1]--;
        if (YoyoCntY[1] == 0)
        {
            YoyoTurnFLG[3] = true;
        }
    }

    YoyoAngle += 2;

    this->pendulum[0]->SetAngle(YoyoAngle);
    this->pendulum[1]->SetAngle(YoyoAngle);


    //-----------------------------------
    if (GrabFlg)
    {
        this->grabbox[0]->Move(grabbox[0]->GetPos());
        this->grabbox[1]->Move(grabbox[1]->GetPos());

        if (ColliderState == 5)
        {
            playerPos = GrabboxPos00;
        }
        else if (ColliderState == 6)
        {
            playerPos = GrabboxPos01;
        }
    }

    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));

    this->playercol->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize.x, PlayerColSize.y, 0.0f));
    this->playercol2->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize2.x, PlayerColSize2.y, 0.0f));
    this->playercol3->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize3.x, PlayerColSize3.y, 0.0f));
    this->slope->SetColliderSize(DirectX::XMFLOAT3(slopeSize.x, slopeSize.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x - 60.0f, GoalSize.y - 50.0f, 0.0f));
    this->pendulum[0]->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize.x, GrabboxSize.y, 0.0f));
    this->pendulum[1]->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize.x, GrabboxSize.y, 0.0f));
    // タイルマップとの衝突判定

    auto& playerColl = this->player->GetCollider();

    auto& col2 = playercol->GetCollider();
    auto& col4 = playercol2->GetCollider();
    auto& col5 = playercol3->GetCollider();
    auto& colgoal = goal->GetCollider();
    auto& pendColl1 = this->pendulum[0]->GetCollider();
    auto& pendColl2 = this->pendulum[1]->GetCollider();
    auto& slopeColl = this->slope->GetCollider();
    std::vector<std::reference_wrapper<BaseCollider>> colhook = {
        hook[0]->GetCollider(),
        hook[1]->GetCollider(),
        hook[2]->GetCollider(),
          hook[3]->GetCollider(),
    };
    PlayerColState = 0;
    PlayerColState3 = 0;
    PlayerColState2 = 0;
    ColliderState = 0;
    HookColliderState = -1;
    auto& tiles = this->p_tileMap->GetTiles();
    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            ColliderState = 1;
        }
        if (col2.CheckCollision(tileColl))
        {
            PlayerColState = 1;//block collider

        }
        if (col4.CheckCollision(tileColl))
        {
            PlayerColState2 = 1;//block collider

        }
        if (col5.CheckCollision(tileColl))
        {
            PlayerColState3 = 1;//block collider

        }
        if (playerColl.CheckCollision(slopeColl))
        {
            ColliderState = 7;
        }
        if (playerColl.CheckCollision(pendColl1))
        {
            YoyoColStage = 1;

            if (this->p_input->Press("GRAB"))
            {
                YoyoStage = 1;
                ColliderState = 8;
            }

        }

        if (playerColl.CheckCollision(pendColl2))
        {
            YoyoColStage = 2;

            if (this->p_input->Press("GRAB"))
            {
                YoyoStage = 1;
                ColliderState = 9;
            }

        }
    }

    for (HookNumber = 0; HookNumber < 4; HookNumber++)
    {
        if (playerColl.CheckCollision(colhook[HookNumber]))
        {
            HookColliderState = HookNumber;//;hook collider
            ColliderState = 2;
        }
    }

    if (playerColl.CheckCollision(colgoal))
    {
        //animetion-> t++ -> scene+1
        ScenechangeState2 = 1;
        //ColliderState = 3;//goal collider

    }


    if (gamemode == 0)//Creative Mode
    {
        if (ColliderState == 1)//if ColliderState == 1 ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 2)
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.5f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }


    ////----------------------------------------------
    //// Player Mode
    ////----------------------------------------------
    if (gamemode == 1)
    {
        DirectX::XMFLOAT3 playerPos = this->player->GetPos();
        movestate = 0;

        PlayerGrabPos.x = 0.0f;
        PlayerGrabPos.y = 0.0f;

        // ========================================
        //          失敗時の処理
        // ========================================
        // 降下したら死ぬ！！
        if (playerPos.y <= -8100.0f && (!this->player->GetIsDead()))
        {
            // ターゲットの解除
            this->p_camera->ClearTarget();

            // タイマー測り始める
            this->failedTimer.Reset();
            this->p_sound->Play(SOUND_LABEL::SE_PLAYR_DEAD);

            // 死んだ
            this->player->SetIsDead(true);
        }

        // 死んでるとき
        if (this->player->GetIsDead() && (!this->isFailed))
        {
            // 叫びSE終わったらガッシャ―ン！！！
            if (this->failedTimer.Elapsed() > 1.0f)
            {
                // 失敗
                this->failedTimer.Reset();
                this->p_sound->Play(SOUND_LABEL::SE_PLAYR_FALLDEAD);
                this->isFailed = true;
            }
        }
        // 失敗中
        if (isFailed)
        {
            // 失敗SE終わったらリトライ
            if (this->failedTimer.Elapsed() > 4.0f)
            {
                this->p_sceneManager->ChangeScene(Scene::Stage_11);
                return;
            }
        }
        // ========================================

        // モードの変更
        if (this->p_input->Press("CHANGEMODE0"))
        {
            gamemode = 0;
        }
        if (ColliderState == 0)
        {
            grabstate = 0;
            this->player->y3 = 0.0f;
            this->playerdraw->y3 = 0.0f;
            PlayerAngle = 0.0f;
            radians = 0.0f;
            a = 0;
            pullstate = 0;

        }

        this->player->SetAngle(PlayerAngle);
        this->playerdraw->SetAngle(PlayerAngle);

        this->goal->SetPos(GoalPos.x, GoalPos.y, playerPos.z);
        this->eyes->SetPos(playerPos.x + EyesPos.x, playerPos.y + EyesPos.y, playerPos.z);
        this->lefthand->SetPos(playerPos.x + LefthandPos.x, playerPos.y + LefthandPos.y, playerPos.z);
        this->leftleg->SetPos(playerPos.x + LeftlegPos.x, playerPos.y + LeftlegPos.y, playerPos.z);
        this->righthand->SetPos(playerPos.x + RighthandPos.x, playerPos.y + RighthandPos.y, playerPos.z);
        this->rightleg->SetPos(playerPos.x + RightlegPos.x, playerPos.y + RightlegPos.y, playerPos.z);

        this->playerdraw->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y, playerPos.z);
        this->death2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->idle->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->playercol->SetPos(playerPos.x + PlayerColPos.x, playerPos.y + PlayerColPos.y, playerPos.z);
        this->playercol2->SetPos(playerPos.x + PlayerColPos2.x, playerPos.y + PlayerColPos2.y, playerPos.z);
        this->playercol3->SetPos(playerPos.x + PlayerColPos3.x, playerPos.y + PlayerColPos3.y, playerPos.z);

        this->hook[0]->SetPos(HookPos01.x, HookPos01.y, playerPos.z);
        this->hook[1]->SetPos(HookPos02.x, HookPos02.y, playerPos.z);
        this->hook[2]->SetPos(HookPos03.x, HookPos03.y, playerPos.z);
        this->hook[3]->SetPos(HookPos04.x, HookPos04.y, playerPos.z);

        this->hookdraw[0]->SetPos(HookPos01.x, HookPos01.y + 80.0f, playerPos.z);
        this->hookdraw[1]->SetPos(HookPos02.x, HookPos02.y + 80.0f, playerPos.z);
        this->hookdraw[2]->SetPos(HookPos03.x, HookPos03.y + 80.0f, playerPos.z);
        this->hookdraw[3]->SetPos(HookPos04.x, HookPos04.y + 80.0f, playerPos.z);
        /*     if (this->p_input->Press("UP"))
             {
                 this->player->SetPos(playerPos.x, playerPos.y + 7.0f, playerPos.z);
             }
             if (this->p_input->Press("DOWN"))
             {
                 this->player->SetPos(playerPos.x, playerPos.y - 7.0f, playerPos.z);
             }*/



        if (u > 3)
        {
            u = 0;
        }
        this->idle->SetTextureNumU(u);
        this->walking->SetTextureNumU(u);
        this->walking2->SetTextureNumU(u);
        this->death2->SetTextureNumU(3);

        if (grabstate == 0)
        {
            if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
            {
                if (ustate == 0)
                {
                    u = 0;
                    ustate = 1;
                }
                if (ColliderState == 0)
                {
                    u = 0;

                }
                Vx4 = 0;
                Vx2 = 0;
                idletime += 1;
                if (u == 0 || u == 2)
                {
                    if (idletime % 225 == 0 && superjumpstate == 0)
                    {
                        u += 1;
                    }
                }
                else if (u == 1 || u == 3)
                {
                    if (idletime % 55 == 0 && superjumpstate == 0)
                    {
                        u += 1;
                    }
                }
            }
            else if (p_input->GetLeftAnalogStick().x * 10.0f < -2.0f && superjumpstate == 0)
            {
                Vx4 = -7;
                ustate = 0;
                Vx2 = -1;
                idletime += 1;
                if (idletime % 5 == 0 && jumpstate != 1 && superjumpstate == 0)
                {
                    u += 1;
                }
                if (ColliderState == 0)
                {
                    u = 0;

                }

                if (Vx2 < 0 && PlayerColState3 == 1 && grabstate == 0)
                {
                    movestate = 1;

                }
                else
                {
                    movestate = 0;
                }
                if (movestate != 1)
                {
                    this->player->SetPos(playerPos.x + Vx4, playerPos.y, playerPos.z);
                }


            }
            if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
            {
                if (ustate == 0)
                {
                    u = 0;
                    ustate = 1;
                }
                if (ColliderState == 0)
                {
                    u = 0;

                }
                Vx4 = 0;
                Vx2 = 0;
                idletime += 1;
                if (u == 0 || u == 2)
                {
                    if (idletime % 225 == 0 && superjumpstate == 0)
                    {
                        u += 1;
                    }
                }
                else if (u == 1 || u == 3)
                {
                    if (idletime % 55 == 0 && superjumpstate == 0)
                    {
                        u += 1;
                    }
                }
            }
            else if (p_input->GetLeftAnalogStick().x * 10.0f > 2.0f && superjumpstate == 0)
            {
                Vx4 = 7;
                ustate = 0;
                Vx2 = 1;
                idletime += 1;
                if (idletime % 5 == 0 && jumpstate != 1 && superjumpstate == 0)
                {
                    u += 1;
                }
                if (ColliderState == 0)
                {
                    u = 0;

                }
                if (Vx2 > 0 && PlayerColState == 1 && grabstate == 0)
                {
                    movestate = 2;

                }
                else
                {
                    movestate = 0;
                }

                if (movestate != 2)
                {
                    this->player->SetPos(playerPos.x + Vx4, playerPos.y, playerPos.z);
                }

            }
        }




        if (grabstate == 1)
        {
            a = 90.0f;
            z = std::sqrt(p_input->GetRightAnalogStick().x * p_input->GetRightAnalogStick().x + p_input->GetRightAnalogStick().y * p_input->GetRightAnalogStick().y);

            if (p_input->GetRightAnalogStick().x != 0)
            {
                radians = std::atan2(p_input->GetRightAnalogStick().y, p_input->GetRightAnalogStick().x);
            }
            //if (p_input->GetRightAnalogStick().x * 10.0f <= 2.0f && p_input->GetRightAnalogStick().x * 10.0f >= -2.0f)
            //{
            //    //CameraPos.x += 0.0f;
            //}
            //else
            //{
            //    
            //}






            if (p_input->GetRightAnalogStick().y * 10.0f <= 1.2f && p_input->GetRightAnalogStick().y * 10.0f >= -1.2f && p_input->GetRightAnalogStick().x * 10.0f <= 1.2f && p_input->GetRightAnalogStick().x * 10.0f >= -1.2f)
            {
                //powerstate = 0;//CameraPos.y += 0.0f;
                this->player->y3 = 0.0f;
                this->playerdraw->y3 = 0.0f;
                PlayerAngle = 0.0f;
                PlayerGrabPos.x = 0;
                PlayerGrabPos.y = 25.0f;
                eyesy = 90.0f;
                eyesx = 0.0f;
                lefthandx = -62.0f;
                lefthandy = 14.0f;
                leftlegx = -39.0f;
                leftlegy = -29.0f;
                righthandx = 66.0f;
                righthandy = 15.0f;
                rightlegx = 50.0f;
                rightlegy = -30.0f;
            }
            else
            {
                PlayerGrabPos.x = -35.0f * p_input->GetRightAnalogStick().x / z;
                PlayerGrabPos.y = -35.0f * p_input->GetRightAnalogStick().y / z - 5.0f;











                if (player->y3 != z * -2.8f)
                {
                    this->player->y3 += (z * -2.8f - player->y3) / 20;
                    this->playerdraw->y3 += (z * -2.8f - playerdraw->y3) / 20;
                }
                PlayerAngle = radians * 180.0f / 3.1415926 + a;


                if (PlayerAngle >= 90 && PlayerAngle < 180.0f)
                {
                    eyesy = 90.0f - this->player->y3 * 80 * std::pow(sin(radians), 1.9f);
                    eyesx = 0.0f - this->player->y3 * 48 * std::pow(std::abs(cos(radians)), 0.8f);//4角度

                    lefthandy = 14.0f - this->player->y3 * 65 * std::pow(std::abs(sin(radians)), 3.50f);
                    lefthandx = -62.0f - this->player->y3 * 40 * std::pow(std::abs(cos(radians)), 0.67f) - this->player->y3 * 30 * -std::pow(std::abs(cos(radians)), 2.0f);

                    righthandy = 15.0f - this->player->y3 * 68 * std::pow(std::abs(sin(radians)), 0.65f);
                    righthandx = 66.0f - this->player->y3 * 87 * std::pow(std::abs(cos(radians)), 1.40f);

                    leftlegy = -34.0f - this->player->y3 * 20 * std::pow(std::abs(sin(radians)), 0.65f) - this->player->y3 * 6 * -std::pow(std::abs(sin(radians)), 3.0f);
                    leftlegx = -29.0f - this->player->y3 * 20 * std::pow(std::abs(cos(radians)), 3.7f);

                    rightlegy = -33.0f - this->player->y3 * 35 * std::pow(std::abs(sin(radians)), 0.55f) - this->player->y3 * 20 * -std::pow(std::abs(sin(radians)), 4.0f);
                    rightlegx = 44.0f - this->player->y3 * 66 * std::pow(std::abs(cos(radians)), 5.5f) - this->player->y3 * 7 * std::pow(std::abs(cos(radians)), 0.6f);
                    //rightlegy = -36.0f - this->player->y3 * 25 * std::pow(std::abs(sin(radians)), 0.65f) - this->player->y3 * 11 * -std::pow(std::abs(sin(radians)), 3.0f);

                    /*leftlegx = -39.0f - this->player->y3 * 80 * std::pow(sin(radians), 2.0f);
                    leftlegy = -29.0f - this->player->y3 * 48 * std::pow(std::abs(cos(radians)), 0.8f);
                    righthandx = 66.0f - this->player->y3 * 80 * std::pow(sin(radians), 2.0f);
                    righthandy = 15.0f - this->player->y3 * 48 * std::pow(std::abs(cos(radians)), 0.8f);
                    rightlegx = 50.0f - this->player->y3 * 80 * std::pow(sin(radians), 2.0f);
                    rightlegy = -30.0f - this->player->y3 * 48 * std::pow(std::abs(cos(radians)), 0.8f);*/
                    //*std::abs(sin(PlayerAngle));

                }
                else if (PlayerAngle >= 180 && PlayerAngle < 270.0f)
                {
                    eyesy = 90.0f - this->player->y3 * 80 * std::pow(sin(radians), 2.0f);
                    eyesx = 0.0f - this->player->y3 * 48 * -std::pow(std::abs(cos(radians)), 0.8f);//8角度

                    lefthandy = 14.0f - this->player->y3 * 63 * std::pow(std::abs(sin(radians)), 0.65f);
                    lefthandx = -62.0f - this->player->y3 * 88 * -std::pow(std::abs(cos(radians)), 1.25f);

                    righthandy = 15.0f - this->player->y3 * 60 * std::pow(std::abs(sin(radians)), 3.50f);
                    righthandx = 66.0f - this->player->y3 * 44.5f * -std::pow(std::abs(cos(radians)), 0.75f) - this->player->y3 * 30 * +std::pow(std::abs(cos(radians)), 2.0f);

                    leftlegy = -39.0f - this->player->y3 * 35 * std::pow(std::abs(sin(radians)), 0.45f) - this->player->y3 * 20 * -std::pow(std::abs(sin(radians)), 4.0f);
                    leftlegx = -29.0f - this->player->y3 * 71 * -std::pow(std::abs(cos(radians)), 3.7f);

                    rightlegy = -35.0f - this->player->y3 * 20 * std::pow(std::abs(sin(radians)), 0.65f) - this->player->y3 * 6 * -std::pow(std::abs(sin(radians)), 3.0f);
                    rightlegx = 44.0f - this->player->y3 * 20 * -std::pow(std::abs(cos(radians)), 3.7f);
                    //*std::abs(sin(PlayerAngle));

                }
                else if (PlayerAngle >= -90 && PlayerAngle < 0.0f)
                {
                    eyesy = 90.0f - this->player->y3 * 25 * -std::pow(std::abs(sin(radians)), 0.8f) - this->player->y3 * 10 * std::pow(std::abs(sin(radians)), 1.5f);
                    eyesx = 0.0f - this->player->y3 * 45 * -std::pow(std::abs(cos(radians)), 3.8f);//8角度

                    lefthandy = 14.0f - this->player->y3 * 24 * -std::pow(std::abs(sin(radians)), 0.17f) - this->player->y3 * 5 * -std::pow(std::abs(sin(radians)), 0.9f);
                    lefthandx = -65.0f - this->player->y3 * 90 * -std::pow(std::abs(cos(radians)), 2.4f) - this->player->y3 * 12 * std::pow(std::abs(cos(radians)), 1.10f) - this->player->y3 * 3 * -std::pow(std::abs(cos(radians)), 0.2f);


                    righthandy = 15.0f - this->player->y3 * 30 * -std::pow(std::abs(sin(radians)), 3.50f);
                    righthandx = 66.0f - this->player->y3 * 26 * -std::pow(std::abs(cos(radians)), 0.75f) - this->player->y3 * 12 * std::pow(std::abs(cos(radians)), 2.0f);

                    leftlegy = -39.0f - this->player->y3 * 95 * -std::pow(std::abs(sin(radians)), 1.4f) - this->player->y3 * 20 * std::pow(std::abs(sin(radians)), 4.0f) - this->player->y3 * 4 * -std::pow(std::abs(sin(radians)), 7.0f);
                    leftlegx = -26.0f - this->player->y3 * 70 * -std::pow(std::abs(cos(radians)), 0.68f);


                    rightlegy = -35.0f - this->player->y3 * 100 * -std::pow(std::abs(sin(radians)), 10.8f) - this->player->y3 * 36 * std::pow(std::abs(sin(radians)), 8.7f) - this->player->y3 * 20 * -std::pow(std::abs(sin(radians)), 1.0f) - this->player->y3 * 2 * std::pow(std::abs(sin(radians)), 0.1f);
                    rightlegx = 44.0f - this->player->y3 * 19 * -std::pow(std::abs(cos(radians)), 0.5f) - this->player->y3 * 2 * -std::pow(std::abs(cos(radians)), 0.1f);
                    /*rightlegy = -35.0f - this->player->y3 * 87 * -std::pow(std::abs(sin(radians)), 3.1f) - this->player->y3 * 21 * std::pow(std::abs(sin(radians)), 2.5f);
                    rightlegx = 44.0f - this->player->y3 * 19 * -std::pow(std::abs(cos(radians)), 0.5f) - this->player->y3 * 2 * std::pow(std::abs(cos(radians)), 0.01f);*/
                    /* lefthandy = 14.0f - this->player->y3 * 60 * -std::pow(std::abs(sin(radians)), 1.0);
                     lefthandx = -62.0f - this->player->y3 * 88 *-std::pow(std::abs(cos(radians)), 1.25f);*/
                     //*std::abs(sin(PlayerAngle));

                }
                else if (PlayerAngle >= 0 && PlayerAngle < 90.0f)
                {
                    eyesy = 90.0f - this->player->y3 * 25 * -std::pow(std::abs(sin(radians)), 0.8f) - this->player->y3 * 10 * std::pow(std::abs(sin(radians)), 1.5f);
                    eyesx = 0.0f - this->player->y3 * 45 * std::pow(std::abs(cos(radians)), 3.8f);//8角度

                    lefthandy = 11.0f - this->player->y3 * 25 * -std::pow(std::abs(sin(radians)), 3.50f);
                    lefthandx = -62.0f - this->player->y3 * 30 * std::pow(std::abs(cos(radians)), 0.75f) - this->player->y3 * 20 * -std::pow(std::abs(cos(radians)), 2.0f);

                    /* righthandy = 15.0f - this->player->y3 * 18 * -std::pow(std::abs(sin(radians)), 0.48f);
                     righthandx = 66.0f - this->player->y3 * 87 * std::pow(std::abs(cos(radians)), 1.54f);*/

                    righthandy = 15.0f - this->player->y3 * 24 * -std::pow(std::abs(sin(radians)), 0.17f) - this->player->y3 * 4 * -std::pow(std::abs(sin(radians)), 0.7f);
                    righthandx = 66.0f - this->player->y3 * 90 * std::pow(std::abs(cos(radians)), 2.60f) - this->player->y3 * 10 * -std::pow(std::abs(cos(radians)), 1.30f) - this->player->y3 * 3 * std::pow(std::abs(cos(radians)), 0.2f);
                    // leftlegy = -39.0f - this->player->y3 * 25 * -std::pow(std::abs(sin(radians)), 0.65f) - this->player->y3 * 11 * std::pow(std::abs(sin(radians)), 3.0f);
                     //leftlegx = -29.0f - this->player->y3 * 28 * std::pow(std::abs(cos(radians)), 3.7f);

                    leftlegy = -30.0f - this->player->y3 * 100 * -std::pow(std::abs(sin(radians)), 10.8f) - this->player->y3 * 36 * std::pow(std::abs(sin(radians)), 8.7f) - this->player->y3 * 20 * -std::pow(std::abs(sin(radians)), 1.0f);
                    leftlegx = -27.0f - this->player->y3 * 19 * std::pow(std::abs(cos(radians)), 0.5f) - this->player->y3 * 2 * -std::pow(std::abs(cos(radians)), 0.01f);

                    rightlegy = -35.0f - this->player->y3 * 95 * -std::pow(std::abs(sin(radians)), 1.3f) - this->player->y3 * 20 * std::pow(std::abs(sin(radians)), 4.0f) - this->player->y3 * 4 * -std::pow(std::abs(sin(radians)), 7.0f);
                    rightlegx = 44.0f - this->player->y3 * 70 * std::pow(std::abs(cos(radians)), 0.75f) - this->player->y3 * 2 * -std::pow(std::abs(cos(radians)), 0.05f);
                    /*rightlegy = -35.0f - this->player->y3 * 95 * -std::pow(std::abs(sin(radians)), 1.4f) - this->player->y3 * 20 * std::pow(std::abs(sin(radians)), 4.0f);
                    rightlegx = 44.0f - this->player->y3 * 70 * std::pow(std::abs(cos(radians)), 0.58f);*/

                    //lefthandy = 14.0f - this->player->y3 * 53 * -std::pow(std::abs(sin(radians)), 0.48f);
                    //lefthandx = -62.0f - this->player->y3 * 88 * std::pow(std::abs(cos(radians)), 1.54f);
                    //*std::abs(sin(PlayerAngle));

                }

                /*else if (player->y3 != z * -2.5f && p_input->GetRightAnalogStick().y > 0)
                {
                    this->player->y3 += (z * -2.5f - player->y3) / 50;
                }*/
            }
            EyesPos.x = eyesx;
            EyesPos.y = eyesy;
            LefthandPos.x = lefthandx;
            LefthandPos.y = lefthandy;
            LeftlegPos.x = leftlegx;
            LeftlegPos.y = leftlegy;
            RighthandPos.x = righthandx;
            RighthandPos.y = righthandy;
            RightlegPos.x = rightlegx;
            RightlegPos.y = rightlegy;

            /*  if (p_input->GetRightAnalogStick().y >= 0)
              {*/
              //p_input->GetRightAnalogStick().x / z;
               //}
            if (player->y3 <= -1.0f)
            {

                pullstate = 2;
            }
            else
            {
                pullstate = 0;

            }
            if (player->y3 <= -2.3f)
            {

                this->p_input->SetVibration(2, 5);
                this->p_sound->Play(SOUND_LABEL::SE_PLAYR_VIVRATION);

            }
            if (player->y3 <= -2.5f)
            {
                t2 += 1;


            }
            else
            {
                if (t2 > 0)
                {
                    t2 -= 1;
                }
                else
                {
                    t2 = 0;
                }
            }

            if (t2 >= 40)
            {

                deathstate = 1;
                this->p_sound->Play(SOUND_LABEL::SE_PLAYR_DEAD);

            }
            if (deathstate == 1)
            {
                t5 += 1;

            }
            if (t5 >= 20)
            {


                ScenechangeState = true;
                t5 = 0;
            }
        }

        if (ColliderState == 0)
        {
            // YoyoStage = 0;
            grabstate = 0;
            this->player->y3 = 0.0f;
            this->playerdraw->y3 = 0.0f;
            PlayerAngle = 0.0f;
            radians = 0.0f;
            a = 0;
            eyesy = 90.0f;
            eyesx = 0.0f;
            lefthandx = -62.0f;
            lefthandy = 14.0f;
            leftlegx = -39.0f;
            leftlegy = -29.0f;
            righthandx = 66.0f;
            righthandy = 15.0f;
            rightlegx = 50.0f;
            rightlegy = -30.0f;
            EyesPos.x = eyesx;
            EyesPos.y = eyesy;
            LefthandPos.x = lefthandx;
            LefthandPos.y = lefthandy;
            LeftlegPos.x = leftlegx;
            LeftlegPos.y = leftlegy;
            RighthandPos.x = righthandx;
            RighthandPos.y = righthandy;
            RightlegPos.x = rightlegx;
            RightlegPos.y = rightlegy;
            // pullstate = 0;
        }















        if (this->p_input->Press("SPACE") && t == 0 && grabstate == 0 && jumpkeystate == 0)
        {
            this->p_sound->Play(SOUND_LABEL::SE_PLAYR_JUMP);
            if (p_input->GetLeftAnalogStick().x * 10.0f > 2.0f)
            {
                PlayerColSize = { 130.0f,110.0f };
            }
            Vy = 20.0f;
            jumpkeystate = 1;
            jumpstate = 1;
        }

        if (this->p_input->Press("SUPERJUMP") && t == 0 && grabstate == 1 && deathstate != 1)
        {
            this->p_sound->Play(SOUND_LABEL::SE_PLAYR_LEAP);
            pullstate = 0;
            Vypower = std::pow(std::abs(p_input->GetRightAnalogStick().y * 3000.0f), 0.3f);


            Vxpower = std::pow(std::abs(p_input->GetRightAnalogStick().x * 3000.0f), 0.3f);

            // Vy = Vypower * 2.3f;

            if (p_input->GetRightAnalogStick().y > 0)
            {
                Vy = Vypower * -0.55f;
            }
            else if (p_input->GetRightAnalogStick().y < 0)
            {
                if (HookColliderState != 2)
                {
                    Vy = Vypower * 3.7f;
                }
                else if (HookColliderState == 2)
                {
                    Vy = Vypower * 4.3f;

                    PlayerColSize2 = { 120.0f,90.0f };
                    PlayerColSize = { 80.0f,110.0f };
                    PlayerColSize3 = { 80.0f,110.0f };
                }
            }
            else if (p_input->GetRightAnalogStick().y == 0)
            {
                Vy = 0;
            }


            if (p_input->GetRightAnalogStick().x > 0)
            {
                if (HookColliderState != 2)
                {
                    Vx = Vxpower * -0.8f;

                }
                else if (HookColliderState == 2)
                {
                    Vx = Vxpower * -0.25f;
                }

            }
            else if (p_input->GetRightAnalogStick().x < 0)
            {
                if (HookColliderState != 2)
                {
                    PlayerColSize = { 120.0f,130.0f };
                    Vx = Vxpower * 0.9f;
                }
                else if (HookColliderState == 2)
                {
                    Vx = Vxpower * 0.1f;
                }
            }
            else if (p_input->GetRightAnalogStick().x == 0)
            {
                Vx = 0;
            }
            jumpstate = 1;
            superjumpstate = 1;
        }


        if (jumpstate == 1)
        {
            t += 0.5f;
        }

        if (t > 0)
        {

            Vdown = 0.035f * g * t * t;
            /*  if (Vdown >= 25.0f)
              {
                  Vdown = 25.0f;
              }*/

            if (superjumpstate == 2)
            {
                if (Vdelta > 0)
                {
                    Vy = Vy / 1.05f;
                }
            }
            Vdown2 = Vy * (t + 0.5) - 0.035f * g * (t + 0.5) * (t + 0.5);

            Vdelta = Vdown2 - (Vy * t - Vdown);

            if (Vdelta <= -7.0f)
            {
                PlayerSize = { 110.0f,110.0f - Vdelta * 1.1f };

            }

            if (Vdelta <= -14.0f)
            {
                Vdelta = -14.0f;


            }









            if (PlayerColState == 1 && grabstate == 0)
            {
                Vx4 = 0;
                PlayerColSize = { 110.0f,110.0f };
            }
            else if (PlayerColState3 == 1 && grabstate == 0)
            {
                Vx4 = 0;

            }










            this->player->SetPos(playerPos.x + Vx4, playerPos.y + Vdelta, playerPos.z);

            if (Vx > 0)
            {


                if (PlayerColState == 1 && grabstate == 0)
                {
                    movestate = 2;
                    Vx = 0;


                    superjumpstate = 2;
                }
                else
                {
                    movestate = 0;
                }
                if (movestate != 2)
                {
                    this->player->SetPos(playerPos.x + Vx, playerPos.y + Vdelta, playerPos.z);

                }
            }

            if (Vx < 0)
            {


                if (PlayerColState3 == 1 && grabstate == 0)
                {
                    movestate = 1;
                    Vx = 0;

                    superjumpstate = 2;
                }
                else
                {
                    movestate = 0;
                }
                if (movestate != 1)
                {
                    this->player->SetPos(playerPos.x + Vx, playerPos.y + Vdelta, playerPos.z);
                }
            }

            if (PlayerColState2 == 1)
            {
                if (Vdelta > 0)
                {

                    Vy = 0;
                    PlayerColSize2 = { 120.0f,40.0f };
                    PlayerColSize = { 110.0f,110.0f };
                    PlayerColSize3 = { 110.0f,110.0f };
                }

            }

        }
        else if (t <= 0)
        {
            Vdelta = 0;
            Vx = 0;
        }
        if (t <= 0)
        {
            superjumpstate = 0;
        }
        if (HookColliderState == 3)
        {
            PlayerColSize2 = { 120.0f,40.0f };
            PlayerColSize = { 110.0f,110.0f };
            PlayerColSize3 = { 110.0f,110.0f };
        }

        if (this->p_input->Press("GRAB") && YoyoStage == 1)
        {

            ColliderState = 1;
            //jumpstate = 0;
            ////grabstate = 1;
            //t = 0;
            //Vdown = 0;
            //Vy = 0;
            if (YoyoColStage == 1)
            {
                this->player->SetPos(GrabboxPos00.x, GrabboxPos00.y, playerPos.z);
            }
            else if (YoyoColStage == 2)
            {
                this->player->SetPos(GrabboxPos01.x, GrabboxPos01.y, playerPos.z);
            }
        }
        else if (this->p_input->Release("GRAB") && YoyoColStage == 1 || this->p_input->Release("GRAB") && YoyoColStage == 2)
        {
            ColliderState = 0;
            //  YoyoVystate = 1;
            YoyoStage = 0;
            //  jumpstate = 1;
             // Vy = 0;
             // t = 0;

            Vy = 32.0f;
            jumpstate = 1;
        }

        if (jumpstate == 1 && ColliderState == 1)
        {
            YoyoStage = 0;
            jumpstate = 0;
            t = 0;
            Vdown = 0;
            Vy = 0;
            jumpkeystate = 0;
            PlayerColSize2 = { 120.0f,40.0f };
            PlayerColSize = { 110.0f,110.0f };
            PlayerColSize3 = { 110.0f,110.0f };
            PlayerSize = { 110.0f,110.0f };
        }

        /* if (YoyoVystate == 1)
         {
             YoyoVyt += 1;
             movestate = 0;
          Vy = 30;
           jumpstate = 1;

           if (YoyoVyt > 3)
           {
               YoyoStage = 0;
               YoyoVystate = 0;
               YoyoVyt = 0;
               ColliderState = 0;
           }
         }*/
        if (ColliderState == 7)
        {
            t = 0.0f;
            SlopeVx = -7.0f;
            SlopeVy = -7.0f;
            this->player->SetPos(playerPos.x + SlopeVx, playerPos.y + SlopeVy, playerPos.z);
        }
        else
        {
            SlopeVx += 0.0f;
            SlopeVy += 0.0f;
        }
        if (ColliderState != 1)
        {
            t += 0.5f;
        }
        else if (ColliderState == 1)
        {
            t = 0.0f;
        }

        if (superjumpstate == 1 && ColliderState == 0)
        {
            superjumpstate = 4;
        }


        if (HookColliderState != -1 && superjumpstate != 1 && grabstate != 2)
        {


            jumpstate = 0;
            grabstate = 1;
            t = 0;
            Vdown = 0;
            Vy = 0;
            this->player->SetPos(hook[HookColliderState]->GetPos().x, hook[HookColliderState]->GetPos().y, playerPos.z);
            HookColliderState = -1;

        }

        if (ScenechangeState == 1)
        {
            this->p_sceneManager->ChangeScene(Scene::Stage_11);
            return;

        }


        if (ScenechangeState2 == 1)
        {
            this->p_sound->Play(SOUND_LABEL::SE_GOAL);
            t6 += 1;

        }

        if (t6 >= 10)
        {
            this->p_sceneManager->ChangeScene(Scene::Stage_12);
            return;
        }

    }





    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->background->Update();
    this->p_tileMap->Update();
    this->keyConfigUI->Update();

    this->rail->Update();

    this->slope->Update();

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->grabbox[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->pendulum[n]->Update();
    }

    this->goal->Update();
    this->playercol->Update();
    this->playercol2->Update();
    this->playercol3->Update();

    this->idle->Update();
    this->death2->Update();
    this->walking->Update();
    this->walking2->Update();
    this->player->Update();
    this->playerdraw->Update();
    this->lefthand->Update();
    this->leftleg->Update();
    this->righthand->Update();
    this->rightleg->Update();
    this->eyes->Update();

    this->hook[0]->Update();
    this->hook[1]->Update();
    this->hook[2]->Update();
    this->hook[3]->Update();
    this->hookdraw[0]->Update();
    this->hookdraw[1]->Update();
    this->hookdraw[2]->Update();
    this->hookdraw[3]->Update();
    //this->playercol->Draw();
//this->playercol2->Draw();
//this->playercol3->Draw();

    // カメラの更新
    this->p_camera->Update();
    //updateの後にsetposしないと動きがおかしくなる
    this->pendulum[0]->SetPos(GrabboxPos00.x, GrabboxPos00.y, 0.0f);
    this->pendulum[1]->SetPos(GrabboxPos01.x, GrabboxPos01.y, 0.0f);
    this->grabbox[0]->SetPos(GrabboxPos00.x, GrabboxPos00.y, 0.0f);
    this->grabbox[1]->SetPos(GrabboxPos01.x, GrabboxPos01.y, 0.0f);
}

/**	@brief 	シーン全体の描画
*/
void	Stage_11::Draw(void)
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
    this->goal->Draw();
    this->p_tileMap->Draw();

    this->slope->Draw();
    this->rail->Draw();

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->pendulum[n]->Draw();
    }
    /* this->player->Draw();
     this->playercol->Draw();
    this->playercol2->Draw();
    this->playercol3->Draw();*/

    //this->hook[0]->Draw();
    //this->hook[1]->Draw();
    //this->hook[2]->Draw();

    this->hookdraw[0]->Draw();
    this->hookdraw[1]->Draw();
    this->hookdraw[2]->Draw();
    this->hookdraw[3]->Draw();
    if (p_input->GetLeftAnalogStick().x * 10.0f < -2.0f && superjumpstate == 0 && grabstate == 0 && jumpstate == 0)
    {
        if (YoyoStage != 1)
        {
            this->walking2->Draw();
        }
        else if (this->p_input->Press("GRAB") && YoyoStage == 1)
        {
            this->playerdraw->Draw();
            this->lefthand->Draw();
            this->leftleg->Draw();
            this->righthand->Draw();
            this->rightleg->Draw();
            this->eyes->Draw();
        }
    }
    else if (p_input->GetLeftAnalogStick().x * 10.0f >= 2.0f && superjumpstate == 0 && grabstate == 0 && jumpstate == 0)
    {
        if (YoyoStage != 1)
        {
            this->walking->Draw();
        }
        else if (this->p_input->Press("GRAB") && YoyoStage == 1)
        {
            this->playerdraw->Draw();
            this->lefthand->Draw();
            this->leftleg->Draw();
            this->righthand->Draw();
            this->rightleg->Draw();
            this->eyes->Draw();
        }
    }
    else if (p_input->GetLeftAnalogStick().x * 10.0f < 0 && superjumpstate == 0 && grabstate == 0 && jumpstate == 1)
    {
        this->walking2->Draw();
    }
    else if (p_input->GetLeftAnalogStick().x * 10.0f > 0 && superjumpstate == 0 && grabstate == 0 && jumpstate == 1)
    {
        this->walking->Draw();
    }
    else if (superjumpstate != 0 && Vx >= 0 && grabstate == 0 && jumpstate != 0)
    {
        this->walking->Draw();
    }
    else if (superjumpstate != 0 && Vx < 0 && grabstate == 0 && jumpstate != 0)
    {
        this->walking2->Draw();
    }
    else if (grabstate == 0 && jumpstate == 0 && YoyoStage != 1)
    {

        this->idle->Draw();
    }
    else if (grabstate == 0 && jumpstate == 0 && YoyoStage == 1)
    {

        this->playerdraw->Draw();
        this->lefthand->Draw();
        this->leftleg->Draw();
        this->righthand->Draw();
        this->rightleg->Draw();
        this->eyes->Draw();
    }
    if (grabstate != 0 && deathstate == 0)
    {
        this->playerdraw->Draw();
        this->lefthand->Draw();
        this->leftleg->Draw();
        this->righthand->Draw();
        this->rightleg->Draw();
        this->eyes->Draw();
    }
    else if (deathstate == 1)
    {
        this->death2->Draw();
    }

    // キーコンフィグUI
   //this->keyConfigUI->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_11::Finalize(void)
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
    SAFE_DELETE(this->player);
    SAFE_DELETE(this->keyConfigUI);
    SAFE_DELETE(this->rail);//Delete Object
    SAFE_DELETE(this->slope);//Delete Object
    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->grabbox[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->pendulum[n]);
    }

    //テクスチャ
    for (int i = 0; i < 2; i++)
    {
        SAFE_RELEASE(this->textureList[i]);
    }
}
