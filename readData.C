#include <fstream>
#include <string>
#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TTree.h>
#include <TFile.h>
#include "Functions_BeamTest.h"
#include "TGraph.h"

std::ifstream::pos_type filesize(const char* filename)
{

    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
    
}

void readData(){

    Int_t nEvents = -1;

    //Name of output file
    string outputName     = "6GeVHadrons_16102024_12";
    string Directory_Data = "6GeVHadrons_16102024_12/";
   
    string fileT     = Directory_Data + "TR_0_0.dat";               //Trigger
    string file0     = Directory_Data + "wave_0.dat";               //Sinaloa
    string file      = Directory_Data + "wave_1.dat";               //SiPM 1
    string file2     = Directory_Data + "wave_2.dat";               //SiPM 2
    string file3     = Directory_Data + "wave_3.dat";               //SiPM 3
    string file4     = Directory_Data + "wave_4.dat";               //SiPM 4
    string file5     = Directory_Data + "wave_5.dat";               //SiPM 5
    string file6     = Directory_Data + "wave_6.dat";               //Prague 1
    string file7     = Directory_Data + "wave_7.dat";               //Prague 2
    string file8     = Directory_Data + "wave_8.dat";               //RPC1_1
    string file9     = Directory_Data + "wave_9.dat";               //RPC1_2
    string file10    = Directory_Data + "wave_10.dat";              //RPC1_3
    string file11    = Directory_Data + "wave_11.dat";              //RPC1_4
    string file12    = Directory_Data + "wave_12.dat";              //RPC3_1
    string file13    = Directory_Data + "wave_13.dat";              //RPC3_2
    string file14    = Directory_Data + "wave_14.dat";              //RPC3_3
    string file15    = Directory_Data + "wave_15.dat";              //RPC3_4
    string fileTCharge = Directory_Data + "wave_16.dat";              //PMT Trigger
    
    const char* fileout  = "Efficiency&TR.txt";
    std::ofstream out(fileout,      std::ofstream::out);

    float  trigger1     [SIZE_SAMPLE];
    float  sinaloa      [SIZE_SAMPLE];
    float  sipm1        [SIZE_SAMPLE];
    float  sipm2        [SIZE_SAMPLE];
    float  sipm3        [SIZE_SAMPLE];
    float  sipm4        [SIZE_SAMPLE];
    float  sipm5        [SIZE_SAMPLE];
    float  praga1       [SIZE_SAMPLE];
    float  praga2       [SIZE_SAMPLE];
    float  RPC1_1       [SIZE_SAMPLE];
    float  RPC1_2       [SIZE_SAMPLE];
    float  RPC1_3       [SIZE_SAMPLE];
    float  RPC1_4       [SIZE_SAMPLE];
    float  RPC3_1       [SIZE_SAMPLE];
    float  RPC3_2       [SIZE_SAMPLE];
    float  RPC3_3       [SIZE_SAMPLE];
    float  RPC3_4       [SIZE_SAMPLE];
    float  triggerCharge[SIZE_SAMPLE];

    FILE *ptrT;
    FILE *ptr0;
    FILE *ptr;
    FILE *ptr2;
    FILE *ptr3;
    FILE *ptr4;
    FILE *ptr5;
    FILE *ptr6;
    FILE *ptr7;
    FILE *ptr8;
    FILE *ptr9;
    FILE *ptr10;
    FILE *ptr11;
    FILE *ptr12;
    FILE *ptr13;
    FILE *ptr14;
    FILE *ptr15;
    FILE *ptr16;
    FILE *ptr17;
    FILE *ptrTCharge;
    
    int evento = 0, eventRPC3_1 = 0, eventRPC3_2 = 0, eventRPC3_3 = 0, eventRPC3_4 = 0, 
                    eventRPC1_1 = 0, eventRPC1_2 = 0, eventRPC1_3 = 0, eventRPC1_4 = 0,
                    eventSin    = 0, eventSipm1  = 0, eventSipm2  = 0, eventSipm3  = 0,
                    eventSipm4  = 0, eventSipm5  = 0, eventPrag1  = 0, eventPrag2  = 0,
                    eventPMT    = 0;
    
    float EffRPC3_1 = 0.0, EffRPC3_2 = 0.0, EffRPC3_3 = 0.0, EffRPC3_4 = 0.0,
          EffRPC1_1 = 0.0, EffRPC1_2 = 0.0, EffRPC1_3 = 0.0, EffRPC1_4 = 0.0,
          EffSin    = 0.0, EffSipm1  = 0.0, EffSipm2  = 0.0, EffSipm3  = 0.0,
          EffSipm4  = 0.0, EffSipm5  = 0.0, EffPrag1  = 0.0, EffPrag2  = 0.0,
          EffPMT    = 0.0,
          ChargeRPC3_1 = 0.0, ChargeRPC3_2 = 0.0, ChargeRPC3_3 = 0.0, ChargeRPC3_4 = 0.0,
          ChargeRPC1_1 = 0.0, ChargeRPC1_2 = 0.0, ChargeRPC1_3 = 0.0, ChargeRPC1_4 = 0.0,
          chargeSin    = 0.0, ChargeSipm1  = 0.0, ChargeSipm2  = 0.0, ChargeSipm3  = 0.0,
          ChargeSipm4  = 0.0, ChargeSipm5  = 0.0, ChargePrag1  = 0.0, ChargePrag2  = 0.0,
          ChargePMT    = 0.0;
          
    float TimeBeginRPC3_1 = 0.0, TimeBeginRPC3_2  = 0.0, TimeBeginRPC3_3 = 0.0, TimeBeginRPC3_4 = 0.0, 
          TimeBeginRPC1_1 = 0.0, TimeBeginRPC1_2  = 0.0, TimeBeginRPC1_3 = 0.0, TimeBeginRPC1_4 = 0.0,
          TimeBeginSin    = 0.0, TimeBeginSipm1   = 0.0, TimeBeginSipm2  = 0.0, TimeBeginSipm3  = 0.0,
          TimeBeginSipm4  = 0.0, TimeBeginSipm5   = 0.0, TimeBeginPrag1  = 0.0, TimeBeginPrag2  = 0.0,
          TimeBeginPMT    = 0.0;

    float samplingrate=1; //sampling rate = 1GS/s
    float  AmplitudeResolution = 0.00024414; // 1/4098 amplitude resolution = 0.2 mV per bit (LSB)

    Int_t dataPointSz = sizeof RPC1_1[0];
    int   fSize = filesize(file8.c_str());

    ptrT   = fopen(fileT.c_str(), "rb");   //r for read, b for binary Trigger
    if (!ptrT) cerr << "Error opening file: " << fileT << std::endl;
    ptr0   = fopen(file0.c_str(), "rb");   //Sinaloa
    if (!ptr0) cerr << "Error opening file: " << file0 << std::endl;
    ptr    = fopen(file.c_str(), "rb");    //SiPM1
    if (!ptr ) cerr << "Error opening file: " << file  << std::endl;
    ptr2  = fopen(file2.c_str(), "rb");   //SiPM2
    if (!ptr2) cerr << "Error opening file: " << file2 << std::endl;
    ptr3  = fopen(file3.c_str(), "rb");   //SiPM3
    if (!ptr3) cerr << "Error opening file: " << file3 << std::endl;
    ptr4  = fopen(file4.c_str(), "rb");   //SiPM4
    if (!ptr4) cerr << "Error opening file: " << file4 << std::endl;
    ptr5  = fopen(file5.c_str(), "rb");   //SiPM5
    if (!ptr5) cerr << "Error opening file: " << file5 << std::endl;
    ptr6  = fopen(file6.c_str(), "rb");   //Prague1
    if (!ptr6) cerr << "Error opening file: " << file6 << std::endl;
    ptr7  = fopen(file7.c_str(), "rb");   //Prague2
    if (!ptr7) cerr << "Error opening file: " << file7 << std::endl;
    ptr8  = fopen(file8.c_str(), "rb");   //RPC1_1
    if (!ptr8) cerr << "Error opening file: " << file8 << std::endl;
    ptr9  = fopen(file9.c_str(), "rb");   //RPC1_2
    if (!ptr9) cerr << "Error opening file: " << file9 << std::endl;
    ptr10 = fopen(file10.c_str(),"rb");   //RPC1_3
    if (!ptr10) cerr << "Error opening file: " << file10 << std::endl;
    ptr11 = fopen(file11.c_str(),"rb");   //RPC1_4
    if (!ptr11) cerr << "Error opening file: " << file11 << std::endl;
    ptr12 = fopen(file12.c_str(),"rb");   //RPC3_1
    if (!ptr12) cerr << "Error opening file: " << file12 << std::endl;
    ptr13 = fopen(file13.c_str(),"rb");   //RPC3_2
    if (!ptr13) cerr << "Error opening file: " << file13 << std::endl;
    ptr14 = fopen(file14.c_str(),"rb");   //RPC3_3
    if (!ptr14) cerr << "Error opening file: " << file14 << std::endl;
    ptr15 = fopen(file15.c_str(),"rb");   //RPC3_4
    if (!ptr15) cerr << "Error opening file: " << file15 << std::endl;
    ptrTCharge = fopen(fileTCharge.c_str(),"rb");   //PMT
    if (!ptrTCharge) cerr << "Error opening file: " << fileTCharge << std::endl;

    float dt[SIZE_SAMPLE];
    
    Int_t BinRPC = 200, LimIRPC = 100, LimSRPC = 400, BinTrigger = 400, LimITrigger = 400, LimSTrigger = 600;
    //Con cosmicos Int_t BinRPC = 90, LimIRPC = 0, LimSRPC = 250, BinTrigger = 90, LimITrigger = -200, LimSTrigger = 50; 
    
    auto h1  = new TH1F("h1",  "PMT"         ,  BinTrigger, LimITrigger, LimSTrigger);
    auto h2  = new TH1F("h2",  "PMT - RPC1_1",   BinRPC,     LimIRPC,     LimSRPC);
    auto h3  = new TH1F("h3",  "PMT - RPC1_2",   BinRPC,     LimIRPC,     LimSRPC);
    auto h4  = new TH1F("h4",  "PMT - RPC1_3",   BinRPC,     LimIRPC,     LimSRPC);
    auto h5  = new TH1F("h5",  "PMT - RPC1_4",   BinRPC,     LimIRPC,     LimSRPC);
    auto h6  = new TH1F("h6",  "PMT - RPC3_1",   BinRPC,     LimIRPC,     LimSRPC);
    auto h7  = new TH1F("h7",  "PMT - RPC3_2",   BinRPC,     LimIRPC,     LimSRPC);
    auto h8  = new TH1F("h8",  "PMT - RPC3_3",   BinRPC,     LimIRPC,     LimSRPC);
    auto h9  = new TH1F("h9",  "PMT - RPC3_4",   BinRPC,     LimIRPC,     LimSRPC);
    
    Int_t BinChargeRPC = 250, LimIChargeRPC = 23000, LimSChargeRPC = 28000;//1100
    //Int_t BinChargeRPC = 200, LimIChargeRPC = -10, LimSChargeRPC = 200; 
    
    auto hc1 = new TH1F("hc1", "Charge Distribution RPC1_1 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc2 = new TH1F("hc2", "Charge Distribution RPC1_2 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc3 = new TH1F("hc3", "Charge Distribution RPC1_3 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc4 = new TH1F("hc4", "Charge Distribution RPC1_4 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc5 = new TH1F("hc5", "Charge Distribution RPC3_1 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc6 = new TH1F("hc6", "Charge Distribution RPC3_2 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc7 = new TH1F("hc7", "Charge Distribution RPC3_3 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    auto hc8 = new TH1F("hc8", "Charge Distribution RPC3_4 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC);
    
    auto hct1 = new TH2F("hct1", "Charge vs Time RPC1_1 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct2 = new TH2F("hct2", "Charge vs Time RPC1_2 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct3 = new TH2F("hct3", "Charge vs Time RPC1_3 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct4 = new TH2F("hct4", "Charge vs Time RPC1_4 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct5 = new TH2F("hct5", "Charge vs Time RPC3_1 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct6 = new TH2F("hct6", "Charge vs Time RPC3_2 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct7 = new TH2F("hct7", "Charge vs Time RPC3_3 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);
    auto hct8 = new TH2F("hct8", "Charge vs Time RPC3_4 6700 V", BinChargeRPC, LimIChargeRPC, LimSChargeRPC,  BinRPC, LimIRPC, LimSRPC);

    TH2 * h2SignalT1            = new TH2D(   "h2SignalT1", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2SignalTriggerCharge = new TH2D("h2SignalTrigQ", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal0             = new TH2D(    "h2Signal0", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal              = new TH2D(     "h2Signal", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal2             = new TH2D(    "h2Signal2", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal3             = new TH2D(    "h2Signal3", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal4             = new TH2D(    "h2Signal4", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal5             = new TH2D(    "h2Signal5", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal6             = new TH2D(    "h2Signal6", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal7             = new TH2D(    "h2Signal7", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal8             = new TH2D(    "h2Signal8", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal9             = new TH2D(    "h2Signal9", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal10            = new TH2D(   "h2Signal10", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal11            = new TH2D(   "h2Signal11", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal12            = new TH2D(   "h2Signal12", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal13            = new TH2D(   "h2Signal13", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal14            = new TH2D(   "h2Signal14", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
    TH2 * h2Signal15            = new TH2D(   "h2Signal15", "Signal Average; time [ns];Amplitude [mV];", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);

    for (Int_t i = 0; i < SIZE_SAMPLE; i++){
    
        dt[i]=i*samplingrate;
        
    }

    Int_t nTotalEvents = fSize/(SIZE_SAMPLE*dataPointSz);
    if (nEvents<0) nEvents = nTotalEvents;

    //The TTre to be save in output file is created and defined
    TTree* OutTree = new TTree("BeamTest2024", "BeamTest2024");

    //The analisis to monitoring
    TFile output((outputName+".root").c_str(), "RECREATE");
    output.cd();

    for(Int_t event=0; event < nEvents; event++){//nEvents
    
        fread(trigger1     ,sizeof(trigger1),     1,      ptrT);
        fread(triggerCharge,sizeof(triggerCharge),1,ptrTCharge);
        fread(sinaloa      ,sizeof(sinaloa)      ,1,      ptr0);
        fread(sipm1        ,sizeof(sipm1)        ,1,       ptr);
        fread(sipm2        ,sizeof(sipm2)        ,1,      ptr2);
        fread(sipm3        ,sizeof(sipm3)        ,1,      ptr3);
        fread(sipm4        ,sizeof(sipm4)        ,1,      ptr4);
        fread(sipm5        ,sizeof(sipm5)        ,1,      ptr5);
        fread(praga1       ,sizeof(praga1)       ,1,      ptr6);
        fread(praga2       ,sizeof(praga2)       ,1,      ptr7);
        fread(RPC1_1       ,sizeof(RPC1_1)       ,1,      ptr8);
        fread(RPC1_2       ,sizeof(RPC1_2)       ,1,      ptr9);
        fread(RPC1_3       ,sizeof(RPC1_3)       ,1,     ptr10);
        fread(RPC1_4       ,sizeof(RPC1_4)       ,1,     ptr11);
        fread(RPC3_1       ,sizeof(RPC3_1)       ,1,     ptr12);
        fread(RPC3_2       ,sizeof(RPC3_2)       ,1,     ptr13);
        fread(RPC3_3       ,sizeof(RPC3_3)       ,1,     ptr14);
        fread(RPC3_4       ,sizeof(RPC3_4)       ,1,     ptr15);

        for (Int_t i = 0; i < SIZE_SAMPLE; i++){
    
            /*h2SignalT1            -> Fill(dt[i],trigger1[i]*ampRes);
            h2SignalTriggerCharge -> Fill(dt[i],triggerCharge[i]*ampRes);
            h2Signal0             -> Fill(dt[i],sinaloa[i]*ampRes);
            h2Signal              -> Fill(dt[i],sipm1[i]*ampRes);
            h2Signal2             -> Fill(dt[i],sipm2[i]*ampRes);
            h2Signal3             -> Fill(dt[i],sipm3[i]*ampRes);
            h2Signal4             -> Fill(dt[i],sipm4[i]*ampRes);
            h2Signal5             -> Fill(dt[i],sipm5[i]*ampRes);
            h2Signal6             -> Fill(dt[i],praga1[i]*ampRes);
            h2Signal7             -> Fill(dt[i],praga2[i]*ampRes);
            h2Signal8             -> Fill(dt[i],RPC1_1[i]*ampRes);
            h2Signal9             -> Fill(dt[i],RPC1_2[i]*ampRes);
            h2Signal1             -> Fill(dt[i],RPC1_3[i]*ampRes);
            h2Signal11            -> Fill(dt[i],RPC1_4[i]*ampRes);
            h2Signal12            -> Fill(dt[i],RPC3_1[i]*ampRes);
            h2Signal13            -> Fill(dt[i],RPC3_2[i]*ampRes);
            h2Signal14            -> Fill(dt[i],RPC3_3[i]*ampRes);
            h2Signal15            -> Fill(dt[i],RPC3_4[i]*ampRes);*/
            
            if (trigger1[i]*ampRes < 525 ){
             
                for(int j = 0; j < 1024; j++) if (triggerCharge[j]*ampRes < 625 ) TimeBeginPMT = j;
                
                for(int j = 0; j < 1024; j++){
                
                   if (RPC1_1[j]*ampRes < 865 )//865
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC1_1 += RPC1_1[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC1_1[k]*ampRes < 880) ChargeRPC1_1 += RPC1_1[k] * ampRes * samplingrate;
                       //cout << "RPC1_1 Charge = " << ChargeRPC1_1 << "  Event =" << event << endl;
                       hc1->Fill(ChargeRPC1_1);
                       eventRPC1_1++;
                       TimeBeginRPC1_1 = j;
                       hct1->Fill(ChargeRPC1_1, TimeBeginRPC1_1);
                       ChargeRPC1_1 = 0.0;
                       break;
                
                       }
                    
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC1_2[j]*ampRes < 875 )//875
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC1_2 += RPC1_2[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC1_2[k]*ampRes < 880) ChargeRPC1_2 += RPC1_2[k] * ampRes * samplingrate;
                       //cout << "RPC1_2 Charge = " << ChargeRPC1_2 << "  Event =" << event << endl;
                       hc2->Fill(ChargeRPC1_2);
                       eventRPC1_2++;
                       TimeBeginRPC1_2 = j;
                       hct2->Fill(ChargeRPC1_2, TimeBeginRPC1_2);
                       ChargeRPC1_2 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){       
                   
                   if (RPC1_3[j]*ampRes < 990 )
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC1_3 += RPC1_3[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC1_3[k]*ampRes < 880) ChargeRPC1_3 += RPC1_3[k] * ampRes * samplingrate;
                       //cout << "RPC1_3 Charge = " << ChargeRPC1_3 << "  Event =" << event << endl;
                       hc3->Fill(ChargeRPC1_3);
                       eventRPC1_3++;
                       TimeBeginRPC1_3 = j;
                       hct3->Fill(ChargeRPC1_3, TimeBeginRPC1_3);
                       ChargeRPC1_3 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC1_4[j]*ampRes < 880 )//880
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC1_4 += RPC1_4[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC1_4[k]*ampRes < 880) ChargeRPC1_4 += RPC1_4[k] * ampRes * samplingrate;
                       //cout << "RPC1_4 Charge = " << ChargeRPC1_4 << "  Event =" << event << endl;
                       hc4->Fill(ChargeRPC1_4);
                       eventRPC1_4++;
                       TimeBeginRPC1_4 = j;
                       hct4->Fill(ChargeRPC1_4, TimeBeginRPC1_4);
                       ChargeRPC1_4 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC3_1[j]*ampRes < 870 )//870
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC3_1 += RPC3_1[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC3_1[k]*ampRes < 880) ChargeRPC3_1 += RPC3_1[k] * ampRes * samplingrate;
                       //cout << "RPC3_1 Charge = " << ChargeRPC3_1 << "  Event =" << event << endl;
                       hc5->Fill(ChargeRPC3_1);
                       eventRPC3_1++;
                       TimeBeginRPC3_1 = j;
                       hct5->Fill(ChargeRPC3_1, TimeBeginRPC3_1);
                       ChargeRPC3_1 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC3_2[j]*ampRes < 860 )//860
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC3_2 += RPC3_2[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC3_2[k]*ampRes < 880) ChargeRPC3_2 += RPC3_1[k] * ampRes * samplingrate;
                       //cout << "RPC3_2 Charge = " << ChargeRPC3_2 << "  Event =" << event << endl;
                       hc6->Fill(ChargeRPC3_2);
                       eventRPC3_2++;
                       TimeBeginRPC3_2 = j;
                       hct6->Fill(ChargeRPC3_2, TimeBeginRPC3_2);
                       ChargeRPC3_2 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC3_3[j]*ampRes < 870 )//870
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC3_3 += RPC3_3[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC3_3[k]*ampRes < 880) ChargeRPC3_3 += RPC3_3[k] * ampRes * samplingrate;
                       //cout << "RPC3_3 Charge = " << ChargeRPC3_3 << "  Event =" << event << endl;
                       hc7->Fill(ChargeRPC3_3);
                       eventRPC3_3++;
                       TimeBeginRPC3_3 = j;
                       hct7->Fill(ChargeRPC3_3, TimeBeginRPC3_3);
                       ChargeRPC3_3 = 0.0;
                       break;
                
                       }
                       
                   }
                   
                   for(int j = 0; j < 1024; j++){    
                   
                   if (RPC3_4[j]*ampRes < 870 )//870
                   {
                
                       for (int k = j; k < j + 30 ; k++) ChargeRPC3_4 += RPC3_4[k] * ampRes * samplingrate;
                       //for (int k = j; k < j + 30 ; k++) if (RPC3_4[k]*ampRes < 880) ChargeRPC3_4 += RPC3_4[k] * ampRes * samplingrate;
                       //cout << "RPC3_4 Charge = " << ChargeRPC3_4 << "  Event =" << event << endl;
                       hc8->Fill(ChargeRPC3_4);
                       eventRPC3_4++;
                       TimeBeginRPC3_4 = j;
                       hct8->Fill(ChargeRPC3_4, TimeBeginRPC3_4);
                       ChargeRPC3_4 = 0.0;
                       break;
                 
                       }
                       
                   }
                   
                evento++;
                break;              
                   
                }
            
            }
            
            if (TimeBeginPMT != 0){
           
             h1->Fill(TimeBeginPMT);
             
             if (TimeBeginRPC1_1 != 0)
             {
             
                 h2->Fill(TimeBeginPMT-TimeBeginRPC1_1);
                 //h3->Fill(TimeBeginPMTDown-TimeBeginRPC1_1);
             
                 }
             
             if (TimeBeginRPC1_2 != 0)
             {
             
                 h3->Fill(TimeBeginPMT-TimeBeginRPC1_2);
                 //h5->Fill(TimeBeginPMTDown-TimeBeginRPC1_2);
             
                 }
             
             if (TimeBeginRPC1_3 != 0)
             {
             
                 h4->Fill(TimeBeginPMT-TimeBeginRPC1_3);
                 //h7->Fill(TimeBeginPMTDown-TimeBeginRPC1_3);
             
                 }
             
             if (TimeBeginRPC1_4 != 0)
             {
             
                 h5->Fill(TimeBeginPMT-TimeBeginRPC1_4);
                 //h9->Fill(TimeBeginPMTDown-TimeBeginRPC1_4);
             
                 }
             
             if (TimeBeginRPC3_1 != 0)
             {
                
                 h6->Fill(TimeBeginPMT-TimeBeginRPC3_1);
                 //h11->Fill(TimeBeginPMTDown-TimeBeginRPC1_1); 

                 }
             
             if (TimeBeginRPC3_2 != 0)
             {
             
                 h7->Fill(TimeBeginPMT-TimeBeginRPC3_2);
                 //h13->Fill(TimeBeginPMTDown-TimeBeginRPC1_2);
             
                 }
             
             if (TimeBeginRPC3_3 != 0)
             {
             
                 h8->Fill(TimeBeginPMT-TimeBeginRPC3_3);
                 //h15->Fill(TimeBeginPMTDown-TimeBeginRPC1_3);
             
                 }
             
             if (TimeBeginRPC3_4 != 0)
             {
             
                 h9->Fill(TimeBeginPMT-TimeBeginRPC3_4);
                 //h17->Fill(TimeBeginPMTDown-TimeBeginRPC1_4);
             
                 }
              
          }
          
          TimeBeginPMT = 0;
          //TimeBeginPMTDown = 0;
          TimeBeginRPC1_1 = 0;
          TimeBeginRPC1_2 = 0;
          TimeBeginRPC1_3 = 0;
          TimeBeginRPC1_4 = 0;
          TimeBeginRPC3_1 = 0;
          TimeBeginRPC3_2 = 0;
          TimeBeginRPC3_3 = 0;
          TimeBeginRPC3_4 = 0;    
        
    }
    
    TGraph *graph  = new TGraph(1024, dt, trigger1);
    TGraph *graph1 = new TGraph(1024, dt, triggerCharge);
    TGraph *graph2 = new TGraph(1024, dt, sinaloa);
    TGraph *graph3 = new TGraph(1024, dt, RPC1_1);
    TGraph *graph4 = new TGraph(1024, dt, RPC1_2);
    TGraph *graph5 = new TGraph(1024, dt, RPC1_3); 
    TGraph *graph6 = new TGraph(1024, dt, RPC1_4);
    TGraph *graph7 = new TGraph(1024, dt, RPC3_1);
    TGraph *graph8 = new TGraph(1024, dt, RPC3_2);
    TGraph *graph9 = new TGraph(1024, dt, RPC3_3); 
    TGraph *graph10 = new TGraph(1024, dt, RPC3_4);
    TGraph *graph11 = new TGraph(1024, dt, sipm1);
    
    TCanvas* can   = new TCanvas("c" ,"Signals", 1000, 800);
    TCanvas* can1  = new TCanvas("c1","Beam Test - Time Resolution RPC1", 1000, 800);
    TCanvas* can2  = new TCanvas("c2","Beam Test - Time Resolution RPC3", 1000, 800);
    TCanvas* can3  = new TCanvas("c3","Beam Test - Charge RPC1", 1000, 800);
    TCanvas* can4  = new TCanvas("c4","Beam Test - Charge RPC3", 1000, 800);
    TCanvas* can5  = new TCanvas("c5","Beam Test - Charge vs Time RPC1", 1000, 800);
    TCanvas* can6  = new TCanvas("c6","Beam Test - Charge vs Time RPC3", 1000, 800);
    
    can->Divide(3,4);
    can1->Divide(2, 3);
    can2->Divide(2, 2);
    can3->Divide(2, 2);
    can4->Divide(2, 2);
    can5->Divide(2, 2);
    can6->Divide(2, 2);
    
    can->cd(1);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(1);
    graph->SetTitle("Trigger Signal");
    graph->GetXaxis()->SetTitle("Time");
    graph->GetYaxis()->SetTitle("[mV]");
    graph->Draw();
    
    can->cd(2);
    graph1->SetLineColor(kBlue);
    graph1->SetLineWidth(1);
    graph1->SetTitle("PMT Signal");
    graph1->GetXaxis()->SetTitle("Time");
    graph1->GetYaxis()->SetTitle("[mV]");
    graph1->Draw();
    
    can->cd(3);
    graph2->SetLineColor(kBlue);
    graph2->SetLineWidth(1);
    graph2->SetTitle("Sinaloa Signal");
    graph2->GetXaxis()->SetTitle("Time");
    graph2->GetYaxis()->SetTitle("[mV]");
    graph2->Draw();
    
    can->cd(4);
    graph3->SetLineColor(kBlue);
    graph3->SetLineWidth(1);
    graph3->SetTitle("RPC1_1 Signal");
    graph3->GetXaxis()->SetTitle("Time");
    graph3->GetYaxis()->SetTitle("[mV]");
    graph3->Draw();
    
    can->cd(5);
    graph4->SetLineColor(kBlue);
    graph4->SetLineWidth(1);
    graph4->SetTitle("RPC1_2 Signal");
    graph4->GetXaxis()->SetTitle("Time");
    graph4->GetYaxis()->SetTitle("[mV]");
    graph4->Draw();
    
    can->cd(6);
    graph5->SetLineColor(kBlue);
    graph5->SetLineWidth(1);
    graph5->SetTitle("RPC1_3 Signal");
    graph5->GetXaxis()->SetTitle("Time");
    graph5->GetYaxis()->SetTitle("[mV]");
    graph5->Draw();
    
    can->cd(7);
    graph6->SetLineColor(kBlue);
    graph6->SetLineWidth(1);
    graph6->SetTitle("RPC1_4 Signal");
    graph6->GetXaxis()->SetTitle("Time");
    graph6->GetYaxis()->SetTitle("[mV]");
    graph6->Draw();
    
    can->cd(8);
    graph7->SetLineColor(kBlue);
    graph7->SetLineWidth(1);
    graph7->SetTitle("RPC3_1 Signal");
    graph7->GetXaxis()->SetTitle("Time");
    graph7->GetYaxis()->SetTitle("[mV]");
    graph7->Draw();
    
    can->cd(9);
    graph8->SetLineColor(kBlue);
    graph8->SetLineWidth(1);
    graph8->SetTitle("RPC3_2 Signal");
    graph8->GetXaxis()->SetTitle("Time");
    graph8->GetYaxis()->SetTitle("[mV]");
    graph8->Draw();
    
    can->cd(10);
    graph9->SetLineColor(kBlue);
    graph9->SetLineWidth(1);
    graph9->SetTitle("RPC3_3 Signal");
    graph9->GetXaxis()->SetTitle("Time");
    graph9->GetYaxis()->SetTitle("[mV]");
    graph9->Draw();
    
    can->cd(11);
    graph10->SetLineColor(kBlue);
    graph10->SetLineWidth(1);
    graph10->SetTitle("RPC3_4 Signal");
    graph10->GetXaxis()->SetTitle("Time");
    graph10->GetYaxis()->SetTitle("[mV]");
    graph10->Draw();
    
    can->cd(11);
    graph11->SetLineColor(kBlue);
    graph11->SetLineWidth(1);
    graph11->SetTitle("SiPM Signal");
    graph11->GetXaxis()->SetTitle("Time");
    graph11->GetYaxis()->SetTitle("[mV]");
    graph11->Draw();
    
    //PMT
    can1->cd(5);
    TF1 *f1 = new TF1("f1","gaus", 10, 50);
    h1->Fit("f1","R");
    h1->SetLineColor(kBlue);
    h1->SetFillColor(kBlue);
    h1->SetLineWidth(1);
    h1->Draw("");
    h1->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
    h1->GetXaxis()->SetTitle("Time [ns]");
    h1->GetYaxis()->SetTitle("Counts");
    h1->SetMaximum(h1->GetMaximum() + 0.1*h1->GetMaximum());
    
    //PMT-RPC1_1
    can1->cd(1);
    TF1 *f2 = new TF1("f2","gaus", 135, 190);
    h2->Fit("f2","R");
    h2->SetLineColor(kBlue);
    h2->SetFillColor(kBlue);
    h2->SetLineWidth(1);
    h2->Draw("");
    h2->SetMarkerStyle(20); h2->SetMarkerColor(kBlack);
    h2->GetXaxis()->SetTitle("Time [ns]");
    h2->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC1_2
    can1->cd(2);
    TF1 *f3 = new TF1("f3","gaus", 100, 120);
    h3->Fit("f3","R");
    h3->SetLineColor(kBlue);
    h3->SetFillColor(kBlue);
    h3->SetLineWidth(1);
    h3->Draw("");
    h3->SetMarkerStyle(20); h3->SetMarkerColor(kBlack);
    h3->GetXaxis()->SetTitle("Time [ns]");
    h3->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC1_3
    can1->cd(3);
    TF1 *f4 = new TF1("f4","gaus", 100, 120);
    h4->Fit("f4","R");
    h4->SetLineColor(kBlue);
    h4->SetFillColor(kBlue);
    h4->SetLineWidth(1);
    h4->Draw("");
    h4->SetMarkerStyle(20); h4->SetMarkerColor(kBlack);
    h4->GetXaxis()->SetTitle("Time [ns]");
    h4->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC1_4
    can1->cd(4);
    TF1 *f5 = new TF1("f5","gaus", 100, 120);
    h5->Fit("f5","R");
    h5->SetLineColor(kBlue);
    h5->SetFillColor(kBlue);
    h5->SetLineWidth(1);
    h5->Draw("");
    h5->SetMarkerStyle(20); h5->SetMarkerColor(kBlack);
    h5->GetXaxis()->SetTitle("Time [ns]");
    h5->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC3_1
    can2->cd(1);
    TF1 *f6 = new TF1("f6","gaus", 100, 120);
    h6->Fit("f6","R");
    h6->SetLineColor(kBlue);
    h6->SetFillColor(kBlue);
    h6->SetLineWidth(1);
    h6->Draw("");
    h6->SetMarkerStyle(20); h6->SetMarkerColor(kBlack);
    h6->GetXaxis()->SetTitle("Time [ns]");
    h6->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC3_2
    can2->cd(2);
    TF1 *f7 = new TF1("f7","gaus", 110, 170);
    h7->Fit("f7","R");
    h7->SetLineColor(kBlue);
    h7->SetFillColor(kBlue);
    h7->SetLineWidth(1);
    h7->Draw("");
    h7->SetMarkerStyle(20); h7->SetMarkerColor(kBlack);
    h7->GetXaxis()->SetTitle("Time [ns]");
    h7->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC3_3
    can2->cd(3);
    TF1 *f8 = new TF1("f8","gaus", 100, 120);
    h8->Fit("f8","R");
    h8->SetLineColor(kBlue);
    h8->SetFillColor(kBlue);
    h8->SetLineWidth(1);
    h8->Draw("");
    h8->SetMarkerStyle(20); h8->SetMarkerColor(kBlack);
    h8->GetXaxis()->SetTitle("Time [ns]");
    h8->GetYaxis()->SetTitle("Counts");
    
    //PMT-RPC3_4
    can2->cd(4);
    TF1 *f9 = new TF1("f9","gaus", 100, 120);
    h9->Fit("f9","R");
    h9->SetLineColor(kBlue);
    h9->SetFillColor(kBlue);
    h9->SetLineWidth(1);
    h9->Draw("");
    h9->SetMarkerStyle(20); h9->SetMarkerColor(kBlack);
    h9->GetXaxis()->SetTitle("Time [ns]");
    h9->GetYaxis()->SetTitle("Counts");
    
    //Charge RPC1_1
    can3->cd(1);
    TF1 *f10 = new TF1("f10", "landau", LimIChargeRPC, LimSChargeRPC);
    hc1->Draw();
    //hc1->GetXaxis()->SetTitle("Charge [pC]");
    hc1->GetYaxis()->SetTitle("Counts");
    hc1->SetMaximum(hc1->GetMaximum() + 0.1*hc1->GetMaximum());
    hc1->SetLineColor(kBlue);
    hc1->SetFillColor(kBlue);
    hc1->SetLineWidth(1);
    //Charge RPC1_2
    can3->cd(2);
    TF1 *f11 = new TF1("f11", "landau", LimIChargeRPC, LimSChargeRPC);
    hc2->Draw();
    //hc2->GetXaxis()->SetTitle("Charge [pC]");
    hc2->GetYaxis()->SetTitle("Counts");
    hc2->SetMaximum(hc2->GetMaximum() + 0.1*hc2->GetMaximum());
    hc2->SetLineColor(kBlue);
    hc2->SetFillColor(kBlue);
    hc2->SetLineWidth(1);
    //Charge RPC1_3
    can3->cd(3);
    TF1 *f12 = new TF1("f12", "landau", LimIChargeRPC, LimSChargeRPC);
    hc3->Draw();
    //hc3->GetXaxis()->SetTitle("Charge [pC]");
    hc3->GetYaxis()->SetTitle("Counts");
    hc3->SetMaximum(hc3->GetMaximum() + 0.1*hc3->GetMaximum());
    hc3->SetLineColor(kBlue);
    hc3->SetFillColor(kBlue);
    hc3->SetLineWidth(1);
    //Charge RPC1_4
    can3->cd(4);
    TF1 *f13 = new TF1("f13", "landau", LimIChargeRPC, LimSChargeRPC);
    hc4->Draw();
    //hc4->GetXaxis()->SetTitle("Charge [pC]");
    hc4->GetYaxis()->SetTitle("Counts");
    hc4->SetMaximum(hc4->GetMaximum() + 0.1*hc4->GetMaximum());
    hc4->SetLineColor(kBlue);
    hc4->SetFillColor(kBlue);
    hc4->SetLineWidth(1);
    
    //Charge RPC3_1
    can4->cd(1);
    TF1 *f14 = new TF1("f14", "landau", LimIChargeRPC, LimSChargeRPC);
    hc5->Draw();
    //hc5->GetXaxis()->SetTitle("Charge [pC]");
    hc5->GetYaxis()->SetTitle("Counts");
    hc5->SetMaximum(hc5->GetMaximum() + 0.1*hc5->GetMaximum());
    hc5->SetLineColor(kBlue);
    hc5->SetFillColor(kBlue);
    hc5->SetLineWidth(1);
    //Charge RPC3_2
    can4->cd(2);
    TF1 *f15 = new TF1("f15", "landau", LimIChargeRPC, LimSChargeRPC);
    hc6->Draw();
    //hc6->GetXaxis()->SetTitle("Charge [pC]");
    hc6->GetYaxis()->SetTitle("Counts");
    hc6->SetMaximum(hc6->GetMaximum() + 0.1*hc6->GetMaximum());
    hc6->SetLineColor(kBlue);
    hc6->SetFillColor(kBlue);
    hc6->SetLineWidth(1);
    //Charge RPC3_3
    can4->cd(3);
    TF1 *f16 = new TF1("f16", "landau", LimIChargeRPC, LimSChargeRPC);
    hc7->Draw();
    //hc7->GetXaxis()->SetTitle("Charge [pC]");
    hc7->GetYaxis()->SetTitle("Counts");
    hc7->SetMaximum(hc7->GetMaximum() + 0.1*hc7->GetMaximum());
    hc7->SetLineColor(kBlue);
    hc7->SetFillColor(kBlue);
    hc7->SetLineWidth(1);
    //Charge RPC3_4
    can4->cd(4);
    TF1 *f17 = new TF1("f17", "landau", LimIChargeRPC, LimSChargeRPC);
    hc8->Draw();
    //hc8->GetXaxis()->SetTitle("Charge [pC]");
    hc8->GetYaxis()->SetTitle("Counts");
    hc8->SetMaximum(hc8->GetMaximum() + 0.1*hc8->GetMaximum());
    hc8->SetLineColor(kBlue);
    hc8->SetFillColor(kBlue);
    hc8->SetLineWidth(1);
    
    //charge RPC1_1 vs Time
    can5->cd(1);
    hct1->Draw("colz");
    //hct1->GetXaxis()->SetTitle("Charge [pC]");
    hct1->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC1_2 vs Time
    can5->cd(2);
    hct2->Draw("colz");
    //hct2->GetXaxis()->SetTitle("Charge [pC]");
    hct2->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC1_3 vs Time
    can5->cd(3);
    hct3->Draw("colz");
    //hct3->GetXaxis()->SetTitle("Charge [pC]");
    hct3->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC1_4 vs Time
    can5->cd(4);
    hct4->Draw("colz");
    //hct4->GetXaxis()->SetTitle("Charge [pC]");
    hct4->GetYaxis()->SetTitle("Time [ns]");
    
    //charge RPC3_1 vs Time
    can6->cd(1);
    hct5->Draw("colz");
    //hct5->GetXaxis()->SetTitle("Charge [pC]");
    hct5->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC3_2 vs Time
    can6->cd(2);
    hct6->Draw("colz");
    //hct6->GetXaxis()->SetTitle("Charge [pC]");
    hct6->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC3_3 vs Time
    can6->cd(3);
    hct7->Draw("colz");
    //hct7->GetXaxis()->SetTitle("Charge [pC]");
    hct7->GetYaxis()->SetTitle("Time [ns]");
    //charge RPC3_4 vs Time
    can6->cd(4);
    hct8->Draw("colz");
    //hct8->GetXaxis()->SetTitle("Charge [pC]");
    hct8->GetYaxis()->SetTitle("Time [ns]");
    
    can ->SaveAs("Signals.svg");
    can1->SaveAs("TimeResolutionRPC1.svg");
    can2->SaveAs("TimeResolutionRPC3.svg");
    can3->SaveAs("ChargeRPC1.svg");
    can4->SaveAs("ChargeRPC3.svg");
    can5->SaveAs("ChargevsTimeRPC1.svg");
    can6->SaveAs("ChargevsTimeRPC3.svg");

    //printf("\n");
    //OutTree->Write();
    
    double sigma1 = f1->GetParameter(2);           //pmt
    double error1 = f1->GetParError(2);            //pmt
    
    double sigmaUpRPC1_1 = f2->GetParameter(2);    //pmtup-RPC1_1
    double errorUpRPC1_1 = f2->GetParError(2);     //pmtup-RPC1_1
    float TRRPC1_1 = sqrt((pow(sigmaUpRPC1_1,2) - pow(sigma1,2))/2);
    float ERRRPC1_1 = sqrt((pow(errorUpRPC1_1,2) - pow(error1,2))/2);
    
    double sigmaUpRPC1_2 = f3->GetParameter(2);    //pmtup-RPC1_2
    double errorUpRPC1_2 = f3->GetParError(2);     //pmtup-RPC1_2
    float TRRPC1_2 = sqrt((pow(sigmaUpRPC1_2,2) - pow(sigma1,2))/2);
    float ERRRPC1_2 = sqrt((pow(errorUpRPC1_2,2) - pow(error1,2))/2);
    
    double sigmaUpRPC1_3 = f4->GetParameter(2);    //pmtup-RPC1_3
    double errorUpRPC1_3 = f4->GetParError(2);     //pmtup-RPC1_3
    float TRRPC1_3 = sqrt((pow(sigmaUpRPC1_3,2) - pow(sigma1,2))/2);
    float ERRRPC1_3 = sqrt((pow(errorUpRPC1_3,2) - pow(error1,2))/2);
    
    double sigmaUpRPC1_4 = f5->GetParameter(2);    //pmtup-RPC1_4
    double errorUpRPC1_4 = f5->GetParError(2);     //pmtup-RPC1_4
    float TRRPC1_4 = sqrt((pow(sigmaUpRPC1_4,2)  - pow(sigma1,2))/2);
    float ERRRPC1_4 = sqrt((pow(errorUpRPC1_4,2) - pow(error1,2))/2);
    
    double sigmaUpRPC3_1 = f6->GetParameter(2);    //pmtup-RPC3_1
    double errorUpRPC3_1 = f6->GetParError(2);     //pmtup-RPC3_1
    float TRRPC3_1 = sqrt((pow(sigmaUpRPC3_1,2)  - pow(sigma1,2))/2);
    float ERRRPC3_1 = sqrt((pow(errorUpRPC3_1,2) - pow(error1,2))/2);
    
    double sigmaUpRPC3_2 = f7->GetParameter(2);    //pmtup-RPC3_2
    double errorUpRPC3_2 = f7->GetParError(2);     //pmtup-RPC3_2
    float TRRPC3_2 = sqrt((pow(sigmaUpRPC3_2,2)  - pow(sigma1,2))/2);
    float ERRRPC3_2 = sqrt((pow(errorUpRPC3_2,2) - pow(error1,2))/2);
    
    double sigmaUpRPC3_3 = f8->GetParameter(2);    //pmtup-RPC3_3
    double errorUpRPC3_3 = f8->GetParError(2);     //pmtup-RPC3_3
    float TRRPC3_3 = sqrt((pow(sigmaUpRPC3_3,2)  - pow(sigma1,2))/2);
    float ERRRPC3_3 = sqrt((pow(errorUpRPC3_3,2) - pow(error1,2))/2);
    
    double sigmaUpRPC3_4 = f9->GetParameter(2);    //pmtup-RPC3_4
    double errorUpRPC3_4 = f9->GetParError(2);     //pmtup-RPC3_4
    float TRRPC3_4 = sqrt((pow(sigmaUpRPC3_4,2)  - pow(sigma1,2))/2);
    float ERRRPC3_4 = sqrt((pow(errorUpRPC3_4,2) - pow(error1,2))/2);
    
    EffRPC1_1 = (float)eventRPC1_1/(float)evento*100;
    EffRPC1_2 = (float)eventRPC1_2/(float)evento*100;
    EffRPC1_3 = (float)eventRPC1_3/(float)evento*100;
    EffRPC1_4 = (float)eventRPC1_4/(float)evento*100;
    EffRPC3_1 = (float)eventRPC3_1/(float)evento*100;
    EffRPC3_2 = (float)eventRPC3_2/(float)evento*100;
    EffRPC3_3 = (float)eventRPC3_3/(float)evento*100;
    EffRPC3_4 = (float)eventRPC3_4/(float)evento*100;
      
    cout << "-----Efficiency and Time Resolution-----" << endl;
    cout << "nEvents = " << nEvents << endl;
    cout << "Coincidence beetwen PMTDOWN & PMTUP = " << evento << endl;
    cout << "RPC1_1 = " << eventRPC1_1 << endl;
    cout << "RPC1_2 = " << eventRPC1_2 << endl;
    cout << "RPC1_3 = " << eventRPC1_3 << endl;
    cout << "RPC1_4 = " << eventRPC1_4 << endl;
    cout << "RPC3_1 = " << eventRPC3_1 << endl;
    cout << "RPC3_2 = " << eventRPC3_2 << endl;
    cout << "RPC3_3 = " << eventRPC3_3 << endl;
    cout << "RPC3_4 = " << eventRPC3_4 << endl;
    cout << "Eficiencia RPC1_1 = " << EffRPC1_1 << endl;
    cout << "Eficiencia RPC1_2 = " << EffRPC1_2 << endl;
    cout << "Eficiencia RPC1_3 = " << EffRPC1_3 << endl;
    cout << "Eficiencia RPC1_4 = " << EffRPC1_4 << endl;
    cout << "Eficiencia RPC3_1 = " << EffRPC3_1 << endl;
    cout << "Eficiencia RPC3_2 = " << EffRPC3_2 << endl;
    cout << "Eficiencia RPC3_3 = " << EffRPC3_3 << endl;
    cout << "Eficiencia RPC3_4 = " << EffRPC3_4 << endl;
    cout << "TR RPC1_1 = " << TRRPC1_1 << " +/- " << ERRRPC1_1 << endl;
    cout << "TR RPC1_2 = " << TRRPC1_2 << " +/- " << ERRRPC1_2 << endl;
    cout << "TR RPC1_3 = " << TRRPC1_3 << " +/- " << ERRRPC1_3 << endl;
    cout << "TR RPC1_4 = " << TRRPC1_4 << " +/- " << ERRRPC1_4 << endl;
    cout << "TR RPC3_1 = " << TRRPC3_1 << " +/- " << ERRRPC3_1 << endl;
    cout << "TR RPC3_2 = " << TRRPC3_2 << " +/- " << ERRRPC3_2 << endl;
    cout << "TR RPC3_3 = " << TRRPC3_3 << " +/- " << ERRRPC3_3 << endl;
    cout << "TR RPC3_4 = " << TRRPC3_4 << " +/- " << ERRRPC3_4 << endl;
    
    out << "-----Efficiency and Time Resolution-----" << endl;
    out << "nEvents = " << nEvents << endl;
    out << "Coincidence beetwen PMTDOWN & PMTUP = " << evento << endl;
    out << "RPC1_1 = " << eventRPC1_1 << endl;
    out << "RPC1_2 = " << eventRPC1_2 << endl;
    out << "RPC1_3 = " << eventRPC1_3 << endl;
    out << "RPC1_4 = " << eventRPC1_4 << endl;
    out << "RPC3_1 = " << eventRPC3_1 << endl;
    out << "RPC3_2 = " << eventRPC3_2 << endl;
    out << "RPC3_3 = " << eventRPC3_3 << endl;
    out << "RPC3_4 = " << eventRPC3_4 << endl;
    out << "Eficiencia RPC1_1 = " << EffRPC1_1 << endl;
    out << "Eficiencia RPC1_2 = " << EffRPC1_2 << endl;
    out << "Eficiencia RPC1_3 = " << EffRPC1_3 << endl;
    out << "Eficiencia RPC1_4 = " << EffRPC1_4 << endl;
    out << "Eficiencia RPC3_1 = " << EffRPC3_1 << endl;
    out << "Eficiencia RPC3_2 = " << EffRPC3_2 << endl;
    out << "Eficiencia RPC3_3 = " << EffRPC3_3 << endl;
    out << "Eficiencia RPC3_4 = " << EffRPC3_4 << endl;
    out << "TR RPC1_1 = " << TRRPC1_1 << " +/- " << ERRRPC1_1 << endl;
    out << "TR RPC1_2 = " << TRRPC1_2 << " +/- " << ERRRPC1_2 << endl;
    out << "TR RPC1_3 = " << TRRPC1_3 << " +/- " << ERRRPC1_3 << endl;
    out << "TR RPC1_4 = " << TRRPC1_4 << " +/- " << ERRRPC1_4 << endl;
    out << "TR RPC3_1 = " << TRRPC3_1 << " +/- " << ERRRPC3_1 << endl;
    out << "TR RPC3_2 = " << TRRPC3_2 << " +/- " << ERRRPC3_2 << endl;
    out << "TR RPC3_3 = " << TRRPC3_3 << " +/- " << ERRRPC3_3 << endl;
    out << "TR RPC3_4 = " << TRRPC3_4 << " +/- " << ERRRPC3_4 << endl;
    out.close();
    
    //output->Write();
    
    output.Close();


}
