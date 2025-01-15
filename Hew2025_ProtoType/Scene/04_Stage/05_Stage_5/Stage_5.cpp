/**	@file	Stage_5.cpp
*	@brief 	Stage_5
*	@date 2024/12/19
*/
#include"Stage_5.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_5::Stage_5()
{
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->YoyoObject[0] = nullptr;
    this->YoyoObject[1] = nullptr;
    this->pendulum = nullptr;
    this->grabbox = nullptr;
    this->grabbox = nullptr;

    for (n = 0; n < 100; n++)//当たり判定用ブロックの初期化
    {
        this->block[n] = nullptr;
    }

    for (n = 0; n < 7; n++)
    {
        this->hook[n] = nullptr;
    }

    for (n = 0; n < 3; n++)
    {
        this->rail[n] = nullptr;
    }
    
    for (drawnum = 0; drawnum < 1000; drawnum++)//描画用ブロックの初期化
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
Stage_5::~Stage_5()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_5::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Player; }
    if (!this->goal) { this->goal = new Object; }
    if (!this->YoyoObject[0]) { this->YoyoObject[0] = new Object; }//フック用レールの初期化
    if (!this->YoyoObject[1]) { this->YoyoObject[1] = new Object; }//フック用レールの初期化
    if (!this->pendulum) { this->pendulum = new Pendulum(500.0f, 0.5f, 0.0f, 250.0f, 300.0f); }// 中心(250, 300), 振り幅500, 振動数0.5
    if (!this->grabbox) { this->grabbox = new GrabBox; }//倒れるオブジェクトの初期化

    for (n = 0; n < 100; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }//当たり判定用ブロックの初期化
    }

    for (n = 0; n < 7; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object; }//フックの初期化
    }

    for (n = 0; n < 3; n++)
    {
        if (!this->rail[n]) { this->rail[n] = new Object; }//フック用レールの初期化
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
    this->goal->Init(L"Asset/block.png");
    this->YoyoObject[0]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    this->YoyoObject[1]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    this->pendulum->Init(L"Asset/block.png", 1, 1, 1, 0.0f);
    this->grabbox->Init(L"Asset/block.png");//当たり判定用のブロックテクスチャ

    for (n = 0; n < 100; n++)
    {
        this->block[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 7; n++)//フック
    {
        this->hook[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 3; n++)//フックのレール
    {
        this->rail[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
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
    this->block[1]->SetPos(BlockPos01.x, BlockPos01.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[2]->SetPos(BlockPos02.x, BlockPos02.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[3]->SetPos(BlockPos03.x, BlockPos03.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[4]->SetPos(BlockPos04.x, BlockPos04.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[5]->SetPos(BlockPos05.x, BlockPos05.y, 0.0f);//当たり判定用ブロックの座標設定

    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[5]->SetPos(HookPos05.x, HookPos05.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[6]->SetPos(HookPos06.x, HookPos06.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    
    this->rail[0]->SetPos(RailPos00.x, RailPos00.y, 0.0f);//レール当たり判定用ブロックの座標設定
    this->rail[1]->SetPos(RailPos01.x, RailPos01.y, 0.0f);//レール当たり判定用ブロックの座標設定
    this->rail[2]->SetPos(RailPos02.x, RailPos02.y, 0.0f);//レール当たり判定用ブロックの座標設定

    this->YoyoObject[0]->SetPos(YoyoPos00.x, YoyoPos00.y, 0.0f);//ヨーヨーの当たり判定用ブロックの座標設定
    this->YoyoObject[1]->SetPos(YoyoPos01.x, YoyoPos01.y, 0.0f);//ヨーヨーの当たり判定用ブロックの座標設定

    this->pendulum->SetPos(YoyoPos01.x, YoyoPos01.y, 0.0f); // 振り子の初期位置を設定
    this->grabbox->SetPos(GrabboxPos.x, GrabboxPos.y, 0.0f);//当たり判定用ブロックの座標設定

    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);//当たり判定用ブロックの座標設定


    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        this->blockdraw[drawnum]->SetPos(0.0f, -10000.0f, 0.0f);//描画用ブロックの座標設定
    }

    //オブジェクトのサイズを設定
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

    this->block[0]->SetSize(BlockSize00.x, BlockSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[1]->SetSize(BlockSize01.x, BlockSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[2]->SetSize(BlockSize02.x, BlockSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[3]->SetSize(BlockSize03.x, BlockSize03.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[4]->SetSize(BlockSize04.x, BlockSize04.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[5]->SetSize(BlockSize05.x, BlockSize05.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->hook[0]->SetSize(HookSize00.x, HookSize00.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[3]->SetSize(HookSize03.x, HookSize03.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[4]->SetSize(HookSize04.x, HookSize04.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[5]->SetSize(HookSize05.x, HookSize05.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[6]->SetSize(HookSize06.x, HookSize06.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定

    this->rail[0]->SetSize(RailSize00.x, RailSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->rail[1]->SetSize(RailSize01.x, RailSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->rail[2]->SetSize(RailSize02.x, RailSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定
 
    this->YoyoObject[0]->SetSize(YoyoSize00.x, YoyoSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->YoyoObject[1]->SetSize(YoyoSize01.x, YoyoSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->pendulum->SetSize(YoyoSize01.x, YoyoSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->grabbox->SetSize(GrabboxSize.x, GrabboxSize.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);//当たり判定用ブロックの大きさ設定


    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);//描画用ブロックの大きさ設定
    }
}

/**	@brief 	シーン全体の更新
*/
void	Stage_5::Update(void)
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
            CameraPos.x -= 20.0f;
        }
        if (this->p_input->Press("RIGHT"))
        {
            CameraPos.x += 20.0f;
        }
        if (this->p_input->Press("UP"))
        {
            CameraPos.y += 20.0f;
        }
        if (this->p_input->Press("DOWN"))
        {
            CameraPos.y -= 20.0f;
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
        if (GrabFlg == false)
        {
            if (StayGround == false && JumpState != 2)
            {
                CameraPos.y -= 10.0f;
            }

            if (this->p_input->Press("LEFT"))
            {
                CameraPos.x -= 10.0f;
            }

            if (this->p_input->Press("RIGHT"))
            {
                CameraPos.x += 10.0f;
            }
        }
        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
            this->grabbox->Release();
            GrabFlg = false;
        }
            if (ColliderState == 3)
            {
                if (this->p_input->Press("UP"))
                {
                    //掴まる処理
                    this->grabbox->Grab(player);
                    GrabFlg = true;
                    JumpState = 0;
                }
            }

            if (this->p_input->Press("DOWN"))
            {
                //オブジェクトを離す処理
                this->grabbox->Release();
                GrabFlg = false;
            }
            if (this->p_input->Press("SHIFT"))
            {
                gamemode = 0;
            }
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

    this->hook[0]->SetPos(HookPos00.x - CameraPos.x, HookPos00.y - CameraPos.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x - CameraPos.x, HookPos01.y - CameraPos.y, 0.0f);
    this->hook[2]->SetPos(HookPos02.x - CameraPos.x, HookPos02.y - CameraPos.y, 0.0f);
    this->hook[3]->SetPos(HookPos03.x - CameraPos.x, HookPos03.y - CameraPos.y, 0.0f);
    this->hook[4]->SetPos(HookPos04.x - CameraPos.x, HookPos04.y - CameraPos.y, 0.0f);
    this->hook[5]->SetPos(HookPos05.x - CameraPos.x, HookPos05.y - CameraPos.y, 0.0f);
    this->hook[6]->SetPos(HookPos06.x - CameraPos.x, HookPos06.y - CameraPos.y, 0.0f);
    
    this->rail[0]->SetPos(RailPos00.x - CameraPos.x, RailPos00.y - CameraPos.y, 0.0f);
    this->rail[1]->SetPos(RailPos01.x - CameraPos.x, RailPos01.y - CameraPos.y, 0.0f);
    this->rail[2]->SetPos(RailPos02.x - CameraPos.x, RailPos02.y - CameraPos.y, 0.0f);

    this->YoyoObject[0]->SetPos(YoyoPos00.x - CameraPos.x, YoyoPos00.y - CameraPos.y, 0.0f);
    this->YoyoObject[1]->SetPos(YoyoPos01.x - CameraPos.x, YoyoPos01.y - CameraPos.y, 0.0f);

    this->grabbox->SetPos(GrabboxPos.x - CameraPos.x, GrabboxPos.y - CameraPos.y, 0.0f);

    this->goal->SetPos(GoalPos.x - CameraPos.x, GoalPos.y - CameraPos.y, 0.0f);

    if (GrabFlg)
    {
        this->CameraPos = this->GrabboxPos;
    }

    //描画用ブロックの座標更新

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 9; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        this->blockdraw[drawnum]->SetPos(-1100.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 9; drawnum < 15; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        this->blockdraw[drawnum]->SetPos(1450.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 15; drawnum < 51; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum == 24 || drawnum == 33 || drawnum == 42)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(2050.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 51; drawnum < 71; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum == 56 || drawnum == 61 || drawnum == 66)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(750.0f + posx - CameraPos.x, 1400.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 71; drawnum < 77; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x, 1400.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 77; drawnum < 99; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum == 88)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(750.0f + posx - CameraPos.x, 3000.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }


    //-----------------------------------------------------
    if (JumpState == 1)
    {
        if (cnt != 25)
        {
            CameraPos.y += 25.0f;
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
    if (MoveHookFLG[0])//右フックの移動処理
    {
        if (TurnBackFLG[0])
        {
            HookPos00.y -= HookMoveSpeed;
            HookCnt[0]++;

            if (HookCnt[0] == 150)
            {
                TurnBackFLG[0] = false;
            }

        }
        else
        {
            HookPos00.y += HookMoveSpeed;
            HookCnt[0]--;

            if (HookCnt[0] == 0)
            {
                TurnBackFLG[0] = true;
            }
        }
    }

    if (MoveHookFLG[1])//空中右フックの移動処理
    {
        if (TurnBackFLG[1])
        {
            HookPos03.x += HookMoveSpeed;
            HookCnt[1]++;

            if (HookCnt[1] == 150)
            {
                TurnBackFLG[1] = false;
            }
        }
        else
        {
            HookPos03.x -= HookMoveSpeed;
            HookCnt[1]--;

            if (HookCnt[1] == 0)
            {
                TurnBackFLG[1] = true;
            }
        }
    }

    if (MoveHookFLG[2])//空中左フック下の移動処理
    {
        if (TurnBackFLG[2])
        {
            HookPos04.y -= HookMoveSpeed;
            HookCnt[2]++;

            if (HookCnt[2] == 100)
            {
                TurnBackFLG[2] = false;
            }
        }
        else
        {
            HookPos04.y += HookMoveSpeed;
            HookCnt[2]--;

            if (HookCnt[2] == 0)
            {
                TurnBackFLG[2] = true;
            }
        }
    }
    //-----------------------------------
    //ヨーヨーの動き処理
    //横の動き
    if (YoyoTurnFLG[0])
    {
        GrabboxPos.x -= YoyoMoveSpeed;
        YoyoPos01.x -= YoyoMoveSpeed;
        YoyoCntX++;
        if (YoyoCntX == 120)
        {
            YoyoTurnFLG[0] = false;
        }
    }
    else
    {
        GrabboxPos.x += YoyoMoveSpeed;
        YoyoPos01.x += YoyoMoveSpeed;
        YoyoCntX--;
        if (YoyoCntX == 0)
        {
            YoyoTurnFLG[0] = true;
        }
    }

    //縦の動き
    if (YoyoTurnFLG[1])
    {
        GrabboxPos.y -= YoyoMoveSpeed;
        YoyoPos01.y -= YoyoMoveSpeed;
        YoyoCntY++;
        if (YoyoCntY == 60)
        {
            YoyoTurnFLG[1] = false;
        }
    }
    else
    {
        GrabboxPos.y += YoyoMoveSpeed;
        YoyoPos01.y += YoyoMoveSpeed;
        YoyoCntY--;
        if (YoyoCntY == 0)
        {
            YoyoTurnFLG[1] = true;
        }
    }
    //-----------------------------------
    if (GrabFlg)
    {
        this->grabbox->Move(grabbox->GetPos());
    }

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

    this->rail[0]->SetColliderSize(DirectX::XMFLOAT3(RailSize00.x, RailSize00.y, 0.0f));
    this->rail[1]->SetColliderSize(DirectX::XMFLOAT3(RailSize01.x, RailSize01.y, 0.0f));
    this->rail[2]->SetColliderSize(DirectX::XMFLOAT3(RailSize02.x, RailSize02.y, 0.0f));
    
    this->YoyoObject[0]->SetColliderSize(DirectX::XMFLOAT3(YoyoSize00.x, YoyoSize00.y, 0.0f));
    //this->YoyoObject[1]->SetColliderSize(DirectX::XMFLOAT3(YoyoSize01.x, YoyoSize01.y, 0.0f));

    this->pendulum->SetColliderSize(DirectX::XMFLOAT3(YoyoSize01.x, YoyoSize01.y, 0.0f));

    this->grabbox->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize.x, GrabboxSize.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    auto& col1 = player->GetCollider();
    auto& colgoal = goal->GetCollider();
    auto& colYoyo = pendulum->GetCollider();

    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//当たり判定を入れる
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
         block[3]->GetCollider(),
         block[4]->GetCollider(),
         block[5]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colHook = {//当たり判定を入れる
         hook[0]->GetCollider(),
         hook[1]->GetCollider(),
         hook[2]->GetCollider(),
         hook[3]->GetCollider(),
         hook[4]->GetCollider(),
         hook[5]->GetCollider(),
         hook[6]->GetCollider(),
    };


    ColliderState = 0;
    StayGround = false;
    for (BlockNumber = 0; BlockNumber < 6; BlockNumber++)//当たり判定用ブロックの数
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            StayGround = true;
        }
    }

    for (HookNumber = 0; HookNumber < 7; HookNumber++)
    {
        if (col1.CheckCollision(colHook[HookNumber]))
        {
            ColliderState = 2;
            switch (HookNumber)
            {
            case 0:
                MoveHookFLG[0] = true;
                break;

            case 3:
                MoveHookFLG[1] = true;
                break;

            case 4:
                MoveHookFLG[2] = true;
                break;
            }
        }
    }

    if (col1.CheckCollision(colYoyo))
    {
        ColliderState = 3;
    }

    if (col1.CheckCollision(colgoal))
    {
        ColliderState = 4;
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
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
    this->background->Update();
    this->player->Update();
    this->goal->Update();
    this->pendulum->Update();
    this->grabbox->Update();

    for (n = 0; n < 6; n++)//Updateの数
    {
        this->block[n]->Update();
    }

    for (n = 0; n < 7; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->YoyoObject[n]->Update();
    }

    for (drawnum = 0; drawnum < 100; drawnum++)//Updateの数
    {
        this->blockdraw[drawnum]->Update();

    }

    //振り子の座標更新は振り子のアップデート後に行わないとプレイヤーに追従するためここへ移動
    this->pendulum->SetPos(YoyoPos01.x - CameraPos.x, YoyoPos01.y - CameraPos.y, 0.0f);

}

/**	@brief 	シーン全体の描画
*/
void	Stage_5::Draw(void)
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
    this->YoyoObject[0]->Draw();
    this->pendulum->Draw();
    for (n = 0; n < 6; n++)//当たり判定用ブロック描画
    {
        this->block[n]->Draw();
    }

    for (n = 0; n < 3; n++)//当たり判定用ブロック描画
    {
        this->rail[n]->Draw();
    }

    for (n = 0; n < 7; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }


    for (drawnum = 0; drawnum < 100; drawnum++)//描画用ブロック描画
    {
        this->blockdraw[drawnum]->Draw();

    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_5::Finalize(void)
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
    SAFE_DELETE(this->pendulum);
    SAFE_DELETE(this->grabbox);//Delete Object

    for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }

    for (n = 0; n < 5; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 3; n++)
    {
        SAFE_DELETE(this->rail[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->YoyoObject[n]);
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->player);

}
