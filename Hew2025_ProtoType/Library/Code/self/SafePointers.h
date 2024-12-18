#pragma once
// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(pointer) { if( nullptr != pointer ) { pointer->Release(); pointer = nullptr; } }

// 解放用の簡略化マクロ
#define SAFE_DELETE(pointer) { if( nullptr != pointer ) {delete pointer; pointer=nullptr;  } }				// 単体で確保していた場合
#define SAFE_DELETE_ARRAY(pointer) { if( nullptr != pointer ) {delete[] pointer; pointer=nullptr;  } }		// 配列で確保していた場合