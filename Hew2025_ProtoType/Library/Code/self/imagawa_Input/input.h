#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include<iostream>
#include<Xinput.h>
#include<vector>
#include<map>
#pragma comment(lib,"xinput.lib")

/*@brief�@�萔��`�p�b�h����*/
#define XINPUT_A              0x1000	/*@memo �`�{�^���@�@�@�@�@�@�@*/
#define XINPUT_B              0x2000	/*@memo �a�{�^���@�@�@�@�@�@�@*/
#define XINPUT_X              0x4000	/*@memo �w�{�^���@�@�@�@�@�@�@*/
#define XINPUT_Y              0x8000	/*@memo �x�{�^���@�@�@�@�@�@�@*/
#define XINPUT_UP             0x0001	/*@memo �\����{�^���@�@�@�@�@*/
#define XINPUT_DOWN           0x0002	/*@memo �\�����{�^���@�@�@�@�@*/
#define XINPUT_LEFT           0x0004	/*@memo �\�����{�^���@�@�@�@�@*/
#define XINPUT_RIGHT          0x0008	/*@memo �\���E�{�^���@�@�@�@�@*/
#define XINPUT_START          0x0010	/*@memo �H�H�{�^���@�@�@�@�@�@*/
#define XINPUT_BACK           0x0020	/*@memo �H�H�{�^���@�@�@�@�@�@*/
#define XINPUT_LEFT_THUMB     0x0040	/*@memo ���X�e�B�b�N�������݁@*/
#define XINPUT_RIGHT_THUMB    0x0080	/*@memo �E�X�e�B�b�N�������݁@*/
#define XINPUT_LEFT_SHOULDER  0x0100	/*@memo �k�{�^���@�@�@�@�@�@�@*/
#define XINPUT_RIGHT_SHOULDER 0x0200	/*@memo �q�{�^���@�@�@�@�@�@�@*/

//*@brief�@�萔��`�L�[����*/
#define VK_0 0x30	/*@memo �O�L�[*/
#define VK_1 0x31	/*@memo �P�L�[*/
#define VK_2 0x32	/*@memo �Q�L�[*/
#define VK_3 0x33	/*@memo �R�L�[*/
#define VK_4 0x34	/*@memo �S�L�[*/
#define VK_5 0x35	/*@memo �T�L�[*/
#define VK_6 0x36	/*@memo �U�L�[*/
#define VK_7 0x37	/*@memo �V�L�[*/
#define VK_8 0x38	/*@memo �W�L�[*/
#define VK_9 0x39	/*@memo �X�L�[*/
#define VK_A 0x41	/*@memo �`�L�[*/
#define VK_B 0x42	/*@memo �a�L�[*/
#define VK_C 0x43	/*@memo �b�L�[*/
#define VK_D 0x44	/*@memo �c�L�[*/
#define VK_E 0x45	/*@memo �d�L�[*/
#define VK_F 0x46	/*@memo �e�L�[*/
#define VK_G 0x47	/*@memo �f�L�[*/
#define VK_H 0x48	/*@memo �g�L�[*/
#define VK_I 0x49	/*@memo �h�L�[*/
#define VK_J 0x4A	/*@memo �i�L�[*/
#define VK_K 0x4B	/*@memo �j�L�[*/
#define VK_L 0x4C	/*@memo �k�L�[*/
#define VK_M 0x4D	/*@memo �l�L�[*/
#define VK_N 0x4E	/*@memo �m�L�[*/
#define VK_O 0x4F	/*@memo �n�L�[*/
#define VK_P 0x50	/*@memo �o�L�[*/
#define VK_Q 0x51	/*@memo �p�L�[*/
#define VK_R 0x52	/*@memo �q�L�[*/
#define VK_S 0x53	/*@memo �r�L�[*/
#define VK_T 0x54	/*@memo �s�L�[*/
#define VK_U 0x45	/*@memo �t�L�[*/
#define VK_V 0x56	/*@memo �u�L�[*/
#define VK_W 0x57	/*@memo �v�L�[*/
#define VK_X 0x58	/*@memo �w�L�[*/
#define VK_Y 0x59	/*@memo �x�L�[*/
#define VK_Z 0x5A	/*@memo �y�L�[*/


/*@brief�@�񋓌^�F���̓f�o�C�X�̎��*/
enum class InputType
{

	keyboard,
	gamepad,
	mouse

};

/*@brief�@�\���́F���̓}�b�s���O���*/
struct InputMap
{

	InputType type;
	int buttonID;

};


/*@brief�@�A�N�V���������L�[�ɂ��āA�Ή�������̓}�b�s���O���i�[*/
using InputActionMap_t = std::map<std::string, std::vector<InputMap>>;
/*@brief�@�N���X�F�L�[�{�[�h�A�R���g���[���[�A�}�E�X�̓��͂��Ǘ�����N���X*/
class Input
{

private:
	/*@memo�@�����o�ϐ��F���͏��*/

	

	/*@brief�@���݂̓��͏��*/
	BYTE keyState[256] = {};

	/*@brief�@���݂̓��͏��*/
	XINPUT_STATE padState = {};

	/*@brief�@���݂̓��͏��*/
	int mouseState = 0;

	/*@brief�@�A�N�V�������Ɠ��͂̑Ή��t��*/
	InputActionMap_t inputActionMap;

	/*@brief�@���݂̃t���[���̃A�N�V�������*/
	std::map<std::string, bool>currentInput;

	/*@brief�@�P�t���[���O�̃A�N�V�������*/
	std::map<std::string, bool>lastInput;

	/*@brief�@�U���p�����Ԃ��J�E���g����ϐ�*/
	int VibrationTime;

public:

	/*@memo�@�R���X�g���N�^
	 *@brief�@����������
	 */
	Input();

	/*@memo�@�f�X�g���N�^
	 *@brief�@�I������
	 */
	~Input();

	/*@brief�@���͏�Ԃ̍X�V*/
	void Update();

	/*@memo�@�A�i���O�X�e�B�b�N����*/
	/*@brief�@���X�e�B�b�N�̓��͏�Ԃ��擾*/
	DirectX::XMFLOAT2 GetLeftAnalogStick(void);

	/*@brief�@�E�X�e�B�b�N�̓��͏�Ԃ��擾*/
	DirectX::XMFLOAT2 GetRightAnalogStick(void);

	/*@brief�@���g���K�[�̓��͒l���擾*/
	float GetLeftTrigger(void);

	/*@brief�@�E�g���K�[�̓��͒l���擾*/
	float GetRightTrigger(void);

	/*@bruef�@�V�������͏����A�N�V�����ɒǉ�*/
	void a(const std::string& action, const InputMap info);

	/*@brief�@�U��(�R���g���[���[)*/
	/*@memo�@flame�F�U�����p�����鎞��(�P�ʁF�t���[��)*/
	/*@memo�@powoe�F�U���̋���(0�`1)*/
	void SetVibration(int frame = 1, float powor = 1);

	/*@memo�@���͏�Ԃ̊m�F*/
	/*@brief�@Press�i������Ă���Ƃ��j*/
	bool Press(const std::string& action)const;

	/*@brief�@Trigger�i�������u�ԁj*/
	bool Trigger(const std::string& action)const;

	/*@brief�@Release�i�������u�ԁj*/
	bool Release(const std::string& action)const;
};