#pragma once
#pragma warning(disable:4996)

#include <time.h>           // ���ӿ� �ð��帧�� ��Ÿ���� ���� ���̺귯��
#include <conio.h>          // getch()�Լ��� �������� ���Ǵ� ���̺귯��(Ű���� �Է°��� ���� �� ���)
#include <stdio.h>          // �⺻ ������� ���� ���̺귯��
#include <stdlib.h>         // ������ �߻���Ű�� ���� ���̺귯��
#include <string.h>         // url�� �ٷ�� ���� ���̺귯��
#include <stdbool.h>        // ���� �ڷḦ ���� ���� ���̺귯��
#include <Windows.h>        // ���ڻ�, ������ �ٲٱ� ���� ���̺귯��

// 3rd party lib
#include <curl/curl.h>
#include "cJSON/cJSON.h"

// custom lib
#include "Web.h"
#include "JsonManager.h"

typedef struct
{
    char* data;
    int   size;
} response;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);