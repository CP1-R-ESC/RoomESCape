#pragma once
#pragma warning(disable:4996)

#define URL_MAX_SIZE 10000

const char* BASE_URL = "https://apis.data.go.kr/1160100/service/GetStockSecuritiesInfoService/getStockPriceInfo?";
const int   BASE_URL_SIZE = 89;
const char* SERVICE_KEY_ENCORDING = "51d6PLghYwGUH7KCol9ES%2FxPYm%2Fk7LrIpnSEGM3j0NM%2BiVM1EhcRC%2BQmuNXXY1iT9LZvoRoREYkJ95R1iQNibA%3D%3D";
const int   SERVICE_KEY_ENCORDING_SIZE = 101;
const char* SERVICE_KEY_DECORDING = "51d6PLghYwGUH7KCol9ES/xPYm/k7LrIpnSEGM3j0NM+iVM1EhcRC+QmuNXXY1iT9LZvoRoREYkJ95R1iQNibA==";
const int   SERVICE_KEY_DECORDING_SIZE = 89;

// curl type (utf-8 Encording) -> after day, Can I develop Encorder?
const char* SAMSUNG_ELECTRONICS = "%EC%82%BC%EC%84%B1%EC%A0%84%EC%9E%90";

char* InitializeURL(const char* corporationName, const char* beginDate, const char* endDate);