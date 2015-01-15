#ifndef ExN01RandomGenerator_h
#define ExN01RandomGenerator_h 1

#include "TString.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TNtuple.h"
#include "TAxis.h"
#include "math.h"
#include <math.h>

class ExN01RandomGenerator
    {
    public:
    
//        ExN01RandomGenerator(TFile *p_input);
        ExN01RandomGenerator(std::string p_name);
        ~ExN01RandomGenerator();
    
        double X () ;
        double Y () ;
        
        ExN01RandomGenerator& operator= (ExN01RandomGenerator & second);
        
    private:
    
    TFile *p_input_;
    TH1D *hX;
    TH1D *hY;
    
    };    
    
    
#endif

