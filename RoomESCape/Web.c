#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "Web.h"
#include "JsonManager.h"

const char* BASE_URL = "https://apis.data.go.kr/1160100/service/GetStockSecuritiesInfoService/getStockPriceInfo?";
const int   BASE_URL_SIZE = 89;
const char* SERVICE_KEY_ENCORDING = "51d6PLghYwGUH7KCol9ES%2FxPYm%2Fk7LrIpnSEGM3j0NM%2BiVM1EhcRC%2BQmuNXXY1iT9LZvoRoREYkJ95R1iQNibA%3D%3D";
const int   SERVICE_KEY_ENCORDING_SIZE = 101;
const char* SERVICE_KEY_DECORDING = "51d6PLghYwGUH7KCol9ES/xPYm/k7LrIpnSEGM3j0NM+iVM1EhcRC+QmuNXXY1iT9LZvoRoREYkJ95R1iQNibA==";
const int   SERVICE_KEY_DECORDING_SIZE = 89;

const char* SAMSUNG_ELECTRONICS = "%EC%82%BC%EC%84%B1%EC%A0%84%EC%9E%90";

char* InitializeURL(const char* corporationName, const char* beginDate, const char* endDate)
{
    char* url = (char*)malloc(sizeof(char) * URL_MAX_SIZE);

    strcpy(url, BASE_URL);

    strcat(url, "serviceKey=");
    strcat(url, SERVICE_KEY_ENCORDING);     // service key

    strcat(url, "&resultType=json");        // type is json file
    strcat(url, "&numOfRows=1000");         // Get All JsonData

    strcat(url, "&itmsNm=");
    strcat(url, corporationName);           // item is samsung electronics

    strcat(url, "&beginBasDt=");             
    strcat(url, beginDate);                 // Start Date is 2020-00-00

    strcat(url, "&endBasDt=");              // end Date is 2021-00-00
    strcat(url, endDate);

    return url;
}

char* PostWebRequest(char* url)
{
    CURL* curl;
    CURLcode resCode;

    Response webResonse;
    webResonse.jsonData = NULL;
    webResonse.size = 0;

    curl = curl_easy_init();
    if (curl == NULL)
    {
        fprintf(stderr, "Curl Init fail\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webResonse);

#ifdef DEBUG_MODE
    fprintf(stdout, "Load Json File...\n");
#endif // DEBUG_MODE

    resCode = curl_easy_perform(curl);
    if (resCode != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(resCode));
        return NULL;
    }

    char* jsonData = webResonse.jsonData;

    curl_easy_cleanup(curl);

    return jsonData;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t total_size = size * nmemb;
    Response* res = (Response*)userp;

    // 데이터를 메모리에 추가
    res->jsonData = (char*)realloc(res->jsonData, res->size + total_size + 1);
    if (res->jsonData == NULL)
        return -1;  // realloc fail

    // Data Copy
    memcpy(&(res->jsonData[res->size]), contents, total_size);
    res->size += total_size;
    res->jsonData[res->size] = '\0'; // NULL letter becuase char*;

    return total_size;
}