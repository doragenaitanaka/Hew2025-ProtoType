#pragma once
#include"../10_Object/Object.h"

class FedaInOut :public Object
{
public:

	//コンストラクタ
	FedaInOut(Camera* _p_camera);

	//デストラクタ
	~FedaInOut();

	//更新
	void Update(void)override;

	//描画
	void Draw(void)override;

	//終了
	void Finalize(void);

	//フェードアウト
	void FedaOut(bool I_flg=false);
	//フェードイン
	void FedaIn();

	// 減らしていく透明度を設定する
	void SetFadaInDecrease(const float _fadaInDecrease);
	void SetFadaOutDecrease(const float _fadaOutDecrease);

private:
	// 減らしていく透明度
	float fadaInDecrease;	
	float fadaOutDecrease;	
};


