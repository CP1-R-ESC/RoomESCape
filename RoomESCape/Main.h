#pragma once
#pragma warning(disable:4996)

#include <time.h>           // ���ӿ� �ð��帧�� ��Ÿ���� ���� ���̺귯��
#include <conio.h>          // getch()�Լ��� �������� ���Ǵ� ���̺귯��(Ű���� �Է°��� ���� �� ���)
#include <stdio.h>          // �⺻ ������� ���� ���̺귯��
#include <stdlib.h>         // ������ �߻���Ű�� ���� ���̺귯��
#include <string.h>         // url�� �ٷ�� ���� ���̺귯��
#include <stdbool.h>        // ���� �ڷḦ ���� ���� ���̺귯��
#include <Windows.h>        // ���ڻ�, ������ �ٲٱ� ���� ���̺귯��
#include <process.h>		// �����带 ����ϱ� ���� ���̺귯��

// 3rd party lib
#include <curl/curl.h>
#include "cJSON/cJSON.h"

// custom lib
#include "Web.h"
#include "JsonManager.h"
#include "GameManager.h"
#include "RenderManager.h"

#define THREAD_COUNT  2

#define THREAD_GAME   0
#define THREAD_RENDER 1

// Reference
// https://huiyu.tistory.com/entry/C%EC%96%B8%EC%96%B4%EB%A1%9C-%EA%B2%8C%EC%9E%84%EB%A7%8C%EB%93%A4%EA%B8%B0-2-%EA%B2%8C%EC%9E%84-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D-%EC%9A%A9%EC%96%B4

char* url;
char* jsonData;
Corporation* corporation;

unsigned int _stdcall PlayGame_thread();
unsigned int _stdcall RenderDisplay_thread();