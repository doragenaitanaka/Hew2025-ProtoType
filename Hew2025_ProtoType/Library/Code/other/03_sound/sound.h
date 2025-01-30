#pragma once

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	// BGM
	BGM_TITLE = 0,		
	BGM_GAME,

	// SE
	SE_GOAL,
	SE_UI_CLICK,
	SE_PLAYR_JUMP,
	SE_PLAYR_LEAP,
	SE_PLAYR_PICK,
	SE_PLAYR_DROP,
	SE_PLAYR_DEAD,
	SE_PLAYR_FALLDEAD,
	SE_PLAYR_FALLDOWN,
	SE_PLAYR_MOVEHOOK,
	SE_PLAYR_STRETCH,
	SE_PLAYR_VIVRATION,
	SE_PLAYR_PENSHOT,


	SE_GMMICK_PENHIT,

	SOUND_LABEL_MAX
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
		// タイトルBGM（ループさせる場合true設定）
		{"Asset/BGM/TitleBGM.wav", true},	

		// ゲームBGM（ループさせる場合true設定）
		{"Asset/BGM/GameBGM.wav", true},

		// ゴールSE（ループさせる場合true設定）
		{"Asset/SE/StageClear.wav", false},

		// UIクリックSE（ループしない場合false設定）
		{"Asset/SE/Click.wav", false},  	

		// PlayerジャンプSE（ループしない場合false設定）
		{"Asset/SE/Jump.wav", false},

		// PlayerぶっとびSE（ループしない場合false設定）
		{"Asset/SE/RubberJump.wav", false},

		// Player拾うSE（ループしない場合false設定）
		{"Asset/SE/ItemPickup.wav", false},

		// Player捨てるSE（ループしない場合false設定）
		{"Asset/SE/ItemDrop.wav", false},

		// Player死亡SE（ループしない場合false設定）
		{"Asset/SE/PlayerDeadScream.wav", false},

		// Player落下死SE（ループしない場合false設定）
		{"Asset/SE/FallDead.wav", false},

		// Player物倒れるSE（ループしない場合false設定）
		{"Asset/SE/ObjectFallDown.wav", false},

		// PlayerレールSE（ループしない場合false設定）
		{"Asset/SE/HookRail.wav", false},

		// PlayerストレッチSE（ループしない場合false設定）
		{"Asset/SE/nobiru.wav", false},

		// Player千切れて死にそうな時になるSE（ループしない場合false設定）
		{"Asset/SE/vibration.wav", false},

		// Playerペンを投げるSE（ループしない場合false設定）
		{"Asset/SE/RubberJump.wav", false},

		// Gimmickペンが刺さる音SE（ループしない場合false設定）
		{"Asset/SE/ArrowHit.wav", false},
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