#include "communicate.h"

#define MAXLINE 4096

int clientSocket;
int flag_i = 0;

void connect()
{
     //�ͻ���ֻ��Ҫһ���׽����ļ������������ںͷ�����ͨ��
    int recbyte;
    int sin_size;
    char buffer[1024] = { 0 };
    char str[] = "192.168.1.110";

    struct sockaddr_in server_add, client_add; //������������socket  �׽��ֵ����ݽṹ
    unsigned short portnum = 8765; //�˿ں�

    printf("Hello,welcome to client!\r\n");

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //����һ��socket����

    if(-1 == clientSocket)
    {
                    printf("socket fail ! \r\n");
                    return;
    }

    printf("socket ok !\r\n");
    bzero(&server_add,sizeof(struct sockaddr_in));  //����
    server_add.sin_family=AF_INET;  //��ַ��
    server_add.sin_addr.s_addr = inet_addr(str);  //��ַ
    server_add.sin_port=htons(portnum); //�˿ں�

    printf("IP is %s\n", inet_ntoa(server_add.sin_addr));
    printf("Port is %d\n", htons(server_add.sin_port));

    //�������ӵ�client����ʹ��connect����������socket������Զ�˷���������TCP����
    if(-1 == connect(clientSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
    {
                    printf("connect fail !\r\n");
                    return;
    }
    printf("connect ok !\r\n");

    char sendbuf[100];
    sprintf(sendbuf,"%sI miss you!");
    send(clientSocket, sendbuf, strlen(sendbuf), 0);
    flag_i = 1;

}


void receive_msg()
{
    // ����������ɣ�������λ����Ϣ
    char recvbuf[1024];
    recvbuf[0] = '\0';
    int iDataNum = recv(clientSocket, recvbuf, 200, 0);
    while(iDataNum<0)
    {
            recvbuf[0] = '\0';
            int iDataNum = recv(clientSocket, recvbuf, 200, 0);
            perror("recv null");
    }
    printf("Receive:");
    recvbuf[iDataNum] = '\0';
    printf("%s\n", recvbuf);

    close(clientSocket);

    return;
}






void Send_img(QString filepath)
{
        connect();  //8765

	int   sockfd, len;
	char  buffer[MAXLINE];
	struct sockaddr_in  servaddr;
	FILE *fq;
	char str[] = "192.168.1.110";

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
                return;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if (inet_pton(AF_INET, str, &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", str);
                return;
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
                return;
	}

        char* ch;
        QByteArray ba = filepath.toLatin1(); // must
        ch=ba.data();

         qDebug()<<filepath<<"\n";
         qDebug()<<ch;

        if ((fq = fopen(ch, "rb")) == NULL) {
		printf("File open.\n");
		close(sockfd);
		exit(1);
	}

	bzero(buffer, sizeof(buffer));
	while (!feof(fq)) {
		len = fread(buffer, 1, sizeof(buffer), fq);
		if (len != write(sockfd, buffer, len)) {
			printf("write.\n");
			break;
		}
	}

	close(sockfd);
	fclose(fq);

        //������λ����Ϣ
        receive_msg();


        return;
}



char str[10] = {0};
char *int_to_string(int num)
{

        int i=0,j=0;
        char temp[10];

        while(num)
        {
        temp[i++]=num%10+'0';  //�����ּ��ַ�0�ͱ����Ӧ�ַ�
        num/=10;               //��ʱ���ַ���Ϊ����
        }
    temp[i]='\0';
        i=i-1;
        while(i>=0)
    str[j++]=temp[i--];   //��������ַ���תΪ����
        str[j]='\0';               //�ַ���������־
        return str;
}



void Send_R(int AD_value)
{
    int clientSocket;  //�ͻ���ֻ��Ҫһ���׽����ļ������������ںͷ�����ͨ��
    int recbyte;
    int sin_size;
    char buffer[1024] = { 0 };
    char str[] = "192.168.1.110";

    struct sockaddr_in server_add, client_add; //������������socket  �׽��ֵ����ݽṹ
    unsigned short portnum = 2444; //�˿ں�

    //printf("Hello,welcome to client!\r\n");
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //����һ��socket����
    if(-1 == clientSocket)
    {
                    printf("socket fail ! \r\n");
                    return ;
    }
    //printf("socket ok !\r\n");
    bzero(&server_add,sizeof(struct sockaddr_in));  //����
    server_add.sin_family=AF_INET;  //��ַ��
    server_add.sin_addr.s_addr = inet_addr(str);  //��ַ
    server_add.sin_port=htons(portnum); //�˿ں�

    //�������ӵ�client����ʹ��connect����������socket������Զ�˷���������TCP����
    if(-1 == connect(clientSocket,(struct sockaddr *)(&server_add), sizeof(struct sockaddr)))
    {
                    printf("connect fail !\r\n");
                    return ;
    }
    printf("connect ok !\r\n");
    char *passbuf;
    passbuf = int_to_string(AD_value);
    printf("Send: %s\n",passbuf);
    send(clientSocket, passbuf, strlen(passbuf), 0); // �����û�������
    close(clientSocket);
    return;
}
