#pragma once
#pragma warning(disable:4996)

#define URL_MAX_SIZE 10000

const char* BASE_URL;
const int   BASE_URL_SIZE;
const char* SERVICE_KEY_ENCORDING;
const int   SERVICE_KEY_ENCORDING_SIZE;
const char* SERVICE_KEY_DECORDING;
const int   SERVICE_KEY_DECORDING_SIZE;

// curl type (utf-8 Encording) -> after day, Can I develop Encorder?
const char* SAMSUNG_ELECTRONICS;

typedef struct
{
    char* jsonData;
    int   size;
} Response;

char* InitializeURL(const char* corporationName, const char* beginDate, const char* endDate);

char* PostWebRequest(char* url);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);