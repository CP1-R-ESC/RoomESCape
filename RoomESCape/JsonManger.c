#include <stdio.h>
#include <stdlib.h>

#include "JsonManager.h"
#include "cJSON/cJSON.h"

Corporation* InitializeJSON(char* jsonData)
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
		fprintf(stdout, "Stock Count: %d\n", totalCount);

	cJSON* items = cJSON_GetObjectItem(body, "items");
	if (items == NULL)
		return NULL;

	cJSON* itemArray = cJSON_GetObjectItem(items, "item");
	if (itemArray == NULL)
		return NULL;

		cJSON* stockJson = cJSON_GetArrayItem(itemArray, 0);
		if (stockJson == NULL)
			return NULL;

		cJSON* name = cJSON_GetObjectItem(stockJson, "itmsNm");
		if (name == NULL)
			return NULL;

	Corporation* corporation = (Corporation*)malloc(sizeof(Corporation));
	corporation->name = name->valuestring;
	corporation->stockCount = totalCount;
	corporation->stocks = (Stock*)malloc(sizeof(Stock) * totalCount);

#ifdef DEBUG_MODE
	fprintf(stdout, "----------D+0 Day----------\n");
#endif // DEBUG_MODE

	for (int i = 0; i < totalCount; i++)
	{
		cJSON* stockJson = cJSON_GetArrayItem(itemArray, totalCount - i - 1);
		if (stockJson == NULL)
			return NULL;

		cJSON* versus = cJSON_GetObjectItem(stockJson, "vs");
		if (versus == NULL)
			return NULL;
		cJSON* startingPrice = cJSON_GetObjectItem(stockJson, "mkp");
		if (startingPrice == NULL)
			return NULL;
		cJSON* closingPrice = cJSON_GetObjectItem(stockJson, "clpr");
		if (closingPrice == NULL)
			return NULL;

		corporation->stocks[i].versus = atoi(versus->valuestring);
		corporation->stocks[i].startingPrice = atoi(startingPrice->valuestring);
		corporation->stocks[i].closingPrice = atoi(closingPrice->valuestring);

#ifdef DEBUG_MODE
		fprintf(stdout, "Corporation Name: %s\n", corporation->name);
		fprintf(stdout, "%d\n", corporation->stocks[i].versus);
		fprintf(stdout, "%d\n", corporation->stocks[i].startingPrice);
		fprintf(stdout, "%d\n", corporation->stocks[i].closingPrice);
		fprintf(stdout, "----------D+%d Day----------\n", i + 1);
#endif // DEBUG_MODE
	}

	return &corporation;
}