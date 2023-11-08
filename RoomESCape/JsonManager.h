#pragma once
#pragma warning(disable:4996)

typedef struct
{
	float versus;
	int startingPrice;
	int closingPrice;
} Stock;

typedef struct
{
	int stockCount;
	Stock* stocks;
} Corporation;

void InitializeJSON(char* responseData);