#pragma once
#include"../10_Object/Object.h"

class Background :public Object
{
public:
	Background(Camera* _p_camera);
	~Background()override;

	/**	@brief 	オブジェクトの更新
	*/
	void	Update(void)override;

	/**	@brief	定数バッファの更新
	*/
	void	ConstantBufferUpdate(void)override;
};
