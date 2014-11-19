//
//  UseMenuItemLabel.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/18.
//
//

#ifndef __TestProject__UseMenuItemLabel__
#define __TestProject__UseMenuItemLabel__

#include "CCRef.h"
#include "cocos2d.h"
#include "GameInfoDefine.h"

// アイテムを使用するかしないかのボタン
// ボタンのタイプの定義はGameInfoDefineにある（タイプ）
// 今のところは、ボタンの画像は使わない為、ラベルを更新するのみ
// どのアイテムを使うかのデータは、今の所保存しない
namespace GameReadyMenu {
    class UseMenuItemLabel : public cocos2d::MenuItemLabel
    {
    public:
        UseMenuItemLabel();
        ~UseMenuItemLabel();
        static UseMenuItemLabel * create(cocos2d::Node*label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag, const std::string& strOn, const std::string& strOff);

        enum GameInfo::ItemFlag getFlag ();
    protected:
        bool initWithLabel(Node* label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag, const std::string& strOn, const std::string& strOff);
        void setLabelStatus ();
    private:
        enum GameInfo::ItemFlag m_eFlag;
        std::string m_strOn;
        std::string m_strOff;
        cocos2d::ccMenuCallback m_callback;
        
        void touchedItem (Ref* pSender);
    };
}
#endif /* defined(__TestProject__UseMenuItemLabel__) */


