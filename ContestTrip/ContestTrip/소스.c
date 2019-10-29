#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define INF 214000
#define OUTOFQ -1

typedef struct {
	int index;
	char cityname[10];
	int hh;
	int mm;
}city;
typedef struct {
	char cityname[10];
}name;

typedef struct {
	int deptTimeHH;
	int deptTimeMM;
	char deptCity[10];
	int arrTimeHH;
	int arrTimeMM;
	char arrCity[10];
}timetable;
int numberOfCities;
int numberOfTimetables;
int openTime;
char departureCity[10];
char destination[10];
city* Q;
city* cities;
name* S;
int numberofQ;

int extractMin() {
	int hh;
	int mm;
	char tmpname[10];
	int tmpindex;
	int count = numberofQ;
	/*맨처음에 대전을 가져와야하는데 서울을 가져오는 오류 있음!!!*/
	for (int i = 0; i < numberofQ; i++) {
		for (int j = i+1; j < numberOfCities; j++) {
			if (Q[i].hh < Q[j].hh) {
				strcpy(tmpname, Q[i].cityname);
				tmpindex = Q[i].index;
				hh = Q[i].hh;
				mm = Q[i].mm;
				Q[i].hh = Q[j].hh;
				Q[i].mm = Q[j].mm;
				strcpy(Q[i].cityname, Q[j].cityname);
				Q[i].index = Q[j].index;
				strcpy(Q[j].cityname, tmpname);
				Q[j].index = tmpindex;
				Q[j].hh = hh;
				Q[j].mm = mm;
			}
			else if (Q[i].hh == Q[j].hh) {
				if (Q[i].mm < Q[j].mm) {
					strcpy(tmpname, Q[i].cityname);
					tmpindex = Q[i].index;
					hh = Q[i].hh;
					mm = Q[i].mm;
					Q[i].hh = Q[j].hh;
					Q[i].mm = Q[j].mm;
					strcpy(Q[i].cityname, Q[j].cityname);
					Q[i].index = Q[j].index;
					strcpy(Q[j].cityname, tmpname);
					Q[j].index = tmpindex;
					Q[j].hh = hh;
					Q[j].mm = mm;
				}
			}
		}
	}
	int u = Q[0].index;
	Q[0].index = Q[count - 1].index;
	Q[0].hh = Q[count - 1].hh;
	Q[0].mm = Q[count - 1].mm;
	strcpy(Q[0].cityname, Q[count - 1].cityname);
	numberofQ--;

	return u;
}

void main() {
	printf("the number of cities\n");
	scanf("%d%*c", &numberOfCities);
	numberofQ = numberOfCities;
	printf("city names\n");

	cities = (city*)malloc(sizeof(city) * numberOfCities);
	Q = (city*)malloc(sizeof(city) * numberOfCities);
	S = (name*)malloc(sizeof(name) * numberOfCities);

	for (int i = 0; i < numberOfCities; i++) {
		gets(cities[i].cityname);
		cities[i].index = i;
		Q[i].index = i;
		strcpy(Q[i].cityname, cities[i].cityname);
	}
	printf("the number of timetables\n");
	scanf("%d", &numberOfTimetables);
	timetable* timetables = (timetable*)malloc(sizeof(timetable) * numberOfTimetables);

	printf("get timetables\n");
	for (int i = 0; i < numberOfTimetables; i++) {
		scanf("%d %d%*c", &timetables[i].deptTimeHH, &timetables[i].deptTimeMM);
		gets(timetables[i].deptCity);
		scanf("%d %d%*c", &timetables[i].arrTimeHH, &timetables[i].arrTimeMM);
		gets(timetables[i].arrCity);
	}
	printf("opentime : ");
	scanf("%d%*c", &openTime);
	printf("departure : ");
	gets(departureCity);
	printf("destination : ");
	gets(destination);

	/*-****************************************************************/
	int purposedTimeHH = 23;
	int purposedTimeMM = 59;
	int arrnum0fDesti;
	/*find destination and put the value of the latest time*/
	for (int i = 0; i < numberOfCities; i++) {
		if (strcmp(destination, timetables[i].arrCity)==0) {
			if (purposedTimeHH > timetables[i].arrTimeHH) {
				purposedTimeHH = timetables[i].arrTimeHH;
				purposedTimeMM = timetables[i].arrTimeMM;
			}
			else if (purposedTimeHH == timetables[i].arrTimeHH) {
				if (purposedTimeMM > timetables[i].arrTimeMM) {
					purposedTimeMM = timetables[i].arrTimeMM;
				}
			}
		}
	}
	for (int i = 0; i < numberOfCities; i++) {
		if (strcmp(destination, cities[i].cityname)==0) {
			cities[i].hh = purposedTimeHH;
			cities[i].mm = purposedTimeMM;
			Q[i].hh = purposedTimeHH;
			Q[i].mm = purposedTimeMM;
		}
	}
	/*다른애들은 0으로 바꿔줌*/
	for (int i = 0; i < numberOfCities; i++) {
		if (strcmp(cities[i].cityname, destination)!=0) {
			cities[i].hh = 0;
			cities[i].mm = 0;
			Q[i].hh = 0;
			Q[i].mm = 0;
		}
	}
	/*****************************************************************/
	while (numberofQ != 0) {
		//name* adj = (name*)malloc(sizeof(name) * numberOfCities);
		//int i = 0;
		int u = extractMin();
		//strcpy(S[i].cityname, cities[u].cityname);
		for (int i = 0; i <numberOfTimetables; i++) {
			if ((strcmp(timetables[i].arrCity, cities[u].cityname)==0) && timetables[i].arrTimeHH <=cities[u].hh) {
				compare(timetables[i]);
				
			}
		}
		//i++;
	}
	printf("departure :SEOUL %d :%d\ndestination :DAEJEON %d :%d\n", cities[0].hh, cities[0].mm, cities[2].hh, cities[2].mm);//고정값말고 나중엔 유동적인값으로 바꾸기
}

/*cities에 있는 시간정보들이랑 비교해서 선택한게 더 느리면 값 갱신해주는 것*/
int compare(timetable timetable1) {
	char* deptname = timetable1.deptCity;
	for (int i = 0; i < numberOfCities; i++) {
		if (strcmp(cities[i].cityname, deptname)==0) {
			if (cities[i].hh < timetable1.deptTimeHH) {
				cities[i].hh = timetable1.deptTimeHH;
				cities[i].mm = timetable1.deptTimeMM;
				Q[i].hh = timetable1.deptTimeHH;
				Q[i].mm = timetable1.deptTimeMM;
			}
			else if (cities[i].hh == timetable1.deptTimeHH && cities[i].mm < timetable1.deptTimeMM) {
				cities[i].hh = timetable1.deptTimeHH;
				cities[i].mm = timetable1.deptTimeMM;
				Q[i].hh = timetable1.deptTimeHH;
				Q[i].mm = timetable1.deptTimeMM;
			}
		}
	}
}

