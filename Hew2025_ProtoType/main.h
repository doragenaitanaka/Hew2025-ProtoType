#pragma once
// デバッグ用コンソールウィンドウを表示
#define	DEBUG

#ifdef DEBUG
#include <cstdlib> // system関数を使用するために必要
#include<iostream>
#endif // DEBUG

/**	@brief 	コンソールウィンドウの初期化
*	@date	2024/11/02
*/
int InitConsole();