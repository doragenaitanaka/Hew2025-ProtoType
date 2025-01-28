/**	@file	Stage_11.cpp
*	@brief 	Stage_11
*	@date 2024/12/19
*/
#include"Stage_11.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
/**	@brief 	コンストラクタ
*/
Stage_11::Stage_11()
{
    this->background = nullptr;
    this->player = nullptr;
    this->goal = nullptr;
    this->rail = nullptr;
    this->grabbox[0] = nullptr;
    this->grabbox[1] = nullptr;
    this->pendulum[0] = nullptr;
    this->pendulum[1] = nullptr;

    for (n = 0; n < 100; n++)//当たり判定用ブロックの初期化
    {
        this->block[n] = nullptr;
    }

    for (n = 0; n < 4; n++)
    {
        this->hook[n] = nullptr;
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
Stage_11::~Stage_11()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_11::Initialize(void)
{
    if (!this->background) { this->background = new Object; }
    if (!this->player) { this->player = new Player; }
    if (!this->goal) { this->goal = new Object; }
    if (!this->rail) { this->rail = new Object; }

    for (n = 0; n < 100; n++)
    {
        if (!this->block[n]) { this->block[n] = new Object; }//当たり判定用ブロックの初期化
    }

    for (n = 0; n < 2; n++)
    {
        if (!this->grabbox[n]) { this->grabbox[n] = new GrabBox; }//フックの初期化
    }

    for (n = 0; n < 2; n++)
    {
        if (!this->pendulum[n]) { this->pendulum[n] = new Pendulum; }//フックの初期化
    }

    for (n = 0; n < 4; n++)
    {
        if (!this->hook[n]) { this->hook[n] = new Object; }//フックの初期化
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
    this->rail->Init(L"Asset/block.png");

    for (n = 0; n < 100; n++)
    {
        this->block[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
    }

    for (n = 0; n < 2; n++)//ヨーヨー
    {
        this->grabbox[n]->Init(L"Asset/block.png");//当たり判定用のブロックテクスチャ
    }
    for (n = 0; n < 2; n++)//ヨーヨー
    {
        this->pendulum[n]->Init(L"Asset/block.png", 1, 1, 1, 0.0f);
    }
    for (n = 0; n < 4; n++)//フック
    {
        this->hook[n]->Init(L"Asset/block.png");//当たり判定用ブロックのテクスチャ
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
    
    this->grabbox[0]->SetPos(GrabboxPos00.x, GrabboxPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->grabbox[0]->SetPos(GrabboxPos01.x, GrabboxPos01.y, 0.0f);//当たり判定用ブロックの座標設定

    this->pendulum[0]->SetPos(YoyoPos00.x, YoyoPos00.y, 0.0f);//当たり判定用ブロックの座標設定
    this->pendulum[1]->SetPos(YoyoPos01.x, YoyoPos01.y, 0.0f);//当たり判定用ブロックの座標設定

    this->hook[0]->SetPos(HookPos00.x, HookPos00.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[1]->SetPos(HookPos01.x, HookPos01.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[2]->SetPos(HookPos02.x, HookPos02.y, 0.0f);//フックの当たり判定用ブロックの座標設定
    this->hook[3]->SetPos(HookPos03.x, HookPos03.y, 0.0f);//フックの当たり判定用ブロックの座標設定

    this->rail->SetPos(RailPos00.x, RailPos00.y, 0.0f);//レール当たり判定用ブロックの座標設定

    this->goal->SetPos(GoalPos.x, GoalPos.y, 0.0f);//当たり判定用ブロックの座標設定

    //オブジェクトのサイズを設定
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);
    this->rail->SetSize(RailSize00.x, RailSize00.y, 0.0f);//当たり判定用のブロックの大きさ設定

    this->block[0]->SetSize(BlockSize00.x, BlockSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[1]->SetSize(BlockSize01.x, BlockSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[2]->SetSize(BlockSize02.x, BlockSize02.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[3]->SetSize(BlockSize03.x, BlockSize03.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[4]->SetSize(BlockSize04.x, BlockSize04.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[5]->SetSize(BlockSize05.x, BlockSize05.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->block[3]->SetAngle(slopeAngle * 3);//坂道の角度

    this->grabbox[0]->SetSize(GrabboxSize00.x, GrabboxSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->grabbox[0]->SetSize(GrabboxSize01.x, GrabboxSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->pendulum[0]->SetSize(YoyoSize00.x, YoyoSize00.y, 0.0f);//当たり判定用ブロックの大きさ設定
    this->pendulum[1]->SetSize(YoyoSize01.x, YoyoSize01.y, 0.0f);//当たり判定用ブロックの大きさ設定

    this->hook[0]->SetSize(HookSize00.x, HookSize00.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定
    this->hook[3]->SetSize(HookSize03.x, HookSize03.y, 0.0f);//フックの当たり判定用ブロックの大きさ設定

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);//当たり判定用ブロックの大きさ設定
}

/**	@brief 	シーン全体の更新
*/
void	Stage_11::Update(void)
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
                if (ColliderState == 4)
                {
                    CameraPos.y += 10.0f;
                }
            }
        }
        if (this->p_input->Press("SPACE") && JumpState == 0)
        {
            JumpState = 1;
            this->grabbox[0]->Release();
            this->grabbox[1]->Release();
            GrabFlg = false;
        }

        if (ColliderState == 5)
        {
            if (this->p_input->Press("UP"))
            {
                //掴まる処理
                this->grabbox[0]->Grab(player);
                JumpState = 0;
                GrabFlg = true;
            }
        }
        if (ColliderState == 6)
        {
            if (this->p_input->Press("UP"))
            {
                //掴まる処理
                this->grabbox[1]->Grab(player);
                JumpState = 0;
                GrabFlg = true;
            }
        }

        if (this->p_input->Press("DOWN"))
        {
            //オブジェクトを離す処理
            this->grabbox[0]->Release();
            this->grabbox[1]->Release();
            GrabFlg = false;
        }

        if (ColliderState == 4)
        {
            CameraPos.x -= 20.0f;
            CameraPos.y -= 20.0f;
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

    this->rail->SetPos(RailPos00.x - CameraPos.x, RailPos00.y - CameraPos.y, 0.0f);

    this->goal->SetPos(GoalPos.x - CameraPos.x, GoalPos.y - CameraPos.y, 0.0f);

    if (GrabFlg)
    {
        if (ColliderState == 5)
        {
            this->CameraPos = this->GrabboxPos00;
        }
        else if(ColliderState == 6)
        {
            this->CameraPos = this->GrabboxPos01;
        }
    }
    //描画用ブロックの座標更新

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 0; drawnum < 105; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (0 <= drawnum <= 105 and (drawnum - 0) % 35 == 0)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(-1700.0f + posx - CameraPos.x, -200.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 105; drawnum < 145; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (105 <= drawnum <= 145 and (drawnum - 105) % 5 == 0)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(-1700.0f + posx - CameraPos.x, 2550.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 145; drawnum < 205; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (145 <= drawnum <= 205 and (drawnum - 145) % 6 == 0)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(-200.0f + posx - CameraPos.x, 3350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 205; drawnum < 265; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum == 216 || drawnum == 226 || drawnum == 235 || drawnum == 243 || drawnum == 250 || drawnum == 256 || drawnum == 261 || drawnum == 265)
        {
            posy -= 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(-700.0f + posx - CameraPos.x, 3350.0f + posy - CameraPos.y, 0.0f);
        posx += 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 265; drawnum < 301; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (drawnum == 273 || drawnum == 280 || drawnum == 286 || drawnum == 291 || drawnum == 295 || drawnum == 298 || drawnum == 300 || drawnum == 301)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(1300.0f + posx - CameraPos.x, 2650 + posy - CameraPos.y, 0.0f);
        posx -= 100.0f;
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 301; drawnum < 394; drawnum++)//当たり判定ブロックのblock[0]の範囲で小ブロックを描画
    {
        if (301 <= drawnum <= 394 and (drawnum - 301) % 3 == 0)
        {
            posy += 100.0f;
            posx = 0.0f;
        }
        this->blockdraw[drawnum]->SetPos(1400.0f + posx - CameraPos.x, 2550 + posy - CameraPos.y, 0.0f);
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
    if (TurnBackFLG)
    {
        HookPos02.x -= HookMoveSpeed;
        HookCnt++;

        if (HookCnt == 300)
        {
            TurnBackFLG = false;
        }

    }
    else
    {
        HookPos02.x += HookMoveSpeed;
        HookCnt--;

        if (HookCnt == 0)
        {
            TurnBackFLG = true;
        }
    }
    //-----------------------------------
    //ヨーヨーの動き処理
    //横の動き
    if (YoyoTurnFLG[0])
    {
        GrabboxPos00.x -= YoyoMoveSpeed;
        YoyoPos00.x -= YoyoMoveSpeed;
        YoyoCntX[0]++;
        if (YoyoCntX[0] == 200)
        {
            YoyoTurnFLG[0] = false;
        }
    }
    else
    {
        GrabboxPos00.x += YoyoMoveSpeed;
        YoyoPos00.x += YoyoMoveSpeed;
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
        YoyoPos00.y -= YoyoMoveSpeed;
        YoyoCntY[0]++;
        if (YoyoCntY[0] == 100)
        {
            YoyoTurnFLG[1] = false;
        }
    }
    else
    {
        GrabboxPos00.y += YoyoMoveSpeed;
        YoyoPos00.y += YoyoMoveSpeed;
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
        YoyoPos01.x -= YoyoMoveSpeed;
        YoyoCntX[1]++;
        if (YoyoCntX[1] == 200)
        {
            YoyoTurnFLG[2] = false;
        }
    }
    else
    {
        GrabboxPos01.x += YoyoMoveSpeed;
        YoyoPos01.x += YoyoMoveSpeed;
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
        YoyoPos01.y -= YoyoMoveSpeed;
        YoyoCntY[1]++;
        if (YoyoCntY[1] == 100)
        {
            YoyoTurnFLG[3] = false;
        }
    }
    else
    {
        GrabboxPos01.y += YoyoMoveSpeed;
        YoyoPos01.y += YoyoMoveSpeed;
        YoyoCntY[1]--;
        if (YoyoCntY[1] == 0)
        {
            YoyoTurnFLG[3] = true;
        }
    }
    //-----------------------------------
    if (GrabFlg)
    {
        this->grabbox[0]->Move(grabbox[0]->GetPos());
    }

    if (GrabFlg)
    {
        this->grabbox[1]->Move(grabbox[1]->GetPos());
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
    
    this->grabbox[0]->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize00.x, GrabboxSize00.y, 0.0f));
    this->grabbox[1]->SetColliderSize(DirectX::XMFLOAT3(GrabboxSize01.x, GrabboxSize01.y, 0.0f));

    this->pendulum[0]->SetColliderSize(DirectX::XMFLOAT3(YoyoSize00.x, YoyoSize00.y, 0.0f));
    this->pendulum[1]->SetColliderSize(DirectX::XMFLOAT3(YoyoSize01.x, YoyoSize01.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookSize01.x, HookSize01.y, 0.0f));

    this->rail->SetColliderSize(DirectX::XMFLOAT3(RailSize00.x, RailSize00.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x, GoalSize.y, 0.0f));

    auto& col1 = player->GetCollider();
    auto& colgoal = goal->GetCollider();
    auto& colslope = block[3]->GetCollider();

    std::vector<std::reference_wrapper<BaseCollider>> colblock = {//当たり判定を入れる
         block[0]->GetCollider(),
         block[1]->GetCollider(),
         block[2]->GetCollider(),
         block[3]->GetCollider(),
         block[4]->GetCollider(),
         block[5]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colYoyo = {//当たり判定を入れる
        pendulum[0]->GetCollider(),
        pendulum[1]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colbox = {//当たり判定を入れる
    grabbox[0]->GetCollider(),
    grabbox[1]->GetCollider(),
    };

    std::vector<std::reference_wrapper<BaseCollider>> colHook = {//当たり判定を入れる
         hook[0]->GetCollider(),
         hook[1]->GetCollider(),
         hook[2]->GetCollider(),
         hook[3]->GetCollider(),
    };



    ColliderState = 0;
    grabState = 0;
    StayGround = false;

    for (BlockNumber = 0; BlockNumber < 6; BlockNumber++)//当たり判定用ブロックの数
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            StayGround = true;
        }
    }

    for (HookNumber = 0; HookNumber < 4; HookNumber++)
    {
        if (col1.CheckCollision(colHook[HookNumber]))
        {
            ColliderState = 2;
        }
    }

    if (col1.CheckCollision(colgoal))
    {
        ColliderState = 3;
    }

    if (col1.CheckCollision(colslope))
    {
        ColliderState = 4;
    }

    for (HookNumber = 0; HookNumber < 4; HookNumber++)
    {
        if (col1.CheckCollision(colHook[HookNumber]))
        {
            ColliderState = 2;
        }
    }

    if (col1.CheckCollision(colYoyo[0]))
    {
        ColliderState = 5;
    }
    if (col1.CheckCollision(colYoyo[1]))
    {
        ColliderState = 6;
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
        else if (ColliderState == 4)//if ColliderState == 4 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->緑色になる
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
        else if (ColliderState == 4)//if ColliderState == 4 ->水色になる
        {
            player->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else if (ColliderState == 5)//if ColliderState == 5 ->オレンジになる
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        else if (ColliderState == 6)//if ColliderState == 6 ->緑色になる
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
    this->rail->Update();
    this->goal->Update();

    for (n = 0; n < 100; n++)//Updateの数
    {
        this->block[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->grabbox[n]->Update();
    }

    for (n = 0; n < 2; n++)//Updateの数
    {
        this->pendulum[n]->Update();
    }

    for (n = 0; n < 4; n++)//Updateの数
    {
        this->hook[n]->Update();
    }

    for (drawnum = 0; drawnum < 1000; drawnum++)//Updateの数
    {
        this->blockdraw[drawnum]->Update();

    }

    //SetPosをここでしないとプレイヤーに追従するため移動
    this->pendulum[0]->SetPos(YoyoPos00.x - CameraPos.x, YoyoPos00.y - CameraPos.y, 0.0f);
    this->pendulum[1]->SetPos(YoyoPos01.x - CameraPos.x, YoyoPos01.y - CameraPos.y, 0.0f);

    this->grabbox[0]->SetPos(GrabboxPos00.x - CameraPos.x, GrabboxPos00.y - CameraPos.y, 0.0f);
    this->grabbox[1]->SetPos(GrabboxPos01.x - CameraPos.x, GrabboxPos01.y - CameraPos.y, 0.0f);

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
    this->rail->Draw();

    for (n = 0; n < 6; n++)//当たり判定用ブロック描画
    {
        this->block[n]->Draw();
    }

    for (n = 0; n < 2; n++)//当たり判定用ブロック描画
    {
        this->pendulum[n]->Draw();
    }

    for (n = 0; n < 4; n++)//当たり判定用ブロック描画
    {
        this->hook[n]->Draw();
    }


    for (drawnum = 0; drawnum < 394; drawnum++)//描画用ブロック描画
    {
        this->blockdraw[drawnum]->Draw();
    }

    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_11::Finalize(void)
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
    SAFE_DELETE(this->goal);//Delete Object
    SAFE_DELETE(this->rail);//Delete Object

    for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }

    for (n = 0; n < 4; n++)
    {
        SAFE_DELETE(this->hook[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->grabbox[n]);
    }

    for (n = 0; n < 2; n++)
    {
        SAFE_DELETE(this->pendulum[n]);
    }

    for (drawnum = 0; drawnum < 1500; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);


    }
    SAFE_DELETE(this->player);

}
