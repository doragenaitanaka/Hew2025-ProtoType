#pragma once
#include"Library/Code/self/10_Object/Object.h"

class FedaInOut :public Object
{
public:

	//コンストラクタ
	FedaInOut(Camera* _p_camera);

	//デストラクタ
	~FedaInOut();
	
	//初期化
	void Init(void);

	

	//描画
	void Draw(void)override;

	//終了
	void Finalize(void);


	void FedaIn(void);
	void FedaOut(void);

private:
	
};


