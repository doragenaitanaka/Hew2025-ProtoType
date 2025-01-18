//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------

// 頂点のデータを表す構造体（受け取り用）
struct VS_IN
{
    //入力レイアウト側で指定された文字列にあわせたセマンティクスで受け取る
    float4 pos : POSITION;
    float4 col : COLOR0;
    float2 tex : TEX; // UV座標
};

// 頂点のデータを表す構造体（送信用） 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD;
};

// 定数バッファ受け取り用
cbuffer ConstBuffer : register(b0)
{
    matrix matrixWorld; // ワールド変換行列
    matrix matrixView; // ビュー変換行列
    matrix matrixProj; // プロジェクション変換行列
    matrix matrixTex; // UV座標移動行列
    float4 vertexColor; // 頂点カラー
}

// 頂点シェーダーのエントリポイント 
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;

    // ワールド変換行列を頂点座標に掛けて、移動、回転、拡大縮小する
    output.pos = mul(input.pos, matrixWorld);
    // 頂点座標にビュー変換行列を掛ける
    output.pos = mul(output.pos, matrixView);
    // ビュー変換後の頂点座標にプロジェクション変換行列を掛けて、平面の座標にする
    output.pos = mul(output.pos, matrixProj);

    // UV座標を移動させる
    float4 uv;
    uv.xy = input.tex; // 行列掛け算のためfloat4型に移す
    uv.z = 0.0f;
    uv.w = 1.0f;
    uv = mul(uv, matrixTex); // UV座標と移動変換行列を掛け算
    output.tex = uv.xy; // 掛け算の結果を送信用変数にセット

    output.col = input.col * vertexColor; // 頂点カラーのセット

    return output;
}
