//==========================================================================
// This file has been automatically generated for Pythia 8
// MadGraph5_aMC@NLO v. 2.6.5, 2018-02-03
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef Pythia8_Sigma_sm_lvl_lvla_H
#define Pythia8_Sigma_sm_lvl_lvla_H

#include <complex> 

#include "Pythia8/SigmaProcess.h"
#include "Parameters_sm.h"

using namespace std; 

namespace Pythia8 
{
//==========================================================================
// A class for calculating the matrix elements for
// Process: e+ ve > w+ > e+ ve a WEIGHTED<=6 @1
// Process: e+ ve > w+ > mu+ vm a WEIGHTED<=6 @1
// Process: mu+ vm > w+ > e+ ve a WEIGHTED<=6 @1
// Process: mu+ vm > w+ > mu+ vm a WEIGHTED<=6 @1
//--------------------------------------------------------------------------

class Sigma_sm_lvl_lvla : public Sigma3Process 
{
  public:

    // Constructor.
    Sigma_sm_lvl_lvla() {}

    // Initialize process.
    virtual void initProc(); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Select flavour, colour and anticolour.
    virtual void setIdColAcol(); 

    // Evaluate weight for decay angles.
    virtual double weightDecay(Event& process, int iResBeg, int iResEnd); 

    // Info on the subprocess.
    virtual string name() const {return "lvl_lvla (sm)";}

    virtual int code() const {return 10101;}

    virtual string inFlux() const {return "ffbarChg";}

    virtual int resonanceA() const {return 24;}
    // Tell Pythia that sigmaHat returns the ME^2
    virtual bool convertM2() const {return true;}

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 9; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 3; 
    std::complex<double> amp[namplitudes]; 
    double matrix_1_epve_wp_epvea(); 

    // Constants for array limits
    static const int nexternal = 5; 
    static const int nprocesses = 1; 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_sm * pars; 

}; 

}  // end namespace Pythia8

#endif  // Pythia8_Sigma_sm_lvl_lvla_H

