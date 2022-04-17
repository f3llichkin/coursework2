define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<locale.h>
#include<windows.h>
#include <string.h>
enum ConsoleColor {
 Black = 0,
 Blue = 1,
 Green = 2,
 Cyan = 3,
 Red = 4,
 Magenta = 5,
 Brown = 6,
 LightGray = 7,
 DarkGray = 8,
 LightBlue = 9,
 LightGreen = 10,
 LightCyan = 11,
 LightRed = 12,
 LightMagenta = 13,
 Yellow = 14,
 White = 15
};
int searching(char word[], char Link[MAX_PATH]) {
 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 int Error = 0;
 long Size = 0;
 int k = 0;
 FILE* File = fopen(Link, "r+");
 if (File == NULL) {
 	printf("Ошибка в fopen() в %s\n", Link);
 	system("pause");
 	return 1;
 }
 if (fseek(File, 0, SEEK_END) == -1) {
 	printf("Ошибка в fseek()");
 	system("pause");
 	fclose(File);
 	return 2;
 }

 Size = ftell(File);
 if (Size == -1) {
 	printf("Ошибка в ftell()\n");
 	system("pause");
 	fclose(File);
 	return 3;
 }
 char* allTextInfo = (char*)malloc(sizeof(char) * 
Size);
 char* pstr = allTextInfo;
 if (allTextInfo == NULL){
 	printf("Ошибка в malloc()\n");
	return 4;
 }
 if (fseek(File, 0, SEEK_SET) == -1){
 	printf("Ошибка fseek\n");
	system("pause");
 	free(allTextInfo);
 	return 6;
 }
 size_t result = fread(allTextInfo, 1, Size, File);
 if (result != Size)
 {
 	printf("Ошибка в fread()");
 	free(allTextInfo);
 	return 7;
 }
 Error = fclose(File);
 if (Error != 0) {
 	printf("Ошибка в fclose()\n");
 	system("pause");
 	free(allTextInfo);
 	return 8;
 }
 int i = 0;
 if (printf("Исходный текст %s: ", Link) < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 9;
 }
 while (pstr[i] != NULL) {
 	SetConsoleTextAttribute(hConsole, (WORD)((Black<< 4) | Green));
 	if (printf("%c", pstr[i]) < 0) {
 		printf("Ошибка в printf в main.\n");
 		system("pause");
 		return 10;
 	}
 	i++;
 	SetConsoleTextAttribute(hConsole, (WORD)((Black<< 4) | White));
 }
 if (printf("\n") < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 11;
 }
 while ((pstr = strstr(pstr, word)) != NULL)
 {
 	if (printf("Найдено совпадение в %s: ", Link) < 0) {
 		printf("Ошибка в printf в main.\n");
 		system("pause");
 		return 12;
 }
 SetConsoleTextAttribute(hConsole, (WORD)((Black<< 4) | Red));
 while (pstr[k] != '.') {
 	if (printf("%c", pstr[k]) < 0) {
 		printf("Ошибка в printf в main.\n");
 		system("pause");
 		return 13;
 	}
 	k++;
 }
 SetConsoleTextAttribute(hConsole, (WORD)((Black<< 4) | White));
 k = 0;
 if (printf("\n") < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 14;
 }
 pstr = pstr + strlen(word);
 }
 free(pstr);
 free(allTextInfo); 
 return 0;
}

int main()
{
 int Error = 0;
 char Link[MAX_PATH][MAX_PATH];
 long Size = 0;
 int count = 0;
 char word[MAX_PATH];
 int Ch=3;
 if (setlocale(LC_ALL, "Rus") == NULL) {
 	printf("Ошибка в setlocale()\n");
 	system("pause");
 	return 1;
 }
 if (printf("Введите ссылки на файлы, конец ввода файлов обозначьте вводом end в командную строку, пожалуйста!\n") < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 2;
 }
 for (int i = 0; i < 100; i++) {
 	if (scanf("%[^\n]s", Link[i]) != 1) {
 		printf("Ошибка в scanf()");
 		system("pause");
 		return 3;
 	}
 	getchar();
 	count++;
 	if (strcmp(Link[i], "end") == 0)
 		break;
 	else {
 		if (printf("\nЧисло файлов в библиотеке: %d\n", count) < 0) {
 		printf("Ошибка в printf в main.\n");
 		system("pause");
 		return 4;
 	}
 }
 }
 if (printf("1.Найти введённое слово.\n2.Выйти.\n") < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 5;
 }
 while (Ch!= 2) {
 	if (scanf("%d", &Ch) != 1) {
 	printf("Ошибка в scanf()");
 	system("pause");
 	return 6;
 }
 if (Ch == 1) {
 	if (printf("\nВведите данные, которые необходимо найти, например: password/weather/pin/location и т.д. ...:\n") < 0) {
 	printf("Ошибка в printf()\n");
 	system("pause");
 	return 7;
 }
 getchar();
 if (scanf("%[^\n]s", word) != 1) {
 	printf("Ошибка в scanf()");
 	system("pause");
 	return 8;
 }
 for (int i = 0; i < count - 1; i++) {
 	Error = searching(word, Link[i]);
 	if (Error != 0) {
 		printf("\nОшибка в searching() в %s\n", Link[i]);
 		return 9;
 	}
 }
 if (printf("Если хотите продолжить поиск - введите 1, если хотите закончить поиск - введите 2\n") < 0) {
 	printf("Ошибка в printf в main.\n");
 	system("pause");
 	return 10;
  }
 }else if(Ch==2){
 	if (printf("Вот и всё!\n") < 0) {
 	printf("Ошибка в printf()\n");
 	system("pause");
 	return 11;
 }
 return 0;
 }else {
 	if (printf("Введите корректный выбор!\n") < 0) {
 	printf("Ошибка в printf()\n");
 	system("pause");
 	return 12;
 	}
   }
 }
 return 0;
 }