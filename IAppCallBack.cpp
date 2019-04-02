/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/06
**   File: IAppManager.h
**   Function:  interface of AppManager for user
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

#include "IAppCallBack.h"

static int  IAppCallBack_default_setDescriptor(struct IAppCallBack *callback , const char *descriptor) {
    printf("%s line:%d %s\n" , __FILE__ , __LINE__ , descriptor) ;
    return -1;
}

static const char* IAppCallBack_default_getDescriptor(struct IAppCallBack *callback) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , callback) ;
    return "iapcallback_default";
}

static int  IAppCallBack_default_free(struct IAppCallBack *callback) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , callback) ;
    return 0;
}

static int  IAppCallBack_default_predict(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

static int  IAppCallBack_default_process(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

static int  IAppCallBack_default_onKey(struct IAppCallBack *callback , const KeyInfo *key) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , key) ;
    return 0;
}

static int  IAppCallBack_default_change(struct IAppCallBack *callback , ENUM_PARAMETER_TYPE type, const float *data , int sz) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

static int  IAppCallBack_default_pose(struct IAppCallBack *callback , const PoseState *poseState) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , poseState) ;
    return 0;
}

static int  IAppCallBack_default_decree(struct IAppCallBack *callback , const Decree *decree) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , decree) ;
    return 0;
}

static int  IAppCallBack_default_sync(struct IAppCallBack *callback , int64_t timestamp) {
    printf("%s line:%d %ld\n" , __FILE__ , __LINE__ , timestamp) ;
    return 0;
}

int IAppCallBack_default_init(struct IAppCallBack *callback) {
    if (callback == NULL)
       return -1 ;

    callback->setDescriptor = IAppCallBack_default_setDescriptor ;
    callback->getDescriptor = IAppCallBack_default_getDescriptor ;

    callback->free = IAppCallBack_default_free ;
    callback->predict = IAppCallBack_default_predict ;

    callback->process = IAppCallBack_default_process ;
    callback->onKey = IAppCallBack_default_onKey ;

    callback->change = IAppCallBack_default_change ;
    callback->pose = IAppCallBack_default_pose ;

    callback->decree = IAppCallBack_default_decree ;
    callback->sync = IAppCallBack_default_sync ;

    return 0;
}
