﻿/**	@file	Test_Uryu.cpp
*	@brief 	瓜生用のゲームシーンクラス
*	@date	2024/05/10
*/
#include"Test_Uryu.h"
#include"../../Library/Code/self/03_Windows/WindowSetup.h"

#include<Windows.h>


/**	@brief 	コンストラクタ
*	@date	2024/05/10
*/
Test_Uryu::Test_Uryu()
{
    this->p_object = nullptr;
    /** @brief 二つ目のオブジェクトを出す用
    *   @date 2024/12/11
    */
    this->p_object2 = nullptr;

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
    //if (!this->p_object) { this->p_object = new Object; }
    //if (!this->p_object2) { this->p_object2 = new Object; }

    //if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // 頂点シェーダ
    //if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // ピクセルシェーダ
    //if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // 入力レイアウト
    //if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // サンプラー

    //// オブジェクト
    //this->p_object->Init(L"Asset/block.png");
    //this->p_object2->Init(L"Asset/block.png");


    ////--------------------------------------------------------------------------
    ////		描画関連の初期化
    ////--------------------------------------------------------------------------	

    //HRESULT hr;
    //// シェーダ
    //{
    //    // 頂点シェーダコンパイル
    //    hr = this->p_vertexShader->CompileFromFile(
    //        L"Shader/VertexShader.hlsl",            // 使用したいシェーダファイルパス
    //        NULL,
    //        NULL,
    //        "vs_main",                              // シェーダファイル内で書いているエントリーポイント
    //        "vs_5_0",                               // シェーダのバージョン
    //        0,
    //        0
    //    );

    //    //  ピクセルシェーダーファイルコンパイル
    //    hr = this->p_pixelShader->CompileFromFile(
    //        L"Shader/PixelShader.hlsl",
    //        NULL,
    //        NULL,
    //        "ps_main",
    //        "ps_5_0",
    //        0,
    //        0
    //    );

    //    //  シェーダの生成
    //    hr = this->p_vertexShader->Create(NULL);     //  頂点シェーダ
    //    hr = this->p_pixelShader->Create(NULL);      //  ピクセルシェーダ
    //}

    //// インプットレイアウト作成
    //D3D11_INPUT_ELEMENT_DESC layout[]
    //{
    //    // 位置座標があるということを伝える
    //    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    //    // 色情報があるということを伝える
    //    { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    //    //UV座標(uv)
    //    {"TEX",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    //};

    //// 入力レイアウトの作成
    //unsigned int numElements = ARRAYSIZE(layout);                           // レイアウトのサイズ
    //ID3DBlob* p_vsBlob = this->p_vertexShader->GetShaderFile();             // 頂点シェーダーファイルの取得
    //hr = this->p_inputLayout->Create(layout, numElements, p_vsBlob);

    //// サンプラーを作成
    //hr = this->p_sampler->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
    //    D3D11_TEXTURE_ADDRESS_CLAMP,
    //    D3D11_TEXTURE_ADDRESS_CLAMP,
    //    D3D11_TEXTURE_ADDRESS_CLAMP);
    //if (FAILED(hr)) { return; }

    //// ブレンドステートの作成
    //// →透過処理や加算合成を可能にする色の合成方法
    //{
    //    D3D11_BLEND_DESC    brendState;

    //    ZeroMemory(&brendState, sizeof(D3D11_BLEND_DESC));
    //    brendState.AlphaToCoverageEnable = FALSE;
    //    brendState.IndependentBlendEnable = FALSE;
    //    brendState.RenderTarget[0].BlendEnable = TRUE;
    //    brendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    //    brendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    //    brendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    //    brendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    //    brendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    //    brendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    //    brendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    //    ID3D11Device* p_device = this->p_cd3d11->GetDevice();
    //    if (p_device)
    //    {
    //        hr = p_device->CreateBlendState(&brendState, &this->p_brendState);
    //        if (FAILED(hr)) { return; }
    //    }
    //    // 深度テストを無効にする
    //    ID3D11DepthStencilState* p_dSState;
    //    CD3D11_DEPTH_STENCIL_DESC   dsDesc;
    //    ZeroMemory(&dsDesc, sizeof(dsDesc));

    //    dsDesc.DepthEnable = FALSE;     // 深度テストを無効に設定
    //    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    //    if (p_device)
    //    {
    //        hr = p_device->CreateDepthStencilState(&dsDesc, &p_dSState);
    //        if (FAILED(hr)) { return; }

    //        // デバイスコンテキストの取得
    //        ID3D11DeviceContext* p_deviceContext = this->p_cd3d11->GetDeviceContext();
    //        if (p_deviceContext)
    //        {
    //            p_deviceContext->OMSetDepthStencilState(p_dSState, 1);
    //        }
    //    }
    //}
    //// オブジェクトの座標を設定
    //this->p_object->SetPos(TestPos.x, TestPos.y, 0.0f); //初期座標-200.0f
    //this->p_object2->SetPos(TestPos2.x, TestPos2.y, 0.0f); //p_objectから400.0f離れた場所に生成
    ////オブジェクトのサイズを設定
    //this->p_object->SetSize(TestSize.x, TestSize.y, 0.0f); // サイズは100.0f×100.0f
    //this->p_object2->SetSize(TestSize2.x, TestSize2.y, 0.0f); // 同上
}
/**	@brief 	シーン全体の更新
*	@date	2024/05/10
*/
void	Test_Uryu::Update(void)
{

    //if (GetAsyncKeyState(VK_SPACE))
    //{
    //    // シーン遷移
    //    this->p_sceneManager->ChangeScene(Scene::TEST_URYU); // 一旦再読み込みにしている
    //    return;
    //}
    ////右矢印キーで右移動
    //if (GetAsyncKeyState(VK_RIGHT))
    //{
    //    TestPos.x += 20;
    //}
    ////左矢印キーで左移動
    //if (GetAsyncKeyState(VK_LEFT))
    //{
    //    TestPos.x -= 20;
    //}
    ////四角形と四角形の当たり判定をチェックして接触を検知したら色が変わる、離れたら元に戻る
    ////現状はp_objectとp_object2にXMFLOAT2 TestPosとXMFLOAT2 TestSizeでサイズを指定してオブジェクトの座標から直接判定を取っている
    //if( ::rectRect(TestPos.x,TestPos.y,TestSize.x,TestSize.y, TestPos2.x, TestPos2.y, TestSize2.x, TestSize2.y))
    //{
    //    this->p_object->SetColor({1.0f,0.0f,1.0f,1.0f});
    //    this->p_object2->SetColor({ 0.0f,1.0f,0.0f,1.0f });
    //}
    //else
    //{
    //    this->p_object->SetColor({ 1.0f,1.0f,1.0f,1.0f });
    //    this->p_object2->SetColor({ 1.0f,1.0f,1.0f,1.0f });
    //}

    //this->p_object->SetPos(TestPos.x, TestPos.y, 0.0f); //座標更新
    //// オブジェクトの更新
    //this->p_object->Update();
    //this->p_object2->Update();
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
    this->p_object->Draw();
    this->p_object2->Draw();
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	Test_Uryu::Finalize(void)
{
    // 頂点シェーダ
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
    }
    //オブジェクト
    if (this->p_object) {
        delete this->p_object;
        this->p_object = nullptr;
    }

    if (this->p_object2) {
        delete this->p_object2;
        this->p_object2 = nullptr;
    }
}