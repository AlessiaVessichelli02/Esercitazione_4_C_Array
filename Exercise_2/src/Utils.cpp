#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool ImportVectors(const string& FileNamePath,
                   double& S,
                   size_t& n,
                   double*& w,
                   double*& r)
{
    // Apertura del File
    ifstream file;
    file.open(FileNamePath);

    if (file.fail())
    {
        cerr<< "Errore nell'apertura del file"<< endl;
        return false;
    }


    //leggo le righe
    string line;
    //leggo prima riga
    getline(file, line);
    istringstream convertN(line.substr(line.find(';')+1));
    convertN >> S;
    //leggo la seconda riga
    getline(file, line);
    convertN.clear();
    convertN.str(line.substr(line.find(';')+1));
    convertN >> n;
    //salto la terza riga
    while (!file.eof())
    {
        getline(file, line);

        // Skip Comment Line
        if(line[0] != 'w;r')
            break;
    }

    //Inizializzo i due array
    w = new double[n];
    r = new double[n];

    for (size_t i = 0; i < n; i++){
        getline(file, line);
        convertN.clear();
        convertN.str(line);
        convertN >> w[i];
        convertN.ignore(1, ';'); //ignoro il primo numero e il ';' così prendo i secondi numeri
        convertN >> r[i];
    }



    // chiudo il file
    file.close();

    return true;
}

// Funzione per il prodotto scalare per calcolare il tasso di interesse
double DotProduct(const size_t& n,
                        const double* const& w,
                        const double* const& r)
{
    double dotProduct = 0;
    for (unsigned int i = 0; i < n; i++)
        dotProduct += w[i] * r[i];

    return dotProduct;
}

//Funzione per calcolare V
double ValoreV(double S, double dotProduct){
    double V = (1 + dotProduct) * S;
    return V;
}


//Funzione per esprtare i risultati nel file di output
bool ExportResult(const string& FileNamePath,
                  double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& dotProduct,
                  double V)
{
    // Open File
    ofstream file;
    file.open(FileNamePath);

    if (file.fail())
    {
        cerr<< "file open failed"<< endl;
        return false;
    }



    file<< "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
    //stampo r (prendo l'array e dopo ogni valore metto lo spazio)
    file << "w = [ ";
    for (size_t i = 0; i < n; i++){
        file << w[i];
        if(i < n-1)
            file << " ";
    }
    file << " ]" << endl;
    //stampo r (prendo l'array e dopo ogni valore metto lo spazio)
    file << "r = [ ";
    for (size_t i = 0; i < n; i++){
        file << r[i];
        if(i < n-1)
            file << " ";
    }
    file << " ]" << endl;


    file << "Rate of return og the portfolio: " << fixed << setprecision(4) << dotProduct << endl;
    file << "V: " << fixed << setprecision(2) << V << endl;

    // Close File
    file.close();

    return true;
}

string ArrayToString(const size_t& n,
                     const double* const& v)
{
    ostringstream toString;
    toString << "[ ";
    for (size_t i = 0; i < n; i++)
        toString<< ( i != 0 ? " " : " ") << v[i];
    toString << "]";

    return toString.str();
}
