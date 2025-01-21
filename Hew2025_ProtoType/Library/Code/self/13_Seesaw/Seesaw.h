/**	@file 	Seesaw.h
*	@brief  シーソーのクラス
*	@date	2024/12/27
*/
#pragma once
//インクルード
#include"../10_Object/Object.h"
/**	@file 	Seesaw.h
*	@brief  シーソーのクラス
*	@date	2024/12/27
*/

class Seesaw : public Object
{
public:
    /**	@brief 	コンストラクタ
    * @date 2024/12/27
    */
    Seesaw(Camera* _p_camera);

    /**	@brief 	デストラクタ
    * @date 2024/12/27
    */
    ~Seesaw() override;

    /**	@brief 	初期化
    * @date 2024/12/27
    */
    void Uninit();

    /**	@brief 	更新
    * @date 2024/12/27
    */
    void Update(Object* visualObject,Object*p_Right,Object* p_Left,XMFLOAT3 camerapos);

    /**	@brief 	当たり判定確認
    * @date 2024/12/27
    */
    void CheckCollision(Object* player, Object* box,Object* p_Right,Object* p_Left);
    
    /**	@brief 	左のシーソーに乗っているか
    * @date 2024/12/27
    */
    bool IsPlayerOnLeft() const { return PlayerOnSeesawL; }
    
    /**	@brief 	右のシーソーに乗っているか
    * @date 2024/12/27
    */
    bool IsPlayerOnRight() const { return PlayerOnSeesawR; }
  
    /**	@brief  跳ね上がったか
    * @date 2024/12/27
    */
    bool IsBound() const { return BoundFlg; }

    /**	@brief 	再度跳ね上がれるように設定
    * @date 2024/12/27
    */
    void ResetBound() { BoundFlg = false; }

    /**	@brief 	ジャンプフラグを返す
    * @date 2024/12/27
    */
    bool CheckJump() { return JumpFlg; }


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
