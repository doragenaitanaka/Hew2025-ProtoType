#pragma once
#include"../10_Object/Object.h"
#include<cmath>



//2Dベクトル構造体
struct Vector2
{
	float x;
	float y;

	Vector2(): x(0), y(0) {}
	Vector2(float x,float y):x(x),y(y){}
};

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

	//ペンのアングルを+する処理
	void Rotate(Object* objectangle);

	//ペンのアングルを-する処理
	void Rotate2(Object* objectangle);

	/*//ペンのアングルを変える処理
	void Rotate(float angle);

	//ペンのアングルを変える処理
	void Rotate2(float angle);*/

	//ペンのアングルをリセットする処理
	void Reset(Object* objectangle);

	//ペンを発射する処理
	void Shoot(float speed,float DeltaTime);

	/**	@brief 	GrabStateのゲッター
	* @date 2024/12/21
	*/
	int GetGrabState() const;

	/**	@brief 	GrabStateのセッター
	* @date 2024/12/21
	*/
	void SetGrabState(int state); //セッター

	Vector2 p_position;
	Vector2 p_velocity;
	float Angle;

protected:
	Object* p_GrabbedObject; //プレイヤーがオブジェクトを掴んで運ぶ用
	Object* p_Player; //プレイヤーがオブジェクトに捕まる時用
	int h_flag = 0;
	static float DegToRed(float degrees);
};

