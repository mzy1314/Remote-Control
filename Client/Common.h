#pragma once
#include "stdafx.h"
#define SYSINFO  0x01

#define ID_ONLINE WM_USER+1
#define ID_OFFLINE WM_USER+2

typedef struct tagMSGINFO //������Ϣ�ṹ��
{
    int Msg_id;
    BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO //������Ϣ
{
    int os;
    bool Cam; //����ͷ
    double ver;
}SYSTEMINFO;

