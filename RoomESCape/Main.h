#pragma once
#pragma warning(disable:4996)

#include <time.h>           // 게임에 시간흐름을 나타내기 위한 라이브러리
#include <conio.h>          // getch()함수를 쓰기위해 사용되는 라이브러리(키보드 입력값을 받을 때 사용)
#include <stdio.h>          // 기본 입출력을 위한 라이브러리
#include <stdlib.h>         // 난수를 발생시키기 위한 라이브러리
#include <string.h>         // url을 다루기 위한 라이브러리
#include <stdbool.h>        // 논리형 자료를 쓰기 위한 라이브러리
#include <Windows.h>        // 글자색, 배경색을 바꾸기 위한 라이브러리

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