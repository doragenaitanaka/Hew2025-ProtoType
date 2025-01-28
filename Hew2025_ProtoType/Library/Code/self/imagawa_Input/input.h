#pragma once
#include<d3d11.h>
#include<DirectXMath.h>
#include<iostream>
#include<Xinput.h>
#include<vector>
#include<map>
#pragma comment(lib,"xinput.lib")

/*@brief　定数定義パッド入力*/
#define XINPUT_A              0x1000	/*@memo Ａボタン　　　　　　　*/
#define XINPUT_B              0x2000	/*@memo Ｂボタン　　　　　　　*/
#define XINPUT_X              0x4000	/*@memo Ｘボタン　　　　　　　*/
#define XINPUT_Y              0x8000	/*@memo Ｙボタン　　　　　　　*/
#define XINPUT_UP             0x0001	/*@memo 十字上ボタン　　　　　*/
#define XINPUT_DOWN           0x0002	/*@memo 十字下ボタン　　　　　*/
#define XINPUT_LEFT           0x0004	/*@memo 十字左ボタン　　　　　*/
#define XINPUT_RIGHT          0x0008	/*@memo 十字右ボタン　　　　　*/
#define XINPUT_START          0x0010	/*@memo ？？ボタン　　　　　　*/
#define XINPUT_BACK           0x0020	/*@memo ？？ボタン　　　　　　*/
#define XINPUT_LEFT_THUMB     0x0040	/*@memo 左スティック押し込み　*/
#define XINPUT_RIGHT_THUMB    0x0080	/*@memo 右スティック押し込み　*/
#define XINPUT_LEFT_SHOULDER  0x0100	/*@memo Ｌボタン　　　　　　　*/
#define XINPUT_RIGHT_SHOULDER 0x0200	/*@memo Ｒボタン　　　　　　　*/

//*@brief　定数定義キー入力*/
#define VK_0 0x30	/*@memo ０キー*/
#define VK_1 0x31	/*@memo １キー*/
#define VK_2 0x32	/*@memo ２キー*/
#define VK_3 0x33	/*@memo ３キー*/
#define VK_4 0x34	/*@memo ４キー*/
#define VK_5 0x35	/*@memo ５キー*/
#define VK_6 0x36	/*@memo ６キー*/
#define VK_7 0x37	/*@memo ７キー*/
#define VK_8 0x38	/*@memo ８キー*/
#define VK_9 0x39	/*@memo ９キー*/
#define VK_A 0x41	/*@memo Ａキー*/
#define VK_B 0x42	/*@memo Ｂキー*/
#define VK_C 0x43	/*@memo Ｃキー*/
#define VK_D 0x44	/*@memo Ｄキー*/
#define VK_E 0x45	/*@memo Ｅキー*/
#define VK_F 0x46	/*@memo Ｆキー*/
#define VK_G 0x47	/*@memo Ｇキー*/
#define VK_H 0x48	/*@memo Ｈキー*/
#define VK_I 0x49	/*@memo Ｉキー*/
#define VK_J 0x4A	/*@memo Ｊキー*/
#define VK_K 0x4B	/*@memo Ｋキー*/
#define VK_L 0x4C	/*@memo Ｌキー*/
#define VK_M 0x4D	/*@memo Ｍキー*/
#define VK_N 0x4E	/*@memo Ｎキー*/
#define VK_O 0x4F	/*@memo Ｏキー*/
#define VK_P 0x50	/*@memo Ｐキー*/
#define VK_Q 0x51	/*@memo Ｑキー*/
#define VK_R 0x52	/*@memo Ｒキー*/
#define VK_S 0x53	/*@memo Ｓキー*/
#define VK_T 0x54	/*@memo Ｔキー*/
#define VK_U 0x45	/*@memo Ｕキー*/
#define VK_V 0x56	/*@memo Ｖキー*/
#define VK_W 0x57	/*@memo Ｗキー*/
#define VK_X 0x58	/*@memo Ｘキー*/
#define VK_Y 0x59	/*@memo Ｙキー*/
#define VK_Z 0x5A	/*@memo Ｚキー*/


/*@brief　列挙型：入力デバイスの種類*/
enum class InputType
{

	keyboard,
	gamepad,
	mouse

};

/*@brief　構造体：入力マッピング情報*/
struct InputMap
{

	InputType type;
	int buttonID;

};


/*@brief　アクション名をキーにして、対応する入力マッピングを格納*/
using InputActionMap_t = std::map<std::string, std::vector<InputMap>>;
/*@brief　クラス：キーボード、コントローラー、マウスの入力を管理するクラス*/
class Input
{

private:
	/*@memo　メンバ変数：入力状態*/

	

	/*@brief　現在の入力状態*/
	BYTE keyState[256] = {};

	/*@brief　現在の入力状態*/
	XINPUT_STATE padState = {};

	/*@brief　現在の入力状態*/
	int mouseState = 0;

	/*@brief　アクション名と入力の対応付け*/
	InputActionMap_t inputActionMap;

	/*@brief　現在のフレームのアクション状態*/
	std::map<std::string, bool>currentInput;

	/*@brief　１フレーム前のアクション状態*/
	std::map<std::string, bool>lastInput;

	/*@brief　振動継続時間をカウントする変数*/
	int VibrationTime;

public:

	/*@memo　コンストラクタ
	 *@brief　初期化処理
	 */
	Input();

	/*@memo　デストラクタ
	 *@brief　終了処理
	 */
	~Input();

	/*@brief　入力状態の更新*/
	void Update();

	/*@memo　アナログスティック操作*/
	/*@brief　左スティックの入力状態を取得*/
	DirectX::XMFLOAT2 GetLeftAnalogStick(void);

	/*@brief　右スティックの入力状態を取得*/
	DirectX::XMFLOAT2 GetRightAnalogStick(void);

	/*@brief　左トリガーの入力値を取得*/
	float GetLeftTrigger(void);

	/*@brief　右トリガーの入力値を取得*/
	float GetRightTrigger(void);

	/*@bruef　新しい入力情報をアクションに追加*/
	void a(const std::string& action, const InputMap info);

	/*@brief　振動(コントローラー)*/
	/*@memo　flame：振動を継続する時間(単位：フレーム)*/
	/*@memo　powoe：振動の強さ(0～1)*/
	void SetVibration(int frame = 1, float powor = 1);

	/*@memo　入力状態の確認*/
	/*@brief　Press（押されているとき）*/
	bool Press(const std::string& action)const;

	/*@brief　Trigger（押した瞬間）*/
	bool Trigger(const std::string& action)const;

	/*@brief　Release（離した瞬間）*/
	bool Release(const std::string& action)const;
};