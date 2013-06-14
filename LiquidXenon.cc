#include "LiquidXenon.h"

#include <UNIC/Units.h>
using namespace UNIC;

#include <TGraphErrors.h>
#include <TAxis.h>

//______________________________________________________________________________
//

MAD::LiquidXenon::~LiquidXenon()
{
   if (fLeff) delete fLeff;
   if (fEnrEee) delete fEnrEee;
}

//______________________________________________________________________________
//

TGraphErrors* MAD::LiquidXenon::Leff()
{
   if (fLeff) return fLeff;

   const Int_t n = 50;
   Double_t x[n] = { 1, 1.12466, 1.26486, 1.42253, 1.59986, 1.79929, 2.02359,
      2.27585, 2.55955, 2.87862, 3.23746, 3.64103, 4.09492, 4.60538, 5.17947,
      5.82514, 6.55129, 7.36795, 8.28643, 9.31940, 10.4811, 11.7877, 13.2571,
      14.9097, 16.7683, 18.8586, 21.2095, 23.8534, 26.8270, 30.1711, 33.9322,
      38.1621, 42.9193, 48.2696, 54.2868, 61.0540, 68.6649, 77.2245, 86.8511,
      97.6778, 109.854, 123.548, 138.950, 156.271, 175.751, 197.660, 222.300,
      250.011, 281.177, 316.228}; // nuclear recoil energy [keVnr]
   Double_t y[n] = {0.000454669, 0.0092494, 0.0182048, 0.02765, 0.036913,
      0.0456639, 0.05503, 0.0638111, 0.0728037, 0.0831565, 0.0933327,
      0.0968604, 0.0993807, 0.103269, 0.106676, 0.111754, 0.117344, 0.122967,
      0.129121, 0.13526, 0.141768, 0.144309, 0.146698, 0.149436, 0.152274,
      0.155052, 0.157907, 0.161654, 0.165492, 0.171049, 0.175188, 0.178909,
      0.182071, 0.185716, 0.189089, 0.191509, 0.193653, 0.195314, 0.196, 0.196,
      0.196401, 0.197, 0.197356, 0.199, 0.199, 0.199, 0.199, 0.199, 0.199,
      0.199 };
   Double_t xp[n] ={1, 1.12466, 1.26486, 1.42253, 1.59986, 1.79929, 2.02359,
      2.27585, 2.55955, 2.87862, 3.23746, 3.64103, 4.09492, 4.60538, 5.17947,
      5.82514, 6.55129, 7.36795, 8.28643, 9.3194,  10.4811, 11.7877, 13.2571,
      14.9097, 16.7683, 18.8586, 21.2095, 23.8534, 26.827,  30.1711, 33.9322,
      38.1621, 42.9193, 48.2696, 54.2868, 61.054,  68.6649, 77.2245, 86.8511,
      97.6778, 109.854, 123.548, 138.95,  156.271, 175.751, 197.66,  222.3,
      250.011, 281.177, 316.228}; // 1 sigma upper bound of x
   Double_t yp[n] ={0.100983, 0.100453, 0.10002, 0.100115, 0.100222, 0.100342,
      0.100477, 0.100629, 0.100799, 0.100991, 0.10411, 0.107306, 0.110517,
      0.113884, 0.116358, 0.121395, 0.126807, 0.132084, 0.137229, 0.143383,
      0.148906, 0.152364, 0.155381, 0.158515, 0.162384, 0.165862, 0.169121,
      0.172709, 0.176505, 0.181164, 0.1863, 0.189191, 0.192306, 0.19543,
      0.198025, 0.20072, 0.203115, 0.203715, 0.204321, 0.204947, 0.205746,
      0.206608, 0.207655, 0.208613, 0.209, 0.209, 0.209, 0.209, 0.209, 0.209};
   Double_t dx[n], dy[n];
   for (Int_t i=0; i<n; i++) {
      dx[i] = xp[i] - x[i];
      dy[i] = yp[i] - y[i];
   }

   fLeff = new TGraphErrors(n,x,y,dx,dy);
   fLeff->SetTitle("Scintillation efficiency of liquid xenon");
   fLeff->GetXaxis()->SetTitle("Nuclear recoil energy [keV]");
   fLeff->GetYaxis()->SetTitle("L_{eff}");
   fLeff->GetYaxis()->SetRangeUser(0,0.25);

   return fLeff;
}

//______________________________________________________________________________
//

Double_t MAD::LiquidXenon::Eee(Double_t energy_keVnr)
{
   return energy_keVnr*Leff()->Eval(energy_keVnr/keV);
}

//______________________________________________________________________________
//

TGraphErrors* MAD::LiquidXenon::EnrEee()
{

   if (fEnrEee) return fEnrEee;

   const Int_t n = 50;
   Double_t y[n] = { 1, 1.12466, 1.26486, 1.42253, 1.59986, 1.79929, 2.02359,
      2.27585, 2.55955, 2.87862, 3.23746, 3.64103, 4.09492, 4.60538, 5.17947,
      5.82514, 6.55129, 7.36795, 8.28643, 9.31940, 10.4811, 11.7877, 13.2571,
      14.9097, 16.7683, 18.8586, 21.2095, 23.8534, 26.8270, 30.1711, 33.9322,
      38.1621, 42.9193, 48.2696, 54.2868, 61.0540, 68.6649, 77.2245, 86.8511,
      97.6778, 109.854, 123.548, 138.950, 156.271, 175.751, 197.660, 222.300,
      250.011, 281.177, 316.228}; // nuclear recoil energy [keVnr]
   Double_t l[n] = {0.000454669, 0.0092494, 0.0182048, 0.02765, 0.036913,
      0.0456639, 0.05503, 0.0638111, 0.0728037, 0.0831565, 0.0933327,
      0.0968604, 0.0993807, 0.103269, 0.106676, 0.111754, 0.117344, 0.122967,
      0.129121, 0.13526, 0.141768, 0.144309, 0.146698, 0.149436, 0.152274,
      0.155052, 0.157907, 0.161654, 0.165492, 0.171049, 0.175188, 0.178909,
      0.182071, 0.185716, 0.189089, 0.191509, 0.193653, 0.195314, 0.196, 0.196,
      0.196401, 0.197, 0.197356, 0.199, 0.199, 0.199, 0.199, 0.199, 0.199,
      0.199 };
   Double_t x[n];
   for (Int_t i=0; i<n; i++) {
      x[i] = y[i] * l[i];
   }
   Double_t dx[n]={0}, dy[n]={0};

   fEnrEee = new TGraphErrors(n,x,y,dx,dy);
   fEnrEee->SetTitle("");
   fEnrEee->GetXaxis()->SetTitle("Visible recoil energy [keVee]");
   fEnrEee->GetYaxis()->SetTitle("Nuclear recoil energy [keVnr]");

   return fEnrEee;
}

//______________________________________________________________________________
//

Double_t MAD::LiquidXenon::Enr(Double_t energy_keVee)
{
   return EnrEee()->Eval(energy_keVee/keV) * keV;
}

//______________________________________________________________________________
//
