/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/08
**   File: IAppCallBack.h
**   Function:  interface of AppCallBack for user
**   History:
**       2018/11/08 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_IAPP_CALLBACK_H__
#define __IRIS_IAPP_CALLBACK_H__

#include <stdint.h>
#include <sys/cdefs.h>

#include "common.h"

/**
 * @addtogroup sdk interface
 * @{
 */

__BEGIN_DECLS

 typedef enum ENUM_EYE_TYPE {
     LEFT_EYE  = 0 ,   //left eye
     RIGHT_EYE = 1 ,  // right eye
 }ENUM_EYE_TYPE;

 typedef enum ENUM_PARAMETER_TYPE {
     //EYE* LEFT are relative to head
     //matrix = translate(pos) * rotate(quat)
     PARAMETER_EYEMATRIX = 0,
     PARAMETER_EYEPOS = 0x1,
     PARAMETER_EYEQUAT = 0x2,
     //view(getSimulatedEye) =
     // view(EYEVIEW) * view(getSimulatedHead)
     PARAMETER_EYEVIEW = 0x4,
     PARAMETER_FOV =  0x8, //in radian y direction
     PARAMETER_SCREENWIDTH = 0x10,
     PARAMETER_SCREENHEIGHT = 0x20,
     PARAMETER_NEARPLANE = 0x40,
     PARAMETER_FARPLANE = 0x80,
     PARAMETER_PROJECTION = 0x100,
     PARAMETER_WHRATIO = 0x200,

     //EYE* RIGHT are relative to head
     PARAMETER_EYERIGHT = 0x80000000,
     PARAMETER_EYEMATRIX_RIGHT = PARAMETER_EYERIGHT + PARAMETER_EYEMATRIX,
     PARAMETER_EYEPOS_RIGHT = PARAMETER_EYERIGHT + PARAMETER_EYEPOS,
     PARAMETER_EYEQUAT_RIGHT = PARAMETER_EYERIGHT + PARAMETER_EYEQUAT,
     //view(getSimulatedEye) =
     // view(EYEVIEW) * view(getSimulatedHead)
     PARAMETER_EYEVIEW_RIGHT = PARAMETER_EYERIGHT + PARAMETER_EYEVIEW,
     PARAMETER_FOV_RIGHT = PARAMETER_EYERIGHT + PARAMETER_FOV, //in radian y direction
     PARAMETER_SCREENWIDTH_RIGHT = PARAMETER_EYERIGHT + PARAMETER_SCREENWIDTH,
     PARAMETER_SCREENHEIGHT_RIGHT = PARAMETER_EYERIGHT + PARAMETER_SCREENHEIGHT,
     PARAMETER_NEARPLANE_RIGHT = PARAMETER_EYERIGHT + PARAMETER_NEARPLANE,
     PARAMETER_FARPLANE_RIGHT = PARAMETER_EYERIGHT + PARAMETER_FARPLANE,
     PARAMETER_PROJECTION_RIGHT = PARAMETER_EYERIGHT + PARAMETER_PROJECTION,
     PARAMETER_WHRATIO_RIGHT = PARAMETER_EYERIGHT + PARAMETER_WHRATIO
 }ENUM_PARAMETER_TYPE;

 typedef enum  ENUM_IAPPCALLBACK_MODE {
         IAPPCALLBACK_ONCREATE     = 0, //create
         IAPPCALLBACK_ONBACKGROUND = 1, //background
         IAPPCALLBACK_ONDESTROY    = 2, //destroy
 }ENUM_IAPPCALLBACK_MODE;

 /**
 * @brief 向vr系统app回调结构体
 *  定义具体App回调结构类型时 IAppCallBack必须是其起始字段
 *  具体App回调结构类型变量初始化时应先用IAppCallBack_default_init函数再用自行定义初始化函数
 *  the fields of this data structure must begin with IAppCallBack
 *    followed by module specific information.
 * @example
 * typedef struct AppCallBackEx {
 *   IAppCallBack  mAppCallback ;
 *   float         mMatrix[16] ;
 *   char          mDescriptor[256];
 *  }AppCallBackEx;
 *
 *  static const char* AppCallBackEx_default_getDescriptor(struct IAppCallBack *callback) {
 *     struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
 *     return callbackEx->mDescriptor;
 *  }
 *
 *  static int  AppCallBackEx_default_setDescriptor(struct IAppCallBack *callback , const char *descriptor) {
 *     struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
 *     strncpy(callbackEx->mDescriptor, descriptor , 255);
 *     return 0;
 *  }
 *  .
 *  .
 *  .
 *  int AppCallBackEx_default_init(struct AppCallBackEx *appCallbackEx) {
 *      if (appCallbackEx == NULL)
 *         return -1 ;
 *      IAppCallBack *appCallback = (IAppCallBack*)appCallbackEx;
 *      int code = IAppCallBack_default_init((IAppCallBack*)&appCallback) ;
 *      appCallback->setDescriptor = AppCallBackEx_default_setDescriptor ;
 *      appCallback->getDescriptor = AppCallBackEx_default_getDescriptor ;
 *      .
 *      .
 *      .
 *      return 0 ;
 *  }
 */
 typedef struct IAppCallBack {
     /**
 	 * @brief 向vr系统app设置Descriptor值函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  descriptor  app的descriptor值
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  if (appCallback->setDescriptor != NULL)
     *     appCallback->setDescriptor(appCallback,"weixin.com");
 	 */
     int (*setDescriptor)(struct IAppCallBack *callback , const char *descriptor) ;

     /**
 	 * @brief 获取vr系统app的Descriptor值函数
 	 *
 	 * @param[in]  callback      app回调接口指针变量
 	 *
 	 * @return 返回说明
 	 *        -<em>非NULL</em>   成功
 	 *        -<em>NULL</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  if (appCallback->setDescriptor != NULL) {
     *     appCallback->setDescriptor(appCallback,"weixin.com");
     *     const char *descriptor = appCallback->getDescriptor(appCallback) ;
     *  }
 	 */
     const char* (*getDescriptor)(struct IAppCallBack *callback) ;

     /**
 	 * @brief vr系统app释放回调指针函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  if (appCallback->free != NULL)
     *     appCallback->free(appCallback);
 	 */
     int (*free)(struct IAppCallBack *callback);

     /**
 	 * @brief vr系统app功能(背景/销毁)预前处理函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  mode        预前处理模式
     *        -<em>IAPPCALLBACK_ONBACKGROUND</em>  background
 	 *        -<em>IAPPCALLBACK_ONDESTROY</em>     destroy
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *        -<em>-2</em>     失败,非法模式
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  if (appCallback->predict != NULL)
     *     appCallback->predict(appCallback,IAPPCALLBACK_ONBACKGROUND);
 	 */
     int  (*predict)(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode);

     /**
 	 * @brief vr系统app功能(创建/背景/销毁)执行函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  mode        处理模式
     *        -<em>IAPPCALLBACK_ONCREATE</em>      create
     *        -<em>IAPPCALLBACK_ONBACKGROUND</em>  background
 	 *        -<em>IAPPCALLBACK_ONDESTROY</em>     destroy
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *        -<em>-2</em>     失败,非法模式
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  if (appCallback->process != NULL)
     *     appCallback->process(appCallback,IAPPCALLBACK_ONCREATE);
 	 */
     int  (*process)(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode);

     /**
 	 * @brief vr系统app按键处理函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  key         按键相关信息指针变量
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  KeyInfo key ;
     *  if (appCallback->onKey != NULL)
     *     appCallback->onKey(appCallback,&key);
 	 */
     int  (*onKey)(struct IAppCallBack *callback , const KeyInfo *key);

     /**
 	 * @brief vr系统app更新特定参数函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  type        参数类型
 	 * @param[in]  data        参数数组首地址
 	 * @param[in]  sz          参数数据大小
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
     *  float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
     *  int sz = 16 ;
     *  if (appCallback->change != NULL)
     *     appCallback->change(appCallback,type,data,sz);
 	 */
     int  (*change)(struct IAppCallBack *callback , ENUM_PARAMETER_TYPE type, const float *data , int sz);

     /**
 	 * @brief vr系统app更新PoseState信息函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  poseState   姿势信息指针变量
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  PoseState poseState ;
     *  if (appCallback->pose != NULL)
     *     appCallback->pose(appCallback,&poseState);
 	 */
     int  (*pose)(struct IAppCallBack *callback , const PoseState *poseState);

     /**
 	 * @brief vr系统app更新序列化信息函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  decree      序列化信息指针变量
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  Decree decree ;
     *  if (appCallback->decree != NULL)
     *     appCallback->decree(appCallback,&decree);
 	 */
     int  (*decree)(struct IAppCallBack *callback , const Decree *decree);

     /**
 	 * @brief vr系统app时间同步函数
 	 *
 	 * @param[in]  callback    app回调接口指针变量
 	 * @param[in]  timestamp   同步时间戳
 	 *
 	 * @return 返回说明
 	 *        -<em>0</em>      成功
 	 *        -<em>-1</em>     失败
 	 *
 	 * @example
 	 * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
     *  int code = IAppCallBack_default_init(appCallback) ;
     *  int64_t timestamp = (int64_t)time(NULL) + 1 ;
     *  if (appCallback->sync != NULL)
     *     appCallback->sync(appCallback,timestamp);
 	 */
     int  (*sync)(struct IAppCallBack *callback , int64_t timestamp);
 } IAppCallBack;

 /**
  * @brief vr系统app默认回调初始化函数
  *
  * @param[in]  callback    app回调接口指针变量
  *
  * @return 返回说明
  *        -<em>0</em>      成功
  *        -<em>-1</em>     失败
  *
  * @example
  * struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack);
  *  int code = IAppCallBack_default_init(appCallback) ;
  */
 int IAppCallBack_default_init(struct IAppCallBack *callback);

 __END_DECLS

 /**
  * @}
  */

 #endif //__IRIS_IAPP_CALLBACK_H__
