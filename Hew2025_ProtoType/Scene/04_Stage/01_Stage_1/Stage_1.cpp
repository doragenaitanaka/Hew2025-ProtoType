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
    this->p_camera = nullptr;
    this->p_tileMap = nullptr;

    //--------------------------------------------------------------------------
    //		 オブジェクト
    //--------------------------------------------------------------------------	
    this->background = nullptr;
    this->player = nullptr;

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
Stage_1::~Stage_1()
{
    this->Finalize();
}
/**	@brief 	シーン全体の初期化
*/
void	Stage_1::Initialize(void)
{
    // カメラ
    if (!this->p_camera) { this->p_camera = new TrackingCamera; }

    // タイルマップの生成
    if (!this->p_tileMap)
    {
        this->p_tileMap = new TileMap(this->p_camera);
        this->p_tileMap->GenerateMap("Stage1.csv");
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

    // プレイヤーをターゲットに設定
    this->p_camera->SetTarget(this->player);

    /*
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

    if (!this->playercol) { this->playercol = new Object; }
    if (!this->playercol2) { this->playercol2 = new Object; }
    if (!this->playercol3) { this->playercol3 = new Object; }
    if (!this->newcol) { this->newcol = new Object; }
    */

    for (m = 0; m < 4; m++)
    {
        if (!this->hook[m]) {
            this->hook[m] = std::make_shared<Object>(this->p_camera);
        }
        if (!this->hookdraw[m]) {
            this->hookdraw[m] = std::make_shared<Object>(this->p_camera);
        }
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

    for (m = 0; m < 4; m++)
    {
        this->hook[m]->Init(L"Asset/Gimmick/hook.png");
        this->hookdraw[m]->Init(L"Asset/Gimmick/hook.png");
    }

    this->playerdraw->Init(L"Asset/gumbody.png");
    this->eyes->Init(L"Asset/gum_eyes.png");
    this->lefthand->Init(L"Asset/left_hand.png");
    this->righthand->Init(L"Asset/right_hand.png");
    this->leftleg->Init(L"Asset/left_leg.png");
    this->rightleg->Init(L"Asset/right_leg.png");


    this->idle->Init(L"Asset/idle_3.png", 4, 1);
    this->walking->Init(L"Asset/walking_2.png", 4, 1);
    this->walking2->Init(L"Asset/walking_3.png", 4, 1);

    this->playercol->Init(L"Asset/block.png");
    this->playercol2->Init(L"Asset/block.png");
    this->playercol3->Init(L"Asset/block.png");

    this->goal->Init(L"Asset/Gimmick/goal.png");

    this->player->SetAngle(PlayerAngle);
    this->playerdraw->SetAngle(PlayerAngle);

    DirectX::XMFLOAT3 playerPos = this->player->GetPos();
    this->goal->SetPos(GoalPos.x, GoalPos.y, playerPos.z);
    this->eyes->SetPos(playerPos.x + EyesPos.x, playerPos.y + EyesPos.y, playerPos.z);
    this->lefthand->SetPos(playerPos.x + LefthandPos.x, playerPos.y + LefthandPos.y, playerPos.z);
    this->leftleg->SetPos(playerPos.x + LeftlegPos.x, playerPos.y + LeftlegPos.y, playerPos.z);
    this->righthand->SetPos(playerPos.x + RighthandPos.x, playerPos.y + RighthandPos.y, playerPos.z);
    this->rightleg->SetPos(playerPos.x + RightlegPos.x, playerPos.y + RightlegPos.y, playerPos.z);

    this->playerdraw->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y, playerPos.z);

    this->idle->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
    this->walking->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
    this->walking2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
    this->playercol->SetPos(playerPos.x + PlayerColPos.x, playerPos.y + PlayerColPos.y, playerPos.z);
    this->playercol2->SetPos(playerPos.x + PlayerColPos2.x, playerPos.y + PlayerColPos2.y, playerPos.z);
    this->playercol3->SetPos(playerPos.x + PlayerColPos3.x, playerPos.y + PlayerColPos3.y, playerPos.z);

    this->hook[0]->SetPos(HookPos01.x, HookPos01.y, playerPos.z);
    this->hook[1]->SetPos(HookPos02.x, HookPos02.y, playerPos.z);
    this->hook[2]->SetPos(HookPos03.x, HookPos03.y, playerPos.z);
    this->hook[3]->SetPos(HookPos04.x, HookPos04.y, playerPos.z);


    this->hookdraw[0]->SetPos(HookPos01.x, HookPos01.y + 80.0f, playerPos.z);
    this->hookdraw[1]->SetPos(HookPos02.x, HookPos02.y + 80.0f, playerPos.z);
    this->hookdraw[2]->SetPos(HookPos03.x, HookPos03.y + 80.0f, playerPos.z);
    this->hookdraw[3]->SetPos(HookPos04.x, HookPos04.y + 80.0f, playerPos.z);

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

    this->hook[0]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[1]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[2]->SetSize(HookSize01.x, HookSize01.y, 0.0f);
    this->hook[3]->SetSize(HookSize01.x, HookSize01.y, 0.0f);



    this->hookdraw[0]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[1]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[2]->SetSize(HookSize02.x, HookSize02.y, 0.0f);
    this->hookdraw[3]->SetSize(HookSize02.x, HookSize02.y, 0.0f);

    player->SetPos(500.0f, -2870.0f, 0.0f);
    Vx = 0.0f;
    Vy = 0.0f;
    t = 0;
    t2 = 0;
    jumpstate = 0;
    HookColliderState = -1;

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
void	Stage_1::Update(void)
{
    this->p_input->Update();
    this->p_input->GetLeftAnalogStick();

    // リスタート    
    if (this->p_input->Trigger("RETRY"))
    {
        this->p_sceneManager->ChangeScene(Scene::Stage_2);
        return;
    }
    // タイトルに戻る
    if (this->p_input->Trigger("TITLE"))
    {
        this->p_sceneManager->ChangeScene(Scene::TitleScene);
        return;
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

        // 座標デバッグ用
        if (this->p_input->Trigger("SPACE"))
        {
            std::cout << "x:" << std::to_string(playerPos.x) << " y:" << std::to_string(playerPos.y) << std::endl;
        }

    }

    if (gamemode == 1)
    {
        DirectX::XMFLOAT3 playerPos = this->player->GetPos();
        movestate = 0;

        PlayerGrabPos.x = 0.0f;
        PlayerGrabPos.y = 0.0f;


        if (playerPos.y <= -3100.0f)
        {
            this->p_sceneManager->ChangeScene(Scene::Stage_2);
            return;
        }
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

        this->goal->SetPos(GoalPos.x, GoalPos.y, playerPos.z);
        this->eyes->SetPos(playerPos.x + EyesPos.x, playerPos.y + EyesPos.y, playerPos.z);
        this->lefthand->SetPos(playerPos.x + LefthandPos.x, playerPos.y + LefthandPos.y, playerPos.z);
        this->leftleg->SetPos(playerPos.x + LeftlegPos.x, playerPos.y + LeftlegPos.y, playerPos.z);
        this->righthand->SetPos(playerPos.x + RighthandPos.x, playerPos.y + RighthandPos.y, playerPos.z);
        this->rightleg->SetPos(playerPos.x + RightlegPos.x, playerPos.y + RightlegPos.y, playerPos.z);

        this->playerdraw->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y, playerPos.z);

        this->idle->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->walking2->SetPos(playerPos.x + PlayerDrawPos.x, playerPos.y + PlayerDrawPos.y - 20.0f, playerPos.z);
        this->playercol->SetPos(playerPos.x + PlayerColPos.x, playerPos.y + PlayerColPos.y, playerPos.z);
        this->playercol2->SetPos(playerPos.x + PlayerColPos2.x, playerPos.y + PlayerColPos2.y, playerPos.z);
        this->playercol3->SetPos(playerPos.x + PlayerColPos3.x, playerPos.y + PlayerColPos3.y, playerPos.z);

        this->hook[0]->SetPos(HookPos01.x, HookPos01.y, playerPos.z);
        this->hook[1]->SetPos(HookPos02.x, HookPos02.y, playerPos.z);
        this->hook[2]->SetPos(HookPos03.x, HookPos03.y, playerPos.z);
        this->hook[3]->SetPos(HookPos04.x, HookPos04.y, playerPos.z);


        this->hookdraw[0]->SetPos(HookPos01.x, HookPos01.y + 80.0f, playerPos.z);
        this->hookdraw[1]->SetPos(HookPos02.x, HookPos02.y + 80.0f, playerPos.z);
        this->hookdraw[2]->SetPos(HookPos03.x, HookPos03.y + 80.0f, playerPos.z);
        this->hookdraw[3]->SetPos(HookPos04.x, HookPos04.y + 80.0f, playerPos.z);
    }

    //--------------------------------------------------------------------------
    //		オブジェクトの更新
    //--------------------------------------------------------------------------	
    this->background->Update();
    this->p_tileMap->Update();

    this->goal->Update();
    this->playercol->Update();
    this->playercol2->Update();
    this->playercol3->Update();

    this->idle->Update();

    this->walking->Update();
    this->walking2->Update();
    this->player->Update();
    this->playerdraw->Update();
    this->lefthand->Update();
    this->leftleg->Update();
    this->righthand->Update();
    this->rightleg->Update();
    this->eyes->Update();

    this->hook[0]->Update();
    this->hook[1]->Update();
    this->hook[2]->Update();
    this->hook[3]->Update();

    this->hookdraw[0]->Update();
    this->hookdraw[1]->Update();
    this->hookdraw[2]->Update();
    this->hookdraw[3]->Update();

    // カメラの更新
    this->p_camera->Update();
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
    this->goal->Draw();
    this->p_tileMap->Draw();

    /* this->player->Draw();
     this->playercol->Draw();
    this->playercol2->Draw();
    this->playercol3->Draw();*/

    //this->hook[0]->Draw();
    //this->hook[1]->Draw();
    //this->hook[2]->Draw();

    this->hookdraw[0]->Draw();
    this->hookdraw[1]->Draw();
    this->hookdraw[2]->Draw();
    this->hookdraw[3]->Draw();

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
    if (grabstate != 0)
    {
        this->playerdraw->Draw();
        this->lefthand->Draw();
        this->leftleg->Draw();
        this->righthand->Draw();
        this->rightleg->Draw();
        this->eyes->Draw();
    }
    this->player->Draw();
}

/**	@brief 	シーン全体の終了処理
*/
void	Stage_1::Finalize(void)
{
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
}
