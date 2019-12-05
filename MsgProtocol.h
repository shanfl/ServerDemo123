#pragma once
#include <stdint.h>
#include <string>


enum class CompressType
{
    NONE = 0,
    ZIP = 1,
    SNAPPY = 2,    
};

struct MsgHeader
{
    uint32_t    msgid;
    int64_t     tm;
    int32_t     cookie;
    int32_t     compress;
    int32_t     uncompresize;
    int32_t     length;
};




class MsgBase
{
public:
    MsgBase()
    {
        mHeader = {0};        
    }

    void Reset()
    {
        mHeader = {0};  
        mMsgRaw.clear();
    }

    void operator= (const MsgBase& msg)
    {
        mHeader = msg.mHeader;
        mMsgRaw = msg.mMsgRaw;
    }

    bool Parser(const char* msg,int len)
    {
        MsgHeader*header = (MsgHeader*)msg;
        mHeader = *header;
        switch (mHeader.compress)
        {
        case (int)CompressType::NONE:
            
            break;
        
        default:
            break;
        }





    }
protected:
    MsgHeader mHeader;
    std::string mMsgRaw;
};
