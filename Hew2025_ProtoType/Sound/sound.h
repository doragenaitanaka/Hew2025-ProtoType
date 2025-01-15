#pragma once

#include <xaudio2.h>
#include <xaudio2fx.h>
#include <memory>
#include <vector>
#include <string>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001 = 1,			// �T���v��BGM
	SOUND_LABEL_SE000 = 2,	    // �T���v��SE
	SOUND_LABEL_SE001 = 3,			// �T���v��SE



	SOUND_LABEL_MAX,			// �T�E���h�̐�
} SOUND_LABEL;

class Sound {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/Goal-Wo-Nerae.wav", true},	// �T���v��BGM�i���[�v������̂�true�ݒ�j
//		{"asset/BGM/������.wav", true},	    // �T���v��BGM
		{"asset/SE/hit0.wav", false},  	// �T���v��SE�i���[�v���Ȃ��̂�false�ݒ�j
//		{"asset/SE/������.wav", false},		// �T���v��SE



	};


	Sound();//�v���C�x�[�g�R���X�g���N�^
	~Sound();//�v���C�x�[�g�f�X�g���N�^

	//�R���X�g���N�^�̃R�s�[�Ƒ�����Z�q���폜
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];
	float masterVolume;
	std::vector<IXAudio2SourceVoice*> sourceVoices;


	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL label);

	static Sound& getInstance();
	void init();
	void loadsound(const char* filename, IXAudio2SourceVoice** sourceVoice);
	void setMasterVolume(float volume);
	float getMasterVolume()const;

	void addSourceVoice(IXAudio2SourceVoice* sourceVoice);
	IXAudio2* getXAudio2()const;

};


//class AudioManager //�V���O���g���N���X
//{
//private:
//
//	
//	AudioManager() ;//�v���C�x�[�g�R���X�g���N�^
//	~AudioManager() ;//�v���C�x�[�g�f�X�g���N�^
//
//	//�R���X�g���N�^�̃R�s�[�Ƒ�����Z�q���폜
//	AudioManager(const AudioManager&) = delete;
//	AudioManager& operator=(const AudioManager&) = delete;
//
//	IXAudio2* p_XAudio2;
//	IXAudio2MasteringVoice* p_MasterVoice;
//	float masterVolume;
//	std::vector<IXAudio2SourceVoice*> sourceVoices;
//
//
//public:
//	static AudioManager& getInstance();
//	void init();
//	void Uninit();
//	bool loadSound(const std::string& filename, IXAudio2SourceVoice** sourceVoice);
//	void setMasterVolume(float volume);
//	float getMasterVolume() const;
//
//	void addSourceVoice(IXAudio2SourceVoice* sourceVoice);
//	IXAudio2* getXAudio2()const;
//};


