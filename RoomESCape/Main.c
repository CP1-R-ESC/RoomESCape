#include "Main.h"

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
        //char data[URL_MAX_SIZE] = "";  // 적절한 크기의 버퍼를 할당하세요.
        //strcat(data, BASE_URL);
        //strcat(data, "serviceKey=");
        //strcat(data, SERVICE_KEY_ENCORDING);    // service key
        //strcat(data, "&itmsNm=");
        //strcat(data, SAMSUNG_ELECTRONICS);      // item is samsung electronics
        //strcat(data, "&resultType=json");       // type is json file
        //strcat(data, "&beginBasDt=20200000");   // Start Date is 2020-00-00
        //strcat(data, "&endBasDt=20210000");     // end Date is 2021-00-00

        char* data = InitializeURL(SAMSUNG_ELECTRONICS, "20200000", "20210000");

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