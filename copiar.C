//Script that removes "0x" at the end of each line and, in this case
//merges datafiles on one.

//Pablo Bravo Collado       ptbravo@uc.cl

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

int copiar() {
    std::string linea;
    std::ofstream outfile("DAQ_FILE");
    char array[74];
    Int_t i, j, contador;

    std::ifstream file1("data1"); //file1
    j = 0;
    while (j<22837420) {
        i = 0;
        getline(file1, linea);
        if (linea.length()==72) {
            strcpy (array, linea.c_str());
            while (i<72) {
                outfile << array[i];
                i += 1;
            }
            outfile << "\n";
            j += 1;
        }
    }
    file1.close();

    std::ifstream file2("data2");
    j = 0;
    while (j<12434810) {
        i = 0;
        getline(file2, linea);
        if (linea.length()==73) {
            strcpy (array, linea.c_str());
            while (i<72) {
                outfile << array[i];
                i += 1;
            }
            outfile << "\n";
            j += 1;
        }
    }
    file2.close();

    // std::ifstream file3("data3");
    // j = 0;
    // getline(file3, linea);
    // while (j<33905253) {
    //     i = 0;
    //     getline(file3, linea);
    //     if (linea.length()==73) {
    //         strcpy (array, linea.c_str());
    //         while (i<72) {
    //             outfile << array[i];
    //             i += 1;
    //         }
    //         outfile << "\n";
    //     }
    //     j += 1;
    // }
    // file3.close();
    //
    // std::ifstream file4("data4");
    // j = 1;
    // getline(file4,linea);
    // while (j<48919220) {
    //     i = 0;
    //     getline(file4, linea);
    //     if (linea.length()==73) {
    //         strcpy (array, linea.c_str());
    //         while (i<72) {
    //             outfile << array[i];
    //             i += 1;
    //         }
    //         outfile << "\n";
    //     }
    //     j += 1;
    // }
    // file4.close();

    outfile.close();
    return 0;
}
