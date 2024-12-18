#pragma once
// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(pointer) { if( nullptr != pointer ) { pointer->Release(); pointer = nullptr; } }

// 解放用の簡略化マクロ
#define SAFE_DELETE(pointer) { if( nullptr != pointer ) {delete pointer; pointer=nullptr;  } }