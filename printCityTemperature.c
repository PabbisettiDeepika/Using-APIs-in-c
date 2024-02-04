// To print temperature of a city using an API

#include <stdio.h>
#include <stdlib.h>

#define CITY_LENGTH 30
#define API_LENGTH 200
#define MAXIMUM_LENGTH 200

void main()
{
	char city[CITY_LENGTH];

	printf("Enter any city to print its temperature: \n");
	scanf("%s", city);
	char apiFirstPart[] = "curl \"https://api.openweathermap.org/data/2.5/weather?q=";
	char apiSecondPart[] = "&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\">";
	char weatherFileName[] = "weather.txt";
	char *api = (char*)malloc(sizeof(char) * API_LENGTH);
	sprintf(api, "%s%s%s%s", apiFirstPart, city, apiSecondPart, weatherFileName);

	system(api);

	char buffer[MAXIMUM_LENGTH];
	char *token;
	char *temperature;
	char delimiter[] = "{}[]\":,";
	FILE *fpWeather = fopen(weatherFileName, "r");

	if (fpWeather != NULL)
	{
		while (fgets(buffer, MAXIMUM_LENGTH, fpWeather))
		{
			token = strtok(buffer, delimiter);
			while (token != NULL)
			{
				if (!strcmp(token, "message"))
				{
					printf("%s city not found.\n", city);
					break;
				}
				if (!strcmp(token, "temp_min"))
				{
					temperature = strtok(NULL, delimiter);
					printf("Temperature in %s: %s", city, temperature);
					break;
				}
				token = strtok(NULL, delimiter);
			}
		}
	}
	else
	{
		printf("Unable to find city temperature.\n");
	}
	fclose(fpWeather);
}