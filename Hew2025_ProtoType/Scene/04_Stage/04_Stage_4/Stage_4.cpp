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
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    for (n = 0; n < 100; n++)//当たり判定用ブロックの初期化
    {
        this->block[n] = nullptr;
    }

    for (n = 0; n < 2; n++)
    {
        this->PushObject[n] = nullptr;
    }

    for (n = 0; n < 5; n++)
    {
        this->hook[n] = nullptr;
    }

    for (n = 0; n < 3; n++)
    {
        this->rail[n] = nullptr;
    }

    for (drawnum = 0; drawnum < 2000; drawnum++)//描画用ブロックの初期化
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
Stage_4::~Stage_4()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_4::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Player; }
    if (!this->goal) { this->goal = new Object; }

    for (n = 0; n < 100; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }//当たり判定用ブロックの初期化
    }

    for (n = 0; n < 2; n++)
    {
        if (!this->PushObject[n]) { this->PushObject[n] = new Object; }//倒れるオブジェクトの初期化
    }

    for (n = 0; n < 5; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object; }//倒れるオブジェクトの初期化
    }

    for (n = 0; n < 3; n++)
    {
        if (!this->rail[n]) { this->rail[n] = new Object; }//倒れるオブジェクトの初期化
    }

    for (drawnum = 0; drawnum < 2000; drawnum++)
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

    for (n = 0; n < 8; n++)//当たり判定用のブロック
    {
        this->block[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 2; n++)//倒れるオブジェクト
    {
        this->PushObject[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 5; n++)//フック
    {
        this->hook[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 3; n++)//フックのレール
    {
        this->rail[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (drawnum = 0; drawnum < 2000; drawnum++)//最大値は3000くらい
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
    this->block[6]->SetPos(BlockPos06.x, BlockPos06.y, 0.0f);//当たり判定用ブロックの座標設定
    this->block[7]->SetPos(BlockPos07.x, BlockPos07.y, 0.0f);//当たり判定用ブロックの座標設定
    
    this->PushObject[0]->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->PushObject[1]->SetPos(PushObjectPos01.x, PushObjectPos01.y, 0.0f);//当たり判定用ブロックの座標設定
    
    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);//当たり判定用ブロックの座標設定
    this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);//当たり判定用ブロックの座標設定
    this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);//当たり判定用ブロックの座標設定
    this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);//当たり判定用ブロックの座標設定

    this->rail[0]->SetPos(RailPos00.x, RailPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->rail[1]->SetPos(RailPos01.x, RailPos01.y, 0.0f);//当たり判定用ブロックの座標設定
    this->rail[2]->SetPos(RailPos02.x, RailPos02.y, 0.0f);//当たり判定用ブロックの座標設定
    
    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);//当たり判定用ブロックの座標設定


    for (drawnum = 0; drawnum < 2000; drawnum++)
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
    this->block[6]->SetSize(BlockSize06.x, BlockSize06.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[7]->SetSize(BlockSize07.x, BlockSize07.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->PushObject[0]->SetSize(PushObjectSize00.x, PushObjectSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->PushObject[1]->SetSize(PushObjectSize01.x, PushObjectSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->hook[0]->SetSize(HookSize00.x, HookSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->hook[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->hook[3]->SetSize(HookSize03.x, HookSize03.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->hook[4]->SetSize(HookSize04.x, HookSize04.y, 0.0f);//当たり判定用ブロックの大きさ設定


    this->rail[0]->SetSize(RailSize00.x, RailSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->rail[1]->SetSize(RailSize01.x, RailSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->rail[2]->SetSize(RailSize02.x, RailSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);//当たり判定用ブロックの大きさ設定


    for (drawnum = 0; drawnum < 2000; drawnum++)
    {
        this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);//描画用ブロックの大きさ設定
    }
}

/**	@brief 	シーン全体の更新
*/
void	Stage_4::Update(void)
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
        if (StayGround == false && JumpState != 2)
        {
            CameraPos.y -= 10.0f;
        }

        if (ColliderState != 2)
        {
            if (this->p_input->Press("LEFT"))
            {
                CameraPos.x -= 10.0f;
            }
        }

        if (this->p_input->Press("RIGHT"))
        {
            CameraPos.x += 10.0f;
        }


        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
        }
        if (this->p_input->Press("UP"))
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
    this->block[6]->SetPos(BlockPos06.x - CameraPos.x, BlockPos06.y - CameraPos.y, 0.0f);
    this->block[7]->SetPos(BlockPos07.x - CameraPos.x, BlockPos07.y - CameraPos.y, 0.0f);

    this->PushObject[0]->SetPos(PushObjectPos00.x - CameraPos.x, PushObjectPos00.y - CameraPos.y, 0.0f);
    this->PushObject[1]->SetPos(PushObjectPos01.x - CameraPos.x, PushObjectPos01.y - CameraPos.y, 0.0f);

    this->hook[0]->SetPos(HookPos00.x - CameraPos.x, HookPos00.y - CameraPos.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x - CameraPos.x, HookPos01.y - CameraPos.y, 0.0f);
    this->hook[2]->SetPos(HookPos02.x - CameraPos.x, HookPos02.y - CameraPos.y, 0.0f);
    this->hook[3]->SetPos(HookPos03.x - CameraPos.x, HookPos03.y - CameraPos.y, 0.0f);
    this->hook[4]->SetPos(HookPos04.x - CameraPos.x, HookPos04.y - CameraPos.y, 0.0f);

    this->rail[0]->SetPos(RailPos00.x - CameraPos.x, RailPos00.y - CameraPos.y, 0.0f);
    this->rail[1]->SetPos(RailPos01.x - CameraPos.x, RailPos01.y - CameraPos.y, 0.0f);
    this->rail[2]->SetPos(RailPos02.x - CameraPos.x, RailPos02.y - CameraPos.y, 0.0f);

    this->goal->SetPos(GoalPos.x - CameraPos.x, GoalPos.y - CameraPos.y, 0.0f);

    //描画用ブロックの座標更新
    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 320; drawnum++)//左側地面
    {
        if (drawnum == 40 || drawnum == 80 || drawnum == 120 || drawnum == 160 || drawnum == 200 || drawnum == 240 || drawnum == 280 || drawnum == 320)
        {
            posx = 0.0f;
            posy -= 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 320; drawnum < 640; drawnum++)//右側地面
    {
        if (drawnum == 360 || drawnum == 400 || drawnum == 440 || drawnum == 480 || drawnum == 520 || drawnum == 560 || drawnum == 600 || drawnum == 640)
        {
            posx = 0.0f;
            posy -= 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(1850.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 640; drawnum < 1648; drawnum++)//左側壁
    {
        if (640 <= drawnum <= 1648 and (drawnum - 640) % 24 == 0)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x, -350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 1648; drawnum < 1674; drawnum++)//空中床左
    {
        if (drawnum == 1661)
        {
            posx = 0.0f;
            posy += 100.0f;;
        }
        this->blockdraw[drawnum]->SetPos(1550.0f + posx - CameraPos.x, 1550.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 1674; drawnum < 1700; drawnum++)//空中床右(下)
    {
        if (drawnum == 1687)
        {
            posx = 0.0f;
            posy += 100.0f;;
        }
        this->blockdraw[drawnum]->SetPos(3650.0f + posx - CameraPos.x, 1550.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 1700; drawnum < 1732; drawnum++)//空中床右(上)
    {
        if (drawnum == 1716)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(2250.0f + posx - CameraPos.x, 3450.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 1732; drawnum < 1736; drawnum++)//空中壁1
    {
        if (drawnum == 1734)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(3650.0f + posx - CameraPos.x, 1750.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 1736; drawnum < 1760; drawnum++)//空中壁2
    {
        if (drawnum == 1748)
        {
            posx += 100.0f;
            posy += 1200.0f;
        }
        this->blockdraw[drawnum]->SetPos(3650.0f + posx - CameraPos.x, 3350.0f + posy - CameraPos.y, 0.0f);
        posy -= 100.0f;
    }

    //-----------------------------------------------------
    if (JumpState == 1)
    {
        if (cnt != 15)
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
    }

    if (MoveHookFLG[2])//空中左フック(上)の移動処理
    {
        if (TurnBackFLG[2])
        {
            HookPos04.x += HookMoveSpeed;
            HookCnt[2]++;

            if (HookCnt[2] == 150)
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
    this->block[6]->SetColliderSize(DirectX::XMFLOAT3(BlockSize06.x, BlockSize06.y, 0.0f));
    this->block[7]->SetColliderSize(DirectX::XMFLOAT3(BlockSize07.x, BlockSize07.y, 0.0f));

    this->PushObject[0]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize00.x, PushObjectSize00.y, 0.0f));
    this->PushObject[1]->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize01.x, PushObjectSize01.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize00.x, HookSize00.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize02.x, HookSize02.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookSize03.x, HookSize03.y, 0.0f));
    this->hook[4]->SetColliderSize(DirectX::XMFLOAT3(HookSize04.x, HookSize04.y, 0.0f));

    this->rail[0]->SetColliderSize(DirectX::XMFLOAT3(RailSize00.x, RailSize00.y, 0.0f));
    this->rail[1]->SetColliderSize(DirectX::XMFLOAT3(RailSize01.x, RailSize01.y, 0.0f));
    this->rail[2]->SetColliderSize(DirectX::XMFLOAT3(RailSize02.x, RailSize02.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    auto& col1 = player->GetCollider();
    auto& colgoal = goal->GetCollider();

    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//当たり判定を入れる
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
         block[3]->GetCollider(),
         block[4]->GetCollider(),
         block[5]->GetCollider(),
         block[6]->GetCollider(),
         block[7]->GetCollider(),
    };


    std::vector<std::reference_wrapper<BaseCollider>> colPush = {//当たり判定を入れる
         PushObject[0]->GetCollider(),
         PushObject[1]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colHook = {//当たり判定を入れる
     hook[0]->GetCollider(),
     hook[1]->GetCollider(),
     hook[2]->GetCollider(),
     hook[3]->GetCollider(),
     hook[4]->GetCollider(),
    };

    ColliderState = 0;
    StayGround = false;
    for (BlockNumber = 0; BlockNumber < 8; BlockNumber++)//当たり判定用ブロックの数
    {
        if (col1.CheckCollision(colblock[BlockNumber]) && (BlockNumber == 0 || BlockNumber == 1 || BlockNumber == 3 || BlockNumber == 4 || BlockNumber == 5 || BlockNumber == 7))
        {
            StayGround = true;
        }

        if (col1.CheckCollision(colblock[BlockNumber]) && (BlockNumber == 2 || BlockNumber == 6))
        {
            ColliderState = 2;
        }
    }

    for (PushNumber = 0; PushNumber < 2; PushNumber++)
    {
        if (col1.CheckCollision(colPush[PushNumber]))
        {
            ColliderState = 3;

        }
    }

    for (HookNumber = 0; HookNumber < 5; HookNumber++)
    {
        if (col1.CheckCollision(colHook[HookNumber]))
        {
            ColliderState = 4;
            switch (HookNumber)
            {
            case 0:
                MoveHookFLG[0] = true;
                break;

            case 1:
                MoveHookFLG[1] = true;
                break;

            case 4:
                MoveHookFLG[2] = true;
                break;
            }
        }
    }

    if (col1.CheckCollision(colgoal))
    {
        ColliderState = 5;

    }

    if (gamemode == 0)//Creative Mode
    {
        if (StayGround == true)//if StayGround == true ->赤になる
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
        else if (ColliderState == 4)//if ColliderState == 4 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->黄色になる
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
        else if (ColliderState == 2)//if ColliderState == 2 ->緑になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->黄色になる
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

    for (n = 0; n < 8; n++)//Updateの数
    {
        this->block[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->PushObject[n]->Update();
    }

    for (n = 0; n < 5; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (drawnum = 0; drawnum < 2000; drawnum++)//Updateの数
    {
        this->blockdraw[drawnum]->Update();

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
    this->goal->Draw();
    for (n = 0; n < 8; n++)//当たり判定用ブロック描画
    {
        this->block[n]->Draw();
    }

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->PushObject[n]->Draw();
    }

    for (n = 0; n < 3; n++)//当たり判定用ブロック描画
    {
        this->rail[n]->Draw();
    }

    for (n = 0; n < 5; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }


    for (drawnum = 0; drawnum < 2000; drawnum++)//描画用ブロック描画
    {
        this->blockdraw[drawnum]->Draw();
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

    for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->PushObject[n]);
    }

    for (n = 0; n < 5; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 3; n++)
    {
        SAFE_DELETE(this->rail[n]);
    }

    SAFE_DELETE(this->goal);


    for (drawnum = 0; drawnum < 2000; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->player);

}
