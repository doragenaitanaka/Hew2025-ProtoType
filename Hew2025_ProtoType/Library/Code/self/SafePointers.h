#pragma once
// Direct3D����̊ȗ����}�N��
#define SAFE_RELEASE(pointer) { if( nullptr != pointer ) { pointer->Release(); pointer = nullptr; } }