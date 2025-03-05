#include"FedaIn&FedaOut.h"


//コンストラクタ
FedaInOut::FedaInOut(Camera* _p_camera)
	:Object(_p_camera),
	fadaInDecrease(0.04f), fadaOutDecrease(0.04f)
{
}

FedaInOut::~FedaInOut()
{
	this->Finalize();
}

void FedaInOut::Update()
{
	Object::Update();
}

void FedaInOut::FedaOut(bool I_flg)
{
	if (I_flg)
	{
		if (this->color.w < 1.0f)
		{
			this->SetAlpha(color.w += this->fadaOutDecrease);
		     
		}
		else
		{
			this->SetAlpha(1.0f);
			I_flg = false;
			return;
		}

	}
}

void FedaInOut::FedaIn()
{
	if (this->color.w >= 0.0f)
	{
		this->SetAlpha(color.w -= this->fadaInDecrease);
	}
}

void FedaInOut::SetFadaInDecrease(const float _fadaInDecrease)
{
	this->fadaInDecrease = _fadaInDecrease;
}

void FedaInOut::SetFadaOutDecrease(const float _fadaOutDecrease)
{
	this->fadaOutDecrease = _fadaOutDecrease;
}


void	FedaInOut::Draw(void)
{
    Object::Draw();
}

/**	@brief 	シーン全体の終了処理
*	@date	2024/05/10
*/
void	FedaInOut::Finalize(void)
{
}

