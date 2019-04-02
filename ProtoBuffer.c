/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/09
**   File: ProtoBuffer.c
**   Function:  ProtoBuffer implement
**   History:
**       2018/11/09 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProtoBuffer.h"

static const uint32_t  PROTOBUFFERDATA_DATA_SIZE    = 1024;
static const uint32_t  PROTOBUFFERDATA_FDDATA_SIZE  = 32;

typedef struct ProtocolBufferData {
    struct ProtoBuffer   mProtoBuffer ;

    ENUM_PROTOBUFFER_ENDIAN             mEndian;
    uint8_t*             mData;
    size_t               mDataSize;
    size_t               mDataCapacity;
    size_t               mDataPos;

    int*                 mFdData;
    size_t               mFdDataSize;
    size_t               mFdDataCapacity;
    size_t               mFdDataPos;
} ProtocolBufferData;

///////////////////////////////////////////////////////////////////////////////////
static int ProtocolBufferData_default_resize_buffer(struct ProtocolBufferData *probufData , size_t sz) {
    size_t nDataCapacity = 0 ;
    size_t nDataRate = sz / PROTOBUFFERDATA_DATA_SIZE ;
    uint8_t *data = NULL ;
    if (probufData == NULL)
        return -1 ;

    nDataRate += 1 ;
    if (probufData->mData == NULL) {
        probufData->mDataSize = 0 ;
        probufData->mDataPos    = 0 ;
        probufData->mDataCapacity = nDataRate * PROTOBUFFERDATA_DATA_SIZE ;
        probufData->mData = (uint8_t*) malloc(probufData->mDataCapacity * sizeof(uint8_t));
    }

    if (probufData->mDataCapacity >= (probufData->mDataSize + sz))
        return 0 ;// memory enough

    nDataCapacity = probufData->mDataCapacity + nDataRate * PROTOBUFFERDATA_DATA_SIZE ;
    data = (uint8_t*)malloc(nDataCapacity * sizeof(uint8_t)) ;
    memcpy(data , probufData->mData , probufData->mDataSize * sizeof(uint8_t)) ;
    free(probufData->mData) ;
    probufData->mData = data ;
    probufData->mDataCapacity = nDataCapacity ;
    return 0 ;
}


static int ProtocolBufferData_default_setEndian(struct ProtoBuffer *probuf, ENUM_PROTOBUFFER_ENDIAN val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (probufData == NULL)
        return -1 ;
    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    probufData->mEndian = val ;
    return 0 ;
}

static int ProtocolBufferData_default_writeInt8(struct ProtoBuffer *probuf, int8_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    probufData->mData[probufData->mDataSize] = (uint8_t) val ;
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeUInt8(struct ProtoBuffer *probuf, uint8_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    probufData->mData[probufData->mDataSize] = (uint8_t) val ;
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeInt16(struct ProtoBuffer *probuf, int16_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeUInt16(struct ProtoBuffer *probuf, uint16_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeInt32(struct ProtoBuffer *probuf, int32_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeUInt32(struct ProtoBuffer *probuf, uint32_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeInt64(struct ProtoBuffer *probuf, int64_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %lx\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 56) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) (val >> 56) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeUInt64(struct ProtoBuffer *probuf, uint64_t val) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %lx\n" , __FILE__ , __LINE__ , val) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 56) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) (val >> 56) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeFloat(struct ProtoBuffer *probuf, float value) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint32_t val = (uint32_t) *((uint32_t*)&value) ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %f\n" , __FILE__ , __LINE__ , value) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeDouble(struct ProtoBuffer *probuf, double value) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint64_t val = (uint64_t) *((uint64_t*)&value) ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    //printf("%s line:%d %lf\n" , __FILE__ , __LINE__ , value) ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        probufData->mData[probufData->mDataSize] = (uint8_t) (val >> 56) ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) val ;
    } else {
        probufData->mData[probufData->mDataSize] = (uint8_t) val ;
        probufData->mData[probufData->mDataSize + 1] = (uint8_t) (val >> 8) ;
        probufData->mData[probufData->mDataSize + 2] = (uint8_t) (val >> 16) ;
        probufData->mData[probufData->mDataSize + 3] = (uint8_t) (val >> 24) ;
        probufData->mData[probufData->mDataSize + 4] = (uint8_t) (val >> 32) ;
        probufData->mData[probufData->mDataSize + 5] = (uint8_t) (val >> 40) ;
        probufData->mData[probufData->mDataSize + 6] = (uint8_t) (val >> 48) ;
        probufData->mData[probufData->mDataSize + 7] = (uint8_t) (val >> 56) ;
    }
    probufData->mDataSize += sizeof(val) ;
    return 0;
}

static int ProtocolBufferData_default_writeCString(struct ProtoBuffer *probuf, const char* val)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    size_t sz = 0 ;
    if (val == NULL)
        return -1 ;

    sz = strlen(val) + 1 ;
    if (ProtocolBufferData_default_resize_buffer(probufData , sz) < 0)
        return -1 ;

    //printf("%s line:%d %s\n" , __FILE__ , __LINE__ , val) ;
    memcpy(probufData->mData + probufData->mDataSize , (const void*)val , sz * sizeof(uint8_t)) ;
    probufData->mDataSize += sz ;
    return 0;
}

static int ProtocolBufferData_default_write(struct ProtoBuffer *probuf, const void* data, size_t sz) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (data == NULL)
        return -1 ;

    if (ProtocolBufferData_default_resize_buffer(probufData , sz) < 0)
        return -1 ;

    //printf("%s line:%d %x\n" , __FILE__ , __LINE__ , sz) ;
    memcpy(probufData->mData + probufData->mDataSize , data , sz * sizeof(uint8_t)) ;
    probufData->mDataSize += sz ;
    return 0;
}

static void ProtocolBufferData_default_reset(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (probufData == NULL)
        return  ;

    //printf("%s line:%d \n" , __FILE__ , __LINE__) ;
    if (probufData->mData)
        free(probufData->mData) ;
    if (probufData->mFdData)
        free(probufData->mFdData) ;
    probufData->mData = NULL;
    probufData->mDataSize = 0;
    probufData->mDataCapacity = 0;
    probufData->mDataPos = 0;
    probufData->mFdData = NULL;
    probufData->mFdDataSize = 0;
    probufData->mFdDataCapacity = 0;
    probufData->mFdDataPos = 0;
}

static void ProtocolBufferData_default_clear(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (probufData == NULL)
        return  ;

    //printf("%s line:%d \n" , __FILE__ , __LINE__) ;
    probufData->mDataSize = 0;
    probufData->mDataCapacity = 0;
    probufData->mDataPos = 0;
    probufData->mFdDataSize = 0;
    probufData->mFdDataCapacity = 0;
    probufData->mFdDataPos = 0;
}

static void ProtocolBufferData_default_free(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (probufData == NULL)
        return  ;
    //printf("%s line:%d \n" , __FILE__ , __LINE__) ;
    if (probufData->mData)
        free(probufData->mData) ;
    if (probufData->mFdData)
        free(probufData->mFdData) ;
    probufData->mData = NULL;
    probufData->mDataSize = 0;
    probufData->mDataCapacity = 0;
    probufData->mDataPos = 0;
    probufData->mFdData = NULL;
    probufData->mFdDataSize = 0;
    probufData->mFdDataCapacity = 0;
    probufData->mFdDataPos = 0;
    free(probufData) ;
}

int ProtocolBufferData_default_getEndian(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (probufData == NULL)
        return -1 ;

    //printf("%s line:%d \n" , __FILE__ , __LINE__) ;
    return probufData->mEndian ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
static int  ProtocolBufferData_default_check_buffer(struct ProtocolBufferData *probufData , size_t sz) {
    if (probufData == NULL)
        return -1 ;
    if ((probufData->mData == NULL) || (probufData->mDataSize < (probufData->mDataPos + sz)))
        return -1 ;
    return 0 ;
}

static int8_t ProtocolBufferData_default_readInt8(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    int8_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    val = probufData->mData[probufData->mDataPos];
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return val ;
}

static uint8_t ProtocolBufferData_default_readUInt8(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint8_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;

    val = probufData->mData[probufData->mDataPos];
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return val ;
}

static int16_t ProtocolBufferData_default_readInt16(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint16_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = ((val << 8) + probufData->mData[probufData->mDataPos + 1]) ;
    } else {
        val = probufData->mData[probufData->mDataPos + 1] ;
        val = ((val << 8) + probufData->mData[probufData->mDataPos]) ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return (int16_t)val ;
}

static uint16_t ProtocolBufferData_default_readUInt16(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint16_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return val ;
}

static int32_t ProtocolBufferData_default_readInt32(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint32_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return (int32_t)val ;
}

static uint32_t ProtocolBufferData_default_readUInt32(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint32_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return val ;
}

static int64_t ProtocolBufferData_default_readInt64(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint64_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 7] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 7] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %ld\n" , __FILE__ , __LINE__ , val) ;
    return (int64_t)val ;
}

static uint64_t ProtocolBufferData_default_readUInt64(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint64_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return -1 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 7] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 7] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %ld\n" , __FILE__ , __LINE__ , val) ;
    return val ;
}

static float ProtocolBufferData_default_readFloat(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint32_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return (float)0.0 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , val) ;
    return (float) *((float*)&val) ;
}

static double ProtocolBufferData_default_readDouble(struct ProtoBuffer *probuf)  {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    uint64_t val = 0 ;
    if (ProtocolBufferData_default_check_buffer(probufData , sizeof(val)) < 0)
        return (double)0.0 ;
    if (probufData->mEndian == BIG_PROTOBUFFER_ENDIAN) {
        val = probufData->mData[probufData->mDataPos] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 7] ;
    } else {
        val = probufData->mData[probufData->mDataPos + 7] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 6] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 5] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 4] ;

        val = (val << 8) + probufData->mData[probufData->mDataPos + 3] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 2] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos + 1] ;
        val = (val << 8) + probufData->mData[probufData->mDataPos] ;
    }
    probufData->mDataPos += sizeof(val) ;
    //printf("%s line:%d %ld\n" , __FILE__ , __LINE__ , val) ;
    return (double) *((double*)&val) ; ;
}

static const char* ProtocolBufferData_default_readCString(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    int sz = 0 ;
    const char *szString = NULL ;
    const char *szEOS = NULL ;
    if (probuf == NULL)
        return NULL ;
    if ((probufData->mData == NULL) || (probufData->mDataSize <= probufData->mDataPos))
        return NULL ;
    sz = probufData->mDataSize - probufData->mDataPos;
    szString = (const char*)(probufData->mData + probufData->mDataPos);
            // is the string's trailing NUL within the parcel's valid bounds?
    szEOS = (const char*)(memchr(szString, 0, (size_t)sz));

    if (!szEOS)
       return NULL ;

    sz = szEOS - szString;
    probufData->mDataPos += (sz + 1);
    return szString;
}

static int ProtocolBufferData_default_read(struct ProtoBuffer *probuf, void* data, size_t sz) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    size_t nDSize = 0 ;
    if ((probuf == NULL) || (data == NULL) || (sz <= 0))
        return -1 ;

    if ((probufData->mData == NULL) || (probufData->mDataSize <= probufData->mDataPos))
        return -1 ;

    nDSize = probufData->mDataSize - probufData->mDataPos;
    if (sz < nDSize)
        nDSize = sz ;
    memcpy(data , probufData->mData + probufData->mDataPos , nDSize * sizeof(int8_t)) ;
    probufData->mDataPos += nDSize ;
    return nDSize ;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int ProtocolBufferData_default_resize_fdbuffer(struct ProtocolBufferData *probufData , size_t sz) {
    size_t nFdDataCapacity = 0 ;
    size_t nFdDataRate = sz / PROTOBUFFERDATA_FDDATA_SIZE ;
    int *data = NULL ;
    if (probufData == NULL)
        return -1 ;

    nFdDataRate += 1 ;
    if (probufData->mFdData == NULL) {
        probufData->mFdDataSize = 0 ;
        probufData->mFdDataPos    = 0 ;
        probufData->mFdDataCapacity = nFdDataRate * PROTOBUFFERDATA_FDDATA_SIZE ;
        probufData->mFdData = (int*) malloc(probufData->mFdDataCapacity * sizeof(int));
    }

    if (probufData->mFdDataCapacity >= (probufData->mFdDataSize + sz))
        return 0 ;// memory enough

    nFdDataCapacity = probufData->mFdDataCapacity + nFdDataRate * PROTOBUFFERDATA_FDDATA_SIZE ;
    data = (int*)malloc(nFdDataCapacity * sizeof(int)) ;
    memcpy(data , probufData->mFdData , probufData->mFdDataSize * sizeof(int)) ;
    free(probufData->mFdData) ;
    probufData->mFdData = data ;
    probufData->mFdDataCapacity = nFdDataCapacity ;
    return 0 ;
}


static int ProtocolBufferData_default_writeFd(struct ProtoBuffer *probuf, int fd) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_fdbuffer(probufData , 1) < 0)
        return -1 ;

    //printf("%s line:%d %d\n" , __FILE__ , __LINE__ , fd) ;
    probufData->mFdData[probufData->mFdDataSize] = fd;
    probufData->mFdDataSize += 1 ;
    return fd;
}

static int ProtocolBufferData_default_writeFdBuffer(struct ProtoBuffer *probuf, int* fdbuf, size_t sz) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    if (ProtocolBufferData_default_resize_fdbuffer(probufData , sz) < 0)
        return -1 ;

    memcpy(probufData->mFdData + probufData->mFdDataSize , fdbuf , sz * sizeof(int)) ;
    probufData->mFdDataSize += sz ;
    return 0;
}

static int ProtocolBufferData_default_readFd(struct ProtoBuffer *probuf) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    int fd = 0 ;
    if (probuf == NULL)
        return -1 ;
    if ((probufData->mFdData == NULL) || (probufData->mFdDataSize <= probufData->mFdDataPos))
        return -1 ;

    fd = probufData->mFdData[probufData->mFdDataPos];
    probufData->mFdDataPos += 1 ;
    return fd;
}

static int ProtocolBufferData_default_readFdBuffer(struct ProtoBuffer *probuf, int *data, size_t sz) {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) probuf ;
    size_t nDSize = 0 ;
    if ((probuf == NULL) || (data == NULL) || (sz <= 0))
        return -1 ;

    if ((probufData->mFdData == NULL) || (probufData->mFdDataSize <= probufData->mFdDataPos))
        return -1 ;

    nDSize = probufData->mFdDataSize - probufData->mFdDataPos;
    if (sz < nDSize)
        nDSize = sz ;
    memcpy(data , probufData->mFdData + probufData->mFdDataPos , nDSize * sizeof(int)) ;
    probufData->mFdDataPos += nDSize ;
    return nDSize ;
}

/*************************************************************************************/

struct ProtoBuffer* ProtoBuffer_defalut_allocate() {
    struct ProtocolBufferData *probufData = (struct ProtocolBufferData*) malloc(sizeof(struct ProtocolBufferData)) ;
    struct ProtoBuffer *probuf = (struct ProtoBuffer*)probufData ;
    if (probufData == NULL)
        return NULL ;

    memset(probufData , 0 , sizeof(struct ProtocolBufferData));
    probufData->mEndian = BIG_PROTOBUFFER_ENDIAN ; //Big-Endian
    probufData->mDataCapacity = PROTOBUFFERDATA_DATA_SIZE ;
    probufData->mData = (uint8_t*) malloc(probufData->mDataCapacity * sizeof(uint8_t));

    probufData->mFdDataCapacity = PROTOBUFFERDATA_FDDATA_SIZE ;
    probufData->mFdData = (int*) malloc(probufData->mFdDataCapacity * sizeof(int));

    probuf->setEndian = ProtocolBufferData_default_setEndian;
    probuf->writeInt8 = ProtocolBufferData_default_writeInt8;
    probuf->writeUInt8 = ProtocolBufferData_default_writeUInt8;

    probuf->writeInt16 = ProtocolBufferData_default_writeInt16;
    probuf->writeUInt16 = ProtocolBufferData_default_writeUInt16;

    probuf->writeInt32 = ProtocolBufferData_default_writeInt32;
    probuf->writeUInt32 = ProtocolBufferData_default_writeUInt32;

    probuf->writeInt64 = ProtocolBufferData_default_writeInt64;
    probuf->writeUInt64 = ProtocolBufferData_default_writeUInt64;

    probuf->writeFloat = ProtocolBufferData_default_writeFloat;
    probuf->writeDouble = ProtocolBufferData_default_writeDouble;

    probuf->writeCString = ProtocolBufferData_default_writeCString;
    probuf->write = ProtocolBufferData_default_write;

    probuf->writeFd = ProtocolBufferData_default_writeFd;
    probuf->writeFdBuffer = ProtocolBufferData_default_writeFdBuffer;

    probuf->reset = ProtocolBufferData_default_reset;
    probuf->clear = ProtocolBufferData_default_clear;
    probuf->free = ProtocolBufferData_default_free;

    probuf->getEndian = ProtocolBufferData_default_getEndian;
    probuf->readInt8 = ProtocolBufferData_default_readInt8;
    probuf->readUInt8 = ProtocolBufferData_default_readUInt8;

    probuf->readInt16 = ProtocolBufferData_default_readInt16;
    probuf->readUInt16 = ProtocolBufferData_default_readUInt16;

    probuf->readInt32 = ProtocolBufferData_default_readInt32;
    probuf->readUInt32 = ProtocolBufferData_default_readUInt32;

    probuf->readInt64 = ProtocolBufferData_default_readInt64;
    probuf->readUInt64 = ProtocolBufferData_default_readUInt64;

    probuf->readFloat = ProtocolBufferData_default_readFloat;
    probuf->readDouble = ProtocolBufferData_default_readDouble;

    probuf->readCString = ProtocolBufferData_default_readCString;
    probuf->read = ProtocolBufferData_default_read;

    probuf->readFd = ProtocolBufferData_default_readFd;
    probuf->readFdBuffer = ProtocolBufferData_default_readFdBuffer;

    return probuf ;
}
