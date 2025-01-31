/**	@file	Stage_4.cpp
*	@brief 	Stage_4
*	@date 2024/12/19
*/
#include"Stage_4.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
#include <memory> 
/**	@brief 	コンストラクタ
*/
Stage_4::Stage_4()
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
Stage_4::~Stage_4()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_4::Initialize(void)
{
    // BGM
    this->p_sound->Play(SOUND_LABEL::BGM_GAME);

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }

    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage4.csv");
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
    this->player->Init(L"Asset/block.png");
    this->player->SetPos(0.0f, -100.0f, 100.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

    //キーコンフィグUI
    if (!this->keyConfigUI) { this->keyConfigUI = new Background(this->p_camera); }
    this->keyConfigUI->Init(L"Asset/UI/KeyConfig.png");
    this->keyConfigUI->SetPos(0.0f, 0.0f, 0.0f);
    this->keyConfigUI->SetSize(1920.0f * 0.7f, 1080.0f * 0.7f, 0.0f);
    this->keyConfigUI->SetIsActive(false);

    for (m = 0; m < 6; m++)
    {
        if (!this->hook[m]) {
            this->hook[m] = std::make_shared<Object>(this->p_camera);
        }
        if (!this->hookdraw[m]) {
            this->hookdraw[m] = std::make_shared<Object>(this->p_camera);
        }
    }
    for (m = 0; m < 3; m++)
    {
        if (!this->rail[m]) { this->rail[m] = std::make_shared<Object>(this->p_camera); }
    }
    for (m = 0; m < 2; m++)
    {
        if (!this->PushObject[m]) { this->PushObject[m] = std::make_shared<Object>(this->p_camera); }
    }
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

    for (m = 0; m < 6; m++)
    {
        this->hook[m]->SetTexture(this->textureList[1]);
        this->hookdraw[m]->SetTexture(this->textureList[1]);
        this->hook[m]->Init();
        this->hookdraw[m]->Init();
    }
    for (m = 0; m < 3; m++)
    {
        this->rail[m]->Init(L"Asset/Gimmick/rail_02.png");
    }
    for (m = 0; m < 2; m++)
    {
        this->PushObject[m]->Init(L"Asset/Gimmick/pencase.png");
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
    this->death2->SetSize(DeathSize.x, DeathSize.y, 0.0f);
    this->playerdraw->SetSize(PlayerDrawSize.x, PlayerDrawSize.y, 0.0f);
    this->eyes->SetSize(EyesSize.x, EyesSize.y, 0.0f);
    this->lefthand->SetSize(LefthandSize.x, LefthandSize.y, 0.0f);
    this->leftleg->SetSize(LeftlegSize.x, LeftlegSize.y, 0.0f);
    this->righthand->SetSize(RighthandSize.x, RighthandSize.y, 0.0f);
    this->rightleg->SetSize(RightlegSize.x, RightlegSize.y, 0.0f);
    this->idle->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->walking->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->walking2->SetSize(IdleSize.x, IdleSize.y, 0.0f);
    this->playercol->SetSize(PlayerColSize.x, PlayerColSize.y, 0.0f);
    this->playercol2->SetSize(PlayerColSize2.x, PlayerColSize2.y, 0.0f);
    this->playercol3->SetSize(PlayerColSize3.x, PlayerColSize3.y, 0.0f);

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);
    this->rail[0]->SetSize(RailSize00.x, RailSize00.y, 0.0f);
    this->rail[0]->SetPos(RailPos00.x, RailPos00.y, 0.0f);

    this->rail[1]->SetSize(RailSize01.x, RailSize01.y, 0.0f);
    this->rail[1]->SetPos(RailPos01.x, RailPos01.y, 0.0f);

    this->rail[2]->SetPos(RailPos02.x, RailPos02.y, 0.0f);
    this->rail[2]->SetSize(RailSize02.x, RailSize02.y, 0.0f);
    this->rail[2]->SetAngle(90.0f);
    for (n = 0; n < 6; n++)
    {

        this->hook[n]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    }
    this->PushObject[0]->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    this->PushObject[0]->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);
    this->PushObject[1]->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    this->PushObject[1]->SetPos(PushObjectPos01.x, PushObjectPos01.y, 0.0f);
    this->PushObject[0]->SetIsActive(false);
    this->PushObject[1]->SetIsActive(false);

    this->hookdraw[0]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[1]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[3]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[4]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[5]->SetSize(HookSize02.x, HookSize02.y, 0.0f);

    player->SetPos(2500.0f, -4200.0f, 0.0f);
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
void	Stage_4::Update(void)
{
    // 入力更新
    this->p_input->Update();
    this->p_input->GetLeftAnalogStick();

    //// 画面揺らせる
    //this->p_camera->Shake(10.0f);

     // リスタート    
    if (this->p_input->Trigger("RETRY"))
    {
        this->p_sceneManager->ChangeScene(Scene::Stage_4);
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
        if (this->p_input->Trigger("SPACE"))
        {
            std::cout << "x:" << playerPos.x << " y:" << playerPos.y << std::endl;
        }

    }
    //-----------------------------------
    //フックの移動処理
    if (MoveHookFLG[0])//地上右フックの移動処理
    {
        if (TurnBackFLG[0])
        {
            HookPos00.y += HookMoveSpeed;
            HookCnt[0]++;

            if (HookCnt[0] == 500)
            {
                TurnBackFLG[0] = false;
            }

        }
        else
        {
            HookPos00.y -= HookMoveSpeed;
            HookCnt[0]--;

            if (HookCnt[0] == 0)
            {
                TurnBackFLG[0] = true;
            }
        }
        this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);
    }

    if (MoveHookFLG[1])//空中右フックの移動処理
    {
        if (TurnBackFLG[1])
        {
            HookPos01.y += HookMoveSpeed;
            HookCnt[1]++;

            if (HookCnt[1] == 400)
            {
                TurnBackFLG[1] = false;
            }
        }
        else
        {
            HookPos01.y -= HookMoveSpeed;
            HookCnt[1]--;

            if (HookCnt[1] == 0)
            {
                TurnBackFLG[1] = true;
            }
        }
        this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);
    }

    if (MoveHookFLG[2])//空中左フック(上)の移動処理
    {
        if (TurnBackFLG[2])
        {
            HookPos04.x += HookMoveSpeed;
            HookCnt[2]++;

            if (HookCnt[2] == 300)
            {
                TurnBackFLG[2] = false;
            }
        }
        else
        {
            HookPos04.x -= HookMoveSpeed;
            HookCnt[2]--;

            if (HookCnt[2] == 0)
            {
                TurnBackFLG[2] = true;
            }
        }
        this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);
    }


    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));

    this->playercol->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize.x, PlayerColSize.y, 0.0f));
    this->playercol2->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize2.x, PlayerColSize2.y, 0.0f));
    this->playercol3->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize3.x, PlayerColSize3.y, 0.0f));


    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[4]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[5]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x - 60.0f, GoalSize.y - 50.0f, 0.0f));
    // タイルマップとの衝突判定
    StayGround = false;
    auto& playerColl = this->player->GetCollider();

    auto& col2 = playercol->GetCollider();
    auto& col4 = playercol2->GetCollider();
    auto& col5 = playercol3->GetCollider();
    auto& colgoal = goal->GetCollider();

    std::vector<std::reference_wrapper<BaseCollider>> colhook = {
        hook[0]->GetCollider(),
        hook[1]->GetCollider(),
        hook[2]->GetCollider(),
           hook[3]->GetCollider(),
        hook[4]->GetCollider(),
        hook[5]->GetCollider(),
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
    }



    for (HookNumber = 0; HookNumber < 6; HookNumber++)
    {
        if (playerColl.CheckCollision(colhook[HookNumber]))
        {
            HookColliderState = HookNumber;//;hook collider
            ColliderState = 2;
        }
        if (playerColl.CheckCollision(colhook[0]))
        {
            MoveHookFLG[0] = true;
        }
        if (playerColl.CheckCollision(colhook[1]))
        {
            MoveHookFLG[1] = true;
        }
        if (playerColl.CheckCollision(colhook[4]))
        {
            MoveHookFLG[2] = true;
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
        if (playerPos.y <= -4500.0f && (!this->player->GetIsDead()))
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
            if (this->failedTimer.Elapsed() > 2.0f)
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
            if (this->failedTimer.Elapsed() > 3.0f)
            {
                this->p_sceneManager->ChangeScene(Scene::Stage_4);
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
        //this->rail->SetAngle(90.0f);

        this->eyes->SetPos(playerPos.x + EyesPos.x, playerPos.y + EyesPos.y, playerPos.z);
        this->lefthand->SetPos(playerPos.x + LefthandPos.x, playerPos.y + LefthandPos.y, playerPos.z);
        this->leftleg->SetPos(playerPos.x + LeftlegPos.x, playerPos.y + LeftlegPos.y, playerPos.z);
        this->righthand->SetPos(playerPos.x + RighthandPos.x, playerPos.y + RighthandPos.y, playerPos.z);
        this->rightleg->SetPos(playerPos.x + RightlegPos.x, playerPos.y + RightlegPos.y, playerPos.z);
        this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);
        this->playerdraw->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y, playerPos.z);
        this->death2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->idle->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->playercol->SetPos(playerPos.x + PlayerColPos.x, playerPos.y + PlayerColPos.y, playerPos.z);
        this->playercol2->SetPos(playerPos.x + PlayerColPos2.x, playerPos.y + PlayerColPos2.y, playerPos.z);
        this->playercol3->SetPos(playerPos.x + PlayerColPos3.x, playerPos.y + PlayerColPos3.y, playerPos.z);
        // this->rail->SetPos(RailPos.x, RailPos.y, playerPos.z);
     /*    this->hook[0]->SetPos(HookPos01.x, HookPos01.y, playerPos.z);
         this->hook[1]->SetPos(HookPos02.x, HookPos02.y, playerPos.z);
         this->hook[2]->SetPos(HookPos03.x, HookPos03.y, playerPos.z);*/

        this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);
        this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);
        this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);
        this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);
        this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);
        this->hook[5]->SetPos(HookPos05.x, HookPos05.y, 0.0f);

        this->hookdraw[0]->SetPos(HookPos00.x, HookPos00.y + 80.0f, 0.0f);
        this->hookdraw[1]->SetPos(HookPos01.x, HookPos01.y + 80.0f, 0.0f);
        this->hookdraw[2]->SetPos(HookPos02.x, HookPos02.y + 80.0f, 0.0f);
        this->hookdraw[3]->SetPos(HookPos03.x, HookPos03.y + 80.0f, 0.0f);
        this->hookdraw[4]->SetPos(HookPos04.x, HookPos04.y + 80.0f, 0.0f);
        this->hookdraw[5]->SetPos(HookPos05.x, HookPos05.y + 80.0f, 0.0f);
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



        if (this->p_input->Press("LEFT"))
        {
            idletime += 1;
            if (idletime % 5 == 0)
            {
                u += 1;
            }
            if (PlayerColState != 1)
            {
                movestate2 = 1;
            }

            if (movestate2 == 1 && PlayerColState == 1 && grabstate == 0)
            {
                movestate = 1;

            }
            else
            {
                movestate = 0;
            }
            if (movestate != 1)
            {
                this->player->SetPos(playerPos.x - 7.0f, playerPos.y, playerPos.z);
            }


        }
        if (this->p_input->Press("RIGHT"))
        {
            idletime += 1;
            if (idletime % 5 == 0)
            {
                u += 1;
            }
            if (PlayerColState != 1)
            {
                movestate2 = 2;
            }
            if (movestate2 == 2 && PlayerColState == 1 && grabstate == 0)
            {
                movestate = 2;

            }
            else
            {
                movestate = 0;
            }
            if (movestate != 2)
            {
                this->player->SetPos(playerPos.x + 7.0f, playerPos.y, playerPos.z);
            }
        }

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
                this->p_sound->Play(SOUND_LABEL::SE_PLAYR_DEAD);
                deathstate = 1;

                //  t2 = 0;
            }
            if (deathstate == 1)
            {
                t5 += 1;
            }
            if (t5 >= 20)
            {


                ScenechangeState = true;
                //t5 = 0;
            }
        }

        if (ColliderState == 0)
        {
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
                Vy = Vypower * -0.35f;
            }
            else if (p_input->GetRightAnalogStick().y < 0)
            {
                Vy = Vypower * 3.0f;
            }
            else if (p_input->GetRightAnalogStick().y == 0)
            {
                Vy = 0;
            }


            if (p_input->GetRightAnalogStick().x > 0)
            {
                Vx = Vxpower * -0.9f;
            }
            else if (p_input->GetRightAnalogStick().x < 0)
            {
                Vx = Vxpower * 0.9f;
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


            if (Vdelta <= -10.0f)
            {
                Vdelta = -10.0f;

            }









            if (PlayerColState == 1 && grabstate == 0)
            {
                Vx4 = 0;

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

        if (jumpstate == 1 && ColliderState == 1)
        {
            jumpstate = 0;
            t = 0;
            Vdown = 0;
            Vy = 0;
            jumpkeystate = 0;
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

            this->p_sceneManager->ChangeScene(Scene::Stage_4);
            return;
        }

        if (ScenechangeState2 == 1)
        {
            this->p_sound->Play(SOUND_LABEL::SE_GOAL);
            this->p_sceneManager->ChangeScene(Scene::Stage_5); 
            return;
        }
    }





    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->background->Update();
    this->p_tileMap->Update();
    this->keyConfigUI->Update();

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
    for (n = 0; n < 2; n++)//Updateの数
    {
        this->PushObject[n]->Update();
    }

    for (n = 0; n < 6; n++)//Updateの数
    {
        this->hook[n]->Update();
        this->hookdraw[n]->Update();
    }

    for (n = 0; n < 3; n++)//Updateの数
    {
        this->rail[n]->Update();
    }



    //this->playercol->Draw();
//this->playercol2->Draw();
//this->playercol3->Draw();

    // カメラの更新
    this->p_camera->Update();

}

/**	@brief 	シーン全体の描画
*/
void	Stage_4::Draw(void)
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
    /* this->player->Draw();
     this->playercol->Draw();
    this->playercol2->Draw();
    this->playercol3->Draw();*/

    //this->hook[0]->Draw();
    //this->hook[1]->Draw();
    //this->hook[2]->Draw();
    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->PushObject[n]->Draw();
    }
    for (n = 0; n < 3; n++)//当たり判定用ブロック描画
    {
        this->rail[n]->Draw();
    }

    for (n = 0; n < 6; n++)//当たり判定用ブロック描画
    {
        this->hookdraw[n]->Draw();
    }

    if (p_input->GetLeftAnalogStick().x * 10.0f < -2.0f && superjumpstate == 0 && grabstate == 0 && jumpstate == 0)
    {
        this->walking2->Draw();
    }
    else if (p_input->GetLeftAnalogStick().x * 10.0f >= 2.0f && superjumpstate == 0 && grabstate == 0 && jumpstate == 0)
    {
        this->walking->Draw();
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
    else if (grabstate == 0 && jumpstate == 0)
    {

        this->idle->Draw();
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
    this->keyConfigUI->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_4::Finalize(void)
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

    //テクスチャ
    for (int i = 0; i < 2; i++)
    {
        SAFE_RELEASE(this->textureList[i]);
    }
}
