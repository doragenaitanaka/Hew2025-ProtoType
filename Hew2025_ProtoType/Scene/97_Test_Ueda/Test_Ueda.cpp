﻿/**	@file	Test_Ueda.cpp
*	@brief 	植田用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Ueda.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>

/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Ueda::Test_Ueda()
{
    this->p_object = nullptr;
	this->p_fallobject = nullptr;
    this->p_camera = nullptr;

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;

}
/**	@brief 	デストラクタ
*	@date	2024/05/10
*/
Test_Ueda::~Test_Ueda()
{
    //std::cout << "TestScene::~TestScene()" << std::endl;
    this->Finalize();
}

/**	@brief 	シーン全体の初期化
*	@date	2024/05/10
*/
void	Test_Ueda::Initialize(void)
{
    if (!this->p_camera) { this->p_camera = new Camera; }

    if (!this->p_object) { this->p_object = new Object(this->p_camera); }
    if (!this->p_fallobject) { this->p_fallobject = new FallObject(this->p_camera); }

    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    if (!this->p_sampler) { this->p_sampler = new CSampler; }

    
    
    


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

    // オブジェクト
    this->p_object->Init(L"Asset/block.png");
    this->p_fallobject->Init(L"Asset/block.png");

    // オブジェクトの座標を設定
    this->p_object->SetPos(TestPos.x, TestPos.y, 0.0f); //初期座標-200.0f
    this->p_fallobject->SetPos(TestPos2.x , TestPos2.y, 0.0f); //p_objectから400.0f離れた場所に生成

    //オブジェクトのサイズを設定
    this->p_object->SetSize(TestSize.x, TestSize.y, 0.0f); // サイズは100.0f×100.0f
    this->p_fallobject->SetSize(TestSize2.x, TestSize2.y, 0.0f); // 同上 
}

/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Ueda::Update(void)
{

    /*@brief　input更新*/
    input.Update();


    

    // オブジェクトの位置更新
    DirectX::XMFLOAT3 pos = this->p_object->GetPos();
    DirectX::XMFLOAT3 pos2 = this->p_fallobject->GetPos();

    auto& col1 = p_object->GetCollider();
    auto& col2 = p_fallobject->GetCollider();
	

    static bool isSpace = false;
    if (input.Trigger("SPACE")) { isSpace = true; }
    if (isSpace) {
        this->p_fallobject->Update(90.0f, 1);//倒れるオブジェクトの更新(どこまで倒れるかの角度、右に倒れるか左に倒れるか（１，右、２左）)
    }
   

    // 入力に応じた位置の更新
    if (input.Press("LEFT")) { pos.x -= 2.0f; input.SetVibration(flame, power); }
	if (input.Press("SHIFT") && input.Press("LEFT")) { pos.x -= 10.0f; input.SetVibration(flame, power); }//左方向ダッシュ
    if (input.Press("RIGHT")) { pos.x += 2.0f; input.SetVibration(flame, power); }
	if (input.Press("SHIFT") && input.Press("RIGHT")) { pos.x += 10.0f; input.SetVibration(flame, power); }//右方向ダッシュ

    if (input.Press("DOWN")) { pos.y -= 2.0f; input.SetVibration(flame, power); }

	if (input.Press("UP")) { pos.y += 2.0f; input.SetVibration(flame, power); }

    // プレイヤーを動かす処理
    DirectX::XMFLOAT2 leftStick = input.GetLeftAnalogStick();
    float moveSpeed = 5.0f;
    pos.x += leftStick.x * moveSpeed;
    pos.y += leftStick.y * moveSpeed;

    // オブジェクトの位置を更新
    this->p_object->SetPos(pos.x, pos.y, pos.z);
    
    if (GetAsyncKeyState(VK_SPACE))
    {
        // シーン遷移
        this->p_sceneManager->ChangeScene(Scene::TEST_UEDA); // 一旦再読み込みにしている
        return;
    }

    // オブジェクトの更新
	this->p_object->Update();//オブジェクトの更新
    
    // カメラの更新
    this->p_camera->Update();
}

/**	@brief 	シーン全体の描画
*	@date	2024/05/10
*/
void	Test_Ueda::Draw(void)

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
	this->p_fallobject->Draw();

    //オブジェクトの移動

}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Ueda::Finalize(void)
{
    //// 頂点シェーダ
    //if (this->p_vertexShader) {
    //    delete   this->p_vertexShader;
    //    this->p_vertexShader = nullptr;
    //}

    //// ピクセルシェーダ
    //if (this->p_pixelShader) {
    //    delete    this->p_pixelShader;
    //    this->p_pixelShader = nullptr;
    //}

    //// 入力レイアウト
    //if (this->p_inputLayout) {
    //    delete    this->p_inputLayout;
    //    this->p_inputLayout = nullptr;
    //}

    //// サンプラー
    //if (this->p_sampler) {
    //    delete  this->p_sampler;
    //    this->p_sampler = nullptr;
    //}

    //// ブレンドステート
    //if (this->p_brendState) {
    //    this->p_brendState->Release();
    //}

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
    SAFE_DELETE(this->p_fallobject);
    SAFE_DELETE(this->p_camera);
    
}