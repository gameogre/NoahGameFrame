// -------------------------------------------------------------------------
//    @FileName         :    NFIHeartBeatManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-17
//    @Module           :    NFIHeartBeatManager
//
// -------------------------------------------------------------------------

#ifndef _NFI_HEARTBEATMANAGER_H_
#define _NFI_HEARTBEATMANAGER_H_

#include <string>
#include "NFMap.h"
#include "NFList.h"
#include "NFDefine.h"
#include "NFCDataList.h"

class  NFCHeartBeatElement
    : public NFList<HEART_BEAT_FUNCTOR_PTR>
{
public:
    bool operator==(const NFCHeartBeatElement& src)
    {
        if (strBeatName == src.strBeatName)
        {
            return true;
        }

        return false;
    }

    NFCHeartBeatElement()
    {
        fBeatTime = 0.0f;
        fTime = 0.0f;
        nCount = 0;
        strBeatName = "";
    };

    virtual ~NFCHeartBeatElement()
    {
        var.Clear();
    }

    void DoHeartBeatEvent();

    float fBeatTime;

    float fTime;
    int nCount;
    std::string strBeatName;
    NFIDENTID self;
    NFCDataList var;
};

class NFIHeartBeatManager
{
public:
    virtual ~NFIHeartBeatManager() {}

    virtual NFIDENTID Self() = 0;

    virtual bool Execute(const float fLastTime, const float fAllTime) = 0;
    virtual bool Exist(const std::string& strHeartBeatName) = 0;

    virtual bool AddHeartBeat(const NFIDENTID self, const std::string& strHeartBeatName, const HEART_BEAT_FUNCTOR_PTR& cb, const NFIDataList& var, const float fTime, const int nCount) = 0;
    virtual bool RemoveHeartBeat(const std::string& strHeartBeatName) = 0;

    template<typename BaseType>
    bool AddHeartBeat(const NFIDENTID self, const std::string& strHeartBeatName, BaseType* pBase, int (BaseType::*handler)(const NFIDENTID&, const std::string&, const float, const int, const NFIDataList&), const NFIDataList& var, const float fTime, const int nCount)
    {
        HEART_BEAT_FUNCTOR functor = boost::bind(handler, pBase, _1, _2, _3, _4, _5);
        HEART_BEAT_FUNCTOR_PTR functorPtr(NF_NEW HEART_BEAT_FUNCTOR(functor));
        return AddHeartBeat(self, strHeartBeatName, functorPtr, var, fTime, nCount);
    }
};

#endif