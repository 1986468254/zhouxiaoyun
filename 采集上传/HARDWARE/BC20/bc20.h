#ifndef __BC20_H
#define __BC20_H

#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

#define PowerKey PBout(13)	// PB13
#define ResetKey PBout(14)	// PB13
void Clear_Buffer(void);	//��ջ���
void BC20_Init(void);			//��ʼ��BC26
char BC20_Receive_Data(void);	//���մ��ƶ˷��͹���������

void Asso_QMTCFG(char* ProductKey,char* DeviceName,char* DeviceSecret);	//
void Asso_QMTCONN(char* ConnectID);	
void Asso_QMTSUB(char* SubTopic);	
void Asso_QMTPUB(char* PubTopic,char* value);

void MQTT_Init(char* ProductKey,char* DeviceName,char* DeviceSecret,char* ConnectID);	//MQTT ���ӳ�ʼ��
void MQTT_Sub(char* SubTopic);	//��������
void MQTT_Pub(char* PubTopic,char* value);	//��������
void PowerKey_Init(void);
void ResetKey_Init(void);
typedef struct
{
	u8 CSQ;			//�����ź�ֵ
	u8 NetStatus;	//����״ֵ̬
} BC20;




#endif



