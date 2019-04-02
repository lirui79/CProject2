/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/13
**   File: IJavaCallBack.h
**   Function:  interface of C callback Java for user
**   History:
**       2018/11/13 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_IJAVA_CALLBACK_H__
#define __IRIS_IJAVA_CALLBACK_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <jni.h>


/**
 * @addtogroup sdk interface
 * @{
 */

__BEGIN_DECLS

typedef struct IJavaCallBack {
    /**
    * @brief C语言回调Java初始化函数
    *
    * @param[in]  callback    回调接口指针变量
    * @param[in]  env         JNIEnv变量指针
    * @param[in]  obj         jobject变量
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *  JNIEnv env ;
    *  jobject obj ;
    *  if (callback->init != NULL)
    *     callback->init(callback,&env,obj);
    */
    int (*init)(struct IJavaCallBack *callback , JNIEnv *env, jobject obj) ;

    /**
    * @brief C语言回调Java重置函数
    *
    * @param[in]  callback    回调接口指针变量
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->reset != NULL)
    *     callback->reset(callback);
    */
    int (*reset)(struct IJavaCallBack *callback) ;

    /**
    * @brief C语言回调Java回调接口内存释放函数
    *
    * @param[in]  callback    回调接口指针变量
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->free != NULL)
    *     callback->free(callback);
    */
    int (*free)(struct IJavaCallBack *callback) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethod != NULL)
    *     callback->callMethod(callback, "onExit");
    */
    int (*callMethod)(struct IJavaCallBack *callback , const char *methodName) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val           回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodL != NULL)
    *     callback->callMethodL(callback, "OnSyncReceived" , (jlong)1);
    */
    int (*callMethodL)(struct IJavaCallBack *callback , const char *methodName, jlong val) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val           回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodI != NULL)
    *     callback->callMethodI(callback, "OnCreate", (jint)2);
    */
    int (*callMethodI)(struct IJavaCallBack *callback , const char *methodName, jint val) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val           回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodZ != NULL)
    *     callback->callMethodZ(callback, "useOneTexture", (jboolean)true);
    */
    int (*callMethodZ)(struct IJavaCallBack *callback , const char *methodName, jboolean val) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIZ != NULL)
    *     callback->callMethodIZ(callback, "setGlobalFollowPose", (jint)1, (jboolean)true);
    */
    int (*callMethodIZ)(struct IJavaCallBack *callback , const char *methodName, jint val1, jboolean val2) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodII != NULL)
    *     callback->callMethodII(callback, "setGlobalWindowParent", (jint)0xade04884, (jint)0x0xade16980);
    */
    int (*callMethodII)(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodJJ != NULL)
    *     callback->callMethodJJ(callback, "OnProgress", (jlong)0x10, (jlong)0x50);
    */
    int (*callMethodJJ)(struct IJavaCallBack *callback , const char *methodName, jlong val1, jlong val2) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodFF != NULL)
    *     callback->callMethodFF(callback, "onMouseMove", (jfloat)0.34, (jfloat)0.32);
    */
    int (*callMethodFF)(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIII != NULL)
    *     callback->callMethodIII(callback, "setSurfaceZorder", (jint)0x1, (jint)0x5, (jint)0x10001);
    */
    int (*callMethodIII)(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2, jint val3) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIFF != NULL)
    *     callback->callMethodIFF(callback, "setGlobalWindowSize", (jint)0x01, (jfloat)1.0, (jfloat)0.5);
    */
    int (*callMethodIFF)(struct IJavaCallBack *callback , const char *methodName, jint val1, jfloat val2, jfloat val3) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodFFF != NULL)
    *     callback->callMethodFFF(callback, "setSize", (jfloat)1.0, (jfloat)0.7, (jfloat)0.6);
    */
    int (*callMethodFFF)(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2, jfloat val3) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    * @param[in]  val4          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodFFFF != NULL)
    *     callback->callMethodFFFF(callback, "setQuat", (jfloat)1.0, (jfloat)0.0, (jfloat)0.0, (jfloat)1.0);
    */
    int (*callMethodFFFF)(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2, jfloat val3, jfloat val4) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    * @param[in]  val4          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIFFF != NULL)
    *     callback->callMethodIFFF(callback, "setPos", (jint)0x06, (jfloat)0.5, (jfloat)0.7, (jfloat)0.4);
    */
    int (*callMethodIFFF)(struct IJavaCallBack *callback , const char *methodName, jint val1, jfloat val2, jfloat val3, jfloat val4) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  handle        回调方法参数
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    * @param[in]  val4          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIIIFF != NULL)
    *     callback->callMethodIIIFF(callback, "onKey", (jint)0x01, (jint)0x00, (jint)0x24, (jfloat)0.5, (jfloat)0.45);
    */
    int (*callMethodIIIFF)(struct IJavaCallBack *callback , const char *methodName, jint handle, jint val1, jint val2, jfloat val3, jfloat val4) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    * @param[in]  val3          回调方法参数
    * @param[in]  val4          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  if (callback->callMethodIIFF != NULL)
    *     callback->callMethodIIFF(callback, (jint)0x01, (jint)0x03, (jfloat)0.7, (jfloat)0.64);
    */
    int (*callMethodIIFF)(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2, jfloat val3, jfloat val4) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  handle        回调方法参数
    * @param[in]  val1          回调方法参数
    * @param[in]  val2          回调方法参数
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  jfloat pos[3] = {0.5 , 0.6 , 0.34} , quat[4] = {1.0 , 0.0 , 0.0 , 1.0};
    *  if (callback->callMethodI_F_F != NULL)
    *     callback->callMethodI_F_F(callback, "setGlobalWindowLocation", (jint)0x01, pos, quat);
    */
    int (*callMethodI_F_F)(struct IJavaCallBack *callback , const char *methodName, jint handle, jfloat const val1[3], jfloat const val2[4]) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val1          回调方法参数 数组[3]
    * @param[in]  val2          回调方法参数 数组[4]
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  jfloat pos[3] = {0.5 , 0.6 , 0.34} , quat[4] = {1.0 , 0.0 , 0.0 , 1.0};
    *  if (callback->callMethod_F_F != NULL)
    *     callback->callMethod_F_F(callback, "setLocation", pos, quat);
    */
    int (*callMethod_F_F)(struct IJavaCallBack *callback , const char *methodName, jfloat const val1[3], jfloat const val2[4]) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  val           回调方法参数  数组首地址
    * @param[in]  sz            回调方法参数  数组大小
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  jfloat surfaceProperty[7] = {0.5 , 0.6 , 0.34 , 1.0 , 0.0 , 0.0 , 1.0};
    *  if (callback->callMethod_FI != NULL)
    *     callback->callMethod_FI(callback, "createSurface", surfaceProperty, (jint)0x07);
    */
    int (*callMethod_FI)(struct IJavaCallBack *callback , const char *methodName, const jfloat *val, jint sz) ;

    /**
    * @brief C语言回调Java回调接口执行回调函数
    *
    * @param[in]  callback      回调接口指针变量
    * @param[in]  methodName    回调方法名称
    * @param[in]  object        对象实体
    * @param[in]  methodSig     回调方法签名
    * @param[in]  val           回调方法参数
    * @param[in]  rgc           垃圾是否回收
    *
    * @return 返回说明
    *        -<em>0</em>      成功
    *        -<em>-1</em>     失败
    *
    * @example
    *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
    *
    *  const char *methodSig = "(Lcom/iris_view/sdk/window/Location;)V";
    *  Location *location = new Location();
    *  jclass deClass = classaMap["com/iris_view/sdk/window/Location"];
    *  if (callback->callMethodOJZ != NULL)
    *     callback->callMethodOJZ(callback, "onLocationChanged", deClass, methodSig, (jlong)0x05, true);
    */
    int (*callMethodOJZ)(struct IJavaCallBack *callback , const char *methodName, jclass object, const char *methodSig, jlong val, jboolean rgc) ;
}IJavaCallBack;

/**
 * @brief 分配C语言回调Java回调接口指针
 *
 * @return
 * 	<em>非NULL</em>  C语言回调Java回调接口对象指针
 * 	<em>NULL</em>   失败
 *
 * @example
 *  struct IJavaCallBack *callback = IJavaCallBack_defalut_allocate();
 *
 *  if (callback->callMethodI != NULL)
 *     callback->callMethodI(callback, "OnCreate", (jint)2);
 *  callback->free(callback) ;
 */
struct IJavaCallBack* IJavaCallBack_defalut_allocate() ;


 __END_DECLS

 /**
  * @}
  */


#endif //__IRIS_IJAVA_CALLBACK_H__
