#pragma once
#include <windows.h>
#define SYSINFO  0x01

typedef struct tagMSGINFO //������Ϣ�ṹ��
{
    int Msg_id;
    BYTE context[1024*5];
}MSGINFO_S;

typedef struct tagSYSTEMINFO
{
    int os;
    bool Cam; //����ͷ
    double ver;
}SYSTEMINFO_S;