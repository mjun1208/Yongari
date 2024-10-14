#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <time.h>

using namespace std;

#define g_device DXUTGetD3D9Device()
#define DX_Time DXUTGetElapsedTime() * TimeScale

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif // _DEBUG

const int WINSIZEX = 720;
const int WINSIZEY = 1280;

using Vector2 = D3DXVECTOR2;
extern float TimeScale;

#include "cSceneManager.h"
#include "cImageManager.h"
#include "cInputManager.h"
#include "cTexture.h"
#include "cButton.h"