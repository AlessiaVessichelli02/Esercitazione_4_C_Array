#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp"

using namespace std;

int main()
{
    string FileName = "./data.csv";
    double S = 0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    //leggo i vettori da file
    if (!ImportVectors(FileName, S, n, w, r)){
        cerr << "Errore durante l'importazione dei vettori" << endl;
        return -1;
    }
    else
        cout << "Importazione riuscita" << endl;
    double dotProduct = DotProduct(n, w, r);
    double V = ValoreV(S, dotProduct);

    //scrivo i vettori sul file di output
    string FileOutput = "./result.txt";
    if (!ExportResult(FileOutput, S, n, w, r, dotProduct, V)){
        cerr << "Errore durante l'espertazione" << endl;
        return -1;
    }
    else
        cout << "Espertazione riuscita" << endl;

    //cancello i vettori
    delete[] w;
    delete[] r;





  return 0;
}

