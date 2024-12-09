#include"CDepthStencil.h"
#include"../../SafePointers.h"
/**	@brief 	�R���X�g���N�^
*	@date 2024/03/29
*/
CD3D11_DepthStencil::CD3D11_DepthStencil()
{
    this->p_DepthStencilView = nullptr;
}

/**	@brief 	�f�X�g���N�^
*	@date 2024/03/29
*/
CD3D11_DepthStencil::~CD3D11_DepthStencil()
{
    this->Release();
}
/**	@brief 	�[�x�X�e���V���̏�����
*	@param	ID3D11Device* p_Device                      Direct3D�f�o�C�X
*	@param	ID3D11DeviceContext* p_ImmediateContext     �f�o�C�X�R���e�L�X�g
*   @param  IDXGISwapChain* p_SwapChain                 �X���b�v�`�F�[��
*   @param  ID3D11RenderTargetView* m_pRenderTargetView �����_�[�^�[�Q�b�g�r���[s
*	@return HRESULT
*	@date 2024/03/29
*/
HRESULT    CD3D11_DepthStencil::Create(ID3D11Device* p_Device, ID3D11DeviceContext* p_ImmediateContext, IDXGISwapChain* p_SwapChain, ID3D11RenderTargetView* m_pRenderTargetView)
{
    // �쐬����e�N�X�`��
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    
    ID3D11Texture2D* p_depthStencilBufer = nullptr; // �[�x�X�e���V���o�b�t�@

    // �o�b�N�o�b�t�@�̎擾
    ID3D11Texture2D* p_backBuffer = nullptr;        
    p_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_backBuffer);

    // �o�b�N�o�b�t�@����𑜓x���擾
    D3D11_TEXTURE2D_DESC buckBufferDesc;
    p_backBuffer->GetDesc(&buckBufferDesc);

    // �e�N�X�`�����\�[�X�̏�����
    descDepth.Width = buckBufferDesc.Width;             // �o�b�N�o�b�t�@�Ɠ�����
    descDepth.Height = buckBufferDesc.Height;           // �o�b�N�o�b�t�@�Ɠ�������
    descDepth.MipLevels = 1;                            // �~�b�v�}�b�v���x����1
    descDepth.ArraySize = 1;                            // �e�N�X�`���z��̃T�C�Y��1
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;   // �[�x�l��24bit��float�^���A�X�e���V���l��8�r�b�g��uint���m��
    descDepth.SampleDesc.Count = 1;                     // �}���`�T���v�����O�͎g�p���Ȃ�
    descDepth.SampleDesc.Quality = 0;                   // �}���`�T���v�����O�̕i���͍Œ�
    descDepth.Usage = D3D11_USAGE_DEFAULT;              // GPU���ǂݏ�������
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;     // �[�x�X�e���V���^�[�Q�b�g�Ƃ��ăo�C���h
    descDepth.CPUAccessFlags = 0;                       // CPU����̓A�N�Z�X���Ȃ�
    descDepth.MiscFlags = 0;                            // ���̑��̃t���O�͐ݒ肵�Ȃ�
    
    SAFE_RELEASE(p_backBuffer);         // �K�v�Ȃ��Ȃ����̂ŉ��

    HRESULT hr;
    hr = p_Device->CreateTexture2D(&descDepth, nullptr, &p_depthStencilBufer);  // �[�x�X�e���V���o�b�t�@�̃e�N�X�`�����쐬    
    if (FAILED(hr)) { return hr; }                                              // �����������`�F�b�N

    // �쐬����r���[�̃^�C�v���w��
    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.Format = descDepth.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;

    // �[�x�X�e���V���r���[���쐬
    hr = p_Device->CreateDepthStencilView(p_depthStencilBufer, &dsDesc, &this->p_DepthStencilView);
   
    if (FAILED(hr)) { return hr; }      // �����������`�F�b�N
    SAFE_RELEASE(p_depthStencilBufer);  // �[�x�X�e���V���o�b�t�@�̉��

    // �����_�[�^�[�Q�b�g�ɃZ�b�g
    p_ImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, this->p_DepthStencilView);
    // �N���A���Ă���
    float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // red, green, blue, alpha
    p_ImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
    p_ImmediateContext->ClearDepthStencilView(this->p_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    return S_OK;    // ������Ԃ�
}

/**	@brief 	�������
*	@date 2024/03/29
*/
void   CD3D11_DepthStencil::Release()
{
    SAFE_RELEASE(this->p_DepthStencilView);
}