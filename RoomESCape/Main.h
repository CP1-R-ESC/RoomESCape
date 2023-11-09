#pragma once
#pragma warning(disable:4996)

#include <time.h>           // 게임에 시간흐름을 나타내기 위한 라이브러리
#include <conio.h>          // getch()함수를 쓰기위해 사용되는 라이브러리(키보드 입력값을 받을 때 사용)
#include <stdio.h>          // 기본 입출력을 위한 라이브러리
#include <stdlib.h>         // 난수를 발생시키기 위한 라이브러리
#include <string.h>         // url을 다루기 위한 라이브러리
#include <stdbool.h>        // 논리형 자료를 쓰기 위한 라이브러리
#include <Windows.h>        // 글자색, 배경색을 바꾸기 위한 라이브러리
#include <process.h>		// 쓰레드를 사용하기 위한 라이브러리

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