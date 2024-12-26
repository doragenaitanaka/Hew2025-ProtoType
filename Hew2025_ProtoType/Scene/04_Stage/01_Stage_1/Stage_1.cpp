/**	@file	Stage_1.cpp
*	@brief 	Stage_1
*	@date 2024/12/19
*/
#include"Stage_1.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_1::Stage_1()
{
    this->background = nullptr;
    this->player = nullptr;
    for (n = 0; n < 10; n++)
    {
        this->block[n] = nullptr;
    }
    for (m = 0; m < 10; m++)
    {
        this->hook[m] = nullptr;
    }
    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        this->blockdraw[drawnum] = nullptr;
    }
    this->goal = nullptr;

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*/
Stage_1::~Stage_1()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_1::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Object; }

    for (n = 0; n < 10; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }
    }
    for (m = 0; m < 10; m++)
    {
        if (!this->hook[m]) { this->hook[m] = new Object; }
    }
    if (!this->goal) { this->goal = new Object; }
    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        if (!this->blockdraw[drawnum]) { this->blockdraw[drawnum] = new Object; }
    }


    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    //オブジェクト
    this->background->Init(L"Asset/back_img_01.png");
    this->player->Init(L"Asset/block.png");
    this->goal->Init(L"Asset/goal1.png");

    for (n = 0; n < 10; n++)
    {
        this->block[n]->Init(L"Asset/block.png");
    }
    for (m = 0; m < 10; m++)
    {
        this->hook[m]->Init(L"Asset/block.png");
    }
    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        this->blockdraw[drawnum]->Init(L"Asset/block.png");
    }
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

    // オブジェクトの座標を設定
    this->background->SetPos(0.0f, 0.0f, 0.0f);
    this->player->SetPos(0.0f, -100.0f, 0.0f);

    this->block[0]->SetPos(BlockPos01.x, BlockPos01.y, 0.0f);
    this->block[1]->SetPos(BlockPos02.x, BlockPos02.y, 0.0f);
    this->block[2]->SetPos(BlockPos03.x, BlockPos03.y, 0.0f);
    this->block[3]->SetPos(BlockPos04.x, BlockPos04.y, 0.0f);
    this->block[4]->SetPos(BlockPos05.x, BlockPos05.y, 0.0f);
    this->block[5]->SetPos(BlockPos06.x, BlockPos06.y, 0.0f);
    this->block[6]->SetPos(BlockPos07.x, BlockPos07.y, 0.0f);
    this->block[7]->SetPos(BlockPos08.x, BlockPos08.y, 0.0f);

    this->hook[0]->SetPos(HookPos01.x, HookPos01.y, 0.0f);
    this->hook[1]->SetPos(HookPos02.x, HookPos02.y, 0.0f);
    this->hook[2]->SetPos(HookPos03.x, HookPos03.y, 0.0f);
    this->hook[3]->SetPos(HookPos04.x, HookPos04.y, 0.0f);

    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);

    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        this->blockdraw[drawnum]->SetPos(0.0f, -10000.0f, 0.0f);
    }

    //オブジェクトのサイズを設定
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->player->SetSize(100.0f, 100.0f, 0.0f);

    this->block[0]->SetSize(BlockSize01.x, BlockSize01.y, 0.0f);
    this->block[1]->SetSize(BlockSize02.x, BlockSize02.y, 0.0f);
    this->block[2]->SetSize(BlockSize03.x, BlockSize03.y, 0.0f);
    this->block[3]->SetSize(BlockSize04.x, BlockSize04.y, 0.0f);
    this->block[4]->SetSize(BlockSize05.x, BlockSize05.y, 0.0f);
    this->block[5]->SetSize(BlockSize06.x, BlockSize06.y, 0.0f);
    this->block[6]->SetSize(BlockSize07.x, BlockSize07.y, 0.0f);
    this->block[7]->SetSize(BlockSize08.x, BlockSize08.y, 0.0f);

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

    for (m = 0; m < 10; m++)
    {
        this->hook[m]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    }

    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);
    }
}

/**	@brief 	シーン全体の更新
*/
void	Stage_1::Update(void)
{

    //collier更新


    input.Update();

    if (GetAsyncKeyState(VK_LEFT))
    {
        CameraPos.x -= 10.0f;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        CameraPos.x += 10.0f;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        CameraPos.y += 10.0f;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        CameraPos.y -= 10.0f;
    }
    //-----------------------------------------------------
    //  座標更新
    //-----------------------------------------------------
    this->block[0]->SetPos(BlockPos01.x - CameraPos.x, BlockPos01.y - CameraPos.y, 0.0f);
    this->block[1]->SetPos(BlockPos02.x - CameraPos.x, BlockPos02.y - CameraPos.y, 0.0f);
    this->block[2]->SetPos(BlockPos03.x - CameraPos.x, BlockPos03.y - CameraPos.y, 0.0f);
    this->block[3]->SetPos(BlockPos04.x - CameraPos.x, BlockPos04.y - CameraPos.y, 0.0f);
    this->block[4]->SetPos(BlockPos05.x - CameraPos.x, BlockPos05.y - CameraPos.y, 0.0f);
    this->block[5]->SetPos(BlockPos06.x - CameraPos.x, BlockPos06.y - CameraPos.y, 0.0f);
    this->block[6]->SetPos(BlockPos07.x - CameraPos.x, BlockPos07.y - CameraPos.y, 0.0f);
    this->block[7]->SetPos(BlockPos08.x - CameraPos.x, BlockPos08.y - CameraPos.y, 0.0f);

    this->hook[0]->SetPos(HookPos01.x - CameraPos.x, HookPos01.y - CameraPos.y, 0.0f);
    this->hook[1]->SetPos(HookPos02.x - CameraPos.x, HookPos02.y - CameraPos.y, 0.0f);
    this->hook[2]->SetPos(HookPos03.x - CameraPos.x, HookPos03.y - CameraPos.y, 0.0f);
    this->hook[3]->SetPos(HookPos04.x - CameraPos.x, HookPos04.y - CameraPos.y, 0.0f);

    this->goal->SetPos(GoalPos.x - CameraPos.x, GoalPos.y - CameraPos.y, 0.0f);

    //Block Draw 座標更新

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 100; drawnum++)//block0 draw
    {
        /* if (drawnum == 50)
         {
             posx = 00.0f;
         }*/
        if (drawnum < 50)
        {
            this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 50)
        {
            this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }

    }
    posx = 0;
    posy = 0.0f;
    for (drawnum = 100; drawnum < 200; drawnum++)//block2 draw
    {
        if (drawnum == 125 || drawnum == 150 | drawnum == 175)
        {
            posx = 0.0f;
        }
        if (drawnum < 125)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x, 50.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 125 && drawnum < 150)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x, -50.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 150 && drawnum < 175)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x, -150.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 175 && drawnum < 200)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x, -250.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
    }
    posx = 0;
    posy = 0.0f;
    for (drawnum = 200; drawnum < 300; drawnum++)//block3 draw
    {
        if (drawnum == 225 || drawnum == 250 | drawnum == 275)
        {
            posx = 0.0f;
        }
        if (drawnum < 225)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x, 450.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 225 && drawnum < 250)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x, 350.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 250 && drawnum < 275)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x, 250.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 275 && drawnum < 300)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x, 150.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 300; drawnum < 320; drawnum++)//block4 draw
    {
        this->blockdraw[drawnum]->SetPos(2450.0f + posx - CameraPos.x, 550.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }
    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 320; drawnum < 360; drawnum++)//block5 draw
    {
        if (drawnum == 340)
        {
            posx = 0.0f;
        }
        if (drawnum < 340 && drawnum >= 320)
        {
            this->blockdraw[drawnum]->SetPos(2650.0f + posx - CameraPos.x, 750.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 340 && drawnum < 360)
        {
            this->blockdraw[drawnum]->SetPos(2650.0f + posx - CameraPos.x, 650.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 360; drawnum < 760; drawnum++)//block3 draw
    {
        if ((drawnum - 60) % 20 == 0 && drawnum != 360)
        {
            posx = 0.0f;
            posy -= 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(2950.0f + posx - CameraPos.x, 2750.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;

    }
    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 760; drawnum < 768; drawnum++)//block3 draw
    {

        this->blockdraw[drawnum]->SetPos(450.0f + posx - CameraPos.x, 1250.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;

    }
    //-----------------------------------
    //Collider更新
    //-----------------------------------

    this->block[0]->SetColliderSize(DirectX::XMFLOAT3(BlockSize01.x, BlockSize01.y, 0.0f));
    this->block[1]->SetColliderSize(DirectX::XMFLOAT3(BlockSize02.x, BlockSize02.y, 0.0f));
    this->block[2]->SetColliderSize(DirectX::XMFLOAT3(BlockSize03.x, BlockSize03.y, 0.0f));
    this->block[3]->SetColliderSize(DirectX::XMFLOAT3(BlockSize04.x, BlockSize04.y, 0.0f));
    this->block[4]->SetColliderSize(DirectX::XMFLOAT3(BlockSize05.x, BlockSize05.y, 0.0f));
    this->block[5]->SetColliderSize(DirectX::XMFLOAT3(BlockSize06.x, BlockSize06.y, 0.0f));
    this->block[6]->SetColliderSize(DirectX::XMFLOAT3(BlockSize07.x, BlockSize07.y, 0.0f));
    this->block[7]->SetColliderSize(DirectX::XMFLOAT3(BlockSize08.x, BlockSize08.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    auto& col1 = player->GetCollider();
    auto& colgoal = goal->GetCollider();

    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//本当に使えますか？
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
         block[3]->GetCollider(),
         block[4]->GetCollider(),
         block[5]->GetCollider(),
         block[6]->GetCollider(),
         block[7]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colhook = {
        hook[0]->GetCollider(),
        hook[1]->GetCollider(),
        hook[2]->GetCollider(),
        hook[3]->GetCollider(),
    };

    ColliderState = 0;

    for (BlockNumber = 0; BlockNumber < 8; BlockNumber++)
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            ColliderState = 1;//block collider

        }
    }

    for (HookNumber = 0; HookNumber < 4; HookNumber++)
    {
        if (col1.CheckCollision(colhook[HookNumber]))
        {
            ColliderState = 2;//hook collider

        }
    }

    if (col1.CheckCollision(colgoal))
    {
        ColliderState = 3;//hook collider

    }
    if (ColliderState == 1)
    {
        player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    }
    else if (ColliderState == 2)
    {
        player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
    }
    else if (ColliderState == 3)
    {
        player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
    }
    else
    {
        player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    this->background->Update();
    this->player->Update();
    this->goal->Update();
    for (n = 0; n < 10; n++)
    {
        this->block[n]->Update();
    }

    for (m = 0; m < 10; m++)
    {
        this->hook[m]->Update();
    }
    for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->Update();

    }
}

/**	@brief 	シーン全体の描画
*/
void	Stage_1::Draw(void)
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
    this->block[1]->Draw();


    /* for (n = 1; n < 8; n++)
     {
         this->block[n]->Draw();
     }*/
    for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->Draw();


    }
    for (m = 0; m < 4; m++)
    {
        this->hook[m]->Draw();
    }
    this->goal->Draw();
    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_1::Finalize(void)
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

    for (n = 0; n < 10; n++)
    {
        SAFE_DELETE(this->block[n]);
    }
    SAFE_DELETE(this->player);

    for (m = 0; m < 10; n++)
    {
        SAFE_DELETE(this->hook[m]);
    }
    for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->goal);
    SAFE_DELETE(this->player);
}
