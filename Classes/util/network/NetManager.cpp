//
//  netMgr.cpp
//  TestProject
//
//  Created by Kim JinHyuck on 2014/10/07.
//
//

#include "defines.h"
//#include "NetManager.h"
#include "base/base64.h"
#include "spine/Json.h"



NetManager* NetManager::m_instance = NULL;

// --------------------------------
// private
// --------------------------------

NetManager::NetManager ()
{
    Initialize(kURL);
}

void NetManager::Initialize (const std::string& url)
{
    this->_url = url;
}

// --------------------------------
// public
// --------------------------------

NetManager* NetManager::getInstance()
{
    if (NULL == m_instance)
    {
        m_instance = new NetManager ();
    }
    
    return m_instance;
}

// 戻り値じゃなくて、ポインターの引数私で出来るように修正する ...
// もしくはstd::stringを渡す ....
bool NetManager::descript (std::string &data)
{
    bool retVal = false;
//    http://javascripter.hatenablog.com/entry/20080907/1220791813
    if (!data.empty())
    {
        int keyLen = std::strlen(kENC_KEY);
        const unsigned char* p_encKey = reinterpret_cast <const unsigned char*> (kENC_KEY);
        const unsigned char* p_uc = reinterpret_cast <const unsigned char*> (data.c_str());
        
        unsigned int btlen = (unsigned int)std::strlen(data.c_str());
        int len = 0;
        unsigned char* buffer;
        
        len = cocos2d::base64Decode(p_uc, btlen, &buffer);
        for (int i = 0; i < len; i++) {
            unsigned char cdata = *(buffer + i);
            unsigned char ckey = *(p_encKey + (i % keyLen));
            *(buffer + i) = cdata - ckey;
        }
        const char* p_decodedStr = reinterpret_cast<const char*>(buffer);
        // ここでいま止まる
//        retVal = new char[std::strlen(p_decodedStr)];
//        strcpy(retVal, p_decodedStr);
        //data = p_decodedStr;
        retVal = true;
    }
    return retVal;
}

void NetManager::test ()
{
//    CCLOG ("%s", this->_url.c_str());
    //std::string url =
    std::string url = std::string (this->_url.c_str());
    url.append("/apiResource/lastResource");
    CCLOG ("%s", url.c_str());
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback(CC_CALLBACK_2(NetManager::onHttpRequestCompleted, this));
    
    // write the post data
    const char* postData = "_user_id=1&_app_id=11000020&_app_ver=1.0.0&_device=pc&_os=I&_market=I&_uuid=1DA58672-65B1-41A0-9470-717FBAE1561A&_lang=JP&_device_model=pc&_graphic_device=pc&_proccessor=pc&_memory_size=22222222&_enc_type=0&device=I&app_version=1.0.0";
    request->setRequestData(postData, strlen(postData));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void NetManager::onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response)
{
    std::vector<char>* data = response->getResponseData();
    std::string result(data->begin(), data->end());
//    CCLOG("1 = %s", result.c_str());
    if (this->descript(result)) {
        Json* json = Json_create(result.c_str());
        int code = Json_getInt(json, "res_code", 0);
        std::string resMessage = std::string(Json_getString(json, "res_message", ""));
        
        CCLOG("code = %d, message = %s", code, resMessage.c_str());
    } else {
    
    }
//    Json* json = Json_create(result.c_str());
//    
//    std::string id = Json_getString(json, "id", "");
//    std::string name = Json_getString(json, "name", "");
//    
//    CCLOG(String::createWithFormat("id:%s , name:%s", id.c_str(), name.c_str())->getCString());
}
