/**	@file	Test_Otani.cpp
*	@brief 	��J�p�̃Q�[���V�[���N���X
*	@date	2024/12/14
*/
#include"Test_Otani.h"

/**	@brief 	�R���X�g���N�^
*	@date	2024/05/10
*/
Test_Otani::Test_Otani()
{
    this->p_object = nullptr;
    /** @brief ��ڂ̃I�u�W�F�N�g���o���p
    *   @date 2024/12/11
    */
    this->p_object2 = nullptr;

    this->p_vertexShader = nullptr;
    this->p_pixelShader = nullptr;
    this->p_inputLayout = nullptr;
    this->p_sampler = nullptr;
    this->p_brendState = nullptr;
}
/**	@brief 	�f�X�g���N�^
*	@date	2024/05/10
*/
Test_Otani::~Test_Otani()
{
    this->Finalize();
}
/**	@brief 	�V�[���S�̂̏�����
*	@date	2024/05/10
*/
void	Test_Otani::Initialize(void)
{
    if (!this->p_object) { this->p_object = new Object; }
    if (!this->p_object2) { this->p_object2 = new Object; }

    if (!this->p_vertexShader) { this->p_vertexShader = new CVertexShader; }            // ���_�V�F�[�_
    if (!this->p_pixelShader) { this->p_pixelShader = new CPixelShader; }               // �s�N�Z���V�F�[�_
    if (!this->p_inputLayout) { this->p_inputLayout = new CInputLayout; }               // ���̓��C�A�E�g
    if (!this->p_sampler) { this->p_sampler = new CSampler; }                           // �T���v���[

    // �I�u�W�F�N�g
    this->p_object->Init(L"Asset/block.png");
    this->p_object2->Init(L"Asset/block.png");


    //--------------------------------------------------------------------------
    //		�`��֘A�̏�����
    //--------------------------------------------------------------------------	

    HRESULT hr;
    // �V�F�[�_
    {
        // ���_�V�F�[�_�R���p�C��
        hr = this->p_vertexShader->CompileFromFile(
            L"Shader/VertexShader.hlsl",            // �g�p�������V�F�[�_�t�@�C���p�X
            NULL,
            NULL,
            "vs_main",                              // �V�F�[�_�t�@�C�����ŏ����Ă���G���g���[�|�C���g
            "vs_5_0",                               // �V�F�[�_�̃o�[�W����
            0,
            0
        );

        //  �s�N�Z���V�F�[�_�[�t�@�C���R���p�C��
        hr = this->p_pixelShader->CompileFromFile(
            L"Shader/PixelShader.hlsl",
            NULL,
            NULL,
            "ps_main",
            "ps_5_0",
            0,
            0
        );

        //  �V�F�[�_�̐���
        hr = this->p_vertexShader->Create(NULL);     //  ���_�V�F�[�_
        hr = this->p_pixelShader->Create(NULL);      //  �s�N�Z���V�F�[�_
    }

    // �C���v�b�g���C�A�E�g�쐬
    D3D11_INPUT_ELEMENT_DESC layout[]
    {
        // �ʒu���W������Ƃ������Ƃ�`����
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        // �F��񂪂���Ƃ������Ƃ�`����
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //UV���W(uv)
        {"TEX",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };

    // ���̓��C�A�E�g�̍쐬
    unsigned int numElements = ARRAYSIZE(layout);                           // ���C�A�E�g�̃T�C�Y
    ID3DBlob* p_vsBlob = this->p_vertexShader->GetShaderFile();             // ���_�V�F�[�_�[�t�@�C���̎擾
    hr = this->p_inputLayout->Create(layout, numElements, p_vsBlob);

    // �T���v���[���쐬
    hr = this->p_sampler->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
        D3D11_TEXTURE_ADDRESS_CLAMP,
        D3D11_TEXTURE_ADDRESS_CLAMP,
        D3D11_TEXTURE_ADDRESS_CLAMP);
    if (FAILED(hr)) { return; }

    // �u�����h�X�e�[�g�̍쐬
    // �����ߏ�������Z�������\�ɂ���F�̍������@
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
        // �[�x�e�X�g�𖳌��ɂ���
        ID3D11DepthStencilState* p_dSState;
        CD3D11_DEPTH_STENCIL_DESC   dsDesc;
        ZeroMemory(&dsDesc, sizeof(dsDesc));

        dsDesc.DepthEnable = FALSE;     // �[�x�e�X�g�𖳌��ɐݒ�
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
        if (p_device)
        {
            hr = p_device->CreateDepthStencilState(&dsDesc, &p_dSState);
            if (FAILED(hr)) { return; }

            // �f�o�C�X�R���e�L�X�g�̎擾
            ID3D11DeviceContext* p_deviceContext = this->p_cd3d11->GetDeviceContext();
            if (p_deviceContext)
            {
                p_deviceContext->OMSetDepthStencilState(p_dSState, 1);
            }
        }
    }
    // �I�u�W�F�N�g�̍��W��ݒ�
    this->p_object->SetPos(TestPos.x, TestPos.y, 0.0f); //�������W-200.0f
    this->p_object2->SetPos(TestPos2.x, TestPos2.y, 0.0f); //p_object����400.0f���ꂽ�ꏊ�ɐ���
    //�I�u�W�F�N�g�̃T�C�Y��ݒ�
    this->p_object->SetSize(TestSize.x, TestSize.y, 0.0f); // �T�C�Y��100.0f�~100.0f
    this->p_object2->SetSize(TestSize2.x, TestSize2.y, 0.0f); // ����
}

/**	@brief 	�V�[���S�̂̍X�V
*	@date	2024/05/10
*/
void	Test_Otani::Update(void)
{
    if (GetAsyncKeyState(VK_SPACE))
    {
        this->p_sceneManager->ChangeScene(Scene::TEST_OTANI);
        return;
    }
    //�E���L�[�ŉE�ړ�
    if (GetAsyncKeyState(VK_RIGHT))
    {
        this->p_object->SetPos(p_object->GetPos().x + 20, p_object->GetPos().y, 0.0f); //���W�X�V
    }
    //�����L�[�ō��ړ�
    if (GetAsyncKeyState(VK_LEFT))
    {
        this->p_object->SetPos(p_object->GetPos().x - 20, p_object->GetPos().y, 0.0f); //���W�X�V
    }


    // �I�u�W�F�N�g�̍X�V
    this->p_object->Update();
    this->p_object2->Update();
}

/**	@brief 	�V�[���S�̂̕`��
*	@date	2024/05/10
*/
void	Test_Otani::Draw(void)
{

    //--------------------------------------------------------------------------
    //		�`��֘A(����ȕp�ɂɕς��邱�Ƃ͂Ȃ��Ǝv��)
    //--------------------------------------------------------------------------	

    // �`��ݒ�p�Ƀf�o�C�X�Ȃǂ��擾
    CD3D11* cd3d11 = CD3D11::GetInstance();
    ID3D11DeviceContext* deviceContext = cd3d11->GetDeviceContext();
    ID3D11DepthStencilView* depthStencilView = cd3d11->GetDepthStencilView();
    ID3D11RenderTargetView* renderTargetView = cd3d11->GetRenderTargetView();
    D3D11_VIEWPORT* viewport = cd3d11->GetViewport();

    // ���̓��C�A�E�g�̐ݒ�
    this->p_inputLayout->SetInputLayout();
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // �V�F�[�_���Z�b�g
    this->p_vertexShader->SetShader(0, 0);
    this->p_pixelShader->SetShader(0, 0);

    // �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
    this->p_sampler->SetSamplerPS(0, 1);

    // �u�����h�X�e�[�g���Z�b�g
    deviceContext->OMSetBlendState(this->p_brendState, NULL, 0xfffffffff);

    //--------------------------------------------------------------------------
    //		�I�u�W�F�N�g�̕`��
    //--------------------------------------------------------------------------	
    this->p_object->Draw();
    this->p_object2->Draw();
}

/**	@brief 	�V�[���S�̂̏I������
*	@date	2024/05/10
*/
void	Test_Otani::Finalize(void)
{
    // ���_�V�F�[�_
    if (this->p_vertexShader) {
        delete   this->p_vertexShader;
        this->p_vertexShader = nullptr;
    }

    // �s�N�Z���V�F�[�_
    if (this->p_pixelShader) {
        delete    this->p_pixelShader;
        this->p_pixelShader = nullptr;
    }

    // ���̓��C�A�E�g
    if (this->p_inputLayout) {
        delete    this->p_inputLayout;
        this->p_inputLayout = nullptr;
    }

    // �T���v���[
    if (this->p_sampler) {
        delete  this->p_sampler;
        this->p_sampler = nullptr;
    }

    // �u�����h�X�e�[�g
    if (this->p_brendState) {
        this->p_brendState->Release();
    }
    //�I�u�W�F�N�g
    if (this->p_object) {
        delete this->p_object;
        this->p_object = nullptr;
    }

    if (this->p_object2) {
        delete this->p_object2;
        this->p_object2 = nullptr;
    }
}