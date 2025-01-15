#pragma once
/**	@file 	Seesaw.h
*	@brief  ペンクラス
*	@date	2024/12/24
*/
#pragma once
//インクルード
#include"../Hew2025_ProtoType/Library/Code/self/10_Object/Object.h"
/**	@file 	Seesaw.h
*	@brief  ペンクラス
*	@date	2024/12/24
*/

class Pen : public Object
{
public:
    /**	@brief 	コンストラクタ
    * @date 2024/12/24
    */
    Pen();

    /**	@brief 	デストラクタ
    * @date 2024/12/24
    */
    ~Pen() override;

    /**	@brief 	初期化
    * @date 2024/12/24
    */
    void Uninit();

    /**	@brief 	更新
    * @date 2024/12/24
    */
    void Update(Object* visualObject, Object* p_Right, Object* p_Left, XMFLOAT3 camerapos);

    /**	@brief 	当たり判定確認
    * @date 2024/12/24
    */
    void CheckCollision(Object* player, Object* box, Object* p_Right, Object* p_Left);

    /**	@brief 	ペンを掴んでいるか
    * @date 2024/12/24
    */
	bool Havepen() const { return HavePen; }


	bool HavePen = false;   //ペンを持っているかの判定
    bool SeesawMoveFlg = false; //シーソーが動いているかの判定
    bool Direction = false;   //シーソーのどちらが動いているかの判定
    bool PlayerOnSeesawL = false;   //左のシーソーに乗っているか
    bool PlayerOnSeesawR = false;   //右のシーソーに乗っているか
    bool BoundFlg = false;  //跳ね上がるための判定
    bool OneBoundFlg = false;   //何度も跳ね上がらないようにする判定
    bool JumpFlg = false;
    int TestCnt = 0;    //count
    int Seesawcnt = 0;
    float seesawSpeed = 1.0f;  //シーソーの速度

private:
    Object* p_Left;
    Object* p_Right;
};