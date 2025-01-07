/**	@file	Test_Imagawa.cpp
*	@brief 	今川用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Imagawa.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"
#include<Windows.h>

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Imagawa::Test_Imagawa()
{
    
    this->p_object = nullptr;
    this->p_object2 = nullptr;
    this->ball = nullptr;

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Imagawa::~Test_Imagawa()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Imagawa::Initialize(void)
{
    if (!this->p_object) { this->p_object = new Object; }
    if (!this->p_object2) { this->p_object2 = new Object; }
    if (!this->ball) { this->ball = new Ball; }

    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }

    // オブジェクト
    this->p_object->Init(L"Asset/block.png");
    this->p_object2->Init(L"Asset/block.png");
    this->ball->Init(L"Asset/block.png");

   

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
    this->p_object->SetPos(TestPos.x, TestPos.y, 0.0f); //初期座標-200.0f
    this->p_object2->SetPos(TestPos2.x, TestPos2.y, 0.0f); //p_objectから400.0f離れた場所に生成
    this->ball->SetPos(BallPos.x, BallPos.y, 0.0f);

    //オブジェクトのサイズを設定
    this->p_object->SetSize(TestSize.x, TestSize.y, 0.0f); // サイズは100.0f×100.0f
    this->p_object2->SetSize(TestSize2.x, TestSize2.y, 0.0f); // 同上
    this->ball->SetSize(BallSize.x, BallSize.y, 0.0f);

    ball->SetFriction(0.95f); // 摩擦係数
    ball->SetState(Ball::STOP);
   
}


/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void Test_Imagawa::Update(void)
{
    /*@brief　input更新*/
    input.Update();

    /**@brief　振動の長さ：５秒*/
    flame = 5;

    /**@brief　振動の強さ：３*/
    power = 0.5f; // ボールの初期速度設定
    ball->SetVelocity(1.0f, velocityY, 0.0f);  // 初期速度設定
    

    // ボールの位置取得
    DirectX::XMFLOAT3 ball_pos = this->ball->GetPos();
    // ボールの状態更新
    if (ball->GetState() == Ball::ROLL)
    {
        // 摩擦を加える処理
        ball->ApplyFriction(0.98f);  // 摩擦係数を適用、減速
    }
 

    // 重力の影響を加えて速度を更新
    velocityY += gravity;

    // 最大落下速度に制限をかける（終端速度のようなもの）
    if (velocityY > maxVelocityY) 
    {
        velocityY = maxVelocityY;
    }

    // ボールの位置をY軸方向に更新
    ball_pos.y -= velocityY;

    // ボールが地面に到達した場合、地面に接触させる
    if (ball_pos.y <= floorY)
    {
        ball_pos.y = floorY;
        velocityY = 0.0f; // 地面に着いたら速度を0にする
    }
    
    auto& col1 = p_object->GetCollider();
    auto& col2 = p_object2->GetCollider();
    auto& col3 = ball->GetCollider();
    if (col1.CheckCollision(col3))
    {
        p_object->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        if (input.Trigger("UP")) 
        {
            ball->SetState(Ball::ROLL);
        }
    }
    else
    {
        p_object->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    if (ball_pos.x >= 250)
    {
        ball->SetState(Ball::STOP);
    }

    // オブジェクトの位置更新
    DirectX::XMFLOAT3 pos = this->p_object->GetPos();
    DirectX::XMFLOAT3 pos2 = this->p_object2->GetPos();

    // 入力に応じた位置の更新
    if (input.Press("LEFT")) { pos.x -= 2.0f; input.SetVibration(flame, power); }
    if (input.Press("RIGHT")) { pos.x += 2.0f; input.SetVibration(flame, power); }
  
    if (input.Press("DOWN")) { pos.y -= 2.0f; input.SetVibration(flame, power); }

    // プレイヤーを動かす処理
    DirectX::XMFLOAT2 leftStick = input.GetLeftAnalogStick();
    float moveSpeed = 5.0f;
    pos.x += leftStick.x * moveSpeed;
    pos.y += leftStick.y * moveSpeed;

    // オブジェクトの位置を更新
    this->p_object->SetPos(pos.x, pos.y, pos.z);
    this->p_object2->SetPos(pos2.x, pos2.y, pos2.z);
    this->ball->SetPos(ball_pos.x, ball_pos.y, ball_pos.z);

    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_IMAGAWA);
        return;
    }

    // オブジェクトを更新
    this->p_object->Update();
    this->p_object2->Update();
    this->ball->Update();
}




/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Imagawa::Draw(void)
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
    this->p_object->Draw();
    this->p_object2->Draw();
    this->ball->Draw();
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Imagawa::Finalize(void)
{
    /*// 頂点シェーダ
    if (this->p_vertexShader) {
        delete   this->p_vertexShader;
        this->p_vertexShader = nullptr;
    }

    // ピクセルシェーダ
    if (this->p_pixelShader) {
        delete    this->p_pixelShader;
        this->p_pixelShader = nullptr;
    }

    // 入力レイアウト
    if (this->p_inputLayout) {
        delete    this->p_inputLayout;
        this->p_inputLayout = nullptr;
    }

    // サンプラー
    if (this->p_sampler) {
        delete  this->p_sampler;
        this->p_sampler = nullptr;
    }

    // ブレンドステート
    if (this->p_brendState) {
        this->p_brendState->Release();
    }*/
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
    SAFE_DELETE(this->p_object);
    SAFE_DELETE(this->p_object2);
    SAFE_DELETE(this->ball);

}
