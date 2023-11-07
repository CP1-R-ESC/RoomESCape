#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <curl/curl.h>

const char* BASE_URL = "https://apis.data.go.kr/1160100/service/GetStockSecuritiesInfoService/getStockPriceInfo?";
const int   BASE_URL_SIZE = 89;
const char* SERVICE_KEY_ENCORDING = "51d6PLghYwGUH7KCol9ES%2FxPYm%2Fk7LrIpnSEGM3j0NM%2BiVM1EhcRC%2BQmuNXXY1iT9LZvoRoREYkJ95R1iQNibA%3D%3D";
const int   SERVICE_KEY_ENCORDING_SIZE = 101;
const char* SERVICE_KEY_DECORDING = "51d6PLghYwGUH7KCol9ES/xPYm/k7LrIpnSEGM3j0NM+iVM1EhcRC+QmuNXXY1iT9LZvoRoREYkJ95R1iQNibA==";
const int   SERVICE_KEY_DECORDING_SIZE = 89;

// URL 인코더 추후 구현
const char* SAMSUNG_ELECTRONICS = "%EC%82%BC%EC%84%B1%EC%A0%84%EC%9E%90";

typedef struct 
{
    char* data;
    int   size;
} response;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t total_size = size * nmemb;
    response* res = (response*)userp;

    // 데이터를 메모리에 추가
    res->data = realloc(res->data, res->size + total_size + 1);
    if (res->data == NULL) {
        // 메모리 할당 실패
        return 0;
    }

    // 데이터 복사
    memcpy(&(res->data[res->size]), contents, total_size);
    res->size += total_size;
    res->data[res->size] = '\0'; // NULL 기호 입력

    return total_size;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    CURL* curl;
    CURLcode resCode;

    response res;
    res.data = NULL;
    res.size = 0;

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Curl Init fail\n");
        return -1;
    }

    if (curl)
    {
        char data[10000] = "";  // 적절한 크기의 버퍼를 할당하세요.
        strcat(data, BASE_URL);
        strcat(data, "serviceKey=");
        strcat(data, SERVICE_KEY_ENCORDING);    // service key
        strcat(data, "&itmsNm=");
        strcat(data, SAMSUNG_ELECTRONICS);      // item is samsung electronics
        strcat(data, "&resultType=json");       // type is json file
        strcat(data, "&beginBasDt=20200000");   // Start Date is 2020-00-00
        strcat(data, "&endBasDt=20210000");     // end Date is 2021-00-00
        curl_easy_setopt(curl, CURLOPT_URL, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&res);

        fprintf(stdout, "Load Json File...\n");

        resCode = curl_easy_perform(curl);
        if (resCode == CURLE_OK)
        {
            fprintf(stdout, "%s", res.data);
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
        }

        free(res.data);
        curl_easy_cleanup(curl);
    }
    return 0;
}