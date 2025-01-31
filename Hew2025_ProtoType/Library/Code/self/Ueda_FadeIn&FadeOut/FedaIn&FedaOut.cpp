#include"FedaIn&FedaOut.h"


//コンストラクタ
FedaInOut::FedaInOut(Camera* _p_camera) :Object(_p_camera)
{
	this->Init();

}


//初期化
void FedaInOut::Init(void)
{
	this->SetAlpha(color.w = 0.0f);
}

FedaInOut::~FedaInOut()
{
	this->Finalize();
}

void FedaInOut::FedaIn()
{
	this->SetAlpha(color.w =+ 5.0f);
}

void FedaInOut::FedaOut()
{
	this->SetAlpha(color.w =-1.0f);

}


void	FedaInOut::Draw(void)
{
    Object* Draw;
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	FedaInOut::Finalize(void)
{
}

