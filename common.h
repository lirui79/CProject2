/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/11/06
**   File: common.h
**   Function:  common struct data define
**   History:
**       2018/11/06 create by lirui
**
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef __IRIS_COMMON_H__
#define __IRIS_COMMON_H__

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/*    Frame:
    y        x: left
    |  z     y: up
    | /      z: towards
    |/
x---+          */

//Quaternion & Position: PoseState
typedef union PoseState {
    struct {
        float pos[3];    //position
        float qua[4];    //quaternion w,x,y,z
        float _reserved;
    } var;
    float data[8];
}PoseState;

typedef struct KeyInfo {
    int32_t KeyCode;
    int32_t Action;
}KeyInfo;

typedef struct Decree {
    int action;
    int flag;
    int type;
}Decree;

typedef struct IrisMotionCursorInfo {
    float x ;
    float y ;
}IrisMotionCursorInfo;

__END_DECLS

#endif //__IRIS_COMMON_H__
