/**	@file 	Seesaw.h
*	@brief  シーソー
*	@date	2024/12/27
*/
#include "Seesaw.h"
//#include "../../../../Scene/98_Test_Uryu/Test_Uryu.h"

/**	@brief 	コンストラクタ
* @date 2024/12/27
*/
Seesaw::Seesaw(Object* left, Object* right)
    : p_Left(left), p_Right(right), SeesawMoveFlg(false), SeesawDirection(false),
    PlayerOnSeesawL(false), PlayerOnSeesawR(false), BoundFlg(false), OneBoundFlg(false),
    TestCnt(0), seesawSpeed(1.0f)
{
}

/**	@brief 	コンストラクタ
* @date 2024/12/27
*/
Seesaw::~Seesaw()
{
}

/**	@brief 	更新
* @date 2024/12/27
*/
void Seesaw::Update(Object* visualObject)
{
    if (SeesawMoveFlg)
    {
        if (SeesawDirection)
        {
            // シーソーの左端が上がり、右端が下がる
            if (p_Left->GetPos().y < 0.0f && p_Right->GetPos().y > -100.0f)
            {
                p_Left->SetPos(p_Left->GetPos().x, p_Left->GetPos().y + 20.0f, 0.0f);
                p_Right->SetPos(p_Right->GetPos().x, p_Right->GetPos().y - 20.0f, 0.0f);
                visualObject->SetAngle(angle -= 4.0f);
            }
            else
            {
                SeesawMoveFlg = false;
                if (PlayerOnSeesawL)
                {
                    BoundFlg = true;
                }
            }
        }
        else
        {
            // シーソーの右端が上がり、左端が下がる
            if (p_Right->GetPos().y < 0.0f && p_Left->GetPos().y > -100.0f)
            {
                p_Right->SetPos(p_Right->GetPos().x, p_Right->GetPos().y + 20.0f, 0.0f);
                p_Left->SetPos(p_Left->GetPos().x, p_Left->GetPos().y - 20.0f, 0.0f);
                visualObject->SetAngle(angle += 4.0f);
            }
            else
            {
                SeesawMoveFlg = false;
                if (PlayerOnSeesawR)
                {
                    BoundFlg = true;
                }
            }
        }
    }

    if (BoundFlg && OneBoundFlg)
    {
        // プレイヤーを投げ飛ばす処理
        TestCnt++;
        if (TestCnt == 10)
        {
            BoundFlg = false;
            OneBoundFlg = false;
            TestCnt = 0;
        }
    }

    // シーソーが下がりきった状態でもプレイヤーが触れられるようにする
    if (p_Left->GetPos().y <= -100.0f)
    {
        p_Left->SetPos(p_Left->GetPos().x, -100.0f, 0.0f);
    }
    if (p_Right->GetPos().y <= -100.0f)
    {
        p_Right->SetPos(p_Right->GetPos().x, -100.0f, 0.0f);
    }
}

/**	@brief 	当たり判定の確認
* @date 2024/12/27
*/
void Seesaw::CheckCollision(Object* player, Object* box)
{
    auto& col1 = player->GetCollider();
    auto& col2 = p_Right->GetCollider();
    auto& col3 = box->GetCollider();
    auto& col4 = p_Left->GetCollider();

    // シーソーの右端の当たり判定
    if (col1.CheckCollision(col2) && p_Right->GetPos().y >= -100.0f)
    {
        if (player->GetPos().y > p_Right->GetPos().y)
        {
            PlayerOnSeesawR = true;
            player->SetPos(player->GetPos().x, p_Right->GetPos().y + 110.0f, 0.0f);
        }
        else
        {
            if (player->GetPos().x < p_Right->GetPos().x)
            {
                player->SetPos(p_Right->GetPos().x - 100.0f, player->GetPos().y, 0.0f);
            }
            else
            {
                player->SetPos(p_Right->GetPos().x + 100.0f, player->GetPos().y, 0.0f);
            }
        }
    }
    // シーソーの左端の当たり判定
    else if (col1.CheckCollision(col4) && p_Left->GetPos().y >= -100.0f)
    {
        if (player->GetPos().y > p_Left->GetPos().y)
        {
            PlayerOnSeesawL = true;
            player->SetPos(player->GetPos().x, p_Left->GetPos().y + 110.0f, 0.0f);
        }
        else
        {
            if (player->GetPos().x < p_Left->GetPos().x)
            {
                player->SetPos(p_Left->GetPos().x - 100.0f, player->GetPos().y, 0.0f);
            }
            else
            {
                player->SetPos(p_Left->GetPos().x + 100.0f, player->GetPos().y, 0.0f);
            }
        }
    }
    else
    {
        PlayerOnSeesawL = false;
        PlayerOnSeesawR = false;
    }

    // 箱の当たり判定
    if (col2.CheckCollision(col3))
    {
        box->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
        SeesawMoveFlg = true;
        SeesawDirection = true;
        box->SetPos(box->GetPos().x, p_Right->GetPos().y + 100.0f, 0.0f);
    }
    else if (col4.CheckCollision(col3))
    {
        box->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
        SeesawMoveFlg = true;
        SeesawDirection = false;
        box->SetPos(box->GetPos().x, p_Left->GetPos().y + 100.0f, 0.0f);
    }
    else
    {
        box->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    }
}
