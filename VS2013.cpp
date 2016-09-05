/*
Used Version  : Studio Visual 2013
OS            :  Windows
coution if the COM can not read. Cange the property  of the Chatacter Set to " Use Muti-Byte Chatacter Set"
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;
#include <windows.h>

HANDLE arduino; //Port name
bool Ret;

//ARDUINO とのシリアル通信初期化
void SerialPortinit()
{
	//1.ポートをオープン
	arduino = CreateFile("\\\\.\\COM13", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//If the Port number up to 10 
	//arduino = CreateFile("\\\\.\\COM13", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (arduino == INVALID_HANDLE_VALUE){
		printf("PORT COULD NOT OPEN\n");
		system("PAUSE");
		exit(0);
	}

	//2.送受信バッファ初期化
	Ret = SetupComm(arduino, 1024, 1024);
	if (!Ret){
		printf("SET UP FAILED\n");
		CloseHandle(arduino);
		system("PAUSE");
		exit(0);
	}
	Ret = PurgeComm(arduino, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	if (!Ret){
		printf("CLEAR FAILED\n");
		CloseHandle(arduino);
		system("PAUSE");
		exit(0);
	}

	//3.基本通信条件の設定
	DCB dcb;
	GetCommState(arduino, &dcb);
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate = 115200;//***
	dcb.fBinary = TRUE;
	dcb.ByteSize = 8;
	dcb.fParity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	Ret = SetCommState(arduino, &dcb);

	if (!Ret){
		printf("SetCommState FAILED\n");
		CloseHandle(arduino);
		system("PAUSE");
		exit(0);
	}

}

int Serialreceived(){

	int count = 0;
	int hantei = 0;
	int recv_num = -1;

	//4.送信
	DWORD dwRead;
	DWORD dwSendSize;
	DWORD dwErrors;
	COMSTAT ComStat;
	DWORD dwCount;

	char sendflag = 'l';
	char data[100], dataff;
	sendflag = 'i';

	printf("\nSend.Data", sendflag);


	for (int k = 0; k < 16; k++)
	{
		ClearCommError(arduino, &dwErrors, &ComStat);

		dwCount = ComStat.cbInQue;

		//send
		Ret = WriteFile(arduino, &sendflag, sizeof(sendflag), &dwSendSize, NULL);

		if (!Ret){ //send error check
			printf("SEND FAILED\n");
			CloseHandle(arduino);
			system("PAUSE");
			exit(0);
		}

		//rec
		Ret = ReadFile(arduino, data, dwCount, &dwRead, NULL);
		//printf("%d", dwCount);

		if (Ret == FALSE)     //失敗した場合
		{
			printf("ReadFile failed. \n");
			CloseHandle(arduino);
			//system("PAUSE");
			exit(0);
		}

		cout << '\n' << "Data Reviced :";
		for (int i = 0; i < dwCount; i++)
		{
			cout << data[i];
		}
		
		cout << '\n';
		Sleep(100);

	}


	return 0;
}

void main(void){

	SerialPortinit(); //Serial 初始化
	Serialreceived();
	system("PAUSE");
	

}
