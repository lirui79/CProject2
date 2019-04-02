#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IAppManager.h"
#include "AppCallBack_example.h"
#include "ProtoBuffer.h"

int test_IAppManager() {
    struct IAppManager *appManager = IAppManager_get() ;
    appManager->debug(appManager , "debug") ;

    ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
    float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
    int sz = 16 ;
    appManager->setParm(appManager,type,data,sz);

    float  vdata[16] = {0} ;
    int vsz = 16 ;
    appManager->getParm(appManager,type,vdata,&vsz) ;

    //struct IAppCallBack *appCallback = (struct IAppCallBack *) malloc(sizeof(struct IAppCallBack));
    struct AppCallBackEx appCallback ;
    int code = AppCallBack_example_init(&appCallback) ;

    appManager->init(appManager,APP_MODE_FULLSCREEN,(void*)&appCallback) ;

    appManager->start(appManager,START_IRIS_WIN,"213131313131223\0") ;

    appManager->request(appManager,IAPPMANAGER_REQUEST_ADJUSTOHPOSE) ;

    appManager->showCursor(appManager,IAPPMANAGER_WAITCURSOR_SHOW) ;

    appManager->pause(appManager,IAPPMANAGER_UPDATEWINDOW_PAUSE) ;

    unsigned int texid[3] = {1 , 2 , 3} ;
    PoseState pose ;
    appManager->setEyeTextureAndPose(appManager,RIGHT_EYE,texid,3,&pose) ;

    IrisMotionCursorInfo info;
    appManager->predict(appManager,LEFT_EYE,IAPPMANAGER_PREDICT_HEAD,(void*)&pose) ;
    appManager->predict(appManager,RIGHT_EYE,IAPPMANAGER_PREDICT_OTHER,(void*)&info) ;

    appManager->reset(appManager,IAPPMANAGER_ELUER_KEEP,IAPPMANAGER_ELUER_RESET,IAPPMANAGER_ELUER_KEEP) ;

    float dir[3] , up[3] , mat[16];
    appManager->simulateHead(appManager, &pose, dir, up, mat) ;

    float pos[3] , mat1[16];
    appManager->simulatedEye(appManager , LEFT_EYE , &pose, pos, mat1) ;

    appManager->quit(appManager) ;

    Decree decree;
    appManager->decree(appManager, &decree) ;

    return 0 ;
}

int test_IAppCallBack() {
    struct IAppCallBack callback ;
    struct IAppCallBack*  appCallback;
    int code = IAppCallBack_default_init(&callback) ;
    appCallback = (struct IAppCallBack*) &callback ;

    appCallback->setDescriptor(appCallback,"weixin.com");

    //const char *descriptor = appCallback->getDescriptor(appCallback) ;
    printf("descriptor:%s\n" , appCallback->getDescriptor(appCallback)) ;

    appCallback->predict(appCallback,IAPPCALLBACK_ONBACKGROUND);

    appCallback->process(appCallback,IAPPCALLBACK_ONCREATE);

    KeyInfo key ;
    appCallback->onKey(appCallback,&key);

    ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
    float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
    int sz = 16 ;
    appCallback->change(appCallback,type,data,sz);

    PoseState poseState ;
    appCallback->pose(appCallback,&poseState);

    Decree decree ;
    appCallback->decree(appCallback,&decree);

    time_t now = time(NULL) ;
    int64_t timestamp = (int64_t)now + 1 ;
    appCallback->sync(appCallback,timestamp);

    appCallback->free(appCallback);
    return 0 ;
}

int test_AppCallBack_example() {
    struct AppCallBackEx callback ;
    struct IAppCallBack* appCallback ;
    int code = AppCallBack_example_init(&callback) ;
    appCallback = (struct IAppCallBack*) &callback ;

    appCallback->setDescriptor(appCallback,"IrisService.com");

    //const char *descriptor = appCallback->getDescriptor(appCallback) ;
    printf("descriptor:%s\n" , appCallback->getDescriptor(appCallback)) ;

    appCallback->free(appCallback);

    appCallback->predict(appCallback,IAPPCALLBACK_ONBACKGROUND);

    appCallback->process(appCallback,IAPPCALLBACK_ONCREATE);

    KeyInfo key ;
    appCallback->onKey(appCallback,&key);

    ENUM_PARAMETER_TYPE type = PARAMETER_EYEVIEW_RIGHT ;
    float data[16] = {1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1} ;
    int sz = 16 ;
    appCallback->change(appCallback,type,data,sz);

    PoseState poseState ;
    appCallback->pose(appCallback,&poseState);

    Decree decree ;
    appCallback->decree(appCallback,&decree);

    int64_t timestamp = (int64_t)time(NULL) + 1 ;
    appCallback->sync(appCallback,timestamp);
    return 0 ;
}

int test_ProtoBuffer() {
    struct ProtoBuffer *probuf = ProtoBuffer_defalut_allocate() ;
    if (!probuf)
         return -1 ;
    probuf->setEndian(probuf,BIG_PROTOBUFFER_ENDIAN) ;
    printf("%d \n" ,probuf->getEndian(probuf)) ;

    int8_t ival8 = 0x7f ;
    probuf->writeInt8(probuf,ival8) ;

    uint8_t uval8 = 0xf8 ;
    probuf->writeUInt8(probuf,uval8) ;

    int16_t ival16 = 0x7fbc ;
    probuf->writeInt16(probuf,ival16) ;

    uint16_t uval16 = 0xfa88 ;
    probuf->writeUInt16(probuf,uval16) ;

    int32_t ival32 = 0x7f0f9ff8 ;
    probuf->writeInt32(probuf,ival32) ;

    uint32_t uval32 = 0x86f0f9f8 ;
    probuf->writeUInt32(probuf,uval32) ;

    int64_t ival64  = 0x7f78ffffffffffff ;
    probuf->writeInt64(probuf,ival64) ;

    uint64_t uval64 = 0x8f87ffffffffffff ;
    probuf->writeUInt64(probuf,uval64) ;

    probuf->writeCString(probuf , "hello world!") ;

    float  fval = 19229.09897f ;
    printf("float - %f\n" , fval) ;
    probuf->writeFloat(probuf , fval) ;

    double dval = 8827319319.2343 ;
    printf("double - %lf\n" , dval) ;
    probuf->writeDouble(probuf , dval) ;

    uint8_t udata[16] = {0x12, 0x42, 0x33 ,0x64 , 0x5 , 0x36 , 0x7 , 0x88 , 0x19 , 0x10 , 0x21 , 0x12 , 0x13 , 0x4 , 0x55 , 0x16} ;
    probuf->write(probuf , udata , 16) ;

    int fd = 0xfff7 ;
    probuf->writeFd(probuf , fd) ;

    int fdata[] = {0x21313 , 0x32423 , 0x123234 , 0x4235 , 0x1020913} ;
    probuf->writeFdBuffer(probuf , fdata , 5) ;

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

    probuf->free(probuf) ;

    return 0 ;
}

int main(int argc , const char *argv[]) {
    test_IAppManager();
    test_IAppCallBack();
    test_AppCallBack_example();
    test_ProtoBuffer() ;
    return 0 ;
}
