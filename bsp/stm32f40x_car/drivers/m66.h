#ifndef _H_M66_
#define _H_M66_

/*
1.��gsm��װ��һ���豸���ڲ�gsm״̬����һ���̴߳���
  Ӧ�ó���ֻ��Ҫ���豸�����в������ɡ�

2.ͨ��AT�����ȡģ������? ��������ģ��Ͳ���Ҫˢ��
  ����Ҳ���ڱȽ�ģ�顣�ж��ʵ������?

3.ģ���״̬����Ϣ�����������·���Ϣ�����պ���/����
  ���߿���·��socket�Ͽ��� (��ͬ��ģ�鲻ͬ,Ҫ�����
  ��)�����֪ͨAPP? ʹ�ûص�������

4.��Ч��socket����
*/


#define GSM_UART_NAME	"uart4"

//#define MAX_SOCKETS	6	//EM310����3  MG323����6

/*
����ʹ�õ�ģ���ͺ�
*/
//#define MG323
#define M66
//#define MC323
//#define EM310



/*
GSM֧�ֲ������ܵ��б�
��ͬ��ģ��֧�ֵ����ͬ������¼������ TTS����
�˴�����ͳһ��һ��gsm.h,��Ӧ����ģ��Ĳ�ͬ����ͬ��
���ϲ�������ο���?

���ƽӿ�Ӧ��Ӧ�ðѹ��ֵܷ��㹻��ϸ
���ʵ��һ������:һ������/�������ƽ�������
*/
typedef enum
{
	CTL_STATUS=1,		//��ѯGSM״̬
	CTL_AT_CMD, 		//����AT����
	CTL_PPP,			//PPP����ά��
	CTL_SOCKET, 		//����socket
	CTL_DNS,			//����DNS����
	CTL_TXRX_COUNT, 	//���ͽ��յ��ֽ���
	CTL_CONNECT,		//ֱ�ӽ�������

}T_GSM_CONTROL_CMD;


typedef enum
{
	GSM_STATE_GET=0,		/*��ѯGSM״̬*/
	GSM_IDLE=1,			/*����*/
	GSM_POWERON,		/*�ϵ���̲����ģ���AT�����ʼ������*/
	GSM_AT,				/*����AT������У���������socket�������շ�����*/
	GSM_AT_SEND,		/*����AT�շ�״̬*/
	GSM_GPRS,		/*��¼GPRS��*/
	GSM_TCPIP,			/*�Ѿ����������Խ���socket����*/
	GSM_SOCKET_PROC,	/*���ڽ���socket����*/
	GSM_ERR_POWERON,
	GSM_ERR_GPRS,
	GSM_ERR_TCPIP,
	GSM_POWEROFF,		/*�Ѿ��ϵ�*/	
}T_GSM_STATE;


typedef enum
{
	SOCKET_STATE=0,		/*��ѯsocket״̬*/
	SOCKET_IDLE = 1,            /*��������*/
	SOCKET_ERR,
	SOCKET_START,				/*��������Զ��*/
	SOCKET_DNS,                 /*DNS��ѯ��*/
	SOCKET_DNS_ERR,
	SOCKET_CONNECT,             /*������*/
	SOCKET_CONNECT_ERR,         /*���Ӵ��󣬶Է���Ӧ��*/
	SOCKET_READY,               /*����ɣ����Խ�������*/
	SOCKET_CLOSE,
}T_SOCKET_STATE;


enum RESP_TYPE
{
	RESP_TYPE_FUNC			=1,
	RESP_TYPE_FUNC_WITHOK	=2,
	RESP_TYPE_STR			=3,
	RESP_TYPE_STR_WITHOK	=4,
};



/*���֧��4������*/
#define MAX_GSM_SOCKET 4

typedef struct
{
	T_SOCKET_STATE	state;          /*����״̬*/
	uint8_t			linkno;			/*��ʹ�õ�link��*/
	char			type;           /*�������� 'u':udp client 't':TCP client  'U' udp server*/
	char			ipstr[64];    /*�������ַ*/
	char			ip_addr[16];     /*dns���IP xxx.xxx.xxx.xxx*/
	uint16_t		port;           /*�˿�*/
	//MsgList			* msglist_tx;
}GSM_SOCKET;

typedef rt_err_t ( *RESP_FUNC )( char *s, uint16_t len );


void gsm_init(void);

void ctl_gprs( char* apn, char* user, char*psw ,uint8_t fdial );

void ctl_socket( uint8_t linkno,char type, char* remoteip, uint16_t remoteport,uint8_t fconnect );

rt_size_t socket_write( uint8_t linkno, uint8_t* buff, rt_size_t count );

rt_err_t gsm_send( char *atcmd,
                   RESP_FUNC respfunc,
                   char * compare_str,
                   uint8_t type,
                   uint32_t timeout,
                   uint8_t retry );

T_GSM_STATE gsmstate( T_GSM_STATE cmd );
T_SOCKET_STATE socketstate( T_SOCKET_STATE cmd );


#endif
