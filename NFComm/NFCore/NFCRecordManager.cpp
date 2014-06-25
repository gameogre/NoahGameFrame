// -------------------------------------------------------------------------
//    @FileName         :    NFCRecordManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-17
//    @Module           :    NFCRecordManager
//
// -------------------------------------------------------------------------

#include "NFCRecordManager.h"

NFCRecordManager::~NFCRecordManager()
{
    NFIRecord* pRecord = this->First();
    while (pRecord)
    {
        delete pRecord;
        pRecord = NULL;

        pRecord = this->Next();
    }
}

NFIRecord* NFCRecordManager::AddRecord(const NFIDENTID& self, const std::string& strRecordName, const NFIValueList& ValueList, const NFIValueList& keyList, const NFIValueList& descList, const NFIValueList& tagList, const NFIValueList& relateRecordData, const int nRows, bool bPublic /*= false*/, bool bPrivate /*= false*/, bool bSave /*= false */, int nIndex)
{
    NFIRecord* pRecord = GetElement(strRecordName);
    if (!pRecord)
    {
        pRecord = new NFCRecord(self, strRecordName, ValueList, keyList, descList, tagList, relateRecordData, nRows, bPublic, bPrivate, bSave, nIndex);
        this->AddElement(strRecordName, pRecord);
    }

    return pRecord;
}

NFIDENTID NFCRecordManager::Self()
{
	return mSelf;
}

void NFCRecordManager::GetRelationRows(const std::string& strSrcRecord, const std::string& strSrcTag, const NFIValueList& var, const std::string& strRelatedRecord, OUT NFIValueList& outRowList)
{
    NFIRecord* pSrcRecord = GetElement(strSrcRecord);
    NFIRecord* pRelatedRecord = GetElement(strRelatedRecord);
    if (NULL == pSrcRecord || NULL == pRelatedRecord)
    {
        return;
    }

    std::string strRelatedTag;
    if (!pSrcRecord->GetRelatedTag(strSrcTag, strRelatedRecord, strRelatedTag))
    {
        return;
    }
    
    pRelatedRecord->FindRowByColValue(strRelatedTag, var, outRowList);
}