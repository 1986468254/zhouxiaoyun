#include "bc20.h"
#include "string.h"

char *Receive_Data;		//
extern u8 USART1_RX_BUFF[200];		//	
extern u16 USART1_RX_LENGTH;			//
BC20 BC20_Status;

void PowerKey_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
// GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PA.8 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_13); 						 //PB.13 ����� 
}

void ResetKey_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
// GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PA.8 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_14); 						 //PB.13 ����� 
}

void Clear_Buffer(void)
{
	memset(USART1_RX_BUFF,0,sizeof(USART1_RX_BUFF));
	USART1_RX_LENGTH = 0;
}


void BC20_Init(void)
{
	delay_ms(1000);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	delay_ms(1000);
	delay_ms(1000);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
	//���Ͳ�������
	Uart1_SendStr("AT");
	delay_ms(300);
	
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
		
	}
	Clear_Buffer();
	//�ر��Զ�����
	Uart1_SendStr("AT+QSCLK=0\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT+QSCLK=0\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	}
	Clear_Buffer();
	
	Uart1_SendStr("AT+CFUN=1\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT+CFUN=1\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	}
	Clear_Buffer();
	
	//�ر�ʡ��ģʽ
	Uart1_SendStr("AT+CPSMS=0\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT+CPSMS=0\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	}
	Clear_Buffer();
	
	//�ر�eDRXģʽ
	Uart1_SendStr("AT+CEDRXS=0\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT+CEDRXS=0\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	}
	Clear_Buffer();
	
	//��ȡ����
	Uart1_SendStr( "AT+CIMI\r\n" );	
	delay_ms( 300 );
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"460");
	
	while(Receive_Data == NULL)
	{
		Clear_Buffer();
		Uart1_SendStr("AT+CIMI\r\n");
		delay_ms(300);
		Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"460");
	}
	Clear_Buffer();
	
	//��������
	Uart1_SendStr("AT+CGATT=1\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"OK");
	Clear_Buffer();
	//�鿴����
	Uart1_SendStr("AT+CGATT?\r\n");
	delay_ms(300);
	Receive_Data = strstr((const char*)USART1_RX_BUFF,(const char*)"+CGATT: 1");
	
	while( Receive_Data == NULL )
	{
		Clear_Buffer();
		Uart1_SendStr( "AT+CGATT?\r\n" );
		delay_ms( 300 );
		Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+CGATT: 1" );
	}
	Clear_Buffer();
	
	//�鿴��ȡ��CSQ��ֵ
	Uart1_SendStr( "AT+CESQ\r\n" );
	delay_ms( 300 );
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+CESQ" );
	if( Receive_Data )
	{
		BC20_Status.CSQ = (Receive_Data[7]-0x30) * 10 + (Receive_Data[8]-0x30 ); //���ַ�ת��Ϊ����
		if( ( BC20_Status.CSQ == 99 ) || ( (Receive_Data[7]-0x30) == 0 ) )	//˵��û���źŻ��źŹ�С
		{
			while( 1 )
			{
				BC20_Status.NetStatus = 0;
				delay_ms( 1000 );
				 LED0 = !LED0;
			}
		}
		else
		{
			BC20_Status.NetStatus = 1;
		}
	}
}

/* �ڸú�����ʹ���� $����Ϊ�˴����㡣�ڰ������ϡ�������Ϣ��ʱ����������ݿ�ͷҪ���� $ */
char BC20_Receive_Data( void )
{
	char* position = NULL;
	
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTRECV" );
	if( Receive_Data )
	{
		position = strrchr( Receive_Data, '}' );
	}
	
	return *(position-20);		//���� $ ����ĵ�һ���ַ�
}
//����MQTT
void Asso_QMTCFG( char* ProductKey, char* DeviceName, char* DeviceSecret )
{
	char temp[200];

	memset( temp, 0, sizeof( temp ) );	//��� temp���������ش���
	
	strcat( temp, "AT+QMTCFG=\"aliauth\",0,\"" );	//AT+MQTCFG="aliauth",0,"
	strcat( temp, ProductKey );		//AT+MQTCFG="aliauth",0,"ProductKey
	strcat( temp, "\",\"" );		//AT+MQTCFG="aliauth",0,"ProductKey","
	strcat( temp, DeviceName ); 	//AT+MQTCFG="aliauth",0,"ProductKey","DeviceName
	strcat( temp, "\",\"" );		//AT+MQTCFG="aliauth",0,"ProductKey","DeviceName","
	strcat( temp, DeviceSecret );	//AT+MQTCFG="aliauth",0,"ProductKey","DeviceName","DeviceSecret
	strcat( temp, "\"\r\n" );		//AT+MQTCFG="aliauth",0,"ProductKey","DeviceName","DeviceSecret"\r\n

	Uart1_SendStr( temp );
}

//��MQTT�ͻ�������
void Asso_QMTCONN( char* ConnectID )
{
	char temp[200];
	
	memset( temp, 0, sizeof( temp ) );	//��� temp���������ش���
	
	strcat( temp, "AT+QMTCONN=0,\"" );	//AT+QMTCONN=0,"
	strcat( temp, ConnectID );			//AT+QMTCONN=0,"ConnectID
	strcat( temp, "\"\r\n" );			//AT+QMTCONN=0,"ConnectID"\r\n
	
	Uart1_SendStr( temp );
}

//��������
void Asso_QMTSUB( char* SubTopic )
{
	char temp[200];
	
	memset( temp, 0, sizeof( temp ) );	//��� temp���������ش���
	
	strcat( temp, "AT+QMTSUB=0,1,\"" );	//AT+QMTSUB=0,1,"
	strcat( temp, SubTopic );			//AT+QMTSUB=0,1,"SubTopic
	strcat( temp, "\",0\r\n" );			//AT+QMTSUB=0,1,"SubTopic",0\r\n
	
	Uart1_SendStr( temp );
}

//������Ϣ
void Asso_QMTPUB( char* PubTopic, char* value )
{
	char temp[200];
	
	memset( temp, 0, sizeof( temp ) );	//��� temp���������ش���
	
	strcat( temp, "AT+QMTPUB=0,0,0,0,\"" );	//AT+QMTPUB=0,0,0,0,"
	strcat( temp, PubTopic );				//AT+QMTPUB=0,0,0,0,"PubTopic
	strcat( temp, "\",\"{params:{CurrentHumidity:" ); //AT+QMTPUB=0,0,0,0,"PubTopic","{params:{CurrentHumidity:
	strcat( temp, value );	//AT+QMTPUB=0,0,0,0,"PubTopic","{params:{CurrentHumidity:value
	strcat( temp, "}}\"" );	//AT+QMTPUB=0,0,0,0,"PubTopic","{params:{CurrentHumidity:value}}"
	
	Uart1_SendStr( temp );
}


//MQTT����
void MQTT_Init( char* ProductKey, char* DeviceName, char* DeviceSecret, char* ConnectID )
{
	Asso_QMTCFG( ProductKey, DeviceName, DeviceSecret );
	delay_ms( 300 );

	
	Clear_Buffer();	
	//------------������Ϣ------------
	
	
	Uart1_SendStr( "AT+QMTOPEN=0,\"iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n" );	//ͨ�� tcp ��ʽ���Ӱ�����
	delay_ms( 1000 );
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTOPEN: 0,0" );	//�鿴����״̬

	
	/* ����ȵ��ɹ����ϰ����� */
	while( Receive_Data == NULL )
	{
		Clear_Buffer();
		Uart1_SendStr( "AT+QMTOPEN=0,\"iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n" );	//ͨ�� tcp ��ʽ���Ӱ�����
		delay_ms( 1000 );
		Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTOPEN: 0,0" );	//�鿴����״̬
	}
	
	
	Clear_Buffer();	
	//------------������Ϣ------------
	//
	
	Asso_QMTCONN( ConnectID );
	delay_ms( 300 );
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTCONN: 0,0,0" );
	
	
	/* ����ȵ��ɹ�ƥ�䵽 MQTT */
	while( Receive_Data == NULL )
	{
		Clear_Buffer();
		Asso_QMTCONN( ConnectID );
		delay_ms( 300 );
		Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTCONN: 0,0,0" );	//�鿴����״̬	
	}
	
	
	Clear_Buffer();

}

void MQTT_Sub( char* SubTopic )
{
	Clear_Buffer();
	Asso_QMTSUB( SubTopic );
	delay_ms( 300 );
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTSUB:" );
	
	while( Receive_Data == NULL )
	{
		Clear_Buffer();
		Asso_QMTSUB( SubTopic );
	delay_ms( 300 );
		Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTSUB:" );
	}
	
	Clear_Buffer();
}

void MQTT_Pub( char* PubTopic, char* value )
{
	Clear_Buffer();
	Asso_QMTPUB( PubTopic, value );
	delay_ms( 300 );
	Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTPUB: 0,0,0" );
	
	while( Receive_Data == NULL )
	{
		Receive_Data = strstr( (const char*)USART1_RX_BUFF, (const char*)"+QMTPUB: 0,0,0" );
	}
	
	Clear_Buffer();

}


