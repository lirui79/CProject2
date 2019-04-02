/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/06
**   File: IAppManager.h
**   Function:  Manager of AppManager for user
**   History:
**       2018/11/06 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_IAPP_MANAGER_H__
#define __IRIS_IAPP_MANAGER_H__

#include <stdint.h>
#include <sys/cdefs.h>

#include "ProtoBuffer.h"
#include "IAppCallBack.h"

/**
 * @addtogroup sdk Manager
 * @{
 */

__BEGIN_DECLS

typedef enum ENUM_APPMODE {
    APP_MODE_FULLSCREEN = 0,  // full screen
    APP_MODE_WINDOW     = 1,  // window
    APP_MODE_SERVICE    = 2,  // service
}ENUM_APPMODE;

typedef enum ENUM_START_TYPE {
    START_IRIS_WIN     = -1 ,  // iris_win_service
    START_IRIS_SERVICE =  0,   // format: "packagename/activityname" - basically window
    START_IRIS_APP     =  1,   // format: "packagename/activityname" - basically fullscreen
    START_ANDROID_APP  =  2,   // format: "packagename/activityname"
    START_IRIS_WINDOW  =  3,   // format: "packagename/activityname" - window from app
}ENUM_START_TYPE;

typedef enum ENUM_IAPPMANAGER_REQUEST {
    IAPPMANAGER_REQUEST_UNLOADIRISVR   = 1 , // unload iris vr when onBackground, onDisconnect would be called
    IAPPMANAGER_REQUEST_LEAVEIRISVR    = 2 , // leave iris vr when on Background would be called
    IAPPMANAGER_REQUEST_ADJUSTOHPOSE   = 3 , // adjust iriswin poseState to head poseState
}ENUM_IAPPMANAGER_REQUEST;

typedef enum ENUM_IAPPMANAGER_WAITCURSOR {
    IAPPMANAGER_WAITCURSOR_HIDE = 0 , // hide wait  Cursor
    IAPPMANAGER_WAITCURSOR_SHOW = 1 , // show wait  Cursor
}ENUM_IAPPMANAGER_WAITCURSOR;

typedef enum ENUM_IAPPMANAGER_UPDATEWINDOW {
    IAPPMANAGER_UPDATEWINDOW_RESUME = 0 , //  resume
    IAPPMANAGER_UPDATEWINDOW_PAUSE  = 1 , //  pause window change not to screen
}ENUM_IAPPMANAGER_UPDATEWINDOW;

typedef enum ENUM_IAPPMANAGER_PREDICT_TYPE {
    IAPPMANAGER_PREDICT_HEAD  = 0 , //头部姿势信息
    IAPPMANAGER_PREDICT_OTHER = 1 , //非头部信息包含光标信息
}ENUM_IAPPMANAGER_PREDICT_TYPE;

typedef enum ENUM_IAPPMANAGER_ELUER_CMD {
    IAPPMANAGER_ELUER_KEEP  = 0 , //  hold keep Elur angle
    IAPPMANAGER_ELUER_RESET = 1 , //  reset Elur angle
}ENUM_IAPPMANAGER_ELUER_CMD;

typedef struct IAppManager {
    /**
	 * @brief vr系统app系统接口更新特定参数函数
	 *
	 * @param[in]  appManager   app系统接口指针
	 * @param[in]  type           参数类型
	 * @param[in]  data           参数数组首地址
	 * @param[in]  sz             参数数据大小
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  const struct IAppManager *appManager = IAppManager_get() ;
     *  ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
     *  float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
     *  int sz = 16 ;
     *  if (appManager->setParm != NULL)
     *     appManager->setParm(appManager,type,data,sz);
	 */
    int (*setParm)(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, const float *data , int sz) ;

    /**
	 * @brief vr系统app系统接口更新特定参数函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     type           参数类型
	 * @param[out]    data           参数数组首地址
	 * @param[inout]  sz             参数数据大小地址 in - data数组实际内存大小  out - data中获取数据参数大小
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
     *  float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
     *  int sz = 16 ;
     *  if (appManager->setParm != NULL) {
     *     appManager->setParm(appManager,type,data,sz);
     *     float  vdata[16] = {0} ;
     *     int vsz = 16 ;
     *     appManager->getParm(appManager,type,vdata,&vsz) ;
     *   }
	 */
    int (*getParm)(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, float *data , int *sz);

    /**
	 * @brief vr系统app系统接口设置调试标识函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     flags          调试参数标识
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->debug != NULL) {
     *     appManager->debug(appManager,“Debug”) ;
     *   }
	 */
    int (*debug)(struct IAppManager *appManager , const char *flags);

    /**
	 * @brief vr系统app系统接口(全屏/窗口/服务)初始化函数
     *        It should be called only once in the entire life cycle
     *        not responsible for delete callback(no good time..)
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     mode          调试参数标识
     *        -<em>APP_MODE_FULLSCREEN</em>  FULLSCREEN  it must be called in the same context or shared context as rendering
     *        -<em>APP_MODE_WINDOW</em>      WINDOW
	 *        -<em>APP_MODE_SERVICE</em>     SERVICE
	 * @param[in]     data          参数内容
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->init != NULL) {
     *     struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack));
     *     int code = IAppCallBack_default_init(appCallback) ;
     *     appManager->init(appManager,APP_MODE_FULLSCREEN,(void*)appCallback) ;
     *   }
	 */
    int (*init)(struct IAppManager *appManager , ENUM_APPMODE mode , const void *data);

    /**
	 * @brief vr系统app系统接口启动(IrisWin/IrisService/IrisApp/AndroidApp/IrisAPPWindow)函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     type           启动标识
     *        -<em>START_IRIS_WIN</em>        IrisWin  data -> key
     *        -<em>START_IRIS_SERVICE</em>    IrisService   format: "packagename/activityname" - basically window
	 *        -<em>START_IRIS_APP</em>        IrisApp       format: "packagename/activityname" - basically fullscreen
     *        -<em>START_ANDROID_APP</em>     AndroidApp    format: "packagename/activityname"
	 *        -<em>START_IRIS_WINDOW</em>     IrisAPPWindow format: "packagename/activityname" - window from app
	 * @param[in]     data           参数内容
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->start != NULL) {
     *     appManager->start(appManager,START_IRIS_WIN,"21313131313122") ;
     *   }
	 */
    int (*start)(struct IAppManager *appManager , ENUM_START_TYPE type ,const char *data);

    /**
	 * @brief vr系统app系统接口请求执行命令(unloadvr/leavevr/iriswinpos)函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     cmd            命令标识
     *        -<em>IAPPMANAGER_REQUEST_UNLOADIRISVR</em>        unload iris vr when onBackground, onDisconnect would be called
     *        -<em>IAPPMANAGER_REQUEST_LEAVEIRISVR</em>         leave iris vr when on Background would be called
	 *        -<em>IAPPMANAGER_REQUEST_ADJUSTOHPOSE</em>        adjust iriswin poseState to head poseState
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->request != NULL) {
     *     appManager->request(appManager,IAPPMANAGER_REQUEST_ADJUSTOHPOSE) ;
     *   }
	 */
    int (*request)(struct IAppManager *appManager , ENUM_IAPPMANAGER_REQUEST cmd);

    /**
	 * @brief vr系统app系统接口显示或隐藏光标函数 use a simple counting mechanism now
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     cmd            命令标识
     *        -<em>IAPPMANAGER_WAITCURSOR_HIDE</em>        hide wait cursor
     *        -<em>IAPPMANAGER_WAITCURSOR_SHOW</em>        show wait cursor
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->showCursor != NULL) {
     *     appManager->showCursor(appManager,IAPPMANAGER_WAITCURSOR_SHOW) ;
     *   }
	 */
    int (*showCursor)(struct IAppManager *appManager , ENUM_IAPPMANAGER_WAITCURSOR cmd);

    /**
	 * @brief vr系统app系统接口暂停/启动窗口更新函数
     * if pause, changes in any window will not be updated to screen
     * but window content will be used
     * note that surface destroy, window destroy are not allowed now
     *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     cmd            命令标识
     *        -<em>IAPPMANAGER_UPDATEWINDOW_RESUME</em>        resume
     *        -<em>IAPPMANAGER_UPDATEWINDOW_PAUSE</em>         pause
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->pause != NULL) {
     *     appManager->pause(appManager,IAPPMANAGER_UPDATEWINDOW_PAUSE) ;
     *   }
	 */
    int (*pause)(struct IAppManager *appManager , ENUM_IAPPMANAGER_UPDATEWINDOW cmd);

    /**
	 * @brief vr系统app系统接口渲染时设置左右眼姿势和纹理信息函数
     *      after rendering, set the textures with associated eye & pose
     *      Must be called in the same context as rendering these two/three textures
     *      if texture <= 0, do not render
     *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     eye            左右眼标识
     *        -<em>LEFT_EYE</em>        左眼
     *        -<em>RIGHT_EYE</em>       右眼
     * @param[in]     texid          纹理标识码数组首地址
     *        -<em>texid[0]</em>        场景纹理标识码
     *        -<em>texid[1]</em>        overlay纹理标识码
     *        -<em>texid[2]</em>        if(sz == 3) 全屏纹理标识码
     * @param[in]     sz            纹理标识码数组大小
     *        -<em>2</em>        纹理数组中包括场景纹理标识码/overlay纹理标识码
     *        -<em>3</em>        纹理数组中包括场景纹理标识码/overlay纹理标识码/全屏纹理标识码
     * @param[in]     pose       与眼相关PoseState信息指针变量
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->setEyeTextureAndPose != NULL) {
     *     unsigned int texid[3] = {1 , 2 , 3} ;
     *     PoseState pose ;
     *     appManager->setEyeTextureAndPose(appManager,RIGHT_EYE,texid,3,&pose) ;
     *   }
	 */
    int (*setEyeTextureAndPose)(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const unsigned int *texid , unsigned int sz , const PoseState *pose);

    /**
	 * @brief vr系统app系统接口预测(头部和非头部)姿势信息函数
     *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     eye            左右眼标识
     *        -<em>LEFT_EYE</em>        左眼
     *        -<em>RIGHT_EYE</em>       右眼
     * @param[in]     type           data数据类型标识
     *        -<em>IAPPMANAGER_PREDICT_HEAD</em>   data中为头部姿势信息  data -> PoseState *pose   pose of head
     *        -<em>IAPPMANAGER_PREDICT_OTHER</em>  data中为非头部信息包含光标信息  data -> IrisMotionCursorInfo *info
     *                                                        pose of no head and info of cursor  for motion info
     * @param[out]    data          信息变量指针
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->predict != NULL) {
     *     PoseState pose ;
     *     IrisMotionCursorInfo info;
     *     appManager->predict(appManager,LEFT_EYE,IAPPMANAGER_PREDICT_HEAD,(void*)&pose) ;
     *     appManager->predict(appManager,RIGHT_EYE,IAPPMANAGER_PREDICT_OTHER,(void*)&info) ;
     *   }
	 */
    int (*predict)(struct IAppManager *appManager , ENUM_EYE_TYPE eye , ENUM_IAPPMANAGER_PREDICT_TYPE type , void *data);

    /**
	 * @brief vr系统app系统接口重置系统三个Euler角度函数
     *       only support yaw now
     *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     pitch          Eluer角度俯仰角重置
     *        -<em>IAPPMANAGER_ELUER_KEEP</em>         保持
     *        -<em>IAPPMANAGER_ELUER_RESET</em>        重置
	 * @param[in]     yaw            Eluer角度偏航角重置
     *        -<em>IAPPMANAGER_ELUER_KEEP</em>         保持
     *        -<em>IAPPMANAGER_ELUER_RESET</em>        重置
	 * @param[in]     roll           Eluer角度翻滚角重置
     *        -<em>IAPPMANAGER_ELUER_KEEP</em>         保持
     *        -<em>IAPPMANAGER_ELUER_RESET</em>        重置
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->reset != NULL) {
     *     appManager->reset(appManager,IAPPMANAGER_ELUER_KEEP,IAPPMANAGER_ELUER_RESET,IAPPMANAGER_ELUER_KEEP) ;
     *   }
	 */
    int (*reset)(struct IAppManager *appManager , ENUM_IAPPMANAGER_ELUER_CMD pitch, ENUM_IAPPMANAGER_ELUER_CMD yaw, ENUM_IAPPMANAGER_ELUER_CMD roll);

    /**
	 * @brief vr系统app系统接口获取头部信息函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     pose           头部姿势信息指针变量
	 * @param[out]    dir            直前方向 direction rotate (0,0,1)
	 * @param[out]    up             向上方向 up rotate (0,1,0)
	 * @param[out]    mat            头部锚定矩阵 head anchor  matrix
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->simulateHead != NULL) {
     *     PoseState pose ;
     *     float dir[3] , up[3] , mat[16];
     *     appManager->simulateHead(appManager, &pose, dir, up, mat) ;
     *   }
	 */
    int (*simulateHead)(struct IAppManager *appManager , const PoseState *pose, float dir[3] ,float up[3] , float mat[16]);

    /**
	 * @brief vr系统app系统接口获取眼部信息函数
	 *     pos eye position relative to head anchor
     *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     eye            左右眼标识
     *        -<em>LEFT_EYE</em>        左眼
     *        -<em>RIGHT_EYE</em>       右眼
	 * @param[in]     pose           头部姿势信息指针变量
	 * @param[out]    pos            眼部位置信息
	 * @param[out]    mat            眼部锚定矩阵 eye matrix
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *        -<em>-2</em>     失败,非法标识
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->simulatedEye != NULL) {
     *     PoseState pose ;
     *     float pos[3] , mat[16];
     *     appManager->simulatedEye(appManager , LEFT_EYE , &pose, pos, mat) ;
     *   }
	 */
    int (*simulatedEye)(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const PoseState *pose, float pos[3] ,float mat[16]);

    /**
	 * @brief vr系统app系统接口退出系统函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->quit != NULL) {
     *     appManager->quit(appManager) ;
     *   }
	 */
    int (*quit)(struct IAppManager *appManager);

    /**
	 * @brief vr系统app系统接口序反列化函数
	 *
	 * @param[in]     appManager   app系统接口指针
	 * @param[in]     probuf         序列化信息结构指针变量
	 *
	 * @return 返回说明
	 *        -<em>0</em>      成功
	 *        -<em>-1</em>     失败
	 *
	 * @example
	 *  struct IAppManager *appManager = IAppManager_get() ;
     *  if (appManager->decree != NULL) {
     *     ProtoBuffer probuf;
     *     appManager->decree(appManager, &probuf) ;
     *   }
	 */
    int (*decree)(struct IAppManager *appManager , ProtoBuffer *probuf);

} IAppManager ;


/**
 * @brief vr系统app默认回调初始化函数
 *
 * @param[in]  callback    app回调接口指针变量
 *
 * @return 返回说明
 *        -<em>非NULL</em>      成功
 *        -<em>NULL</em>     失败
 *
 * @example
 *  struct IAppManager *appManager = IAppManager_get();
 *  int code = appManager->debug(appManager,"debug") ;
 */
struct IAppManager* IAppManager_get();


//-----
// jni
//-----

//int nativeLockCanvas(JNIEnv *env, jclass clazz, jlong nativeABuffer, jobject canvasObj, jobject dirtyRectObj);

//int nativeUnlockCanvas(JNIEnv *env, jclass clazz, jlong nativeABuffer, jobject canvasObj);



__END_DECLS

/**
 * @}
 */

#endif //__IRIS_IAPP_MANAGER_H__
