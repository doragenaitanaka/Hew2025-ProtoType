/**	@file 	GrabBox.h
*	@brief  掴めるオブジェクトのクラス
*	@date	2024/12/21
*/
#pragma once
//インクルード
#include"../10_Object/Object.h"

/**	@file 	GrabBox.h
*	@brief  掴めるオブジェクトのクラス
*	@date	2024/12/21
*/
class GrabBox : public Object
{
public:
	/**	@brief 	コンストラクタ
	* @date 2024/12/21
	*/
	GrabBox();

	/**	@brief 	デストラクタ
	* @date 2024/12/21
	*/
	~GrabBox()override;
	
	/**	@brief 	終了処理
	* @date 2024/12/21
	*/
	void UnInit()override;
	
	/**	@brief 	更新処理
	* @date 2024/12/21
	*/
	void Update()override;

	/**	@brief 	掴み処理
	* @date 2024/12/21
	*/
	void Grab(Object* object);
	
	/**	@brief 	オブジェクトを離す処理
	* @date 2024/12/21
	*/
	void Release();

	/**	@brief 	掴んだ箱を運ぶ処理
	* @date 2024/12/21
	*/
	void Move(const DirectX::XMFLOAT3 objectPos);

	/**	@brief 	GrabStateのゲッター
	* @date 2024/12/21
	*/
	int GetGrabState() const;

	/**	@brief 	GrabStateのセッター
	* @date 2024/12/21
	*/
	void SetGrabState(int state); //セッター
protected:
	Object* p_GrabbedObject; //プレイヤーがオブジェクトを掴んで運ぶ用
	Object* p_Player; //プレイヤーがオブジェクトに捕まる時用
	int GrabState = 0;
};
