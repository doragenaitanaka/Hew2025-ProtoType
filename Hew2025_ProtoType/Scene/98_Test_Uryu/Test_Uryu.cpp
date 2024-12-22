/**	@file	Test_Uryu.cpp
*	@brief 	瓜生用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Uryu.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"
#include"../../Library/Code/self/GrabBox.h"

#include<Windows.h>


/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Uryu::Test_Uryu()
{
    this->p_TestObject = nullptr;
    /** @brief 二つ目のオブジェクトを出す用
    *   @date 2024/12/11
    */
    this->p_TestObject2 = nullptr;
    /** @brief 三つ目のオブジェクトを出す用
    *   @date 2024/12/21
    */
    this->p_TestObject3 = nullptr;


    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Uryu::~Test_Uryu()
{
	this->Finalize();
}
/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Uryu::Initialize(void)
{
    if (!this->p_TestObject) { this->p_TestObject = new Object; }
    if (!this->p_TestObject2) { this->p_TestObject2 = new Object; }
    if (!this->p_TestObject3) { this->p_TestObject3 = new Object; }

    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    // オブジェクト
    this->p_TestObject->Init(L"Asset/block.png");
    this->p_TestObject2->Init(L"Asset/block.png");
    this->p_TestObject3->Init(L"Asset/block.png");


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
    this->p_TestObject->SetPos(TestPos.x, TestPos.y, 0.0f); //初期座標-200.0f
    this->p_TestObject2->SetPos(TestPos2.x, TestPos2.y, 0.0f); //p_objectから400.0f離れた場所に生成
    this->p_TestObject3->SetPos(TestPos3.x, TestPos3.y, 0.0f); //掴めるオブジェクトは中央少し上に生成
    //オブジェクトのサイズを設定
    this->p_TestObject->SetSize(TestSize.x, TestSize.y, 0.0f); // サイズは100.0f×100.0f
    this->p_TestObject2->SetSize(TestSize2.x, TestSize2.y, 0.0f); // ちょっと大きく125.0f × 125.0f
    this->p_TestObject3->SetSize(TestSize3.x, TestSize3.y, 0.0f); // ちょっと大きく125.0f × 125.0f
}
/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Uryu::Update(void)
{
    static GrabBox grabBox; // GrabBoxのインスタンスを静的に保持
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_URYU);
        return;
    }
    //右矢印キーで右移動
    if (GetAsyncKeyState(VK_RIGHT))
    {
        this->p_TestObject->SetPos(p_TestObject->GetPos().x + 20, p_TestObject->GetPos().y, 0.0f); //座標更新
    }
    //左矢印キーで左移動
    if (GetAsyncKeyState(VK_LEFT))
    {
        this->p_TestObject->SetPos(p_TestObject->GetPos().x - 20, p_TestObject->GetPos().y, 0.0f); //座標更新
    }
    //上矢印キーで上移動
    if (GetAsyncKeyState(VK_UP))
    {
        this->p_TestObject->SetPos(p_TestObject->GetPos().x, p_TestObject->GetPos().y + 20, 0.0f); //座標更新
    }
    //下矢印キーで下移動
    if (GetAsyncKeyState(VK_DOWN))
    {
        this->p_TestObject->SetPos(p_TestObject->GetPos().x, p_TestObject->GetPos().y - 20, 0.0f); //座標更新
    }

    if (this->TestMoveFlg == true)
    {
        this->p_TestObject2->SetPos(p_TestObject2->GetPos().x, p_TestObject2->GetPos().y + 15, 0.0f); //座標更新
        this->TestMoveCnt++;
        if (this->TestMoveCnt == 10)
        {
            this->TestMoveFlg = false;
            this->TestMoveCnt = 0;
        }
    }
    else
    {
        this->p_TestObject2->SetPos(p_TestObject2->GetPos().x, p_TestObject2->GetPos().y - 15, 0.0f); //座標更新
        this->TestMoveCnt++;
        if (this->TestMoveCnt == 10)
        {
            this->TestMoveFlg = true;;
            this->TestMoveCnt = 0;
        }
    }

    auto& col1 = p_TestObject->GetCollider();
    auto& col2 = p_TestObject2->GetCollider();
    auto& col3 = p_TestObject3->GetCollider();
    if (col1.CheckCollision(col2))
    {
        p_TestObject->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        
        //Eキーが押されたかどうかをチェック
        if(GetAsyncKeyState(0x45))
        {
            if (grabBox.GetGrabState() == 0)
            {
                grabBox.Grab(p_TestObject);
                TestGrabState = 1;
            }
            else
            {
                grabBox.Release();
                TestGrabState = 0;
            }
        }

    }
    else if (col1.CheckCollision(col3))
    {
        p_TestObject->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

        //こっちのコードは掴めるオブジェクトをプレイヤーの子オブジェクトにして持ち運べるようにしたのを間違えて作ったので一応入れときます、不要なら消してください
        // Eキーが押されたかどうかをチェック
        if (GetAsyncKeyState(0x45)) //ここを変更
        {
            if (grabBox.GetGrabState() == 0)
            {
                // Grab()関数を呼び出して箱を掴む
                grabBox.Grab(p_TestObject3);
                TestGrabState = 2;
            }
            else
            {
                // Release()関数を呼び出して箱を離す
                grabBox.Release();
                TestGrabState = 0;
            }
        }
    }
    else
    {
        p_TestObject->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
        TestGrabState = 0;
    }


    if (TestGrabState == 1)
    {
        // 掴んだオブジェクトの位置をプレイヤーの位置に追従させる
        grabBox.Move(p_TestObject2->GetPos());
    }
    else if (TestGrabState == 2)
    {
        grabBox.Move(p_TestObject->GetPos());
    }
        // オブジェクトの更新
    this->p_TestObject->Update();
    this->p_TestObject2->Update();
    this->p_TestObject3->Update();
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Uryu::Draw(void)
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
    this->p_TestObject2->Draw();
    this->p_TestObject3->Draw();
    this->p_TestObject->Draw();
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Uryu::Finalize(void)
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
    SAFE_DELETE(this->p_TestObject);
    SAFE_DELETE(this->p_TestObject2);
    SAFE_DELETE(this->p_TestObject3);
}
