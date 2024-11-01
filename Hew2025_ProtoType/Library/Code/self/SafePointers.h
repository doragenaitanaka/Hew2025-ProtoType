#pragma once
// Direct3D‰ð•ú‚ÌŠÈ—ª‰»ƒ}ƒNƒ
#define SAFE_RELEASE(pointer) { if( nullptr != pointer ) { pointer->Release(); pointer = nullptr; } }