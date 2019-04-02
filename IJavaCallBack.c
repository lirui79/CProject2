/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/13
**   File: IJavaCallBack.h
**   Function:  interface of  C callback Java  for user
**   History:
**       2018/11/13 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "IJavaCallBack.h"


typedef struct JavaCallBackEx {
    struct IJavaCallBack    mJavaCallBack ;

    JavaVM                 *mJavaVM;
    jobject                 mObject;
    JNIEnv                 *mJNIEnv;
    int32_t                 mAttached; // 1 - attached   0 - not attached
} JavaCallBackEx;

///////////////////////////////////////////////////////////////////////////////
static int  JavaCallBackEx_default_Attach(struct JavaCallBackEx *callbackEx) {
    if (callbackEx->mAttached)
        return 0 ;
    jint jcode = callbackEx->mJavaVM->GetEnv((void **) &(callbackEx->mJNIEnv), JNI_VERSION_1_6);
    if (jcode < 0)
        return -2 ;
    jcode = callbackEx->mJavaVM->AttachCurrentThread(&(callbackEx->mJNIEnv) , 0) ;
    if (jcode != JNI_OK)
        return -3 ;
    callbackEx->mAttached = 1 ;
    return 0 ;
}

static int  JavaCallBackEx_default_Detach(struct JavaCallBackEx *callbackEx) {
    if (callbackEx->mAttached == 0)
        return 0 ;
    callbackEx->mJavaVM->DetachCurrentThread();
    callbackEx->mAttached = 0;
    return 0 ;
}

static int  JavaCallBackEx_default_GetCallbackMethod(struct JavaCallBackEx *callbackEx, const char *methodName, const char *methodSig, jmethodID *methodID) {
    jmethodID mID = NULL ;
    if (callbackEx == NULL)
        return -1 ;

    if (JavaCallBackEx_default_Attach(callbackEx) < 0) {
        return -1;
    }

    jclass classObj = callbackEx->mJNIEnv->GetObjectClass(callbackEx->mObject);
    if (classObj == NULL) {
        JavaCallBackEx_default_Detach(callbackEx);
        return -1;
    }

    mID = callbackEx->mJNIEnv->GetMethodID(classObj, methodName, methodSig);
    if (mID == NULL) {
        JavaCallBackEx_default_Detach(callbackEx);
        return -1;
    }

    *methodID = mID ;
    return 0;
}
////////////////////////////////////////////////////////////////////////
static int  JavaCallBackEx_default_init(struct IJavaCallBack *callback , JNIEnv *env, jobject obj) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    if ((callbackEx == NULL) || (env == NULL))
        return -1 ;

    if (callbackEx->mJavaVM == NULL) {
        env->GetJavaVM(&(callbackEx->mJavaVM));
    }

    if (callbackEx->mObject) {
        env->DeleteGlobalRef(callbackEx->mObject);
        callbackEx->mObject = NULL;
    }

    callbackEx->mObject = env->NewGlobalRef(obj);
    return 0 ;
}

static int  JavaCallBackEx_default_reset(struct IJavaCallBack *callback) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    if (callbackEx == NULL)
        return -1 ;

    if (JavaCallBackEx_default_Attach(callbackEx) < 0) {
        return -1;
    }

    callbackEx->mJNIEnv->DeleteGlobalRef(callbackEx->mObject);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_free(struct IJavaCallBack *callback) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    if (callbackEx == NULL)
        return -1 ;

    if (JavaCallBackEx_default_Attach(callbackEx) < 0) {
        free(callbackEx) ;
        return 0;
    }

    callbackEx->mJNIEnv->DeleteGlobalRef(callbackEx->mObject);
    JavaCallBackEx_default_Detach(callbackEx);
    free(callbackEx) ;
    return 0 ;
}

static int  JavaCallBackEx_default_callMethod(struct IJavaCallBack *callback , const char *methodName) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "()V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodL(struct IJavaCallBack *callback , const char *methodName, jlong val) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(J)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodI(struct IJavaCallBack *callback , const char *methodName, jint val) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(I)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodZ(struct IJavaCallBack *callback , const char *methodName, jboolean val) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(Z)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIZ(struct IJavaCallBack *callback , const char *methodName, jint val1, jboolean val2) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(IZ)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodII(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(II)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodJJ(struct IJavaCallBack *callback , const char *methodName, jlong val1, jlong val2) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(JJ)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIII(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2, jint val3) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(III)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIFF(struct IJavaCallBack *callback , const char *methodName, jint val1, jfloat val2, jfloat val3)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(IFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodFFF(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2, jfloat val3)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(FFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodFF(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(FF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodFFFF(struct IJavaCallBack *callback , const char *methodName, jfloat val1, jfloat val2, jfloat val3, jfloat val4)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;
    if (callbackEx == NULL)
        return -1 ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(FFFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3, val4);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIFFF(struct IJavaCallBack *callback , const char *methodName, jint val1, jfloat val2, jfloat val3, jfloat val4) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(IFFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3, val4);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIIIFF(struct IJavaCallBack *callback , const char *methodName, jint handle, jint val1, jint val2, jfloat val3, jfloat val4)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(IIIFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, handle, val1, val2, val3, val4);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodIIFF(struct IJavaCallBack *callback , const char *methodName, jint val1, jint val2, jfloat val3, jfloat val4) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(IIFF)V", &methodID) < 0)
        return -1 ;

    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, val1, val2, val3, val4);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodI_F_F(struct IJavaCallBack *callback , const char *methodName, jint handle, jfloat const val1[3], jfloat const val2[4]) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "(I[F[F)V", &methodID) < 0)
        return -1 ;

    jfloatArray pos = callbackEx->mJNIEnv->NewFloatArray(3);
    jfloatArray qua = callbackEx->mJNIEnv->NewFloatArray(4);
    callbackEx->mJNIEnv->SetFloatArrayRegion(pos, 0, 3, val1);
    callbackEx->mJNIEnv->SetFloatArrayRegion(qua, 0, 4, val2);
    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, handle, pos, qua);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethod_F_F(struct IJavaCallBack *callback , const char *methodName, jfloat const val1[3], jfloat const val2[4]) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "([F[F)V", &methodID) < 0)
        return -1 ;

    jfloatArray pos = callbackEx->mJNIEnv->NewFloatArray(3);
    jfloatArray qua = callbackEx->mJNIEnv->NewFloatArray(4);
    callbackEx->mJNIEnv->SetFloatArrayRegion(pos, 0, 3, val1);
    callbackEx->mJNIEnv->SetFloatArrayRegion(qua, 0, 4, val2);
    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, pos, qua);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethod_FI(struct IJavaCallBack *callback , const char *methodName, const jfloat *val, jint sz) {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, "()V", &methodID) < 0)
        return -1 ;

    jfloatArray pose = callbackEx->mJNIEnv->NewFloatArray(sz);
    callbackEx->mJNIEnv->SetFloatArrayRegion(pose, 0, sz, val);
    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, pose);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

static int  JavaCallBackEx_default_callMethodOJZ(struct IJavaCallBack *callback , const char *methodName, jclass object, const char *methodSig, jlong val, jboolean rgc)  {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*)callback;
    jmethodID methodID = NULL, methodCtor = NULL;
    jobject obj = NULL ;

    if (JavaCallBackEx_default_GetCallbackMethod(callbackEx, methodName, methodSig, &methodID) < 0)
        return -1 ;

    methodCtor = callbackEx->mJNIEnv->GetMethodID(object, "<init>", "(JZ)V");
    obj = callbackEx->mJNIEnv->NewObject(object, methodCtor, val, rgc);
    callbackEx->mJNIEnv->CallVoidMethod(callbackEx->mObject, methodID, obj);
    JavaCallBackEx_default_Detach(callbackEx);
    return 0 ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IJavaCallBack* IJavaCallBack_defalut_allocate() {
    struct JavaCallBackEx *callbackEx = (struct JavaCallBackEx*) malloc(sizeof(struct JavaCallBackEx)) ;
    struct IJavaCallBack *callback = (struct IJavaCallBack*)callbackEx ;

    if (callbackEx == NULL)
        return NULL ;

    memset(callbackEx , 0 , sizeof(struct JavaCallBackEx));

    callbackEx->init = JavaCallBackEx_default_init;
    callbackEx->reset = JavaCallBackEx_default_reset;
    callbackEx->free = JavaCallBackEx_default_free;

    callbackEx->callMethod    = JavaCallBackEx_default_callMethod;
    callbackEx->callMethodL   = JavaCallBackEx_default_callMethodL;
    callbackEx->callMethodI   = JavaCallBackEx_default_callMethodI;
    callbackEx->callMethodZ   = JavaCallBackEx_default_callMethodZ;

    callbackEx->callMethodIZ  = JavaCallBackEx_default_callMethodIZ ;
    callbackEx->callMethodII  = JavaCallBackEx_default_callMethodII;
    callbackEx->callMethodJJ  = JavaCallBackEx_default_callMethodJJ;
    callbackEx->callMethodFF  = JavaCallBackEx_default_callMethodFF;

    callbackEx->callMethodIII = JavaCallBackEx_default_callMethodIII;
    callbackEx->callMethodIFF = JavaCallBackEx_default_callMethodIFF;
    callbackEx->callMethodFFF = JavaCallBackEx_default_callMethodFFF;

    callbackEx->callMethodFFFF = JavaCallBackEx_default_callMethodFFFF;
    callbackEx->callMethodIFFF = JavaCallBackEx_default_callMethodIFFF;
    callbackEx->callMethodIIFF = JavaCallBackEx_default_callMethodIIFF;

    callbackEx->callMethodI_F_F = JavaCallBackEx_default_callMethodI_F_F;
    callbackEx->callMethod_F_F  = JavaCallBackEx_default_callMethod_F_F;
    callbackEx->callMethod_FI   = JavaCallBackEx_default_callMethod_FI;
    callbackEx->callMethodOJZ   = JavaCallBackEx_default_callMethodOJZ;

    callbackEx->callMethodIIIFF = JavaCallBackEx_default_callMethodIIIFF;

    return callbackEx;
}
