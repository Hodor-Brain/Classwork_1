#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

struct Word
{
	char ukr[20] = {};
	char eng[20] = {};
};

void flush();

int menu();

void newword(char* text, char* word);

void Add();

void Find();