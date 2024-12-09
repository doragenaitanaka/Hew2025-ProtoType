//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------

// ピクセルの情報の構造体（受け取り用）
struct PS_IN
{
    //float4型　→　float型が４つの構造体
    float4 pos : SV_POSITION;   // ピクセルの画面上の座標
    float4 col : COLOR0;        //  ピクセル上のカラー値
    float2 tex : TEXCOORD;      // ピクセルのUV座標
};

//struct PS_OUT
//{
//    float4 pos : SV_POSITION;   // ピクセルの画面上の座標
//    float4 col : COLOR0;        //  ピクセル上のカラー値
//};

// グローバル変数の宣言
// ※C言語からデータを渡された時にセットされる変数
Texture2D myTexture : register(t0);     // テクスチャ
SamplerState mySampler : register(s0);  // サンプラー
    
// ピクセルシェーダーのエントリポイント
float4 ps_main(PS_IN input) : SV_Target
{   
    //Sample関数→テクスチャから該当のV位置のピクセル色をとってくる
    float4 color = myTexture.Sample(mySampler, input.tex);
    //テクスチャの色に頂点データの色を掛ける
    color = color * input.col;
    // 決定した色を返す
    return color;
}
