#include"../imagawa_Input/input.h"

/*@brief　コンストラクタ: アクション名と対応する入力（キーボード、ゲームパッド）を設定*/
Input::Input()
{
    /**@brief　振動時間*/
    VibrationTime = 0;

    /*@brief　アクション名とキー/ボタンをマッピング
      @memo　 キー入力、パッド入力の定数定義は"input.h"の一番上を参考に
      @memo　テンプレート：inputActionMap["アクション名"] = { {InputType::keyboard, VK_}, {InputType::gamepad, XINPUT_} };
    */
    inputActionMap["RIGHT"] = { {InputType::keyboard, VK_RIGHT}, {InputType::gamepad, XINPUT_RIGHT},{InputType::gamepad, XINPUT_RIGHT} };
    inputActionMap["LEFT"]  = { {InputType::keyboard, VK_LEFT}, {InputType::gamepad, XINPUT_LEFT } };
    inputActionMap["UP"]   = { {InputType::keyboard, VK_UP}, {InputType::gamepad, XINPUT_UP   } };
    inputActionMap["DOWN"] = { {InputType::keyboard, VK_DOWN}, {InputType::gamepad, XINPUT_DOWN } };
    inputActionMap["SPACE"] = { {InputType::keyboard, VK_SPACE}, {InputType::gamepad, XINPUT_A } };
    inputActionMap["SHIFT"] = { {InputType::keyboard, VK_SHIFT},  };
    inputActionMap["CHANGEMODE0"] = { {InputType::keyboard, VK_A},};
    inputActionMap["CHANGEMODE1"] = { {InputType::keyboard, VK_D}, };
    inputActionMap["SUPERJUMP"] = { {InputType::keyboard, VK_CONTROL}, {InputType::gamepad, XINPUT_LEFT_SHOULDER  } };

    inputActionMap["L1"] = { {InputType::keyboard, VK_LEFT}, {InputType::gamepad, XINPUT_LEFT_SHOULDER  } };
    inputActionMap["R1"] = { {InputType::keyboard, VK_RIGHT}, {InputType::gamepad, XINPUT_RIGHT_SHOULDER  } };


    /*@brief　入力状態を初期化*/
    for (const auto& mapInfo : inputActionMap)
    {

        /*@memo　現在の状態*/
        currentInput[mapInfo.first] = false;

        /*@memo　前フレームの状態*/
        lastInput[mapInfo.first] = false;

    }
}

/*@brief　デストラクタ*/
Input::~Input()
{
    /**@brief　振動を終了させる*/
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(0, &vibration);
}

/*@brief　入力状態を更新する関数*/
void Input::Update()
{

    /*@brief　1フレーム前のキー状態を保存*/
    lastInput = currentInput;

    /*@brief　キーボード状態の更新*/
    BOOL hr = GetKeyboardState(keyState);

    /*@brief　コントローラー状態の更新*/
    XInputGetState(0, &padState);

    /*@brief　各アクションについて現在の入力状態を更新*/
    for (const auto& mapInfo : inputActionMap)
    {

        /*@brief　このアクションが押されているか*/
        bool isPressed = false;

        /*@brief　アクションに割り当てられたすべての入力を確認*/
        for (const auto& inputInfo : mapInfo.second)
        {

            /*@brief　キーボードの入力判定*/
            if (inputInfo.type == InputType::keyboard && (keyState[inputInfo.buttonID] & 0x80)) 
            {

                isPressed = true;

            }

            /*@brief　コントローラーの入力判定*/
            if (inputInfo.type == InputType::gamepad && (padState.Gamepad.wButtons & inputInfo.buttonID)) 
            {

                isPressed = true;

            }

            /*@brief　マウスの入力判定*/
            if (inputInfo.type == InputType::mouse && (mouseState & inputInfo.buttonID)) 
            {

                isPressed = true;

            }

            /*@brief　いずれかが押されていたら判定終了*/
            if (isPressed) { break;}

        }

       /*@brief　現在の入力判定を保存*/
        currentInput[mapInfo.first] = isPressed;
    }
    /*@brief　振動継続時間をカウント*/
    if (VibrationTime > 0) {
        VibrationTime--;
        if (VibrationTime == 0)
        { /*@brief　振動継続時間が経った時に振動を止める*/
            XINPUT_VIBRATION vibration;
            ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
            vibration.wLeftMotorSpeed = 0;
            vibration.wRightMotorSpeed = 0;
            XInputSetState(0, &vibration);
        }
    }
}

/*@brieg　アクションが現在押されているか確認*/
bool Input::Press(const std::string& action) const
{

    /*@brief　現在と前フレームの入力状態を取得*/
    auto it = currentInput.find(action);

    /*@brief　押されていればtrue*/
    return (it != currentInput.end()) && it->second; 

}

/*@brieg　アクションが押された瞬間か確認*/
bool Input::Trigger(const std::string& action) const
{

    /*@brief　現在と前フレームの入力状態を取得*/
    auto itCurrent = currentInput.find(action);
    auto itLast = lastInput.find(action);

    /*@brief　アクションが定義されていなければfalse*/
    if (itCurrent == currentInput.end() || itLast == lastInput.end())
    {

        return false;

    }

    /*@brief　現在押されていて、前フレームで押されていない場合*/
    return itCurrent->second && !itLast->second; 

}

/*@brieg　アクションが離された瞬間か確認*/
bool Input::Release(const std::string& action) const
{

    /*@brief　現在と前フレームの入力状態を取得*/
    auto itCurrent = currentInput.find(action);
    auto itLast = lastInput.find(action);

    /*@brief　アクションが定義されていなければfalse*/
    if (itCurrent == currentInput.end() || itLast == lastInput.end())
    {

        return false;

    }

    /*@brief　現在は押されていなくて、前フレームでは押されていた場合*/
    return !itCurrent->second && itLast->second;

}

/*@memo　DX21から抜粋*/
/**@brief 左アナログスティック*/
DirectX::XMFLOAT2 Input::GetLeftAnalogStick(void)
{
    SHORT x = padState.Gamepad.sThumbLX; // -32768～32767
    SHORT y = padState.Gamepad.sThumbLY; // -32768～32767

    DirectX::XMFLOAT2 res;
    res.x = x / 32767.0f; //-1～1
    res.y = y / 32767.0f; //-1～1
    return res;
}

/**@brief 右アナログスティック*/
DirectX::XMFLOAT2 Input::GetRightAnalogStick(void)
{
    SHORT x =padState.Gamepad.sThumbRX; // -32768～32767
    SHORT y =padState.Gamepad.sThumbRY; // -32768～32767

    DirectX::XMFLOAT2 res;
    res.x = x / 32767.0f; //-1～1
    res.y = y / 32767.0f; //-1～1
    return res;
}

/**@brief　左トリガー*/
float Input::GetLeftTrigger(void)
{
    BYTE t = padState.Gamepad.bLeftTrigger; // 0～255
    return t / 255.0f;
}

/**@brief　右トリガー*/
float Input::GetRightTrigger(void)
{
    BYTE t = padState.Gamepad.bRightTrigger; // 0～255
    return t / 255.0f;
}

/** @brief　振動の処理*/
void Input::SetVibration(int frame, float powor)
{
    /**@brief　XINPUT_VIBRATION構造体のインスタンスを作成*/
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

    /**@brief モーターの強度を設定（0～65535）*/
    vibration.wLeftMotorSpeed = (WORD)(powor * 65535.0f);
    vibration.wRightMotorSpeed = (WORD)(powor * 65535.0f);
    XInputSetState(0, &vibration);

    /**@brief　振動継続時間を代入*/
    VibrationTime = frame;
}

bool Input::IsStickCheck(const DirectX::XMFLOAT2& stick, float deadZone)
{
    // ベクトルの長さを計算
    float magnitude = std::sqrt(stick.x * stick.x + stick.y * stick.y);

    // デッドゾーンを超えているかを判定
    return magnitude > deadZone;
}
