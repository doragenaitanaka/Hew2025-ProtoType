#pragma once
/**	@file 	Seesaw.h
*	@brief  �y���N���X
*	@date	2024/12/24
*/
#pragma once
//�C���N���[�h
#include"../Hew2025_ProtoType/Library/Code/self/10_Object/Object.h"
/**	@file 	Seesaw.h
*	@brief  �y���N���X
*	@date	2024/12/24
*/

class Pen : public Object
{
public:
    /**	@brief 	�R���X�g���N�^
    * @date 2024/12/24
    */
    Pen();

    /**	@brief 	�f�X�g���N�^
    * @date 2024/12/24
    */
    ~Pen() override;

    /**	@brief 	������
    * @date 2024/12/24
    */
    void Uninit();

    /**	@brief 	�X�V
    * @date 2024/12/24
    */
    void Update(Object* visualObject, Object* p_Right, Object* p_Left, XMFLOAT3 camerapos);

    /**	@brief 	�����蔻��m�F
    * @date 2024/12/24
    */
    void CheckCollision(Object* player, Object* box, Object* p_Right, Object* p_Left);

    /**	@brief 	�y����͂�ł��邩
    * @date 2024/12/24
    */
	bool Havepen() const { return HavePen; }


	bool HavePen = false;   //�y���������Ă��邩�̔���
    bool SeesawMoveFlg = false; //�V�[�\�[�������Ă��邩�̔���
    bool Direction = false;   //�V�[�\�[�̂ǂ��炪�����Ă��邩�̔���
    bool PlayerOnSeesawL = false;   //���̃V�[�\�[�ɏ���Ă��邩
    bool PlayerOnSeesawR = false;   //�E�̃V�[�\�[�ɏ���Ă��邩
    bool BoundFlg = false;  //���ˏオ�邽�߂̔���
    bool OneBoundFlg = false;   //���x�����ˏオ��Ȃ��悤�ɂ��锻��
    bool JumpFlg = false;
    int TestCnt = 0;    //count
    int Seesawcnt = 0;
    float seesawSpeed = 1.0f;  //�V�[�\�[�̑��x

private:
    Object* p_Left;
    Object* p_Right;
};