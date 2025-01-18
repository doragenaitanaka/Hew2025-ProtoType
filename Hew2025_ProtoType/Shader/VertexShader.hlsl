//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[
//--------------------------------------------------------------------------------------

// ���_�̃f�[�^��\���\���́i�󂯎��p�j
struct VS_IN
{
    //���̓��C�A�E�g���Ŏw�肳�ꂽ������ɂ��킹���Z�}���e�B�N�X�Ŏ󂯎��
    float4 pos : POSITION;
    float4 col : COLOR0;
    float2 tex : TEX; // UV���W
};

// ���_�̃f�[�^��\���\���́i���M�p�j 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD;
};

// �萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register(b0)
{
    matrix matrixWorld; // ���[���h�ϊ��s��
    matrix matrixView; // �r���[�ϊ��s��
    matrix matrixProj; // �v���W�F�N�V�����ϊ��s��
    matrix matrixTex; // UV���W�ړ��s��
    float4 vertexColor; // ���_�J���[
}

// ���_�V�F�[�_�[�̃G���g���|�C���g 
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;

    // ���[���h�ϊ��s��𒸓_���W�Ɋ|���āA�ړ��A��]�A�g��k������
    output.pos = mul(input.pos, matrixWorld);
    // ���_���W�Ƀr���[�ϊ��s����|����
    output.pos = mul(output.pos, matrixView);
    // �r���[�ϊ���̒��_���W�Ƀv���W�F�N�V�����ϊ��s����|���āA���ʂ̍��W�ɂ���
    output.pos = mul(output.pos, matrixProj);

    // UV���W���ړ�������
    float4 uv;
    uv.xy = input.tex; // �s��|���Z�̂���float4�^�Ɉڂ�
    uv.z = 0.0f;
    uv.w = 1.0f;
    uv = mul(uv, matrixTex); // UV���W�ƈړ��ϊ��s����|���Z
    output.tex = uv.xy; // �|���Z�̌��ʂ𑗐M�p�ϐ��ɃZ�b�g

    output.col = input.col * vertexColor; // ���_�J���[�̃Z�b�g

    return output;
}
