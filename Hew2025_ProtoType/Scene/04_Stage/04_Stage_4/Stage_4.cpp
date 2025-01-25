/**	@file	Stage_4.cpp
*	@brief 	Stage_4
*	@date 2024/12/19
*/
#include"Stage_4.h"
#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_4::Stage_4()
{

    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;

    for (n = 0; n < 2; n++)
    {
        this->PushObject[n] = nullptr;
    }

    for (n = 0; n < 6; n++)
    {
        this->hook[n] = nullptr;
    }

    for (n = 0; n < 3; n++)
    {
        this->rail[n] = nullptr;
    }

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

    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }


    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage4.csv");
    }


    if (!this->background) { this->background = new Object(this->p_camera); }
    this->background->Init(L"Asset/back_img_01.png");
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->background->SetPos(0.0f, 0.0f, 0.0f);

    if (!this->player) { this->player = new Player(this->p_camera); }
    this->player->Init(L"Asset/gumbody2.png");
    this->player->SetSize(100.0f, 100.0f, 0.0f);
    this->player->SetPos(2500.0f, -4200.0f, 0.0f);
    DirectX::XMFLOAT3 playerPos = this->player->GetPos();

    if (!this->goal) { this->goal = new Object(this->p_camera); }
    this->goal->Init(L"Asset/block.png");
    this->goal->SetSize(200.0f, 300.0f, 0.0f);
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);

    if (!this->PushObject[0]) { this->PushObject[0] = new Object(this->p_camera); }
    this->PushObject[0]->Init(L"Asset/block.png");
    this->PushObject[0]->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    this->PushObject[0]->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);

    if (!this->PushObject[1]) { this->PushObject[1] = new Object(this->p_camera); }
    this->PushObject[1]->Init(L"Asset/block.png");
    this->PushObject[1]->SetSize(PushObjectSize.x, PushObjectSize.y, 0.0f);
    this->PushObject[1]->SetPos(PushObjectPos01.x, PushObjectPos01.y, 0.0f);

    for (n = 0; n < 6; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object(this->p_camera); }
        this->hook[n]->Init(L"Asset/block.png");
        this->hook[n]->SetSize(HookSize.x, HookSize.y, 0.0f);
    }
    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);
    this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);
    this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);
    this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);
    this->hook[5]->SetPos(HookPos05.x, HookPos05.y, 0.0f);


    for (n = 0; n < 3; n++)
    {
        if (!this->rail[n]) { this->rail[n] = new Object(this->p_camera); }
        this->rail[n]->Init(L"Asset/block.png");
    }
    this->rail[0]->SetSize(RailSize00.x, RailSize00.y, 0.0f);
    this->rail[1]->SetSize(RailSize01.x, RailSize01.y, 0.0f);
    this->rail[2]->SetSize(RailSize02.x, RailSize02.y, 0.0f);
    this->rail[0]->SetPos(RailPos00.x, RailPos00.y, 0.0f);
    this->rail[1]->SetPos(RailPos01.x, RailPos01.y, 0.0f);
    this->rail[2]->SetPos(RailPos02.x, RailPos02.y, 0.0f);


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
**/
void	Stage_4::Update(void)
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

        if (this->p_input->Press("LEFT"))
        {
            playerPos.x -= 10.0f;
        }
        if (this->p_input->Press("RIGHT"))
        {
            playerPos.x += 10.0f;
        }

 
        if (StayGround == false && JumpState != 2)
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

    this->PushObject[0]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize.x, PushObjectSize.y, 0.0f));
    this->PushObject[1]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize.x, PushObjectSize.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[4]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));
    this->hook[5]->SetColliderSize(DirectX::XMFLOAT3(HookSize.x, HookSize.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(200.0f, 300.0f, 0.0f));

    // タイルマップとの衝突判定
    ColliderState = 0;
    StayGround = false;
    auto& playerColl = this->player->GetCollider();
    auto& goalColl = this->goal->GetCollider();
    auto& tiles = this->p_tileMap->GetTiles();
    auto& pushColl1 = this->PushObject[0]->GetCollider();
    auto& pushColl2 = this->PushObject[1]->GetCollider();

    auto& HookColl1 = this->hook[0]->GetCollider();
    auto& HookColl2 = this->hook[1]->GetCollider();
    auto& HookColl3 = this->hook[2]->GetCollider();
    auto& HookColl4 = this->hook[3]->GetCollider();
    auto& HookColl5 = this->hook[4]->GetCollider();
    auto& HookColl6 = this->hook[5]->GetCollider();

    for (auto& tile : tiles)
    {
        auto& tileColl = tile->GetCollider();
        if (playerColl.CheckCollision(tileColl))
        {
            //std::cout << "当たった" << std::endl;
            StayGround = true;
        }
    }

    if (playerColl.CheckCollision(pushColl1) || playerColl.CheckCollision(pushColl2))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 2;
    }

    if (playerColl.CheckCollision(HookColl1) || playerColl.CheckCollision(HookColl2) || playerColl.CheckCollision(HookColl3) || playerColl.CheckCollision(HookColl4) || playerColl.CheckCollision(HookColl5) || playerColl.CheckCollision(HookColl6))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 3;
        if (playerColl.CheckCollision(HookColl1))
        {
            MoveHookFLG[0] = true;
        }
        if (playerColl.CheckCollision(HookColl2))
        {
            MoveHookFLG[1] = true;
        }
        if (playerColl.CheckCollision(HookColl5))
        {
            MoveHookFLG[2] = true;
        }
    }

   if (playerColl.CheckCollision(goalColl))
    {
        //std::cout << "当たった" << std::endl;
        ColliderState = 4;
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
        else if (ColliderState == 4)//if ColliderState == 4 ->黄色になる
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
        else if (ColliderState == 4)//if ColliderState == 4 ->黄色になる
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
    this->player->Update();
    this->goal->Update();

    // カメラの更新
    this->p_camera->Update();

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->PushObject[n]->Update();
    }

    for (n = 0; n < 6; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (n = 0; n < 3; n++)//Updateの数
    {
        this->rail[n]->Update();
    }



    if (ColliderState == 5)
    {
        p_sceneManager->ChangeScene(Scene::Stage_5);
    }
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
        this->hook[n]->Draw();
    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_4::Finalize(void)
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


    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->PushObject[n]);
    }

    for (n = 0; n < 6; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 3; n++)
    {
        SAFE_DELETE(this->rail[n]);
    }

    SAFE_DELETE(this->goal);

    SAFE_DELETE(this->player);

}
