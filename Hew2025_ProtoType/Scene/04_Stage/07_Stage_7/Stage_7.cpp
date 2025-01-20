/**	@file	Stage_7.cpp
*	@brief 	Stage_7
*	@date 2024/12/19
*/
#include"Stage_7.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_7::Stage_7()
{
    this->background = nullptr;
    this->player = nullptr;
    for (n = 0; n < 100; n++)//当たり判定用ブロックの初期化
    {
        this->block[n] = nullptr;
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)//描画用ブロックの初期化
    {
        this->blockdraw[drawnum] = nullptr;
    }

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*/
Stage_7::~Stage_7()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_7::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Player; }
    if (!this->goal) { this->goal = new Object; }


    for (n = 0; n < 100; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }//当たり判定用ブロックの初期化
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        if (!this->blockdraw[drawnum]) { this->blockdraw[drawnum] = new Object; }//描画用ブロックの初期化
    }


    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    //オブジェクト
    this->background->Init(L"Asset/back_img_01.png");
    this->player->Init(L"Asset/gumbody2.png");
    this->goal->Init(L"Asset/goal1.png");


    for (n = 0; n < 100; n++)
    {
        this->block[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)//最大値は3000くらい
    {
        this->blockdraw[drawnum]->Init(L"Asset/block.png");//描画用ブロックのテクスチャ
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

    this->block[0]->SetPos(BlockPos00.x, BlockPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[1]->SetPos(BlockPos01.x, BlockPos01.y+400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[2]->SetPos(BlockPos02.x, BlockPos02.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[3]->SetPos(BlockPos03.x, BlockPos03.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[4]->SetPos(BlockPos04.x, BlockPos04.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[5]->SetPos(BlockPos05.x, BlockPos05.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[6]->SetPos(BlockPos06.x, BlockPos06.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[7]->SetPos(BlockPos07.x, BlockPos07.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[8]->SetPos(BlockPos08.x, BlockPos08.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[9]->SetPos(BlockPos09.x, BlockPos09.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[10]->SetPos(BlockPos10.x, BlockPos10.y + 400, 0.0f);//当たり判定用ブロックの座標設定
    this->block[11]->SetPos(BlockPos11.x, BlockPos11.y + 400, 0.0f);//当たり判定用ブロックの座標設定


    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        this->blockdraw[drawnum]->SetPos(0.0f, -10000.0f, 0.0f);//描画用ブロックの座標設定
    }

    //オブジェクトのサイズを設定
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

    this->block[0]->SetSize(BlockSize00.x, BlockSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[1]->SetSize(BlockSize01.x, BlockSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[2]->SetSize(BlockSize02.x, BlockSize02.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[3]->SetSize(BlockSize03.x, BlockSize03.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[4]->SetSize(BlockSize04.x, BlockSize04.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[5]->SetSize(BlockSize05.x, BlockSize05.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[6]->SetSize(BlockSize06.x, BlockSize06.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[7]->SetSize(BlockSize07.x, BlockSize07.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[8]->SetSize(BlockSize08.x, BlockSize08.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[9]->SetSize(BlockSize09.x, BlockSize09.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[10]->SetSize(BlockSize10.x, BlockSize10.y, 0.0f);//当たり判定用ブロックの大きさ設
    this->block[11]->SetSize(BlockSize11.x, BlockSize11.y, 0.0f);//当たり判定用ブロックの大きさ設


    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);//描画用ブロックの大きさ設定
    }
}

/**	@brief 	シーン全体の更新
*/
void	Stage_7::Update(void)
{
    this->p_input->Update();

    p_input->GetLeftAnalogStick();

    //----------------------------------------------
    // Creative Mode
    //----------------------------------------------
    if (gamemode == 0)
    {
        if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
        {
            CameraPos.x += 0.0f;
        }
        else
        {
            CameraPos.x += p_input->GetLeftAnalogStick().x * 10.0f;
        }
        if (p_input->GetLeftAnalogStick().y * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().y * 10.0f >= -2.0f)
        {
            CameraPos.y += 0.0f;
        }
        else
        {
            CameraPos.y += p_input->GetLeftAnalogStick().y * 10.0f;
        }

        if (this->p_input->Press("LEFT"))
        {

            CameraPos.x -= 10.0f;
        }
        if (this->p_input->Press("RIGHT"))
        {
            CameraPos.x += 10.0f;
        }
        if (this->p_input->Press("UP"))
        {
            CameraPos.y += 10.0f;
        }
        if (this->p_input->Press("DOWN"))
        {
            CameraPos.y -= 10.0f;
        }
    }

    //----------------------------------------------
    // Player Mode
    //----------------------------------------------
    if (gamemode == 1)
    {


    }



    //-----------------------------------------------------
    //  座標更新
    //-----------------------------------------------------
    //全てのブロックの座標は(BlockPosXX.x - CameraPos.x, BlockPosXX.y - CameraPos.yが必要です。

    //当たり判定用ブロックの座標更新

    this->block[0]->SetPos(BlockPos00.x - CameraPos.x, BlockPos00.y - CameraPos.y, 0.0f);
    this->block[1]->SetPos(BlockPos01.x - CameraPos.x, BlockPos01.y - CameraPos.y, 0.0f);
    this->block[2]->SetPos(BlockPos02.x - CameraPos.x, BlockPos02.y - CameraPos.y, 0.0f);
    this->block[3]->SetPos(BlockPos03.x - CameraPos.x, BlockPos03.y - CameraPos.y, 0.0f);
    this->block[4]->SetPos(BlockPos04.x - CameraPos.x, BlockPos04.y - CameraPos.y, 0.0f);
    this->block[5]->SetPos(BlockPos05.x - CameraPos.x, BlockPos05.y - CameraPos.y, 0.0f);
    this->block[6]->SetPos(BlockPos06.x - CameraPos.x, BlockPos06.y - CameraPos.y, 0.0f);
    this->block[7]->SetPos(BlockPos07.x - CameraPos.x, BlockPos07.y - CameraPos.y, 0.0f);
    this->block[8]->SetPos(BlockPos08.x - CameraPos.x, BlockPos08.y - CameraPos.y, 0.0f);
    this->block[9]->SetPos(BlockPos09.x - CameraPos.x, BlockPos09.y - CameraPos.y, 0.0f);
    this->block[10]->SetPos(BlockPos10.x - CameraPos.x, BlockPos10.y - CameraPos.y, 0.0f);
    this->block[11]->SetPos(BlockPos11.x - CameraPos.x, BlockPos11.y - CameraPos.y, 0.0f);

    //描画用ブロックの座標更新

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 11; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        
            this->blockdraw[drawnum]->SetPos(-500.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 11; drawnum <36 ; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum ==16  || drawnum == 21 || drawnum == 26||drawnum==31)
        {
            posx = 0.0f;
        }
        if (drawnum < 16)
        {
            this->blockdraw[drawnum]->SetPos(-500.0f + posx - CameraPos.x, 250.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
       }
        else if (drawnum >= 16 && drawnum < 21)
        {
            this->blockdraw[drawnum]->SetPos(-500.0f + posx - CameraPos.x, 350.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 21 && drawnum < 26)
        {
            this->blockdraw[drawnum]->SetPos(-500.0f + posx - CameraPos.x, 450.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 26 && drawnum < 31)
        {
            this->blockdraw[drawnum]->SetPos(-500.0f + posx - CameraPos.x, 550.0f + posy - CameraPos.y, 0.0f);
            posx += 100.0f;
        }

    }

    posx = 0.0f;
    posy = 0.0f;




    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y, 0.0f));

    this->block[0]->SetColliderSize(DirectX::XMFLOAT3(BlockSize00.x, BlockSize00.y, 0.0f));

    this->block[1]->SetColliderSize(DirectX::XMFLOAT3(BlockSize01.x, BlockSize01.y, 0.0f));

    this->block[2]->SetColliderSize(DirectX::XMFLOAT3(BlockSize02.x, BlockSize02.y, 0.0f));

    this->block[3]->SetColliderSize(DirectX::XMFLOAT3(BlockSize03.x, BlockSize03.y, 0.0f));

    this->block[4]->SetColliderSize(DirectX::XMFLOAT3(BlockSize04.x, BlockSize04.y, 0.0f));

    this->block[5]->SetColliderSize(DirectX::XMFLOAT3(BlockSize05.x, BlockSize05.y, 0.0f));

    this->block[6]->SetColliderSize(DirectX::XMFLOAT3(BlockSize06.x, BlockSize06.y, 0.0f));

    this->block[7]->SetColliderSize(DirectX::XMFLOAT3(BlockSize07.x, BlockSize07.y, 0.0f));

    this->block[8]->SetColliderSize(DirectX::XMFLOAT3(BlockSize08.x, BlockSize08.y, 0.0f));

    this->block[9]->SetColliderSize(DirectX::XMFLOAT3(BlockSize09.x, BlockSize09.y, 0.0f));

    this->block[10]->SetColliderSize(DirectX::XMFLOAT3(BlockSize10.x, BlockSize10.y, 0.0f));

    this->block[11]->SetColliderSize(DirectX::XMFLOAT3(BlockSize11.x, BlockSize11.y, 0.0f));

    auto& col1 = player->GetCollider();


    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//当たり判定を入れる
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
         block[3]->GetCollider(),
         block[4]->GetCollider(),
         block[5]->GetCollider(),
         block[6]->GetCollider(),
         block[7]->GetCollider(),
         block[8]->GetCollider(),
         block[9]->GetCollider(),
         block[10]->GetCollider(),
         block[11]->GetCollider(),

    };



    ColliderState = 0;

    for (BlockNumber = 0; BlockNumber < 1; BlockNumber++)//当たり判定用ブロックの数
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            ColliderState = 1;

        }
    }

    if (gamemode == 0)//Creative Mode
    {
        if (ColliderState == 1)//if ColliderState == 1 ->赤になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }

    this->background->Update();
    this->player->Update();

    for (n = 0; n < 12; n++)//Updateの数
    {
        this->block[n]->Update();
    }


    for (drawnum = 0; drawnum < 100; drawnum++)//Updateの数
    {
        this->blockdraw[drawnum]->Update();

    }
}

/**	@brief 	シーン全体の描画
*/
void	Stage_7::Draw(void)
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
    for (n = 0; n < 12; n++)//当たり判定用ブロック描画
    {
        this->block[n]->Draw();
    }

    for (drawnum = 0; drawnum < 100; drawnum++)//描画用ブロック描画
    {
        this->blockdraw[drawnum]->Draw();

    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_7::Finalize(void)
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

    for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }



    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->player);

}
