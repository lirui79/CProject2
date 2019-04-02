
/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/08
**   File: IAppManager.h
**   Function:  example for appCallback
**   History:
**       2018/11/08 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "AppCallBack_example.h"


static int  AppCallBack_example_setDescriptor(struct IAppCallBack *callback , const char *descriptor) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %s\n" , __FILE__ , __LINE__ , descriptor) ;
    strncpy(callbackEx->mDescriptor, descriptor , 255);
    return 0;
}

static const char* AppCallBack_example_getDescriptor(struct IAppCallBack *callback) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , callback) ;
    return callbackEx->mDescriptor;
}

static int  AppCallBack_example_free(struct IAppCallBack *callback) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , callback) ;
    return 0;
}

static int  AppCallBack_example_predict(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

static int  AppCallBack_example_process(struct IAppCallBack *callback , ENUM_IAPPCALLBACK_MODE mode) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

static int  AppCallBack_example_onKey(struct IAppCallBack *callback , const KeyInfo *key) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , key) ;
    return 0;
}

static int  AppCallBack_example_change(struct IAppCallBack *callback , ENUM_PARAMETER_TYPE type, const float *data , int sz) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

static int  AppCallBack_example_pose(struct IAppCallBack *callback , const PoseState *poseState) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , poseState) ;
    return 0;
}

static int  AppCallBack_example_decree(struct IAppCallBack *callback , const Decree *decree) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , decree) ;
    return 0;
}

static int  AppCallBack_example_sync(struct IAppCallBack *callback , int64_t timestamp) {
    struct AppCallBackEx *callbackEx = (struct AppCallBackEx *) callback ;
    printf("%s line:%d %ld\n" , __FILE__ , __LINE__ , timestamp) ;
    return 0;
}

int AppCallBack_example_init(struct AppCallBackEx *callbackEx) {
    if (callbackEx == NULL)
       return -1 ;
    struct IAppCallBack *callback = (struct IAppCallBack *)callbackEx ;
    if (IAppCallBack_default_init(callback) < 0) {
       return -2 ;
    }

    callback->setDescriptor = AppCallBack_example_setDescriptor ;
    callback->getDescriptor = AppCallBack_example_getDescriptor ;

    callback->free = AppCallBack_example_free ;
    callback->predict = AppCallBack_example_predict ;

    callback->process = AppCallBack_example_process ;
    callback->onKey = AppCallBack_example_onKey ;

    callback->change = AppCallBack_example_change ;
    callback->pose = AppCallBack_example_pose ;

    callback->decree = AppCallBack_example_decree ;
    callback->sync = AppCallBack_example_sync ;

    return 0;
}
