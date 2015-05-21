/*
*	ヘッダーファイルのインクルード
*	ライブラリのリンク
*	マクロ定義
*
*	2015/05/01		Y.Ozawa
*/

#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Application.h"
#include "Object.h"
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Debug.h"
#include "Common.h"

//ライブラリのリンク
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//マクロ定義

//コンソールを開く
#define OpenConsole() {\
	AllocConsole();\
	FILE *fp;\
	freopen_s(&fp, "CONOUT$", "w", stdout);\
	freopen_s(&fp, "CONIN$", "r", stdin);\
}
//コンソールを閉じる
#define CloseConsole() {\
	FreeConsole();\
}
//ポインタをリリースする
#define SafeRelease(p) {\
	if (p)\
		{\
		p->Release();\
		p = nullptr;\
		}\
}



