//Script that reads Quarknet's raw output and ports it to a ROOT Tree.
//The Quarknet's output consists only of event lines(no initialization
//must be there or periodic outputs (normal output of these is every 5 min)
//
//The lines should also be free of the hidden "0x" character at the end of each
//line that the DAQ automatically writes, the script Copiar.C fixes that problem
//
//Ideally both scripts could be merged and the lines that are of no interest
//could be ignored automatically.
//
//Pablo Bravo Collado       ptbravo@uc.cl

//Include
#include <iostream>
#include <sstream>
#include <iomanip>
#include <TTimeStamp.h>
#include "TFile.h"
#include "TTree.h"
#include <bitset>

void simplev2() {
  TFile *f = new TFile("NAME_OF_MY_FILE.root","RECREATE");   //open .root file

  Int_t contador_errores = 0;

  //Varialbes de la linea del archivo
  Char_t p0[9], p1[3], p2[3], p3[3], p4[3], p5[3], p6[3], p7[3], p8[3], p9[9], p10[11], p11[7], p12[2], p13[3], p14[2], p15[6];

  //Variables Tiempo
  std::string syear,smonth,sday,shour,sminute, ssec, snsec0;
  Char_t line[74];
  Int_t year, month, day, hour, minute, sec;
  TTimeStamp timestamp;
  Long_t c1, c2, tclock, nsec, insec0, insec1, ns;

  //Variables de Status
  std::string GPS, flag;

  //Channel 0
  Double_t ch0_r_edge, ch0_f_edge;
  std::string ch0_bin_re, ch0_bin_fe, ch0_re_time, ch0_fe_time;
  Char_t ch0_reox[5], ch0_feox[5];
  Long_t ch0_int_re, ch0_int_fe, ch0_rticks, ch0_fticks;

  //Channel 1
  Double_t ch1_r_edge, ch1_f_edge;
  std::string ch1_bin_re, ch1_bin_fe, ch1_re_time, ch1_fe_time;
  Char_t ch1_reox[5], ch1_feox[5];
  Long_t ch1_int_re, ch1_int_fe, ch1_rticks, ch1_fticks;

  //Channel 2
  Double_t ch2_r_edge, ch2_f_edge;
  std::string ch2_bin_re, ch2_bin_fe, ch2_re_time, ch2_fe_time;
  Char_t ch2_reox[5], ch2_feox[5];
  Long_t ch2_int_re, ch2_int_fe, ch2_rticks, ch2_fticks;

  //Channel 3
  Double_t ch3_r_edge, ch3_f_edge;
  std::string ch3_bin_re, ch3_bin_fe, ch3_re_time, ch3_fe_time;
  Char_t ch3_reox[5], ch3_feox[5];
  Long_t ch3_int_re, ch3_int_fe, ch3_rticks, ch3_fticks;

  //Variables para el arbol
  //El arbol contiene el tiempo exacto del evento, utilizando t_sec and t_nsec
  //La variable trigger representa el inicio de un NUEVO evento (dependiendo de
  //la cercanía de 2 señales, el Quaknet agrupa estas señales en el mismo o
  //distinto evento)
  //Cada contador/canal tiene booleanos para la presencia de un rising/falling
  //edge en cada evento. Estos booleanos son muy útiles para recorrer el TTree
  //de forma rápida para estudios de flujo.
  //Las variables chX_t_Ye corresponden a la diferencia temporal entre la señal
  //del contador respecto al inicio del pulso, útiles para vida media.

  Bool_t status, trigger, ch0_re, ch0_fe, ch1_re, ch1_fe, ch2_re, ch2_fe, ch3_re, ch3_fe;
  Long_t t_sec, t_nsec;
  Double_t ch0_t_re, ch0_t_fe, ch1_t_re, ch1_t_fe, ch2_t_re, ch2_t_fe, ch3_t_re, ch3_t_fe;


  //Crear Tree
  TTree *t = new TTree("vidatree", "Tree del experimento");
  t->Branch("t_sec", &t_sec, "t_sec/L");
  t->Branch("t_nsec", &t_nsec, "t_nsec/L");
  t->Branch("trigger", &trigger, "trigger/O");
  t->Branch("ch0_re", &ch0_re, "ch0_re/O");
  t->Branch("ch0_fe", &ch0_fe, "ch0_fe/O");
  t->Branch("ch0_t_re", &ch0_t_re, "ch0_t_re/D");
  t->Branch("ch0_t_fe", &ch0_t_fe, "ch0_t_fe/D");
  t->Branch("ch1_re", &ch1_re, "ch1_re/O");
  t->Branch("ch1_fe", &ch1_fe, "ch1_fe/O");
  t->Branch("ch1_t_re", &ch1_t_re, "ch1_t_re/D");
  t->Branch("ch1_t_fe", &ch1_t_fe, "ch1_t_fe/D");
  t->Branch("ch2_re", &ch2_re, "ch2_re/O");
  t->Branch("ch2_fe", &ch2_fe, "ch2_fe/O");
  t->Branch("ch2_t_re", &ch2_t_re, "ch2_t_re/D");
  t->Branch("ch2_t_fe", &ch2_t_fe, "ch2_t_fe/D");
  t->Branch("ch3_re", &ch3_re, "ch3_re/O");
  t->Branch("ch3_fe", &ch3_fe, "ch3_fe/O");
  t->Branch("ch3_t_re", &ch3_t_re, "ch3_t_re/D");
  t->Branch("ch3_t_fe", &ch3_t_fe, "ch3_t_fe/D");
  t->Branch("status", &status,"status/O");

  //Abrir archivo de texto
  FILE *fp = fopen("DAQ_FILE","r");



  while (fgets(&line[0],73,fp)){
    try {
    sscanf(line,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", p0, p1, p2, p3,p4, p5,p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);

    //Transformar datos de fecha a UNIX time
    syear = string(p11,4,2);                 //year
    year = std::stoi(syear,nullptr,10)+1900;
    smonth = string(p11,2,2);                 //
    month = std::stoi(smonth,nullptr,10);
    sday = string (p11,0,2);                //day
    day = std::stoi(sday,nullptr,10);
    shour = string (p10,0,2);               //hour
    hour = std::stoi(shour,NULL,10);
    sminute = string (p10,2,2);             //minute
    minute = std::stoi(sminute,NULL,10);
    ssec = string (p10,4,2);
    sec = std::stoi(ssec,NULL,10);
    timestamp = TTimeStamp(year,month,day,hour,minute,sec);
    t_sec= timestamp.GetSec();
    snsec0 = string (p10,7,3);
    insec0 = ((Long_t)strtol(snsec0.c_str(),NULL,10));
    insec1 = ((Long_t)strtol(p15,NULL,10));
    ns = insec0+insec1;
    while (ns>=1000) {
        t_sec+=1;
        ns-=1000;
    }
    c1 = (Long_t)strtol(p0,NULL,16);
    c2 = (Long_t)strtol(p9,NULL,16);
    if (c1>=c2) {
        tclock= (c1-c2)*40;
    }
    if (c2>c1) {
        tclock = c1+(4294967295-c2);  //big number = FFFF FFFF
    }
    t_nsec=tclock+(ns*1000000);
    while (t_nsec>=1000000000) {
        t_sec+=1;
        t_nsec-=1000000000;
    }

    //Status Branch
    status = 0; //1 Error!!!!!!
    GPS = string(p12);
    flag = string(p14);
    if (GPS.compare("A") || flag.compare("0")) {
      status = 1;
    }

    //ch0 Branch
    strcpy(ch0_reox,"0x");
    strcpy(ch0_feox,"0x");
    strcat(ch0_reox,p1);
    strcat(ch0_feox,p2);
    ch0_int_re = std::stoi(ch0_reox,nullptr,16);
    ch0_int_fe = std::stoi(ch0_feox,nullptr,16);
    ch0_bin_re = std::bitset<8>(ch0_int_re).to_string();
    ch0_bin_fe = std::bitset<8>(ch0_int_fe).to_string();
    if (ch0_bin_re.compare(2,1,"1") == 0) {
      ch0_re = 1;
      ch0_re_time = string (ch0_bin_re,3,5);
      ch0_rticks = (std::stoi(ch0_re_time,nullptr,2));
      ch0_t_re = ch0_rticks*1.2;
    }
    if (ch0_bin_re.compare(2,1,"1") != 0) {
      ch0_re = 0;
      ch0_t_re = 0;
    }
    if (ch0_bin_fe.compare(2,1,"1") == 0) {
      ch0_fe = 1;
      ch0_fe_time = string (ch0_bin_fe,3,5);
      ch0_fticks = (std::stoi(ch0_fe_time,nullptr,2));
      ch0_t_fe = ch0_fticks*1.2;
    }
    if (ch0_bin_fe.compare(2,1,"1") != 0) {
      ch0_fe = 0;
      ch0_t_fe = 0;
    }
    trigger = 0;
    if (ch0_bin_re.compare(0,1,"1")==0){
        trigger = 1;
    }

    //ch1 Branch
    strcpy(ch1_reox,"0x");
    strcpy(ch1_feox,"0x");
    strcat(ch1_reox,p3);
    strcat(ch1_feox,p4);
    ch1_int_re = std::stoi(ch1_reox,nullptr,16);
    ch1_int_fe = std::stoi(ch1_feox,nullptr,16);
    ch1_bin_re = std::bitset<8>(ch1_int_re).to_string();
    ch1_bin_fe = std::bitset<8>(ch1_int_fe).to_string();
    if (ch1_bin_re.compare(2,1,"1") == 0) {
      ch1_re = 1;
      ch1_re_time = string (ch1_bin_re,3,5);
      ch1_rticks = (std::stoi(ch1_re_time,nullptr,2));
      ch1_t_re= ch1_rticks*1.2;
    }
    if (ch1_bin_re.compare(2,1,"1") != 0) {
      ch1_re = 0;
      ch1_t_re = 0;
    }
    if (ch1_bin_fe.compare(2,1,"1") == 0) {
      ch1_fe = 1;
      ch1_fe_time = string (ch1_bin_fe,3,5);
      ch1_fticks = (std::stoi(ch1_fe_time,nullptr,2));
      ch1_t_fe = ch1_fticks*1.2;
    }
    if (ch1_bin_fe.compare(2,1,"1") != 0) {
      ch1_fe = 0;
      ch1_t_fe = 0;
    }

    //ch2 Branch
    strcpy(ch2_reox,"0x");
    strcpy(ch2_feox,"0x");
    strcat(ch2_reox,p5);
    strcat(ch2_feox,p6);
    ch2_int_re = std::stoi(ch2_reox,nullptr,16);
    ch2_int_fe = std::stoi(ch2_feox,nullptr,16);
    ch2_bin_re = std::bitset<8>(ch2_int_re).to_string();
    ch2_bin_fe = std::bitset<8>(ch2_int_fe).to_string();
    if (ch2_bin_re.compare(2,1,"1") == 0) {
      ch2_re = 1;
      ch2_re_time = string (ch2_bin_re,3,5);
      ch2_rticks = (std::stoi(ch2_re_time,nullptr,2));
      ch2_t_re = ch2_rticks*1.2;
    }
    if (ch2_bin_re.compare(2,1,"1") != 0) {
      ch2_re = 0;
      ch2_t_re = 0;
    }
    if (ch2_bin_fe.compare(2,1,"1") == 0) {
      ch2_fe = 1;
      ch2_fe_time = string (ch2_bin_fe,3,5);
      ch2_fticks = (std::stoi(ch2_fe_time,nullptr,2));
      ch2_t_fe = ch2_fticks*1.2;
    }
    if (ch2_bin_fe.compare(2,1,"1") != 0) {
      ch2_fe = 0;
      ch2_t_fe = 0;
    }

    //ch3 Branch
    strcpy(ch3_reox,"0x");
    strcpy(ch3_feox,"0x");
    strcat(ch3_reox,p7);
    strcat(ch3_feox,p8);
    ch3_int_re = std::stoi(ch3_reox,nullptr,16);{}
    ch3_int_fe = std::stoi(ch3_feox,nullptr,16);
    ch3_bin_re = std::bitset<8>(ch3_int_re).to_string();
    ch3_bin_fe = std::bitset<8>(ch3_int_fe).to_string();
    if (ch3_bin_re.compare(2,1,"1") == 0) {
      ch3_re = 1;
      ch3_re_time = string (ch3_bin_re,3,5);
      ch3_rticks = (std::stoi(ch3_re_time,nullptr,2));
      ch3_t_re = ch3_rticks*1.2;
    }
    if (ch3_bin_re.compare(2,1,"1") != 0) {
      ch3_re = 0;
      ch3_t_re = 0;
    }
    if (ch3_bin_fe.compare(2,1,"1") == 0) {
      ch3_fe = 1;
      ch3_fe_time = string (ch3_bin_fe,3,5);
      ch3_fticks = (std::stoi(ch3_fe_time,nullptr,2));
      ch3_t_fe = ch3_fticks*1.2;
    }
    if (ch3_bin_fe.compare(2,1,"1") != 0) {
      ch3_fe = 0;
      ch3_t_fe = 0;
    }
    t->Fill();
    }catch(...) {
        contador_errores+=1;
    }

  }
  //Write to File
  t->Write();
  cout << contador_errores << endl;
  fclose(fp);
}
