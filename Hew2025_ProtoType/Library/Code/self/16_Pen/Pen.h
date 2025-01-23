#pragma once
#include"../10_Object/Object.h"

/**	@file 	Pen.h
*/
class Pen : public Object
{
public:
	//コンストラクタ
	Pen();

	//デストラクタ
	~Pen();

	//終了処理
	void UnInit();

	//更新処理
	void Update();

	//持つ処理
	void have(Object* object);

	//離す処理
	void Release();

	//ペンを運ぶ処理
	void Move(const DirectX::XMFLOAT3 objectPos);

	//ペンを発射する処理
	void Shoot(const DirectX::XMFLOAT3 objectPos);

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
	int h_flag = 0;
};

