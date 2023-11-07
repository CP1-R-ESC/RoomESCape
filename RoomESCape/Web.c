#include <stdlib.h>
#include <string.h>

#include "Web.h"

char* InitializeURL(const char* corporationName, const char* beginDate, const char* endDate)
{
    char* url = malloc(sizeof(char[URL_MAX_SIZE]));

    strcat(url, BASE_URL);
    strcat(url, "&resultType=json");       // type is json file

    strcat(url, "serviceKey=");
    strcat(url, SERVICE_KEY_ENCORDING);    // service key

    strcat(url, "&itmsNm=");
    strcat(url, corporationName);      // item is samsung electronics

    strcat(url, "&beginBasDt=");   // Start Date is 2020-00-00
    strcat(url, beginDate);

    strcat(url, "&endBasDt=");     // end Date is 2021-00-00
    strcat(url, endDate);

    return url;
}