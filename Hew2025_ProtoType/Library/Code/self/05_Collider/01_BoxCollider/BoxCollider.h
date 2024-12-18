#pragma once
#include "../00_BaseCollider/BaseCollider.h"
#include "../02_CircleCollider/CircleCollider.h"
class BoxCollider : public BaseCollider
{
private:
    DirectX::XMFLOAT3 size;

public:

	/**	@brief  コンストラクタ
	*	@date	2024/12/16
	*/
    //BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size);
	BoxCollider(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _size);

	/**	@brief  デストラクタ
	*	@date	2024/12/16
	*/
    ~BoxCollider();


	/**	@brief  サイズの変更
	*	@date	2024/12/15
	*	@param XMFLOAT3 _size 変更したいサイズの値
	*	@return	bool idk 接触しているか
	*/
    void SetSize(DirectX::XMFLOAT3);


	/**	@brief  サイズの取得
	*	@date	2024/12/16
	*	@return	XMFLOAT3 size Objectのサイズ
	*/
    DirectX::XMFLOAT3 GetSize(void);

	/**	@brief  円との当たり判定
	*	@date	2024/12/15
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	bool CheckCollisionCircle(BaseCollider& _other) override;

	/**	@brief  矩形との当たり判定
	*	@date	2024/12/15
	*	@param  BaseCollider& idk 接触判定を取る対象オブジェクト
	*	@return	bool idk 接触しているか
	*/
	bool CheckCollisionRectangle(BaseCollider& _other) override;
};


