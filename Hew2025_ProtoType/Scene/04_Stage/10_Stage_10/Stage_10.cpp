/**	@file	Stage_10.cpp
*	@brief 	Stage_10
*	@date 2024/12/19
*/
#include"Stage_10.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_10::Stage_10()
{
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->PushObject = nullptr;
    for (n = 0; n < 100; n++)//当たり判定用ブロックの初期化
    {
        this->block[n] = nullptr;
    }

    for (n = 0; n < 6; n++)
    {
        this->hook[n] = nullptr;
    }

    for (n = 0; n < 6; n++)
    {
        this->rail[n] = nullptr;
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
Stage_10::~Stage_10()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_10::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Player; }
    if (!this->PushObject) { this->PushObject = new Object; }
    if (!this->goal) { this->goal = new Object; }

    for (n = 0; n < 100; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }//当たり判定用ブロックの初期化
    }

    for (n = 0; n < 6; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object; }//フックの初期化
    }

    for (n = 0; n < 6; n++)
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
    this->PushObject->Init(L"Asset/block.png");
    for (n = 0; n < 100; n++)
    {
        this->block[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 6; n++)//フック
    {
        this->hook[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 6; n++)//フックのレール
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

        this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);//フックの当たり判定用ブロックの座標設定
        this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);//フックの当たり判定用ブロックの座標設定
        this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);//フックの当たり判定用ブロックの座標設定
        this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);//フックの当たり判定用ブロックの座標設定
        this->hook[4]->SetPos(HookPos04.x, HookPos04.y, 0.0f);//フックの当たり判定用ブロックの座標設定
        this->hook[5]->SetPos(HookPos05.x, HookPos05.y, 0.0f);//フックの当たり判定用ブロックの座標設定

        this->rail[0]->SetPos(RailPos00.x, RailPos00.y, 0.0f);//レール当たり判定用ブロックの座標設定
        this->rail[1]->SetPos(RailPos01.x, RailPos01.y, 0.0f);//レール当たり判定用ブロックの座標設定
        this->rail[2]->SetPos(RailPos02.x, RailPos02.y, 0.0f);//レール当たり判定用ブロックの座標設定
        this->rail[3]->SetPos(RailPos03.x, RailPos03.y, 0.0f);//レール当たり判定用ブロックの座標設定
        this->rail[4]->SetPos(RailPos04.x, RailPos04.y, 0.0f);//レール当たり判定用ブロックの座標設定
        this->rail[5]->SetPos(RailPos05.x, RailPos05.y, 0.0f);//レール当たり判定用ブロックの座標設定

        this->PushObject->SetPos(PushObjectPos00.x, PushObjectPos00.y, 0.0f);//レール当たり判定用ブロックの座標設定

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

        this->hook[0]->SetSize(HookSize00.x, HookSize00.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
        this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
        this->hook[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
        this->hook[3]->SetSize(HookSize03.x, HookSize03.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
        this->hook[4]->SetSize(HookSize04.x, HookSize04.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
        this->hook[5]->SetSize(HookSize05.x, HookSize05.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定

        this->rail[0]->SetSize(RailSize00.x, RailSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
        this->rail[1]->SetSize(RailSize01.x, RailSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
        this->rail[2]->SetSize(RailSize02.x, RailSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定
        this->rail[3]->SetSize(RailSize03.x, RailSize03.y, 0.0f);//当たり判定用ブロックの大きさ設定
        this->rail[4]->SetSize(RailSize04.x, RailSize04.y, 0.0f);//当たり判定用ブロックの大きさ設定
        this->rail[5]->SetSize(RailSize05.x, RailSize05.y, 0.0f);//当たり判定用ブロックの大きさ設定

        this->PushObject->SetSize(PushObjectSize00.x, PushObjectSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定

        this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

        for (drawnum = 0; drawnum < 1500; drawnum++)
        {
            this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);//描画用ブロックの大きさ設定
        }
}

/**	@brief 	シーン全体の更新
*/
void	Stage_10::Update(void)
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

        if (this->p_input->Press("LEFT"))
        {
            CameraPos.x -= 10.0f;
        }

        if (ColliderState != 5)
        {
            if (this->p_input->Press("RIGHT"))
            {
                CameraPos.x += 10.0f;
            }
        }

        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
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

    this->hook[0]->SetPos(HookPos00.x - CameraPos.x, HookPos00.y - CameraPos.y, 0.0f);
    this->hook[1]->SetPos(HookPos01.x - CameraPos.x, HookPos01.y - CameraPos.y, 0.0f);
    this->hook[2]->SetPos(HookPos02.x - CameraPos.x, HookPos02.y - CameraPos.y, 0.0f);
    this->hook[3]->SetPos(HookPos03.x - CameraPos.x, HookPos03.y - CameraPos.y, 0.0f);
    this->hook[4]->SetPos(HookPos04.x - CameraPos.x, HookPos04.y - CameraPos.y, 0.0f);
    this->hook[5]->SetPos(HookPos05.x - CameraPos.x, HookPos05.y - CameraPos.y, 0.0f);

    this->rail[0]->SetPos(RailPos00.x - CameraPos.x, RailPos00.y - CameraPos.y, 0.0f);
    this->rail[1]->SetPos(RailPos01.x - CameraPos.x, RailPos01.y - CameraPos.y, 0.0f);
    this->rail[2]->SetPos(RailPos02.x - CameraPos.x, RailPos02.y - CameraPos.y, 0.0f);
    this->rail[3]->SetPos(RailPos03.x - CameraPos.x, RailPos03.y - CameraPos.y, 0.0f);
    this->rail[4]->SetPos(RailPos04.x - CameraPos.x, RailPos04.y - CameraPos.y, 0.0f);
    this->rail[5]->SetPos(RailPos05.x - CameraPos.x, RailPos05.y - CameraPos.y, 0.0f);

    this->PushObject->SetPos(PushObjectPos00.x - CameraPos.x, PushObjectPos00.y - CameraPos.y, 0.0f);

    this->goal->SetPos(GoalPos.x - CameraPos.x, GoalPos.y - CameraPos.y, 0.0f);

    //描画用ブロックの座標更新
    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 300; drawnum++)//ゴール地面
    {
        if (0 <= drawnum <= 300 and (drawnum - 0) % 15 == 0)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(-1800.0f + posx - CameraPos.x, -1050.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 300; drawnum < 336; drawnum++)//ゴール上壁
    {
        if (300 <= drawnum <= 336 and (drawnum - 300) % 4 == 0)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(-750.0f + posx - CameraPos.x, 2050.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 336; drawnum < 651; drawnum++)//右床
    {
        if (336 <= drawnum <= 651 and (drawnum - 336) % 15 == 0)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(3050.0 + posx - CameraPos.x, -1100.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 651; drawnum < 1041; drawnum++)//右床
    {
        if (651 <= drawnum <= 1041 and (drawnum - 651) % 10 == 0)
        {
            posx = 0.0f;
            posy += 100.0f;
        }
        this->blockdraw[drawnum]->SetPos(4550.0 + posx - CameraPos.x, -1100.0f + posy - CameraPos.y, 0.0f);
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
    //左から順
    if (TurnBackFLG[0])
    {
        HookPos00.y -= HookMoveSpeed[1];
        HookCnt[0]++;

        if (HookCnt[0] == 150)
        {
            TurnBackFLG[0] = false;
        }

    }
    else
    {
        HookPos00.y += HookMoveSpeed[1];
        HookCnt[0]--;

        if (HookCnt[0] == 0)
        {
            TurnBackFLG[0] = true;
        }
    }


    if (TurnBackFLG[1])
    {
        HookPos01.y -= HookMoveSpeed[2];
        HookCnt[1]++;

        if (HookCnt[1] == 110)
        {
            TurnBackFLG[1] = false;
        }

    }
    else
    {
        HookPos01.y += HookMoveSpeed[2];
        HookCnt[1]--;

        if (HookCnt[1] == 0)
        {
            TurnBackFLG[1] = true;
        }
    }


    if (TurnBackFLG[2])
    {
        HookPos02.y -= HookMoveSpeed[3];
        HookCnt[2]++;

        if (HookCnt[2] == 175)
        {
            TurnBackFLG[2] = false;
        }

    }
    else
    {
        HookPos02.y += HookMoveSpeed[3];
        HookCnt[2]--;

        if (HookCnt[2] == 0)
        {
            TurnBackFLG[2] = true;
        }
    }


    if (TurnBackFLG[3])
    {
        HookPos03.y -= HookMoveSpeed[4];
        HookCnt[3]++;

        if (HookCnt[3] == 125)
        {
            TurnBackFLG[3] = false;
        }

    }
    else
    {
        HookPos03.y += HookMoveSpeed[4];
        HookCnt[3]--;

        if (HookCnt[3] == 0)
        {
            TurnBackFLG[3] = true;
        }
    }


    if (TurnBackFLG[4])
    {
        HookPos04.y -= HookMoveSpeed[5];
        HookCnt[4]++;

        if (HookCnt[4] == 225)
        {
            TurnBackFLG[4] = false;
        }

    }
    else
    {
        HookPos04.y += HookMoveSpeed[5];
        HookCnt[4]--;

        if (HookCnt[4] == 0)
        {
            TurnBackFLG[4] = true;
        }
    }


    if (MoveHookFLG)//一番右のフックの動き出し判定
    {
        if (TurnBackFLG[5])
        {
            HookPos05.y -= HookMoveSpeed[0];
            HookCnt[5]++;

            if (HookCnt[5] == 200)
            {
                TurnBackFLG[5] = false;
            }

        }
        else
        {
            HookPos05.y += HookMoveSpeed[0];
            HookCnt[5]--;

            if (HookCnt[5] == 0)
            {
                TurnBackFLG[5] = true;
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

    this->PushObject->SetColliderSize(DirectX::XMFLOAT3(PushObjectSize00.x, PushObjectSize00.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    auto& col1 = player->GetCollider();
    auto& colpush = PushObject->GetCollider();
    auto& colgoal = goal->GetCollider();
    auto& colwall = block[3]->GetCollider(); 

    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//当たり判定を入れる
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colHook = {//当たり判定を入れる
     hook[0]->GetCollider(),
     hook[1]->GetCollider(),
     hook[2]->GetCollider(),
     hook[3]->GetCollider(),
     hook[4]->GetCollider(),
     hook[5]->GetCollider(),
    };

    ColliderState = 0;
    StayGround = false;
    for (BlockNumber = 0; BlockNumber < 3; BlockNumber++)//当たり判定用ブロックの数
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            StayGround = true;
        }
    }

    for (HookNumber = 0; HookNumber < 6; HookNumber++)
    {
        if (col1.CheckCollision(colHook[HookNumber]))
        {
            ColliderState = 2;
            if (HookNumber == 5)
            {
                MoveHookFLG = true;
            }
        }
    }

    if (col1.CheckCollision(colgoal))
    {
        ColliderState = 3;
    }

    if (col1.CheckCollision(colpush))
    {
        ColliderState = 4;
    }

    if (col1.CheckCollision(colwall))
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
        else if (ColliderState == 2)//if ColliderState == 2 ->紫になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 3)//if ColliderState == 3 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->緑になる
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
        else if (ColliderState == 3)//if ColliderState == 3 ->黄色になる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else if (ColliderState == 4)//if ColliderState == 4 ->ピンクになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->緑になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }



    this->background->Update();
    this->player->Update();
    this->goal->Update();
    this->PushObject->Update();
    for (n = 0; n < 4; n++)//Updateの数
    {
        this->block[n]->Update();
    }

    for (n = 0; n < 6; n++)//Updateの数
    {
        this->hook[n]->Update();
    }


    for (drawnum = 0; drawnum < 100; drawnum++)//Updateの数
    {
        this->blockdraw[drawnum]->Update();

    }
}

/**	@brief 	シーン全体の描画
*/
void	Stage_10::Draw(void)
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
    this->PushObject->Draw();

    for (n = 0; n < 4; n++)//当たり判定用ブロック描画
    {
        this->block[n]->Draw();
    }

    for (n = 0; n < 6; n++)//当たり判定用ブロック描画
    {
        this->rail[n]->Draw();
    }

    for (n = 0; n < 6; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)//描画用ブロック描画
    {
        this->blockdraw[drawnum]->Draw();

    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_10::Finalize(void)
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
    SAFE_DELETE(this->goal);
    SAFE_DELETE(this->PushObject);
    for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }

    for (n = 0; n < 6; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 6; n++)
    {
        SAFE_DELETE(this->rail[n]);
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->player);

}
