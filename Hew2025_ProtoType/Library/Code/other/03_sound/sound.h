#pragma once

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,		// サンプルBGM

	SOUND_LABEL_SE_SHOT01,

	SOUND_LABEL_MAX,
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
		// サンプルBGM（ループさせる場合true設定）
		{"Asset/SE/Age_of_Discovery.wav", true},	

		// サンプルSE（ループしない場合false設定）
		{"asset/SE/attack01.wav", false},  			
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

	static	Sound* sound;	// サウンド

	Sound() = default;
	~Sound() = default;	
public:
	/**	@brief 	サウンドの生成
	*	@date	2024/12/14
	*	@memo	この関数を始めに実行する
	*/
	static	void	CreateInstance(void);

	/**	@brief 	サウンドの削除
	*	@date	2024/12/14
	*/
	static	void	DestroyInstance(void);

	/**	@brief 	サウンドの取得
	*	@return	Sound*	
	*	@date	2024/12/14
	*	@memo	この関数を使って各ファイルで生成済シーンマネージャーを取得する
	*/
	static	Sound* GetInstance(void);

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
};