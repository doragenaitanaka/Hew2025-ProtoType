#pragma once
// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(pointer) { if( nullptr != pointer ) { pointer->Release(); pointer = nullptr; } }