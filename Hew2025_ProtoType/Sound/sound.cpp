#include "sound.h"
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

////=============================================================================
//// 初期化
////=============================================================================
//HRESULT Sound::Init()
//{
//	HRESULT hr;
//
//	HANDLE hFile;
//	DWORD  dwChunkSize;
//	DWORD  dwChunkPosition;
//	DWORD  filetype;
//
//	// COMの初期化
//	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	if (FAILED(hr)) {
//		CoUninitialize();
//		return -1;
//	}
//
//	/**** Create XAudio2 ****/
//	hr = XAudio2Create(&m_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
//	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
//	if (FAILED(hr)) {
//		CoUninitialize();
//		return -1;
//	}
//
//	/**** Create Mastering Voice ****/
//	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
//	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
//	if (FAILED(hr)) {
//		if (m_pXAudio2)	m_pXAudio2->Release();
//		CoUninitialize();
//		return -1;
//	}
//
//	/**** Initalize Sound ****/
//	for (int i = 0; i < SOUND_LABEL_MAX; i++)
//	{
//		memset(&m_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
//		memset(&m_buffer[i], 0, sizeof(XAUDIO2_BUFFER));
//
//		hFile = CreateFileA(m_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
//			OPEN_EXISTING, 0, NULL);
//		if (hFile == INVALID_HANDLE_VALUE) {
//			return HRESULT_FROM_WIN32(GetLastError());
//		}
//		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
//			return HRESULT_FROM_WIN32(GetLastError());
//		}
//
//		//check the file type, should be fourccWAVE or 'XWMA'
//		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
//		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
//		if (filetype != fourccWAVE)		return S_FALSE;
//
//		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
//		ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition);
//
//		//fill out the audio data buffer with the contents of the fourccDATA chunk
//		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
//		m_DataBuffer[i] = new BYTE[dwChunkSize];
//		ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition);
//
//		CloseHandle(hFile);
//
//		// 	サブミットボイスで利用するサブミットバッファの設定
//		m_buffer[i].AudioBytes = dwChunkSize;
//		m_buffer[i].pAudioData = m_DataBuffer[i];
//		m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
//		if (m_param[i].bLoop)
//			m_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
//		else
//			m_buffer[i].LoopCount = 0;
//
//		m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format));
//	}
//
//	return hr;
//}
//
////=============================================================================
//// 開放処理
////=============================================================================
//void Sound::Uninit(void)
//{
//	for (int i = 0; i < SOUND_LABEL_MAX; i++)
//	{
//		if (m_pSourceVoice[i])
//		{
//			m_pSourceVoice[i]->Stop(0);
//			m_pSourceVoice[i]->FlushSourceBuffers();
//			m_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
//			delete[]  m_DataBuffer[i];
//		}
//	}
//
//	m_pMasteringVoice->DestroyVoice();
//
//	if (m_pXAudio2) m_pXAudio2->Release();
//
//	// COMの破棄
//	CoUninitialize();
//}
//
////=============================================================================
//// 再生
////=============================================================================
//void Sound::Play(SOUND_LABEL label)
//{
//	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];
//
//	if (pSV != nullptr)
//	{
//		pSV->DestroyVoice();
//		pSV = nullptr;
//	}
//
//	// ソースボイス作成
//	m_pXAudio2->CreateSourceVoice(&pSV, &(m_wfx[(int)label].Format));
//	pSV->SubmitSourceBuffer(&(m_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加
//
//	// 再生
//	pSV->Start(0);
//
//}
//
////=============================================================================
//// 停止
////=============================================================================
//void Sound::Stop(SOUND_LABEL label)
//{
//	if (m_pSourceVoice[(int)label] == NULL) return;
//
//	XAUDIO2_VOICE_STATE xa2state;
//	m_pSourceVoice[(int)label]->GetState(&xa2state);
//	if (xa2state.BuffersQueued)
//	{
//		m_pSourceVoice[(int)label]->Stop(0);
//	}
//}
//
////=============================================================================
//// 一時停止
////=============================================================================
//void Sound::Resume(SOUND_LABEL label)
//{
//	IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];
//	pSV->Start();
//}
//
//
//
////=============================================================================
//// ユーティリティ関数群
////=============================================================================
//HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
//{
//	HRESULT hr = S_OK;
//	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
//		return HRESULT_FROM_WIN32(GetLastError());
//	DWORD dwChunkType;
//	DWORD dwChunkDataSize;
//	DWORD dwRIFFDataSize = 0;
//	DWORD dwFileType;
//	DWORD bytesRead = 0;
//	DWORD dwOffset = 0;
//	while (hr == S_OK)
//	{
//		DWORD dwRead;
//		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		switch (dwChunkType)
//		{
//		case fourccRIFF:
//			dwRIFFDataSize = dwChunkDataSize;
//			dwChunkDataSize = 4;
//			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
//				hr = HRESULT_FROM_WIN32(GetLastError());
//			break;
//		default:
//			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
//				return HRESULT_FROM_WIN32(GetLastError());
//		}
//		dwOffset += sizeof(DWORD) * 2;
//		if (dwChunkType == fourcc)
//		{
//			dwChunkSize = dwChunkDataSize;
//			dwChunkDataPosition = dwOffset;
//			return S_OK;
//		}
//		dwOffset += dwChunkDataSize;
//		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
//	}
//	return S_OK;
//}
//
//HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
//{
//	HRESULT hr = S_OK;
//	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
//		return HRESULT_FROM_WIN32(GetLastError());
//	DWORD dwRead;
//	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
//		hr = HRESULT_FROM_WIN32(GetLastError());
//	return hr;
//}

//シングルトンインスタンスの取得
AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

//コンストラクタ
AudioManager::AudioManager() :p_XAudio2(nullptr), p_MasterVoice(nullptr),masterVolume(1.0f) 
{
}

//デストラクタ
AudioManager::~AudioManager()
{
	if (p_MasterVoice) p_MasterVoice->DestroyVoice();
	if (p_XAudio2) p_XAudio2->Release();
}

//初期化
void AudioManager::init()
{
	HRESULT hr=XAudio2Create(&p_XAudio2,0,XAUDIO2_DEFAULT_PROCESSOR);
	hr = XAudio2Create(&p_XAudio2, 0);
	if (FAILED(hr)) 
	{
		CoUninitialize();
		return;
	}
	hr = p_XAudio2->CreateMasteringVoice(&p_MasterVoice);
	if (FAILED(hr)) 
	{
		if (p_XAudio2) p_XAudio2->Release();
		CoUninitialize();
	}
	setMasterVolume(masterVolume);//初期ボリュームの設定
}

//マスターボリュームの設定
void AudioManager::setMasterVolume(float volume)
{
	if (p_MasterVoice)
	{
		masterVolume = volume;
		p_MasterVoice->SetVolume(volume);

		//各ソースボイスのボリュームを設定
		for (auto sourceVoice : sourceVoices)
		{
			sourceVoice->SetVolume(volume);
		}
	}
	
}

//マスターボリュームの取得
float AudioManager::getMasterVolume()const
{
	return masterVolume;
}


//ソースボイスの追加
void AudioManager::addSourceVoice(IXAudio2SourceVoice* sourceVoice)
{
	if (sourceVoice)
	{
		sourceVoices.push_back(sourceVoice);
		sourceVoice->SetVolume(masterVolume);//初期ボリュームを設定
	}
}

//XAudio2のインスタンスの取得
IXAudio2* AudioManager::getXAudio2()const
{
	return p_XAudio2;
}

//サウンドの読み込み
void AudioManager::loadsound(const char* fileName, IXAudio2SourceVoice** sourceVoice)
{
	//WAVファイルの読み込み
	std::ifstream file(fileName, std::ios::binary);
	if (!file)
	{
		std::cerr << "Error: file not found" << std::endl;
		return;
	}
	std::vector<char>buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	WAVEFORMATEX wf={0};
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = 44100;
	wf.wBitsPerSample = 16;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;

	HRESULT hr = getXAudio2()->CreateSourceVoice(sourceVoice, &wf);
	if (FAILED(hr))
	{
		std::cerr << "Error: CreateSourceVoice" << std::endl;
		return;
	}

	XAUDIO2_BUFFER bufferData = { 0 };
	bufferData.AudioBytes = buffer.size();
	bufferData.pAudioData = reinterpret_cast<BYTE*>(&buffer[0]);
	bufferData.Flags = XAUDIO2_END_OF_STREAM;

	(*sourceVoice)->SubmitSourceBuffer(&bufferData);
	addSourceVoice(*sourceVoice);	

	//再生
	(*sourceVoice)->Start();
}

//サウンドの終了
void AudioManager::Uninit()
{
	if (p_MasterVoice) p_MasterVoice->DestroyVoice();//使用したサウンドの解放
	if (p_XAudio2) p_XAudio2->Release();//XAudio2の解放
}



