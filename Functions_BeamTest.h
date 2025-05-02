#ifndef FUNCTIONS_BEAMTEST_H // Verifica si no se ha definido ya esta macro
#define FUNCTIONS_BEAMTEST_H // Define la macro

#include <iostream>

using namespace std;

#define SIZE_SAMPLE 1024
#define GATE1 200
#define GATE2 221
#define START_INTEGRATION 230
#define END_INTEGRATION 1014

const double ampRes = 0.24414;

//*************************** Function Declaration ***************************
float Trigger_Time1(float*, float*, int &);

float Get_Basement(float*, int);

float Get_Min_Val(float*, int);

float Get_Max_Val(float*, int);

float Get_Charge(float*, float*, float &);

float Get_DownASignal(Double_t*, float*);

#endif // FIN DE INCLUDE GUARD
