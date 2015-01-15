#include "ExN01RandomGenerator.hh"
#include <cstdlib>
#include "TString.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "TMath.h"
#include "TFile.h"


double casuale (double min, double max)			//random numbers generator
    {
    return (min + (max - min)*rand()/(1.*RAND_MAX));
    }


ExN01RandomGenerator::ExN01RandomGenerator (std::string p_name)
    {
    p_input_ = new TFile(p_name.c_str(),"read");
    hX = (TH1D*)p_input_->Get("hodoX");
    hY = (TH1D*)p_input_->Get("hodoY");
    }    
    
ExN01RandomGenerator::~ExN01RandomGenerator()
    {}
    
double ExN01RandomGenerator::X ()
    {
    int go_out = 0;
    double base = 0.;
    while(go_out == 0)
        {
        double height = 0.;
        base = casuale(0.,8.);
        height = casuale(0., hX->GetBinContent(4));
        if (height < hX->GetBinContent(hX->FindBin(base)))      go_out = 1;
        }
    return base - hX->GetMean();
    }       
    

double ExN01RandomGenerator::Y ()
    {
    int go_out = 0;
    double base = 0.;
    while(go_out == 0)
        {
        double height = 0.;
        base = casuale(0.,8.);
        height = casuale(0., hY->GetBinContent(5));
        if (height < hY->GetBinContent(hY->FindBin(base)))      go_out = 1;        
        }
    return base - hY->GetMean();
    }
    
ExN01RandomGenerator& ExN01RandomGenerator::operator= (ExN01RandomGenerator & second)
    {
    p_input_ = second.p_input_;
    return (*this);
    }           
    
    
    
