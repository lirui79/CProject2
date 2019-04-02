/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/09
**   File: ProtoBuffer.h
**   Function:  interface of protocol buffer
**   History:
**       2018/11/09 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_PROTO_BUFFER_H__
#define __IRIS_PROTO_BUFFER_H__

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

typedef enum  ENUM_PROTOBUFFER_ENDIAN {
    LITTLE_PROTOBUFFER_ENDIAN = 0 ,   //  0 - little-Endian
    BIG_PROTOBUFFER_ENDIAN    = 1 ,   //  1 - Big-Endian
}ENUM_PROTOBUFFER_ENDIAN;


typedef struct ProtoBuffer {
    /**
	 * @brief 设置ProtoBuffer中数据的字节序列
	 *
	 * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     字节序列
	 * 	<em>LITTLE_PROTOBUFFER_ENDIAN</em> 小头字节序列 - little-Endian
	 *	<em>BIG_PROTOBUFFER_ENDIAN</em>    大头字节序列 - Big-Endian
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->setEndian(probuf,BIG_PROTOBUFFER_ENDIAN) ;
     *  probuf->free(probuf) ;
     */
	int (*setEndian)(struct ProtoBuffer *probuf, ENUM_PROTOBUFFER_ENDIAN val);

    /**
	 * @brief 往数据包的中插入8位有符号整型值
	 *
	 * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     8位有符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int8_t ival8 = 0x7f ;
     *  probuf->writeInt8(probuf,ival8) ;
     *  probuf->free(probuf) ;
     */
	int (*writeInt8)(struct ProtoBuffer *probuf, int8_t val);

    /**
	 * @brief 往数据包的中插入8位无符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     8位有符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  uint8_t uval8 = 0xf8 ;
     *  probuf->writeUInt8(probuf,uval8) ;
     *  probuf->free(probuf) ;
     */
	int (*writeUInt8)(struct ProtoBuffer *probuf, uint8_t val);

    /**
	 * @brief 往数据包的中插入16位有符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     8位有符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int16_t ival16 = 0x7fbc ;
     *  probuf->writeInt16(probuf,ival16) ;
     *  probuf->free(probuf) ;
     */
	int (*writeInt16)(struct ProtoBuffer *probuf, int16_t val);

    /**
	 * @brief 往数据包的中插入16位无符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     16位无符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt16(probuf,0xfa88) ;
     *  probuf->free(probuf) ;
     */
	int (*writeUInt16)(struct ProtoBuffer *probuf, uint16_t val);

    /**
	 * @brief 往数据包的中插入32位有符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     32位有符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeInt32(probuf,0x7f0f9ff8) ;
     *  probuf->free(probuf) ;
     */
	int (*writeInt32)(struct ProtoBuffer *probuf, int32_t val);

    /**
	 * @brief 往数据包的中插入32位无符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     32位无符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt32(probuf,0x86f0f9f8) ;
     *  probuf->free(probuf) ;
     */
	int (*writeUInt32)(struct ProtoBuffer *probuf, uint32_t val);

    /**
	 * @brief 往数据包的中插入64位有符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     64位有符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int64_t val = 0x7f78ffffffffffff;
     *  probuf->writeInt64(probuf,val) ;
     *  probuf->free(probuf) ;
     */
	int (*writeInt64)(struct ProtoBuffer *probuf, int64_t val);

    /**
	 * @brief 往数据包的中插入64位无符号整型值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     64位无符号整型值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  uint64_t val = 0x8ffacff54ff76ffb ;
     *  probuf->writeUInt64(probuf,val) ;
     *  probuf->free(probuf) ;
     */
	int (*writeUInt64)(struct ProtoBuffer *probuf, uint64_t val);

    /**
	 * @brief 往数据包的中插入float变量
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     float变量值
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  float  fval = 19229.09897f ;
     *  probuf->writeFloat(probuf , fval) ;
     *  probuf->free(probuf) ;
     */
	int (*writeFloat)(struct ProtoBuffer *probuf, float val);

    /**
	 * @brief 往数据包的中插入double变量值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     double变量
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  double dval = 8827319319.2343 ;
     *  probuf->writeDouble(probuf , dval) ;
     *  probuf->free(probuf) ;
     */
	int (*writeDouble)(struct ProtoBuffer *probuf, double val);

    /**
	 * @brief 往数据包的中插入c语言字符串值
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] val     c语言字符串
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  if (probuf)
     *     probuf->writeCString(probuf,"hello world!") ;
     *  probuf->free(probuf) ;
     */
	int (*writeCString)(struct ProtoBuffer *probuf, const char* val);

    /**
	 * @brief 往数据包的中插入数组
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] data    数组首地址
	 * @param[in] len     数组字节大小
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  uint8_t data[16] = {1, 2, 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15 , 16} ;
     *  if (probuf)
     *     probuf->write(probuf,data , 16) ;
     *  probuf->free(probuf) ;
     */
	int (*write)(struct ProtoBuffer *probuf, const void* data, size_t len);

	/**
	 * @brief 往数据包的中插入文件描述符
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @param[in] fd      文件描述符
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int fd = 2001 ;
     *  if (probuf)
     *     probuf->writeFd(probuf,fd) ;
     *  probuf->free(probuf) ;
     */
	int (*writeFd)(struct ProtoBuffer *probuf, int fd);

	/**
	 * @brief 往数据包的中插入文件描述符数组
	 *
     * @param[in] probuf   ProtoBuffer指针变量
	 * @param[in] fdbuf    Buffer首地址  int32_t fdbuf[]
	 * @param[in] size     Buffer数组大小
	 *
	 * @return
	 * 	<em>0</em> 成功
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int data[24] = {1001, 2787, 35636 , 34424 , 9865 , 6757 , 7 , 348 , 429 , 76510 , 5411 , 9812 , 6513 , 3414 , 54315 , 1236 , 0} ;
     *  if (probuf)
     *     probuf->writeFdBuffer(probuf,data , 24) ;
     *  probuf->free(probuf) ;
     */
	int (*writeFdBuffer)(struct ProtoBuffer *probuf, int* fdbuf, size_t size);

    /**
	 * @brief 重置数据包销毁内存
     *
     * @param[in] probuf  ProtoBuffer指针变量
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  if (probuf)
     *     probuf->reset(probuf) ;
     *  probuf->free(probuf) ;
     */
	void (*reset)(struct ProtoBuffer *probuf);

    /**
	 * @brief 清除数据包不销毁内存
     *
     * @param[in] probuf  ProtoBuffer指针变量
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  if (probuf)
     *     probuf->clear(probuf) ;
     *  probuf->free(probuf) ;
     */
	void (*clear)(struct ProtoBuffer *probuf);

    /**
     * @brief 析构ProtoBuffer指针
     *
     * @param[in] probuf  ProtoBuffer指针变量
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *
     *  probuf->free(probuf) ;
     */
    void (*free)(struct ProtoBuffer *probuf);

    /**
	 * @brief 获取ProtoBuffer中数据的字节序列
	 *
	 * @param[in] probuf  ProtoBuffer指针变量
	 *
	 * @return
     * 	<em>LITTLE_PROTOBUFFER_ENDIAN</em> 成功  小头字节序列 - little-Endian
	 *	<em>BIG_PROTOBUFFER_ENDIAN</em>    成功  大头字节序列 - Big-Endian
	 *	<em>-1</em>    获取字节序  失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->setEndian(probuf,BIG_PROTOBUFFER_ENDIAN) ;
     *  printf("%d \n" ,probuf->getEndian(probuf)) ;
     *  probuf->free(probuf) ;
     */
	int (*getEndian)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 从数据包的中读取8位有符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取8位有符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeInt8(probuf,98) ;
     *  printf("int8_t : %x \n" , probuf->readInt8(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	 int8_t (*readInt8)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中8位无符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取8位无符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt8(probuf,0xaf) ;
     *  printf("uint8_t : %x \n" , probuf->readUInt8(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	 uint8_t (*readUInt8)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中16位有符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取16位有符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->readInt16(probuf,0x3298) ;
     *  printf("int16_t : %x \n" , probuf->readInt16(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	int16_t (*readInt16)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中16位无符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 *    读取16位无符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt16(probuf,0x80af) ;
     *  printf("uint16_t : %x \n" , probuf->readUInt16(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	uint16_t (*readUInt16)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中32位有符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取32位有符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeInt32(probuf,0x32090f45) ;
     *  printf("int32_t : %x \n" , probuf->readInt32(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	int32_t (*readInt32)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中32位无符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取32位无符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt32(probuf,0x90fa3265) ;
     *  printf("uint32_t : %x \n" , probuf->readUInt32(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	uint32_t (*readUInt32)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中64位有符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取64位有符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeInt64(probuf,0x430ada89328fa7ff) ;
     *  printf("uint64_t : %lx \n" , probuf->readInt64(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	int64_t (*readInt64)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中64位无符号整型值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取64位无符号整型值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeUInt64(probuf,0x8faada87ff430932) ;
     *  printf("uint64_t : %lx \n" , probuf->readUInt64(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	uint64_t (*readUInt64)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中float变量
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取float变量值
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeFloat(probuf,1432.9876f) ;
     *  printf("float : %f \n" , probuf->readFloat(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	float (*readFloat)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中double变量值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	  读取double变量
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeDouble(probuf,1232132.989f) ;
     *  printf("double : %lf \n" , probuf->readDouble(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	double (*readDouble)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 读取数据包的中c语言字符串值
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 *
 	 * @return
 	 * 	<em>非NULL</em> c语言字符串值
 	 *	<em>NULL</em>   失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->writeCString(probuf,"hello world!") ;
     *  printf("CString : %s \n" , probuf->readCString(probuf)) ;
     *  probuf->free(probuf) ;
     */
 	const char* (*readCString)(struct ProtoBuffer *probuf);

     /**
 	 * @brief 从数据包的中读取数组
 	 *
     * @param[in] probuf  ProtoBuffer指针变量
 	 * @param[out] data   数组首地址
 	 * @param[out] len    数组字节大小指针变量
 	 *
 	 * @return
 	 * 	<em>0</em> 成功
 	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int8_t data[8] = {1 , 9 , 43 , 8 , 14 , 76 , 92 , 57} , buffer[8];
     *  int sz = 0 ;
     *  probuf->write(probuf,data,8) ;
     *  sz = probuf->read(probuf,buffer,8) ;
     *  probuf->free(probuf) ;
     */
 	int (*read)(struct ProtoBuffer *probuf, void* data, size_t size);

	/**
	 * @brief 从数据包的中读取一个Fd
	 *
     * @param[in] probuf  ProtoBuffer指针变量
	 * @return
	 * 	<em>>=0</em>   读取的Fd值
	 * 	<em><0</em>    失败错误码
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  probuf->wrietFd(probuf,1028) ;
     *  printf("fd : %d \n" , probuf->readFd(probuf)) ;
     *  probuf->free(probuf) ;
     */
	int (*readFd)(struct ProtoBuffer *probuf);

	/**
	 * @brief 读取数据包的中文件描述符数组
	 *
     * @param[in]   probuf    ProtoBuffer指针变量
	 * @param[out]  fdbuf    读取的Buffer首地址  int fdbuf[]
	 * @param[out]  size     读取的Buffer数组大小
	 *
	 * @return
	 * 	<em>>0</em> 成功 数组大小
	 *	<em>-1</em> 失败
     *
     * @example
     *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
     *  int fdD[6] = {23 , 54 , 76 , 89 , 321 , 343} , fdV[6] , sz;
     *  probuf->writeFdBuffer(probuf,fdD,6) ;
     *  sz = probuf->readFdBuffer(probuf,fdV,6) ;
     *  probuf->free(probuf) ;
     */
	int (*readFdBuffer)(struct ProtoBuffer *probuf, int *fdbuf, size_t size);
}ProtoBuffer;

/**
 * @brief 分配一个ProtoBuffer结构
 *
 * @return
 * 	<em>非NULL</em> ProtoBuffer 对象指针
 * 	<em>NULL</em>  失败
 *
 * @example
 *  struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate();
 *  if (probuf)
 *     probuf->writeCString(probuf,"debug") ;
 *  probuf->free(probuf) ;
 */
struct ProtoBuffer* ProtoBuffer_defalut_allocate() ;

__END_DECLS

#endif //__IRIS_COMMON_H__
