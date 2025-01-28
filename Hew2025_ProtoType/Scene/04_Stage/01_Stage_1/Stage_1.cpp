/**	@file	Stage_1.cpp
*	@brief 	Stage_1
*	@date 2024/12/19
*/
#include"Stage_1.h"

#include"../../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>
#include <memory> 
/**	@brief 	コンストラクタ
*/
Stage_1::Stage_1()
{
   // std::unique_ptr<Object[]> blockdraw = std::make_unique<Object[]>(1000);
    this->background = nullptr;
    this->player = nullptr;
    this->playerdraw = nullptr;
    this->lefthand = nullptr;
    this->righthand = nullptr;
    this->leftleg = nullptr;
    this->rightleg = nullptr;
    this->eyes = nullptr;
    this->idle = nullptr;
    this->walking = nullptr;
    this->walking2 = nullptr;
    this->jump = nullptr;
    this->jump2 = nullptr;
    this->playercol = nullptr;
    this->playercol2 = nullptr;
    this->playercol3 = nullptr;
    this->newcol = nullptr;
  /*  for (n = 0; n < 8; n++)
    {
        this->block[n] = nullptr;
    }
    for (m = 0; m < 4; m++)
    {
        this->hook[m] = nullptr;
    }*/
    /*for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        this->blockdraw[drawnum] = nullptr;
    }*/
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
    if (!this->player) { this->player = new Player; }
    if (!this->playerdraw) { this->playerdraw = new Player; }
    if (!this->lefthand) { this->lefthand = new Object; }
    if (!this->righthand) { this->righthand = new Object; }
    if (!this->leftleg) { this->leftleg = new Object; }
    if (!this->rightleg) { this->rightleg = new Object; }
    if (!this->eyes) { this->eyes = new Object; }
    if (!this->idle) { this->idle = new Object; }
    if (!this->walking) { this->walking = new Object; }
    if (!this->walking2) { this->walking2 = new Object; }
    if (!this->jump) { this->jump = new Object; }
    if (!this->jump2) { this->jump2 = new Object; }

    if (!this->playercol) { this->playercol = new Object; }
    if (!this->playercol2) { this->playercol2 = new Object; }
    if (!this->playercol3) { this->playercol3 = new Object; }
    if (!this->newcol) { this->newcol = new Object; }
    for (n = 0; n < 8; n++)
    {
        if (!this->block[n]) {
            this->block[n] = std::make_shared<Object>();
        }
    }
    for (m = 0; m < 4; m++)
    {
        if (!this->hook[m]) {
            this->hook[m] = std::make_shared<Object>();
        }
        if (!this->hookdraw[m]) {
            this->hookdraw[m] = std::make_shared<Object>();
        }
    }
 
    for (drawnum = 0; drawnum < 768; drawnum++)
    {
        if (!this->blockdraw[drawnum]) {
            this->blockdraw[drawnum] = std::make_shared<Object>();
        }
        
    }

    if (!this->goal) { this->goal = new Object; }
    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    //オブジェクト
    this->background->Init(L"Asset/back_img_01.png");
    this->player->Init(L"Asset/block.png");
    this->playerdraw->Init(L"Asset/gumbody.png");
    this->eyes->Init(L"Asset/gum_eyes.png");
    this->lefthand->Init(L"Asset/left_hand.png");
    this->righthand->Init(L"Asset/right_hand.png");
    this->leftleg->Init(L"Asset/left_leg.png");
    this->rightleg->Init(L"Asset/right_leg.png");

    this->idle->Init(L"Asset/idle 3.png",4,1);
    this->walking->Init(L"Asset/walking_2.png", 4, 1);
    this->walking2->Init(L"Asset/walking_3.png", 4, 1);
    this->jump->Init(L"Asset/jump_3.png",5,1);
    this->jump2->Init(L"Asset/jump_4.png",5,1);

    this->playercol->Init(L"Asset/block.png");
    this->playercol2->Init(L"Asset/block.png");
    this->playercol3->Init(L"Asset/block.png");
    this->newcol->Init(L"Asset/block.png");
    this->goal->Init(L"Asset/goal4.png");

    for (n = 0; n < 8; n++)
    {
        this->block[n]->Init(L"Asset/block.png");
    }
    for (m = 0; m < 4; m++)
    {
        this->hook[m]->Init(L"Asset/fook.png");
        this->hookdraw[m]->Init(L"Asset/fook.png");
    }
    for (drawnum = 0; drawnum < 760; drawnum++)
    {
        this->blockdraw[drawnum]->Init(L"Asset/lightwood2.png");
    }
    for (drawnum = 760; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->Init(L"Asset/darkwood2.png");
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
    this->player->SetPos(PlayerPos.x, PlayerPos.y, 0.0f);
    this->playercol->SetPos(PlayerPos.x, PlayerPos.y, 0.0f);
    this->playercol2->SetPos(PlayerPos.x, PlayerPos.y, 0.0f);
    this->playercol3->SetPos(PlayerPos.x, PlayerPos.y, 0.0f);
    this->newcol->SetPos(PlayerPos.x, PlayerPos.y, 0.0f);



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

   /* for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->SetPos(0.0f, -1000.0f, 0.0f);
    }*/

    //オブジェクトのサイズを設定
    this->background->SetSize(1920.0f, 1080.0f, 0.0f);
    this->player->SetSize(PlayerSize.x, PlayerSize.y, 0.0f);

        this->playerdraw->SetSize(PlayerDrawSize.x, PlayerDrawSize.y, 0.0f);
        this->eyes->SetSize(EyesSize.x, EyesSize.y, 0.0f);
        this->lefthand->SetSize(LefthandSize.x, LefthandSize.y, 0.0f);
        this->leftleg->SetSize(LeftlegSize.x, LeftlegSize.y, 0.0f);
        this->righthand->SetSize(RighthandSize.x, RighthandSize.y, 0.0f);
        this->rightleg->SetSize(RightlegSize.x, RightlegSize.y, 0.0f);

        this->idle->SetSize(IdleSize.x+20.0f, IdleSize.y + 20.0f, 0.0f);

        this->walking->SetSize(IdleSize.x, IdleSize.y, 0.0f);
        this->walking2->SetSize(IdleSize.x, IdleSize.y, 0.0f);

        this->jump->SetSize(IdleSize.x, IdleSize.y, 0.0f);

        this->jump2->SetSize(IdleSize.x, IdleSize.y, 0.0f);

    this->playercol->SetSize(PlayerColSize.x, PlayerColSize.y, 0.0f);
    this->playercol2->SetSize(PlayerColSize2.x, PlayerColSize2.y, 0.0f);
    this->playercol3->SetSize(PlayerColSize3.x, PlayerColSize3.y, 0.0f);
    this->newcol->SetSize(NewColSize.x, NewColSize.y, 0.0f);

    this->block[0]->SetSize(BlockSize01.x, BlockSize01.y, 0.0f);
    this->block[1]->SetSize(BlockSize02.x, BlockSize02.y, 0.0f);
    this->block[2]->SetSize(BlockSize03.x, BlockSize03.y, 0.0f);
    this->block[3]->SetSize(BlockSize04.x, BlockSize04.y, 0.0f);
    this->block[4]->SetSize(BlockSize05.x, BlockSize05.y, 0.0f);
    this->block[5]->SetSize(BlockSize06.x, BlockSize06.y, 0.0f);
    this->block[6]->SetSize(BlockSize07.x, BlockSize07.y, 0.0f);
    this->block[7]->SetSize(BlockSize08.x, BlockSize08.y, 0.0f);

    this->goal->SetSize(GoalSize.x, GoalSize.y, 0.0f);

   
        this->hook[0]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
        this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
        this->hook[2]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
        this->hook[3]->SetSize(HookSize01.x, HookSize01.y, 0.0f);


        this->hookdraw[0]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
        this->hookdraw[1]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
        this->hookdraw[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
        this->hookdraw[3]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->SetSize(100.0f, 100.0f, 0.0f);
    }
    Vx = 0.0f;
    Vy = 0.0f;
    t = 0;
    t2 = 0;
    jumpstate = 0;
    HookColliderState = -1;
}

/**	@brief 	シーン全体の更新
*/
void	Stage_1::Update(void)
{
    this->p_input->Update();

    p_input->GetLeftAnalogStick();
    ScenechangeState = false;
    //----------------------------------------------
    // Creative Mode
    //----------------------------------------------
    if (gamemode == 0)
    {
        if (this->p_input->Press("CHANGEMODE1"))
        {
            gamemode = 1;
        }
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

    /*
	XMFLOAT2 EyesPos = { 0.0f, +50.0f };
	XMFLOAT2 EyesSize = { 30.0f,30.0f };

	XMFLOAT2 LefthandPos = { -50.0f,0.0f };
	XMFLOAT2 LefthandSize = { 30.0f,30.0f };

	XMFLOAT2 LeftlegPos = { -50.0f, -50.0f };
	XMFLOAT2 LeftlegSize = { 30.0f,30.0f };

	XMFLOAT2 RighthandPos = { 50.0f, 0.0f };
	XMFLOAT2 RighthandSize = { 30.0f,30.0f };

	XMFLOAT2 RightlegPos = { 50.0f, -50.0f };*/



    //-----------------------------------------------------
    //  座標更新
    //-----------------------------------------------------
    this->player->SetPos(PlayerPos.x - CameraPos2.x, PlayerPos.y - CameraPos2.y, 0.0f);

    
    this->idle->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y-10.0f, 0.0f);
    this->walking->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y - 10.0f, 0.0f);
    this->walking2->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y - 10.0f, 0.0f);
    this->jump->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y - 30.0f, 0.0f);
    this->jump2->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y - 30.0f, 0.0f);

    this->eyes->SetPos(PlayerPos.x+ EyesPos.x - CameraPos2.x, PlayerPos.y + EyesPos.y - CameraPos2.y, 0.0f);
    this->lefthand->SetPos(PlayerPos.x+ LefthandPos.x - CameraPos2.x, PlayerPos.y + LefthandPos.y - CameraPos2.y, 0.0f);
    this->leftleg->SetPos(PlayerPos.x+ LeftlegPos.x - CameraPos2.x, PlayerPos.y+ LeftlegPos.y - CameraPos2.y, 0.0f);
    this->righthand->SetPos(PlayerPos.x+ RighthandPos.x - CameraPos2.x, PlayerPos.y+ RighthandPos.y - CameraPos2.y, 0.0f);
    this->rightleg->SetPos(PlayerPos.x+ RightlegPos.x - CameraPos2.x, PlayerPos.y + RightlegPos.y - CameraPos2.y, 0.0f);

    this->playerdraw->SetPos(PlayerPos.x + PlayerDrawPos.x - CameraPos2.x, PlayerPos.y + PlayerDrawPos.y - CameraPos2.y, 0.0f);//PlayerPos+-x
    this->playercol->SetPos(PlayerColPos.x - CameraPos2.x, PlayerColPos.y - CameraPos2.y, 0.0f);
    this->playercol2->SetPos(PlayerColPos2.x - CameraPos2.x, PlayerColPos2.y - CameraPos2.y, 0.0f);
    this->playercol3->SetPos(PlayerColPos3.x - CameraPos2.x, PlayerColPos3.y - CameraPos2.y, 0.0f);
    this->newcol->SetPos(NewColPos.x - CameraPos2.x, NewColPos.y - CameraPos2.y, 0.0f);
    this->newcol->SetSize(NewColSize.x , NewColSize.y, 0.0f);
    this->player->SetAngle(PlayerAngle);
    this->playerdraw->SetAngle(PlayerAngle);
    this->block[0]->SetPos(BlockPos01.x - CameraPos.x - CameraPos2.x, BlockPos01.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[1]->SetPos(BlockPos02.x - CameraPos.x - CameraPos2.x, BlockPos02.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[2]->SetPos(BlockPos03.x - CameraPos.x - CameraPos2.x, BlockPos03.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[3]->SetPos(BlockPos04.x - CameraPos.x - CameraPos2.x, BlockPos04.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[4]->SetPos(BlockPos05.x - CameraPos.x - CameraPos2.x, BlockPos05.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[5]->SetPos(BlockPos06.x - CameraPos.x - CameraPos2.x, BlockPos06.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[6]->SetPos(BlockPos07.x - CameraPos.x - CameraPos2.x, BlockPos07.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->block[7]->SetPos(BlockPos08.x - CameraPos.x - CameraPos2.x, BlockPos08.y - CameraPos.y - CameraPos2.y, 0.0f);

    this->hook[0]->SetPos(HookPos01.x - CameraPos.x - CameraPos2.x, HookPos01.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->hook[1]->SetPos(HookPos02.x - CameraPos.x - CameraPos2.x, HookPos02.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->hook[2]->SetPos(HookPos03.x - CameraPos.x - CameraPos2.x, HookPos03.y - CameraPos.y - CameraPos2.y, 0.0f);
    this->hook[3]->SetPos(HookPos04.x - CameraPos.x - CameraPos2.x, HookPos04.y - CameraPos.y - CameraPos2.y, 0.0f);

    this->hookdraw[0]->SetPos(HookPos01.x - CameraPos.x - CameraPos2.x, HookPos01.y - CameraPos.y - CameraPos2.y+80.0f, 0.0f);
    this->hookdraw[1]->SetPos(HookPos02.x - CameraPos.x - CameraPos2.x, HookPos02.y - CameraPos.y - CameraPos2.y + 80.0f, 0.0f);
    this->hookdraw[2]->SetPos(HookPos03.x - CameraPos.x - CameraPos2.x, HookPos03.y - CameraPos.y - CameraPos2.y + 80.0f, 0.0f);
    this->hookdraw[3]->SetPos(HookPos04.x - CameraPos.x - CameraPos2.x, HookPos04.y - CameraPos.y - CameraPos2.y + 80.0f, 0.0f);
    this->goal->SetPos(GoalPos.x - CameraPos.x - CameraPos2.x, GoalPos.y - CameraPos.y - CameraPos2.y, 0.0f);

    
    //-----------------------------------------------------
//  UV
//-----------------------------------------------------
// 
// 
    //this->idle->splitX = 5;
    //this->idle->numU = 1;
   this->idle->SetTextureNumV(-0.0);


  /* idletime += 1;
   if (idletime % 4 == 0)
   {
       u += 1;
   }*/

    
    if (u > 3)
    {
        u=0;
    }
    this->idle->SetTextureNumU(u);
    this->walking->SetTextureNumU(u);
    this->walking2->SetTextureNumU(u);
  
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
            this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x-CameraPos2.x, -350.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 50)
        {
            this->blockdraw[drawnum]->SetPos(-2950.0f + posx - CameraPos.x-CameraPos2.x, -350.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }

    }
    posx = 0;
    posy = 0.0f;
    for (drawnum = 100; drawnum < 200; drawnum++)//block2 draw
    {
        if (drawnum == 125 || drawnum == 150 || drawnum == 175)
        {
            posx = 0.0f;
        }
        if (drawnum < 125)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x-CameraPos2.x, 50.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 125 && drawnum < 150)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x-CameraPos2.x, -50.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 150 && drawnum < 175)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x-CameraPos2.x, -150.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 175 && drawnum < 200)
        {
            this->blockdraw[drawnum]->SetPos(1250.0f + posx - CameraPos.x-CameraPos2.x, -250.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
    }
    posx = 0;
    posy = 0.0f;
    for (drawnum = 200; drawnum < 300; drawnum++)//block3 draw
    {
        if (drawnum == 225 || drawnum == 250 || drawnum == 275)
        {
            posx = 0.0f;
        }
        if (drawnum < 225)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x-CameraPos2.x, 450.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 225 && drawnum < 250)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x-CameraPos2.x, 350.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 250 && drawnum < 275)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x-CameraPos2.x, 250.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 275 && drawnum < 300)
        {
            this->blockdraw[drawnum]->SetPos(1650.0f + posx - CameraPos.x-CameraPos2.x, 150.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
    }

    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 300; drawnum < 320; drawnum++)//block4 draw
    {
        this->blockdraw[drawnum]->SetPos(2450.0f + posx - CameraPos.x-CameraPos2.x, 550.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
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
            this->blockdraw[drawnum]->SetPos(2650.0f + posx - CameraPos.x-CameraPos2.x, 750.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
            posx += 100.0f;
        }
        else if (drawnum >= 340 && drawnum < 360)
        {
            this->blockdraw[drawnum]->SetPos(2650.0f + posx - CameraPos.x-CameraPos2.x, 650.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
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
        this->blockdraw[drawnum]->SetPos(2950.0f + posx - CameraPos.x-CameraPos2.x, 2750.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
        posx += 100.0f;

    }
    posx = 0.0f;
    posy = 0.0f;
    for (drawnum = 760; drawnum < 768; drawnum++)//block3 draw
    {

        this->blockdraw[drawnum]->SetPos(450.0f + posx - CameraPos.x-CameraPos2.x, 1250.0f + posy- CameraPos.y-CameraPos2.y, 0.0f);
        posx += 100.0f;

    }
    //-----------------------------------
    //Collider更新
    //-----------------------------------
    this->player->SetColliderSize(DirectX::XMFLOAT3(PlayerSize.x, PlayerSize.y , 0.0f));
 
    this->playercol->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize.x, PlayerColSize.y, 0.0f));
    this->playercol3->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize3.x, PlayerColSize3.y, 0.0f));
    this->playercol2->SetColliderSize(DirectX::XMFLOAT3(PlayerColSize2.x , PlayerColSize2.y, 0.0f));
    this->newcol->SetColliderSize(DirectX::XMFLOAT3(NewColSize.x, NewColSize.y, 0.0f));

    this->block[0]->SetColliderSize(DirectX::XMFLOAT3(BlockSize01.x, BlockSize01.y, 0.0f));
    this->block[1]->SetColliderSize(DirectX::XMFLOAT3(BlockSize02.x, BlockSize02.y, 0.0f));
    this->block[2]->SetColliderSize(DirectX::XMFLOAT3(BlockSize03.x, BlockSize03.y, 0.0f));
    this->block[3]->SetColliderSize(DirectX::XMFLOAT3(BlockSize04.x, BlockSize04.y, 0.0f));
    this->block[4]->SetColliderSize(DirectX::XMFLOAT3(BlockSize05.x, BlockSize05.y, 0.0f));
    this->block[5]->SetColliderSize(DirectX::XMFLOAT3(BlockSize06.x, BlockSize06.y, 0.0f));
    this->block[6]->SetColliderSize(DirectX::XMFLOAT3(BlockSize07.x, BlockSize07.y, 0.0f));
    this->block[7]->SetColliderSize(DirectX::XMFLOAT3(BlockSize08.x, BlockSize08.y, 0.0f));

    this->hook[0]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[1]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[2]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));
    this->hook[3]->SetColliderSize(DirectX::XMFLOAT3(HookColSize01.x, HookColSize01.y, 0.0f));

    this->goal->SetColliderSize(DirectX::XMFLOAT3(GoalSize.x-60.0f, GoalSize.y-50.0f, 0.0f));

    auto& col1 = player->GetCollider();
    auto& col2 = playercol->GetCollider();
    auto& col5 = playercol3->GetCollider();
    auto& col3=newcol->GetCollider();
    auto& col4 = playercol2->GetCollider();
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
    PlayerColState = 0;
    PlayerColState3 = 0;
    PlayerColState2 = 0;
    NewColState = -1;
    HookColliderState = -1;
    for (BlockNumber = 0; BlockNumber < 8; BlockNumber++)
    {
        if (col1.CheckCollision(colblock[BlockNumber]))
        {
            ColliderState = 1;//block collider

        }
        if (col2.CheckCollision(colblock[BlockNumber]))
        {
            PlayerColState = 1;//block collider

        }
        if (col4.CheckCollision(colblock[BlockNumber]))
        {
            PlayerColState2 = 1;//block collider

        }
        if (col5.CheckCollision(colblock[BlockNumber]))
        {
            PlayerColState3 = 1;//block collider

        }
        if (col3.CheckCollision(colblock[BlockNumber]))
        {
            NewColState = BlockNumber;//block collider


        }
       
    }

    for (HookNumber = 0; HookNumber < 4; HookNumber++)
    {
        if (col1.CheckCollision(colhook[HookNumber]))
        {
            HookColliderState = HookNumber;//;hook collider
            ColliderState = 2;
        }
        //if (col2.CheckCollision(colhook[HookNumber]))
        //{
        //    HookColliderState = HookNumber;//;hook collider
        //    PlayerColState = 2;
        //}
    }

    if (col1.CheckCollision(colgoal))
    {
        //animetion-> t++ -> scene+1
      ScenechangeState2 = 1;
        //ColliderState = 3;//goal collider

    }



    if (gamemode == 0)//Creative Mode
    {
        if (ColliderState == 1)
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.5f));
        }
        else if (ColliderState == 2)
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.5f));
        }
        else if (ColliderState == 3)
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.5f));
        }
        else
        {
            player->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.5f));
        }
    }
    //----------------------------------------------
   // Player Mode
   //----------------------------------------------
    if (gamemode == 1)
    {
        PlayerGrabPos.x = 0.0f;
        PlayerGrabPos.y = 0.0f;


        
        
        /*if (grabstate == 0)
        {
            PlayerAngle = 0.0f;
        }*/
        if (CameraPos.x <= -1100.0f)
        {
            CameraPos.x = -1100.0f;
       }
        if (CameraPos.y <= -1100.0f)
        {
            this->p_sceneManager->ChangeScene(Scene::Stage_1);
            return;
        }
        movestate = 0;

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
        if (this->p_input->Press("CHANGEMODE0"))
        {
            gamemode = 0;
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
                CameraPos.x += 0.0f;
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
                ustate = 0;
                Vx2 = -1;
                idletime += 1;
                if (idletime % 5 == 0 && jumpstate != 1 &&superjumpstate == 0)
                {
                    u += 1;
                }

                if (Vx2 <0&&PlayerColState3==1&& grabstate == 0)
                {
                    movestate = 1;

                }
                else
                {
                    movestate = 0;
                }
                if (movestate != 1)
                {
                    CameraPos.x -= 7.0f;
                }


            }
            if (p_input->GetLeftAnalogStick().x * 10.0f <= 2.0f && p_input->GetLeftAnalogStick().x * 10.0f >= -2.0f)
            {
                if (ustate == 0)
                {
                    u = 0;
                    ustate = 1;
                }
                CameraPos.x += 0.0f;
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
                ustate = 0;
                Vx2 = 1;
                idletime += 1;
                if (idletime % 5 == 0&&jumpstate!=1&&superjumpstate == 0)
                {
                    u += 1;
                }
                if (Vx2>0&&PlayerColState == 1 && grabstate == 0)
                {
                    movestate = 2;

                }
                else
                {
                    movestate = 0;
                }

                if (movestate != 2)
                {
                    CameraPos.x += 7.0f;
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
                PlayerGrabPos.x = -35.0f *p_input->GetRightAnalogStick().x/z;
                PlayerGrabPos.y = -35.0f * p_input->GetRightAnalogStick().y / z -5.0f;




                






                if (player->y3 != z * -2.8f)
                {
                    this->player->y3 += (z * -2.8f - player->y3) / 20;
                    this->playerdraw->y3 += (z * -2.8f - playerdraw->y3) / 20;
                }
                PlayerAngle = radians * 180.0f / 3.1415926 + a;


                if (PlayerAngle >= 90 && PlayerAngle < 180.0f)
                {
                    eyesy = 90.0f - this->player->y3 * 80*std::pow(sin(radians), 1.9f);
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
                    lefthandx = -65.0f - this->player->y3 * 90 * -std::pow(std::abs(cos(radians)), 2.4f) - this->player->y3 * 12 * std::pow(std::abs(cos(radians)),1.10f) - this->player->y3 * 3 * -std::pow(std::abs(cos(radians)), 0.2f);
                    

                    righthandy = 15.0f - this->player->y3 * 30 * -std::pow(std::abs(sin(radians)), 3.50f);
                    righthandx = 66.0f - this->player->y3 * 26 * -std::pow(std::abs(cos(radians)), 0.75f) - this->player->y3 * 12 * std::pow(std::abs(cos(radians)), 2.0f);

                    leftlegy = -39.0f - this->player->y3 * 95 * -std::pow(std::abs(sin(radians)),1.4f) - this->player->y3 *20 * std::pow(std::abs(sin(radians)), 4.0f) - this->player->y3 * 4 * -std::pow(std::abs(sin(radians)), 7.0f);
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
                    eyesx = 0.0f - this->player->y3 * 45 * std::pow(std::abs(cos(radians)),3.8f);//8角度

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
              ScenechangeState = true;
                t2 = 0;
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
        //if (powerstate == 1)
        //{
        //  
        //    if (player->y3 >= -2.0f && player->y3 <= 0.0f)//z
        //    {
        //        this->player->y3 -= 0.02f;
        //    }
        //    else if (player->y3 < -2.0f)
        //    {
        //        this->player->y3 = -2.0f;
        //    }

        //}
        //else
        //{
        //    if (player->y3 <= 0.0f)
        //    {
        //        this->player->y3 += 0.1f;

        //    }
        //    if (player->y3 + 0.6f > 0.0f)
        //    {
        //        this->player->y3 = 0.0f;
        //    }

        //}
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
            
            if (movestate2 == 1 &&PlayerColState==1&& grabstate == 0)
            {
                movestate = 1;
              
            }
            else
            {
                movestate = 0;
            }
            if (movestate != 1)
            {
                CameraPos.x -= 7.0f;
            }
         
           
        }
        if (this->p_input->Press("RIGHT"))
        {
            idletime += 1;
            if (idletime %5 == 0)
            {
                u += 1;
            }
            if (PlayerColState != 1)
            {
                movestate2 = 2;
            }
            if (movestate2==2 && PlayerColState == 1 && grabstate == 0)
            {
                movestate = 2;
                
            }
            else
            {
                movestate = 0;
            }
            if (movestate != 2)
            {
                CameraPos.x += 7.0f;
            }
           /* if (grabstate == 0 && PlayerColState != 1)
            {
                CameraPos.x += 7.0f;
            }
            else if (grabstate == 1)
            {
                PlayerAngle += 1.0f;
            }*/
            
            //}
        }
        /*if (!(GetAsyncKeyState(VK_DOWN)))
        {
            if (player->y3 <= 0.0f)
            {
                this->player->y3 += 0.6f;

            }
            if (player->y3 + 0.6f > 0.0f)
            {
                this->player->y3 = 0.0f;
            }


        }*/
        if (GetAsyncKeyState(VK_DOWN))
        {
            //this->p_player->x3 += 0.01f; //座標更新
            if (player->y3 >= -4.0f && player->y3 <= 0.0f)
            {
                this->player->y3 -= 0.04f;
                this->playerdraw->y3 -= 0.04f;
            }
            else if (player->y3 < -4.0f)
            {
                this->player->y3 = -4.0f;
                this->playerdraw->y3 = -4.0f;
               this->p_sceneManager->ChangeScene(Scene::Stage_1);
                return;
          
            }
        }
       
        if (this->p_input->Press("LEFT2"))
        {
            PlayerAngle-= 1.0f;
           
        }
      
       
        if (this->p_input->Press("RIGHT2"))
        {
            PlayerAngle += 1.0f;
        }
       
        if (this->p_input->Press("SPACE")&&t==0 && grabstate ==0&&jumpkeystate==0 )
        {
            
            Vy = 20.0f;
            jumpkeystate = 1;
            jumpstate = 1;
        }

        if (this->p_input->Press("SUPERJUMP") && t == 0&&grabstate==1)
        {
            
            pullstate = 0;
            Vypower = std::pow(std::abs(p_input->GetRightAnalogStick().y * 3000.0f), 0.3f);
            

            Vxpower = std::pow( std::abs(p_input->GetRightAnalogStick().x * 3000.0f),0.3f );

           // Vy = Vypower * 2.3f;

            if (p_input->GetRightAnalogStick().y > 0)
            {
                Vy = Vypower * -1.35f;
            }
            else if (p_input->GetRightAnalogStick().y < 0)
            {
                Vy= Vypower * 2.25f;
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
        //if (t>0&&t <= 4.0f)
        //{
        //    PlayerPos.y += Vy*Vy/g;
        //    //CameraPos.y += Vy;
        //}
        /*if (t = 1)
        {
            CameraPos.y += Vy;
        }*/
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
               
            Vdelta= Vdown2 - (Vy * t - Vdown);
           
            if (NewColState != -1)
            {
                Vnew = PlayerPos.y - (PlayerSize.y+30.0f) / 2 - block[NewColState]->GetSize().y / 2 - block[NewColState]->GetPos().y + 20.0f;
                /*if (Vdelta  <= -5.0f)
                {
                    Vdelta = -5.0f;
                }*/
            }
            else
            {
                Vnew = 0;
            }
            if (NewColState != -1 && std::abs(Vdelta) > std::abs(Vnew) && Vdelta < 0)
            {

                CameraPos.y -= Vnew + 1.0f;
                NewColState = -1;
            }
            else
            {
                if (Vdelta <= -13.0f)
                {
                    Vdelta = -13.0f;

                }
                    CameraPos.y += Vdelta;
                
            }
            //CameraPos.y -= 0.01f*g * t * t;               
            NewColSize.y = std::abs(Vdelta) * 18.0;

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
                    CameraPos.x += Vx;
                }
                /* if (grabstate == 0 && PlayerColState != 1)
                 {
                     CameraPos.x += 7.0f;
                 }
                 else if (grabstate == 1)
                 {
                     PlayerAngle += 1.0f;
                 }*/

                 //}
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
                    CameraPos.x += Vx;
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
            NewColSize.y = 0;
            Vx = 0;
        }
        if (t <= 0)
        {
            superjumpstate = 0;
        }
        
        
      

        //for (BlockNumber = 0; BlockNumber < 8; BlockNumber++)
        //{
        //    if (CameraPos.y - 1.0f)
        //    {
        //        if (col1.CheckCollision(colblock[BlockNumber]));//block collider
        //        {
        //            jumpstate = 0;
        //            t = 0;
        //            Vdown = 0;
        //            Vy = 0;
        //        }
        //    }
        //}
        if (jumpstate == 1 && ColliderState == 1)
        {
            jumpstate = 0;
            t = 0;
            Vdown = 0;
            Vy = 0;
            jumpkeystate = 0;
        }
        /*else if (jumpstate == 1 && PlayerColState == 1 && Vdelta > 0)
        {

        }*/
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

        
        

        if (HookColliderState!=-1&&superjumpstate!=1&&grabstate!=2)
        {
            PlayerPos.x = hook[HookColliderState]->GetPos().x+CameraPos2.x;
            PlayerPos.y = hook[HookColliderState]->GetPos().y+150.0f+ CameraPos2.y;
            jumpstate = 0;
            grabstate = 1;
            t = 0;
            Vdown = 0;
            Vy = 0;
           HookColliderState = -1;
        }
       else if (HookColliderState != -1 && superjumpstate != 1 && pullstate == 1)
        {
           
            jumpstate = 0;
            grabstate = 1;
            t = 0;
            Vdown = 0;
            Vy = 0;  
                PlayerPos.x = hook[HookColliderState]->GetPos().x- 200 * cos(p_input->GetRightAnalogStick().x);
                PlayerPos.y = hook[HookColliderState]->GetPos().y + 150.0f;
                CameraPos.x += 20 * cos(p_input->GetRightAnalogStick().x);
            
        }
        
            if (PlayerPos.x != 0)
            {
                CameraPos.x += PlayerPos.x;
                PlayerPos.x = 0;
            }
            else
            {
                PlayerPos.x = 0;

            }
            if (PlayerPos.y != -150.0f)
            {
                CameraPos.y += PlayerPos.y;
                PlayerPos.y = -150.0f;
            }
            else
            {
                PlayerPos.y = -150.0f;

            }
        
      if (pullstate == 2)
        {
            if (CameraPos2.x != -50 * p_input->GetRightAnalogStick().x)
            {
                CameraPos2.x += -50 * p_input->GetRightAnalogStick().x/10;
            }
            else if(CameraPos2.x == -50 * p_input->GetRightAnalogStick().x)
            {
                CameraPos2.x = -50 * p_input->GetRightAnalogStick().x / 10;
            }
            if (CameraPos2.y != -26 * p_input->GetRightAnalogStick().y)
            {
                CameraPos2.y += -26 * p_input->GetRightAnalogStick().y / 10;
            }
            else if (CameraPos2.y == -26 * p_input->GetRightAnalogStick().y)
            {
                CameraPos2.y = -26 * p_input->GetRightAnalogStick().y / 10;
            }
            Camera2xdelta = CameraPos2.x;
            Camera2ydelta = CameraPos2.y;

        }
        else if(pullstate == 0)
        {
           
            if (CameraPos2.x != 0)
            {
                CameraPos2.x = CameraPos2.x-CameraPos2.x /4;
            }
            else if(CameraPos2.x <=3.0f&& CameraPos2.x >= -3.0f)
            {
                CameraPos2.x = 0;
            }

            if (CameraPos2.y != 0)
            {
                CameraPos2.y = CameraPos2.y - CameraPos2.y / 4;
            }
            else if (CameraPos2.y <= 3.0f && CameraPos2.y >= -3.0f)
            {
                CameraPos2.y = 0;
            }

        }











        if (CameraPos2.x < -100.0f)
        {
            CameraPos2.x = -100.0f;
        }
        if (CameraPos2.x > 100.0f)
        {
            CameraPos2.x = 100.0f;
        }
        if (CameraPos2.y < -52.0f)
        {
            CameraPos2.y = -52.0f;
        }
        if (CameraPos2.y > 52.0f)
        {
            CameraPos2.y = 52.0f;
        }
        if (pullstate == 1)
        {
            
                if (PlayerPos.x != 20*cos(p_input->GetRightAnalogStick().x))
                {
                    CameraPos.x += 20 * cos(p_input->GetRightAnalogStick().x)/5;
                    PlayerPos.x = 20 * cos(p_input->GetRightAnalogStick().x)/5;
                     PlayerColPos.x = 10.0f;
                     PlayerColPos2.x = 10.0f;
                     NewColPos.x = 10.0f;
                }
                else
                {
                    PlayerPos.x = 20 * cos(p_input->GetRightAnalogStick().x);
                      PlayerColPos.x = 10.0f;
                      PlayerColPos2.x = 10.0f;
                      NewColPos.x = 10.0f;

                }
                if (PlayerPos.y != -150.0f)
                {
                    CameraPos.y += PlayerPos.y;
                    PlayerPos.y = -150.0f;
                    PlayerColPos.x = -150.0f;
                    PlayerColPos2.x = -150.0f;
                    NewColPos.x = -150.0f;
                }
                else
                {
                    PlayerPos.y = -150.0f;
                    PlayerColPos.x = -150.0f;
                    PlayerColPos2.x = -150.0f;
                    NewColPos.x = -150.0f;
                }



                /*  CameraPos.x += 100.0f;
                  PlayerPos.x+= -100.0f;
                  PlayerColPos.x += -100.0f;
                  PlayerColPos2.x += -100.0f;
                  NewColPos.x += -100.0f;
                  CameraPos.y += 100.0f;
                  PlayerPos.y += -100.0f;
                  PlayerColPos.y += -100.0f;
                  PlayerColPos2.y += -100.0f;
                  NewColPos.y += -100.0f;*/
               
            
        }
        else
        {
            t3 = 0;
        }
            
            
        
        /*if (PlayerPos.x <0)
        {
            CameraPos.x -= 10.0f;

        }
        else
        {
            PlayerPos.x = 0;

        }*/






    }
    this->background->Update();
    this->player->Update();
    
  
    this->playerdraw->Update();
    this->lefthand->Update();
    this->leftleg->Update();
    this->righthand->Update();
    this->rightleg->Update();
    this->eyes->Update();

    this->idle->Update();
    this->walking->Update();
    this->walking2->Update();
    this->jump->Update();

    this->playercol->Update();
    this->playercol2->Update();
    this->playercol3->Update();
    this->newcol->Update();
    this->goal->Update();
   
        this->block[0]->Update();
        this->block[1]->Update();
        this->block[2]->Update();
        this->block[3]->Update();
        this->block[4]->Update();
        this->block[5]->Update();
        this->block[6]->Update();
        this->block[7]->Update();
    

    
        this->hook[0]->Update();
        this->hook[1]->Update();
        this->hook[2]->Update();
        this->hook[3]->Update();

        this->hookdraw[0]->Update();
        this->hookdraw[1]->Update();
        this->hookdraw[2]->Update();
        this->hookdraw[3]->Update();
    for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->Update();

    }

    if (ScenechangeState == true)
    {
        ScenechangeState = false;
        this->p_sceneManager->ChangeScene(Scene::Stage_1);
        return;
    }
    if (ScenechangeState2 == 1)
    {
        
        this->p_sceneManager->ChangeScene(Scene::Stage_2);
        return;
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

    this->goal->Draw();
    /* for (n = 1; n < 8; n++)
     {
         this->block[n]->Draw();
     }*/
   for (drawnum = 0; drawnum < 768; drawnum++)
    {
        this->blockdraw[drawnum]->Draw();


    }
    
        this->hookdraw[0]->Draw();
        this->hookdraw[1]->Draw();
        this->hookdraw[2]->Draw();
        this->hookdraw[3]->Draw();
    

    //this->player->Draw();
    //this->playercol->Draw();
    //this->playercol2->Draw();
    //this->playercol3->Draw();

    //this->newcol->Draw();
   
   /* this->playerdraw->Draw();
    this->lefthand->Draw();
    this->leftleg->Draw();
    this->righthand->Draw();
    this->rightleg->Draw();*/

 
        
    //this->idle->Draw();
    if (p_input->GetLeftAnalogStick().x * 10.0f < -2.0f && superjumpstate == 0&&grabstate == 0 && jumpstate == 0)
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
    else if (p_input->GetLeftAnalogStick().x * 10.0f >0 && superjumpstate == 0 && grabstate == 0 && jumpstate == 1)
    {
        this->walking->Draw();
    }
    else if (superjumpstate != 0 && Vx >= 0 && grabstate == 0 && jumpstate !=0)
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



    if (grabstate != 0)
    {
        this->playerdraw->Draw();
        this->lefthand->Draw();
        this->leftleg->Draw();
        this->righthand->Draw();
        this->rightleg->Draw();
        this->eyes->Draw();
    }
    //this->walking->Draw();

  //  this->eyes->Draw();
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

   

    //SAFE_DELETE_ARRAY(this->block[10]);
    //SAFE_DELETE(this->player);
    //SAFE_DELETE_ARRAY(this->hook[10]);
    
    //SAFE_DELETE_ARRAY(this->blockdraw[999]);
   // }
    SAFE_DELETE(this->goal);
    SAFE_DELETE(this->playercol);
    SAFE_DELETE(this->playercol2);
    SAFE_DELETE(this->playercol3);
    SAFE_DELETE(this->newcol);
    SAFE_DELETE(this->player);
    SAFE_DELETE(this->playerdraw);
 
    SAFE_DELETE(this->lefthand);
    SAFE_DELETE(this->leftleg);
    SAFE_DELETE(this->righthand);
    SAFE_DELETE(this->rightleg);
    SAFE_DELETE(this->eyes);
    SAFE_DELETE(this->idle);
    SAFE_DELETE(this->walking);
    SAFE_DELETE(this->walking2);
    SAFE_DELETE(this->jump);
  /*  SAFE_DELETE(this->block[0]);
    SAFE_DELETE(this->block[1]);
    SAFE_DELETE(this->block[2]);
    SAFE_DELETE(this->block[3]);
    SAFE_DELETE(this->block[4]);
    SAFE_DELETE(this->block[5]);
    SAFE_DELETE(this->block[6]);
    SAFE_DELETE(this->block[7]);



    SAFE_DELETE(this->hook[0]);
    SAFE_DELETE(this->hook[1]);
    SAFE_DELETE(this->hook[2]);
    SAFE_DELETE(this->hook[3]);*/
    /* for (n = 0; n < 100; n++)
    {
        SAFE_DELETE(this->block[n]);
    }


    for (m = 0; m < 100; n++)
    {
        SAFE_DELETE(this->hook[m]);
    }*/
   /* for (drawnum = 0; drawnum < 1000; drawnum++)
    {
        SAFE_DELETE(this->blockdraw[drawnum]);
    }*/
}
