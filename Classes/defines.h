//
//  defines.h
//  TestProject
//
//  Created by Kim JinHyuck on 2014/10/07.
//
//

// これは、cppで呼ぶための物

// インクルードは、
// 1. Cライブラリ
// 2. C++ライブラリ
// 3. その他ライブラリの .h
// 4. プロジェクトの .h
// という順序にしてください。

#ifndef TestProject_defines_h
#define TestProject_defines_h

#define kDEBUG_MODE 1

#if kDEBUG_MODE == 1
#define kURL "http://urlrul"
#else
#define kURL "http://urlurl-release"
#endif

#define kENC_KEY "enckey123412421"

#define kFONT_NORMAL "Marker Felt.ttf"

#endif

#include "NetManager.h"











