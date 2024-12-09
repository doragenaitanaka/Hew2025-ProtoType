//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------

// �s�N�Z���̏��̍\���́i�󂯎��p�j
struct PS_IN
{
    //float4�^�@���@float�^���S�̍\����
    float4 pos : SV_POSITION;   // �s�N�Z���̉�ʏ�̍��W
    float4 col : COLOR0;        //  �s�N�Z����̃J���[�l
    float2 tex : TEXCOORD;      // �s�N�Z����UV���W
};

//struct PS_OUT
//{
//    float4 pos : SV_POSITION;   // �s�N�Z���̉�ʏ�̍��W
//    float4 col : COLOR0;        //  �s�N�Z����̃J���[�l
//};

// �O���[�o���ϐ��̐錾
// ��C���ꂩ��f�[�^��n���ꂽ���ɃZ�b�g�����ϐ�
Texture2D myTexture : register(t0);     // �e�N�X�`��
SamplerState mySampler : register(s0);  // �T���v���[
    
// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main(PS_IN input) : SV_Target
{   
    //Sample�֐����e�N�X�`������Y����V�ʒu�̃s�N�Z���F���Ƃ��Ă���
    float4 color = myTexture.Sample(mySampler, input.tex);
    //�e�N�X�`���̐F�ɒ��_�f�[�^�̐F���|����
    color = color * input.col;
    // ���肵���F��Ԃ�
    return color;
}