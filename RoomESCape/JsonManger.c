#include <stdio.h>
#include <stdlib.h>

#include "JsonManager.h"
#include "cJSON/cJSON.h"

void InitializeJSON(char* jsonData)
{
	cJSON* root = cJSON_Parse(jsonData);
	if (root == NULL)
		return NULL;

	cJSON* response = cJSON_GetObjectItem(root, "response");
	if (response == NULL)
		return NULL;

	cJSON* body = cJSON_GetObjectItem(response, "body");
	if (body == NULL)
		return NULL;

		cJSON* _totalCount = cJSON_GetObjectItem(body, "totalCount");
		int totalCount = _totalCount->valueint;
		fprintf(stdout, "%d\n", totalCount);

	cJSON* items = cJSON_GetObjectItem(body, "items");
	if (items == NULL)
		return NULL;

	cJSON* itemArray = cJSON_GetObjectItem(items, "item");
	if (itemArray == NULL)
		return NULL;

	cJSON* item0 = cJSON_GetArrayItem(itemArray, 0);
	if (item0 == NULL)
		return NULL;

		cJSON* versus0 = cJSON_GetObjectItem(item0, "vs");
		if (versus0 == NULL)
			return NULL;
		cJSON* startingPrice0 = cJSON_GetObjectItem(item0, "mkp");
		if (startingPrice0 == NULL)
			return NULL;
		cJSON* closingPrice0  = cJSON_GetObjectItem(item0, "clpr");
		if (closingPrice0 == NULL)
			return NULL;

		Stock stock;
		stock.versus = atoi(versus0->valuestring);
		stock.startingPrice = atoi(startingPrice0->valuestring);
		stock.closingPrice = atoi(closingPrice0->valuestring);

	fprintf(stdout, "%d\n", stock.versus);
	fprintf(stdout, "%d\n", stock.startingPrice);
	fprintf(stdout, "%d\n", stock.closingPrice);

	//int arraySize = cJSON_GetArraySize(itemArray);
	//for (int i = 0; i < arraySize; i++)
	//{
	//	cJSON* item = cJSON_GetArrayItem(itemArray, i);
	//	if (item)
	//	{
	//		// 각 항목의 필드에 접근 가능
	//		cJSON* basDt = cJSON_GetObjectItem(item, "basDt");
	//		cJSON* itmsNm = cJSON_GetObjectItem(item, "itmsNm");
	//		// 필요한 데이터를 처리
	//	}
	//}

}