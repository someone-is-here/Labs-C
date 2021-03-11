#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <locale.h>
#include <math.h>

void showFCSNInfo();
void showFITMInfo();
void showFREEInfo();
void showFCADInfo();
void showFICInfo();
int chooseFaculty(int,int,int,double);
double findFact(double);
double calculate(double, int);
double calculateRec(double, int, double);
int findN(double,double);
double findDif(double, int);
void taskBSUIRInfo();
#endif