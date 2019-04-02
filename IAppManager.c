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

static int IAppManager_default_setParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, const float *data , int sz) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

static int IAppManager_default_getParm(struct IAppManager *appManager , ENUM_PARAMETER_TYPE type, float *data , int *sz) {
    printf("%s line:%d %x\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

static int IAppManager_default_debug(struct IAppManager *appManager , const char *flags) {
    printf("%s line:%d %s\n" , __FILE__ , __LINE__ , flags) ;

    return 0;
}

static int IAppManager_default_init(struct IAppManager *appManager , ENUM_APPMODE mode , const void *data) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , mode) ;
    return 0;
}

static int IAppManager_default_start(struct IAppManager *appManager , ENUM_START_TYPE type ,const char *data) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , type) ;
    return 0;
}

static int IAppManager_default_request(struct IAppManager *appManager , ENUM_IAPPMANAGER_REQUEST cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

static int IAppManager_default_showCursor(struct IAppManager *appManager , ENUM_IAPPMANAGER_WAITCURSOR cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

static int IAppManager_default_pause(struct IAppManager *appManager , ENUM_IAPPMANAGER_UPDATEWINDOW cmd) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , cmd) ;
    return 0;
}

static int IAppManager_default_setEyeTextureAndPose(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const unsigned int *texid , unsigned int sz , const PoseState *pose) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

static int IAppManager_default_predict(struct IAppManager *appManager , ENUM_EYE_TYPE eye , ENUM_IAPPMANAGER_PREDICT_TYPE type , void *data) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

static int IAppManager_default_reset(struct IAppManager *appManager , ENUM_IAPPMANAGER_ELUER_CMD pitch, ENUM_IAPPMANAGER_ELUER_CMD yaw, ENUM_IAPPMANAGER_ELUER_CMD roll) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , yaw) ;
    return 0;
}

static int IAppManager_default_simulateHead(struct IAppManager *appManager , const PoseState *pose, float dir[3] ,float up[3] , float mat[16]) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , pose) ;
    return 0;
}

static int IAppManager_default_simulatedEye(struct IAppManager *appManager , ENUM_EYE_TYPE eye, const PoseState *pose, float pos[3] ,float mat[16]) {
    printf("%s line:%d %d\n" , __FILE__ , __LINE__ , eye) ;
    return 0;
}

static int IAppManager_default_quit(struct IAppManager *appManager) {
    printf("%s line:%d\n" , __FILE__ , __LINE__) ;
    return 0;
}

static int IAppManager_default_decree(struct IAppManager *appManager , const Decree *decree) {
    printf("%s line:%d %p\n" , __FILE__ , __LINE__ , decree) ;
    return 0;
}

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
} ;

struct IAppManager* IAppManager_get() {
    return (&appManager_defalt);
}
