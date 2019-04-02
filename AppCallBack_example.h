/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/08
**   File: AppCallback_example.h
**   Function:  example for appCallback
**   History:
**       2018/11/08 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_APPCALLBACK_EXAMPLE_H__
#define __IRIS_APPCALLBACK_EXAMPLE_H__

#include <stdint.h>
#include <sys/cdefs.h>

#include "IAppManager.h"

__BEGIN_DECLS

typedef struct AppCallBackEx {
    struct IAppCallBack  mAppCallBack ;
    char                 mDescriptor[256] ;
}AppCallBackEx;

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
 *  struct AppCallBackEx appCallback ;
 *  int code = AppCallBack_example_init(&appCallback) ;
 */
int AppCallBack_example_init(struct AppCallBackEx *callbackEx);

__END_DECLS

#endif //
