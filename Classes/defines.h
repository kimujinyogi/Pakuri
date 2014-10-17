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
#define kURL "http://x-native.thiefstory.love-dev.pgasp.jp"
#else
#define kURL "http://native.thiefstory.love-dev.pgasp.jp"
#endif

#define kENC_KEY "zappy20140529"

#endif

#include "NetManager.h"
