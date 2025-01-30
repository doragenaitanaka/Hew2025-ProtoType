/**	@file	Stage_8.cpp
*	@brief 	Stage_8
*	@date 2024/12/19
*/
#include"Stage_8.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_8::Stage_8()
{
    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;

    for (n = 0; n < 2; n++)
    {
        this->PushObject[n] = nullptr;
    }

    for (n = 0; n < 2; n++)
    {
        this->Pen[n] = nullptr;
    }

    for (n = 0; n < 5; n++)
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
Stage_8::~Stage_8()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_8::Initialize(void)
{

    // BGM
    this->p_sound->Play(SOUND_LABEL::BGM_GAME);

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }

    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage8.csv");
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
    this->player->SetPos(200.0f, -4250.0f, 0.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

    // プレイヤーをターゲットに設定
    this->p_camera->SetTarget(this->player);

    // ゴール
    if (!this->goal) { this->goal = new Object(this->p_camera); }
    this->goal->Init(L"Asset/Gimmick/goal.png");
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);
    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

    //フックの初期化
    for (int i = 0; i < 5; i++)
    {
        if (!this->hook[i]) { this->hook[i] = new Object(this->p_camera); }
        this->hook[i]->Init(L"Asset/Gimmick/hook.png");
        this->hook[i]->SetPos(this->HookPos[i].x, this->HookPos[i].y, 0.0f);
        this->hook[i]->SetSize(this->HookSize[i].x, this->HookSize[i].y, 0.0f);
    }

    //倒れるオブジェクトの初期化
    for (int i = 0; i < 2; i++)
    {
        if (!this->PushObject[i]) { this->PushObject[i] = new Object(this->p_camera); }
        this->PushObject[i]->Init(L"Asset/Gimmick/pencase.png");
        this->PushObject[i]->SetPos(this->PushObjectPos[i].x, this->PushObjectPos[i].y, 0.0f);
        this->PushObject[i]->SetSize(this->PushObjectSize[i].x, this->PushObjectSize[i].y, 0.0f);
    }

    //ペンの初期化
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            if (!this->Pen[i]) { this->Pen[i] = new Object(this->p_camera); }
            this->Pen[i]->Init(L"Asset/Gimmick/pen.png");
            this->Pen[i]->SetPos(this->PenPos[i].x, this->PenPos[i].y, 0.0f);
            this->Pen[i]->SetSize(this->PenSize[i].x, this->PenSize[i].y, 0.0f);
            this->Pen[i]->SetAngle(180.0f);
        }
        if (i == 1)
        {
            if (!this->Pen[i]) { this->Pen[i] = new Object(this->p_camera); }
            this->Pen[i]->Init(L"Asset/Gimmick/pen.png");
            this->Pen[i]->SetPos(this->PenPos[i].x, this->PenPos[i].y, 0.0f);
            this->Pen[i]->SetSize(this->PenSize[i].x, this->PenSize[i].y, 0.0f);
        }

    }

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
void	Stage_8::Update(void)
{
    // 入力更新
    this->p_input->Update();
    this->p_input->GetLeftAnalogStick();
    DirectX::XMFLOAT3 playerPos = this->player->GetPos();

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

        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
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
    if (JumpState == 1)
    {
        auto playerPos = this->player->GetPos();
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

    // プレイヤーの座標を更新
    this->player->SetPos(playerPos.x, playerPos.y, playerPos.z);

    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));
    this->goal->SetColliderSize(DirectX::XMFLOAT3(200.0f, 300.0f, 0.0f));

    // タイルマップとの衝突判定
    ColliderState = 0;
    StayGround = false;
    auto& playerColl = this->player->GetCollider();
    auto& goalColl = this->goal->GetCollider();
    auto& tiles = this->p_tileMap->GetTiles();

    // フック
    std::vector<std::reference_wrapper<BaseCollider>> colHook = {//当たり判定を入れる
         this->hook[0]->GetCollider(),
         this->hook[1]->GetCollider(),
         this->hook[2]->GetCollider(),
         this->hook[3]->GetCollider(),
         this->hook[4]->GetCollider()
    };

    // フック
    std::vector<std::reference_wrapper<BaseCollider>> colPush = {//当たり判定を入れる
         this->PushObject[0]->GetCollider(),
         this->PushObject[1]->GetCollider()
    };

    // フック
    std::vector<std::reference_wrapper<BaseCollider>> colPen = {//当たり判定を入れる
         this->Pen[0]->GetCollider(),
         this->Pen[1]->GetCollider()
    };

    if (this->gamemode == 0)//Creative Mode
    {
        if (ColliderState == 1)//if ColliderState == 1 ->赤になる
        {
            this->player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else
        {
            this->player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            ColliderState = 1;
        }
    }

    for (this->HookNumber = 0; this->HookNumber < 5; this->HookNumber++)
    {
        if (playerColl.CheckCollision(colHook[this->HookNumber]))
        {
            this->ColliderState = 2;
        }
    }

    for (this->PushNumber = 0; this->PushNumber < 2; this->PushNumber++)
    {
        if (playerColl.CheckCollision(colPush[this->PushNumber]))
        {
            this->ColliderState = 3;
        }
    }

    for (this->PenNumber = 0; this->PenNumber < 2; this->PenNumber++)
    {
        if (playerColl.CheckCollision(colPen[this->PenNumber]))
        {
            this->ColliderState = 4;
        }
    }

    if (playerColl.CheckCollision(goalColl))
    {
        this->ColliderState = 5;
    }

    if (ColliderState == 5)
    {
        p_sceneManager->ChangeScene(Scene::Stage_9);
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
        else if (ColliderState == 4)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
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
        this->Pen[n]->Update();
    }
    // カメラの更新
    this->p_camera->Update();


}

/**	@brief 	シーン全体の描画
*/
void	Stage_8::Draw(void)
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

    for (n = 0; n < 5; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->PushObject[n]->Draw();
    }

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->Pen[n]->Draw();
    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_8::Finalize(void)
{
    
    this->p_sound->Stop(SOUND_LABEL::BGM_GAME);// BGM
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
    SAFE_DELETE(this->goal);
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
        SAFE_DELETE(this->Pen[n]);
    }

}
