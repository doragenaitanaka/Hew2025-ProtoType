/**	@file 	Seesaw.h
*	@brief  シーソーのクラス
*	@date	2024/12/27
*/
#pragma once
//インクルード
#include"10_Object/Object.h"
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
    Seesaw(Object* left, Object* right);
  
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
    void Update(Object* visualObject);

    /**	@brief 	当たり判定確認
    * @date 2024/12/27
    */
    void CheckCollision(Object* player, Object* box);
    
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

private:
    Object* p_Left;
    Object* p_Right;

    bool SeesawMoveFlg; //シーソーが動いているかの判定
    bool SeesawDirection;   //シーソーのどちらが動いているかの判定
    bool PlayerOnSeesawL;   //左のシーソーに乗っているか
    bool PlayerOnSeesawR;   //右のシーソーに乗っているか
    bool BoundFlg;  //跳ね上がるための判定
    bool OneBoundFlg;   //何度も跳ね上がらないようにする判定
    int TestCnt;    //count
    float seesawSpeed;  //シーソーの速度
};
