#pragma once

#include <xaudio2.h>
#include <xaudio2fx.h>
#include <memory>
#include <vector>
#include <string>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	SOUND_LABEL_BGM001 = 1,			// サンプルBGM
	SOUND_LABEL_SE000 = 2,	    // サンプルSE
	SOUND_LABEL_SE001 = 3,			// サンプルSE



	SOUND_LABEL_MAX,			// サウンドの数
} SOUND_LABEL;

class Sound {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"asset/BGM/Goal-Wo-Nerae.wav", true},	// サンプルBGM（ループさせるのでtrue設定）
//		{"asset/BGM/○○○.wav", true},	    // サンプルBGM
		{"asset/SE/hit0.wav", false},  	// サンプルSE（ループしないのでfalse設定）
//		{"asset/SE/○○○.wav", false},		// サンプルSE



	};


	Sound();//プライベートコンストラクタ
	~Sound();//プライベートデストラクタ

	//コンストラクタのコピーと代入演算子を削除
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];
	float masterVolume;
	std::vector<IXAudio2SourceVoice*> sourceVoices;


	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL label);

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL label);

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL label);

	static Sound& getInstance();
	void init();
	void loadsound(const char* filename, IXAudio2SourceVoice** sourceVoice);
	void setMasterVolume(float volume);
	float getMasterVolume()const;

	void addSourceVoice(IXAudio2SourceVoice* sourceVoice);
	IXAudio2* getXAudio2()const;

};


//class AudioManager //シングルトンクラス
//{
//private:
//
//	
//	AudioManager() ;//プライベートコンストラクタ
//	~AudioManager() ;//プライベートデストラクタ
//
//	//コンストラクタのコピーと代入演算子を削除
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


