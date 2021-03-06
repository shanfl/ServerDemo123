#pragma once
#include <stdint.h>
#include <string>
#include <time.h>
#include "byte_buffer.h"

#include "protobuf-2.5.0/src"

#ifndef PROTOBUF_LITE
# include <google/protobuf/message.h>  // for Message
# define ProtobufMessage ::google::protobuf::Message
#else
# include <google/protobuf/message_lite.h>  // for MessageLite
# define ProtobufMessage ::google::protobuf::MessageLite
#endif



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
    int32_t     rawsize;
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
        //mMsgRaw.clear();
        mRawData.Clear();
    }

    void operator= (const MsgBase& msg)
    {
        mHeader = msg.mHeader;
        //mMsgRaw = msg.mMsgRaw;
        mRawData = msg.mRawData;
    }

    bool Parser(const char* msg,int len)
    {
        MsgHeader*header = (MsgHeader*)msg;
        mHeader = *header;

        mRawData.SetData((const uint8_t*)&mHeader,sizeof(MsgHeader));
        
        switch (mHeader.compress)
        {
        case (int)CompressType::NONE:
            mRawData.Append((const uint8_t*)msg + sizeof(MsgHeader),len - sizeof(MsgHeader));
            break;
        
        default:
            break;
        }        
    }

    size_t Serialize(int msgid,const char*msg,size_t length)
    {
        Reset();
        mHeader.msgid = msgid;
        mHeader.tm = time(NULL);
        mHeader.rawsize = length;
        mHeader.length = length;
        mRawData.SetData((const uint8_t*)&mHeader,sizeof(MsgHeader));
        mRawData.Append((const uint8_t*)msg,length);
        return mRawData.size();
    }

    size_t Serialize(int msgid,ProtobufMessage & protomsg)
    {
        std::string strmsg = protomsg.SerializeAsString();
        Reset();   
        mHeader.msgid       = msgid;
        mHeader.tm          = time(NULL);
        mHeader.rawsize     = strmsg.length();
        mHeader.length      = strmsg.length();
        mRawData.SetData((const uint8_t*)&mHeader,sizeof(MsgHeader));
        mRawData.Append((const uint8_t*)strmsg.c_str(),strmsg.length());
        return mRawData.size();
    }


protected:
    MsgHeader mHeader;
    //std::string mMsgRaw;
    ByteBuffer mRawData;
};
