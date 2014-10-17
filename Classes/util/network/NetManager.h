//
//  netMgr.h
//  TestProject
//
//  Created by Kim JinHyuck on 2014/10/07.
//
//

#ifndef __TestProject__netMgr__
#define __TestProject__netMgr__

#include "cocos2d.h"
#include "network/HttpClient.h"

class NetManager
{
private:
    static NetManager* m_instance;

    NetManager ();
//    NetManager (std::string* url);
//    char* _url;
    std::string _url;
//    std::string* _url;
    
    void Initialize (const std::string& url);
    
public:
    static NetManager* getInstance ();
    
    bool descript (std::string &data);
    void test ();
    virtual void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response);

};

#endif /* defined(__TestProject__netMgr__) */

