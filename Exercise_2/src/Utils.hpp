#pragma once
#include "iostream"

using namespace std;

bool ImportVectors(const string& FileNamePath,
                   double& S,
                   size_t& n,
                   double*& w,
                   double*& r);

double DotProduct(const size_t& n,
                  const double* const& w,
                  const double* const& r);

double ValoreV(double S, double dotProduct);

bool ExportResult(const string& FileNamePath,
                  double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& dotProduct,
                  double V);

string ArrayToString(const size_t& n,
                     const double* const& v);
