#pragma once
#pragma warning(disable:4996)

#define DEBUG_MODE

typedef struct
{
	int versus;
	int startingPrice;
	int closingPrice;
} Stock;

typedef struct
{
	char* name;
	int stockCount;
	Stock* stocks;
} Corporation;

Corporation* InitializeJSON(char* responseData);