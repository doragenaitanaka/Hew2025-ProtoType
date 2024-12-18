#include"../../Library/Code/self/imagawa_Input/input.h"

/*@brief�@�R���X�g���N�^: �A�N�V�������ƑΉ�������́i�L�[�{�[�h�A�Q�[���p�b�h�j��ݒ�*/
Input::Input()
{
    /**@brief�@�U������*/
    VibrationTime = 0;

    /*@brief�@�A�N�V�������ƃL�[/�{�^�����}�b�s���O
      @memo�@ �L�[���́A�p�b�h���͂̒萔��`��"input.h"�̈�ԏ���Q�l��
      @memo�@�e���v���[�g�FinputActionMap["�A�N�V������"] = { {InputType::keyboard, VK_}, {InputType::gamepad, XINPUT_} };
    */
    inputActionMap["RIGHT"] = { {InputType::keyboard, VK_D}, {InputType::gamepad, XINPUT_RIGHT} };
    inputActionMap["LEFT"]  = { {InputType::keyboard, VK_A}, {InputType::gamepad, XINPUT_LEFT } };
    inputActionMap["UP" ]   = { {InputType::keyboard, VK_W}, {InputType::gamepad, XINPUT_UP   } };
    inputActionMap["DOWN" ] = { {InputType::keyboard, VK_S}, {InputType::gamepad, XINPUT_DOWN } };

    /*@brief�@���͏�Ԃ�������*/
    for (const auto& mapInfo : inputActionMap)
    {

        /*@memo�@���݂̏��*/
        currentInput[mapInfo.first] = false;

        /*@memo�@�O�t���[���̏��*/
        lastInput[mapInfo.first] = false;

    }

}

/*@brief�@�f�X�g���N�^*/
Input::~Input()
{
    /**@brief�@�U�����I��������*/
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(0, &vibration);
}

/*@brief�@���͏�Ԃ��X�V����֐�*/
void Input::Update()
{

    /*@brief�@1�t���[���O�̃L�[��Ԃ�ۑ�*/
    lastInput = currentInput;

    /*@brief�@�L�[�{�[�h��Ԃ̍X�V*/
    BOOL hr = GetKeyboardState(keyState);

    /*@brief�@�R���g���[���[��Ԃ̍X�V*/
    XInputGetState(0, &padState);

    /*@brief�@�e�A�N�V�����ɂ��Č��݂̓��͏�Ԃ��X�V*/
    for (const auto& mapInfo : inputActionMap)
    {

        /*@brief�@���̃A�N�V������������Ă��邩*/
        bool isPressed = false;

        /*@brief�@�A�N�V�����Ɋ��蓖�Ă�ꂽ���ׂĂ̓��͂��m�F*/
        for (const auto& inputInfo : mapInfo.second)
        {

            /*@brief�@�L�[�{�[�h�̓��͔���*/
            if (inputInfo.type == InputType::keyboard && (keyState[inputInfo.buttonID] & 0x80)) 
            {

                isPressed = true;

            }

            /*@brief�@�R���g���[���[�̓��͔���*/
            if (inputInfo.type == InputType::gamepad && (padState.Gamepad.wButtons & inputInfo.buttonID)) 
            {

                isPressed = true;

            }

            /*@brief�@�}�E�X�̓��͔���*/
            if (inputInfo.type == InputType::mouse && (mouseState & inputInfo.buttonID)) 
            {

                isPressed = true;

            }

            /*@brief�@�����ꂩ��������Ă����画��I��*/
            if (isPressed) { break;}

        }

       /*@brief�@���݂̓��͔����ۑ�*/
        currentInput[mapInfo.first] = isPressed;
    }
    /*@brief�@�U���p�����Ԃ��J�E���g*/
    if (VibrationTime > 0) {
        VibrationTime--;
        if (VibrationTime == 0)
        { /*@brief�@�U���p�����Ԃ��o�������ɐU�����~�߂�*/
            XINPUT_VIBRATION vibration;
            ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
            vibration.wLeftMotorSpeed = 0;
            vibration.wRightMotorSpeed = 0;
            XInputSetState(0, &vibration);
        }
    }

}

/*@brieg�@�A�N�V���������݉�����Ă��邩�m�F*/
bool Input::Press(const std::string& action) const
{

    /*@brief�@���݂ƑO�t���[���̓��͏�Ԃ��擾*/
    auto it = currentInput.find(action);

    /*@brief�@������Ă����true*/
    return (it != currentInput.end()) && it->second; 

}

/*@brieg�@�A�N�V�����������ꂽ�u�Ԃ��m�F*/
bool Input::Trigger(const std::string& action) const
{

    /*@brief�@���݂ƑO�t���[���̓��͏�Ԃ��擾*/
    auto itCurrent = currentInput.find(action);
    auto itLast = lastInput.find(action);

    /*@brief�@�A�N�V��������`����Ă��Ȃ����false*/
    if (itCurrent == currentInput.end() || itLast == lastInput.end())
    {

        return false;

    }

    /*@brief�@���݉�����Ă��āA�O�t���[���ŉ�����Ă��Ȃ��ꍇ*/
    return itCurrent->second && !itLast->second; 

}

/*@brieg�@�A�N�V�����������ꂽ�u�Ԃ��m�F*/
bool Input::Release(const std::string& action) const
{

    /*@brief�@���݂ƑO�t���[���̓��͏�Ԃ��擾*/
    auto itCurrent = currentInput.find(action);
    auto itLast = lastInput.find(action);

    /*@brief�@�A�N�V��������`����Ă��Ȃ����false*/
    if (itCurrent == currentInput.end() || itLast == lastInput.end())
    {

        return false;

    }

    /*@brief�@���݂͉�����Ă��Ȃ��āA�O�t���[���ł͉�����Ă����ꍇ*/
    return !itCurrent->second && itLast->second;

}

/*@memo�@DX21���甲��*/
/**@brief ���A�i���O�X�e�B�b�N*/
DirectX::XMFLOAT2 Input::GetLeftAnalogStick(void)
{
    SHORT x = padState.Gamepad.sThumbLX; // -32768�`32767
    SHORT y = padState.Gamepad.sThumbLY; // -32768�`32767

    DirectX::XMFLOAT2 res;
    res.x = x / 32767.0f; //-1�`1
    res.y = y / 32767.0f; //-1�`1
    return res;
}

/**@brief �E�A�i���O�X�e�B�b�N*/
DirectX::XMFLOAT2 Input::GetRightAnalogStick(void)
{
    SHORT x =padState.Gamepad.sThumbRX; // -32768�`32767
    SHORT y =padState.Gamepad.sThumbRY; // -32768�`32767

    DirectX::XMFLOAT2 res;
    res.x = x / 32767.0f; //-1�`1
    res.y = y / 32767.0f; //-1�`1
    return res;
}

/**@brief�@���g���K�[*/
float Input::GetLeftTrigger(void)
{
    BYTE t = padState.Gamepad.bLeftTrigger; // 0�`255
    return t / 255.0f;
}

/**@brief�@�E�g���K�[*/
float Input::GetRightTrigger(void)
{
    BYTE t = padState.Gamepad.bRightTrigger; // 0�`255
    return t / 255.0f;
}

/** @brief�@�U���̏���*/
void Input::SetVibration(int frame, float powor)
{
    /**@brief�@XINPUT_VIBRATION�\���̂̃C���X�^���X���쐬*/
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

    /**@brief ���[�^�[�̋��x��ݒ�i0�`65535�j*/
    vibration.wLeftMotorSpeed = (WORD)(powor * 65535.0f);
    vibration.wRightMotorSpeed = (WORD)(powor * 65535.0f);
    XInputSetState(0, &vibration);

    /**@brief�@�U���p�����Ԃ���*/
    VibrationTime = frame;
}