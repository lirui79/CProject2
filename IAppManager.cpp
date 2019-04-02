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

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "IAppManager.h"

class AppManager : public IAppManager {
public:
    AppManager() ;
    virtual ~AppManager() ;

    int setParm(ENUM_PARAMETER_TYPE type, const float *data , int sz);

    int getParm(ENUM_PARAMETER_TYPE type, float *data , int *sz);

    int init(ENUM_APPMODE mode , const void *data) ;

    int decree(ProtoBuffer *probuf);

protected:
    static int IAppManager_default_setParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, const float *data , int sz);

    static int IAppManager_default_getParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, float *data , int *sz);

    static int IAppManager_default_debug(struct IAppManager *appManager , const char *flags);

    static int IAppManager_default_init(struct IAppManager *appManager , ENUM_APPMODE mode , const void *data) ;

    static int IAppManager_default_start(struct IAppManager *appManager , ENUM_START_TYPE type ,const char *data);

    static int IAppManager_default_request(struct IAppManager *appManager , ENUM_IAPPMANAGER_REQUEST cmd);

    static int IAppManager_default_showCursor(struct IAppManager *appManager , ENUM_IAPPMANAGER_WAITCURSOR cmd);

    static int IAppManager_default_pause(struct IAppManager *appManager , ENUM_IAPPMANAGER_UPDATEWINDOW cmd);

    static int IAppManager_default_setEyeTextureAndPose(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const unsigned int *texid , unsigned int sz , const PoseState *pose);

    static int IAppManager_default_predict(struct IAppManager *appManager , ENUM_EYE_TYPE eye , ENUM_IAPPMANAGER_PREDICT_TYPE type , void *data);

    static int IAppManager_default_reset(struct IAppManager *appManager , ENUM_IAPPMANAGER_ELUER_CMD pitch, ENUM_IAPPMANAGER_ELUER_CMD yaw, ENUM_IAPPMANAGER_ELUER_CMD roll) ;

    static int IAppManager_default_simulateHead(struct IAppManager *appManager , const PoseState *pose, float dir[3] ,float up[3] , float mat[16]);

    static int IAppManager_default_simulatedEye(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const PoseState *pose, float pos[3] ,float mat[16]);

    static int IAppManager_default_quit(struct IAppManager *appManager) ;

    static int IAppManager_default_decree(struct IAppManager *appManager , ProtoBuffer *probuf);
private:
    char mName[16] ;
    int  mType ;
} ;


AppManager::AppManager() {
    strcpy(mName , "hello world!") ;
    mType = 123124 ;
    IAppManager::setParm = AppManager::IAppManager_default_setParm ;
    IAppManager::getParm = AppManager::IAppManager_default_getParm ;
    IAppManager::debug = AppManager::IAppManager_default_debug ;
    IAppManager::init = AppManager::IAppManager_default_init ;
    IAppManager::start = AppManager::IAppManager_default_start ;
    IAppManager::request = AppManager::IAppManager_default_request ;
    IAppManager::showCursor = AppManager::IAppManager_default_showCursor ;
    IAppManager::pause = AppManager::IAppManager_default_pause ;
    IAppManager::setEyeTextureAndPose = AppManager::IAppManager_default_setEyeTextureAndPose ;
    IAppManager::predict = AppManager::IAppManager_default_predict ;
    IAppManager::reset = AppManager::IAppManager_default_reset ;
    IAppManager::simulateHead = AppManager::IAppManager_default_simulateHead ;
    IAppManager::simulatedEye = AppManager::IAppManager_default_simulatedEye ;
    IAppManager::quit = AppManager::IAppManager_default_quit ;
    IAppManager::decree = AppManager::IAppManager_default_decree ;
}

AppManager::~AppManager() {

}

int AppManager::setParm(ENUM_PARAMETER_TYPE type, const float *data , int sz) {
    struct IAppManager *appManager = (struct IAppManager*) this ;
    return appManager->setParm(appManager , type , data , sz) ;
}

int AppManager::getParm(ENUM_PARAMETER_TYPE type, float *data , int *sz) {
    struct IAppManager *appManager = (struct IAppManager*) this ;
    return appManager->getParm(appManager , type , data , sz) ;
}

int AppManager::init(ENUM_APPMODE mode , const void *data) {
    struct IAppManager *appManager = (struct IAppManager*) this ;
    return appManager->init(appManager , mode , data) ;
}

int AppManager::decree(ProtoBuffer *probuf) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , probuf) ;

    printf("int8_t : %x \n" , probuf->readInt8(probuf)) ;

    printf("uint8_t : %x \n" , probuf->readUInt8(probuf)) ;

    printf("int16_t : %x \n" , probuf->readInt16(probuf)) ;

    printf("uint16_t : %x \n" , probuf->readUInt16(probuf)) ;


    printf("int32_t : %x \n" , probuf->readInt32(probuf)) ;

    printf("uint32_t : %x \n" , probuf->readUInt32(probuf)) ;

    printf("int64_t : %lx \n" , probuf->readInt64(probuf)) ;

    printf("uint64_t : %lx \n" , probuf->readUInt64(probuf)) ;


    printf("CString : %s \n" , probuf->readCString(probuf)) ;

    printf("float : %f \n" , probuf->readFloat(probuf)) ;

    printf("double : %lf \n" , probuf->readDouble(probuf)) ;

    uint8_t udata1[16] ;
    int usz = probuf->read(probuf , udata1 , 16) ;

    for (int j = 0 ; j < usz ; ++j)
       printf("data %d %x\n", j , udata1[j]);


    printf("Fd file : %x \n" , probuf->readFd(probuf)) ;

    int fdata1[5] ;
    int sz = probuf->readFdBuffer(probuf , fdata1 , 5) ;
    for (int i = 0 ; i < sz ; ++i)
       printf("FdBuffer %d  %x\n", i , fdata1[i]);

    probuf->clear(probuf) ;

    probuf->reset(probuf) ;
    return 0;
}

int AppManager::IAppManager_default_setParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, const float *data , int sz) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

int AppManager::IAppManager_default_getParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, float *data , int *sz) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

int AppManager::IAppManager_default_debug(struct IAppManager *appManager , const char *flags) {
    AppManager *appManagerEx = (AppManager*) appManager ;
    printf("%s line:%d %s  %s  %d\n" , __FILE__ , __LINE__ , flags , appManagerEx->mName , appManagerEx->mType) ;

    return 0;
}

int AppManager::IAppManager_default_init(struct IAppManager *appManager , ENUM_APPMODE mode , const void *data) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

int AppManager::IAppManager_default_start(struct IAppManager *appManager , ENUM_START_TYPE type ,const char *data) {
    printf("%s line:%d %d %s\n" , __FILE__ , __LINE__ , type , data) ;
    return 0;
}

int AppManager::IAppManager_default_request(struct IAppManager *appManager , ENUM_IAPPMANAGER_REQUEST cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

int AppManager::IAppManager_default_showCursor(struct IAppManager *appManager , ENUM_IAPPMANAGER_WAITCURSOR cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

int AppManager::IAppManager_default_pause(struct IAppManager *appManager , ENUM_IAPPMANAGER_UPDATEWINDOW cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

int AppManager::IAppManager_default_setEyeTextureAndPose(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const unsigned int *texid , unsigned int sz , const PoseState *pose) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

int AppManager::IAppManager_default_predict(struct IAppManager *appManager , ENUM_EYE_TYPE eye , ENUM_IAPPMANAGER_PREDICT_TYPE type , void *data) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

int AppManager::IAppManager_default_reset(struct IAppManager *appManager , ENUM_IAPPMANAGER_ELUER_CMD pitch, ENUM_IAPPMANAGER_ELUER_CMD yaw, ENUM_IAPPMANAGER_ELUER_CMD roll) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , yaw) ;
    return 0;
}

int AppManager::IAppManager_default_simulateHead(struct IAppManager *appManager , const PoseState *pose, float dir[3] ,float up[3] , float mat[16]) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , pose) ;
    return 0;
}

int AppManager::IAppManager_default_simulatedEye(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const PoseState *pose, float pos[3] ,float mat[16]) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

int AppManager::IAppManager_default_quit(struct IAppManager *appManager) {
    printf("%s line:%d\n" , __FILE__ , __LINE__) ;
    return 0;
}

int AppManager::IAppManager_default_decree(struct IAppManager *appManager , ProtoBuffer *probuf) {
    AppManager *appManagerEx = (AppManager*) appManager ;
    return appManagerEx->decree(probuf) ;
}
/*
static IAppManager appManager_defalt = {
    .setParm = IAppManager_default_setParm ,
    .getParm = IAppManager_default_getParm ,
    .debug = IAppManager_default_debug ,
    .init = IAppManager_default_init ,
    .start = IAppManager_default_start ,
    .request = IAppManager_default_request ,
    .showCursor = IAppManager_default_showCursor ,
    .pause = IAppManager_default_pause ,
    .setEyeTextureAndPose = IAppManager_default_setEyeTextureAndPose ,
    .predict = IAppManager_default_predict ,
    .reset = IAppManager_default_reset ,
    .simulateHead = IAppManager_default_simulateHead ,
    .simulatedEye = IAppManager_default_simulatedEye ,
    .quit = IAppManager_default_quit ,
    .decree = IAppManager_default_decree ,
} ;*/

static AppManager appManager_defalt ;

struct IAppManager* IAppManager_get() {
    return (&appManager_defalt);
}
