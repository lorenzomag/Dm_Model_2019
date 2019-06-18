//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.5, 2018-02-03
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "Sigma_sm_lvl_lvla.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace Pythia8 
{

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: e+ ve > w+ > e+ ve a WEIGHTED<=6 @1
// Process: e+ ve > w+ > mu+ vm a WEIGHTED<=6 @1
// Process: mu+ vm > w+ > e+ ve a WEIGHTED<=6 @1
// Process: mu+ vm > w+ > mu+ vm a WEIGHTED<=6 @1

//--------------------------------------------------------------------------
// Initialize process.

void Sigma_sm_lvl_lvla::initProc() 
{
  // Instantiate the model class and set parameters that stay fixed during run
  pars = Parameters_sm::getInstance(); 
  pars->setIndependentParameters(particleDataPtr, couplingsPtr, slhaPtr); 
  pars->setIndependentCouplings(); 
  // Set massive/massless matrix elements for c/b/mu/tau
  mcME = 0.; 
  mbME = particleDataPtr->m0(5); 
  mmuME = 0.; 
  mtauME = particleDataPtr->m0(15); 
  jamp2[0] = new double[1]; 
}

//--------------------------------------------------------------------------
// Evaluate |M|^2, part independent of incoming flavour.

void Sigma_sm_lvl_lvla::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(particleDataPtr, couplingsPtr, slhaPtr, alpS); 
  pars->setDependentCouplings(); 
  // Reset color flows
  for(int i = 0; i < 1; i++ )
    jamp2[0][i] = 0.; 

  // Local variables and constants
  const int ncomb = 32; 
  static bool goodhel[ncomb] = {ncomb * false}; 
  static int ntry = 0, sum_hel = 0, ngood = 0; 
  static int igood[ncomb]; 
  static int jhel; 
  double t[nprocesses]; 
  // Helicities for the process
  static const int helicities[ncomb][nexternal] = {{-1, -1, -1, -1, -1}, {-1,
      -1, -1, -1, 1}, {-1, -1, -1, 1, -1}, {-1, -1, -1, 1, 1}, {-1, -1, 1, -1,
      -1}, {-1, -1, 1, -1, 1}, {-1, -1, 1, 1, -1}, {-1, -1, 1, 1, 1}, {-1, 1,
      -1, -1, -1}, {-1, 1, -1, -1, 1}, {-1, 1, -1, 1, -1}, {-1, 1, -1, 1, 1},
      {-1, 1, 1, -1, -1}, {-1, 1, 1, -1, 1}, {-1, 1, 1, 1, -1}, {-1, 1, 1, 1,
      1}, {1, -1, -1, -1, -1}, {1, -1, -1, -1, 1}, {1, -1, -1, 1, -1}, {1, -1,
      -1, 1, 1}, {1, -1, 1, -1, -1}, {1, -1, 1, -1, 1}, {1, -1, 1, 1, -1}, {1,
      -1, 1, 1, 1}, {1, 1, -1, -1, -1}, {1, 1, -1, -1, 1}, {1, 1, -1, 1, -1},
      {1, 1, -1, 1, 1}, {1, 1, 1, -1, -1}, {1, 1, 1, -1, 1}, {1, 1, 1, 1, -1},
      {1, 1, 1, 1, 1}};
  // Denominators: spins, colors and identical particles
  const int denominators[nprocesses] = {4}; 

  ntry = ntry + 1; 

  // Reset the matrix elements
  for(int i = 0; i < nprocesses; i++ )
  {
    matrix_element[i] = 0.; 
    t[i] = 0.; 
  }

  // Define permutation
  int perm[nexternal]; 
  for(int i = 0; i < nexternal; i++ )
  {
    perm[i] = i; 
  }

  // For now, call setupForME() here
  id1 = -11; 
  id2 = 12; 
  if( !setupForME())
  {
    return; 
  }

  if (sum_hel == 0 || ntry < 10)
  {
    // Calculate the matrix element for all helicities
    for(int ihel = 0; ihel < ncomb; ihel++ )
    {
      if (goodhel[ihel] || ntry < 2)
      {
        calculate_wavefunctions(perm, helicities[ihel]); 
        t[0] = matrix_1_epve_wp_epvea(); 

        double tsum = 0; 
        for(int iproc = 0; iproc < nprocesses; iproc++ )
        {
          matrix_element[iproc] += t[iproc]; 
          tsum += t[iproc]; 
        }
        // Store which helicities give non-zero result
        if (tsum != 0. && !goodhel[ihel])
        {
          goodhel[ihel] = true; 
          ngood++; 
          igood[ngood] = ihel; 
        }
      }
    }
    jhel = 0; 
    sum_hel = min(sum_hel, ngood); 
  }
  else
  {
    // Only use the "good" helicities
    for(int j = 0; j < sum_hel; j++ )
    {
      jhel++; 
      if (jhel >= ngood)
        jhel = 0; 
      double hwgt = double(ngood)/double(sum_hel); 
      int ihel = igood[jhel]; 
      calculate_wavefunctions(perm, helicities[ihel]); 
      t[0] = matrix_1_epve_wp_epvea(); 

      for(int iproc = 0; iproc < nprocesses; iproc++ )
      {
        matrix_element[iproc] += t[iproc] * hwgt; 
      }
    }
  }

  for (int i = 0; i < nprocesses; i++ )
    matrix_element[i] /= denominators[i]; 



}

//--------------------------------------------------------------------------
// Evaluate |M|^2, including incoming flavour dependence.

double Sigma_sm_lvl_lvla::sigmaHat() 
{
  // Select between the different processes
  if(id1 == -11 && id2 == 12)
  {
    // Add matrix elements for processes with beams (-11, 12)
    return matrix_element[0] * 2; 
  }
  else if(id1 == -13 && id2 == 14)
  {
    // Add matrix elements for processes with beams (-13, 14)
    return matrix_element[0] * 2; 
  }
  else
  {
    // Return 0 if not correct initial state assignment
    return 0.; 
  }
}

//--------------------------------------------------------------------------
// Select identity, colour and anticolour.

void Sigma_sm_lvl_lvla::setIdColAcol() 
{
  if(id1 == -11 && id2 == 12)
  {
    // Pick one of the flavor combinations (-13, 14, 22), (-11, 12, 22)
    int flavors[2][3] = {{-13, 14, 22}, {-11, 12, 22}}; 
    vector<double> probs; 
    double sum = matrix_element[0] + matrix_element[0]; 
    probs.push_back(matrix_element[0]/sum); 
    probs.push_back(matrix_element[0]/sum); 
    int choice = rndmPtr->pick(probs); 
    id3 = flavors[choice][0]; 
    id4 = flavors[choice][1]; 
    id5 = flavors[choice][2]; 
  }
  else if(id1 == -13 && id2 == 14)
  {
    // Pick one of the flavor combinations (-13, 14, 22), (-11, 12, 22)
    int flavors[2][3] = {{-13, 14, 22}, {-11, 12, 22}}; 
    vector<double> probs; 
    double sum = matrix_element[0] + matrix_element[0]; 
    probs.push_back(matrix_element[0]/sum); 
    probs.push_back(matrix_element[0]/sum); 
    int choice = rndmPtr->pick(probs); 
    id3 = flavors[choice][0]; 
    id4 = flavors[choice][1]; 
    id5 = flavors[choice][2]; 
  }
  setId(id1, id2, id3, id4, id5); 
  // Pick color flow
  int ncolor[1] = {1}; 
  if((id1 == -11 && id2 == 12 && id3 == -11 && id4 == 12 && id5 == 22) || (id1
      == -11 && id2 == 12 && id3 == -13 && id4 == 14 && id5 == 22) || (id1 ==
      -13 && id2 == 14 && id3 == -11 && id4 == 12 && id5 == 22) || (id1 == -13
      && id2 == 14 && id3 == -13 && id4 == 14 && id5 == 22))
  {
    vector<double> probs; 
    double sum = jamp2[0][0]; 
    for(int i = 0; i < ncolor[0]; i++ )
      probs.push_back(jamp2[0][i]/sum); 
    int ic = rndmPtr->pick(probs); 
    static int colors[1][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; 
    setColAcol(colors[ic][0], colors[ic][1], colors[ic][2], colors[ic][3],
        colors[ic][4], colors[ic][5], colors[ic][6], colors[ic][7],
        colors[ic][8], colors[ic][9]);
  }
}

//--------------------------------------------------------------------------
// Evaluate weight for angles of decay products in process

double Sigma_sm_lvl_lvla::weightDecay(Event& process, int iResBeg, int iResEnd) 
{
  // Just use isotropic decay (default)
  return 1.; 
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void Sigma_sm_lvl_lvla::calculate_wavefunctions(const int perm[], const int
    hel[])
{
  // Calculate wavefunctions for all processes
  double p[nexternal][4]; 
  int i; 

  // Convert Pythia 4-vectors to double[]
  for(i = 0; i < nexternal; i++ )
  {
    p[i][0] = pME[i].e(); 
    p[i][1] = pME[i].px(); 
    p[i][2] = pME[i].py(); 
    p[i][3] = pME[i].pz(); 
  }

  // Calculate all wavefunctions
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  ixxxxx(p[perm[2]], mME[2], hel[2], -1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  vxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  FFV2_3(w[1], w[0], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[5]); 
  FFV2_3(w[2], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[6]); 
  FFV1_2(w[2], w[4], pars->GC_3, pars->ZERO, pars->ZERO, w[7]); 
  FFV1_1(w[0], w[4], pars->GC_3, pars->ZERO, pars->ZERO, w[8]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  VVV1_0(w[4], w[5], w[6], -pars->GC_3, amp[0]); 
  FFV2_0(w[7], w[3], w[5], pars->GC_100, amp[1]); 
  FFV2_0(w[1], w[8], w[6], pars->GC_100, amp[2]); 


}
double Sigma_sm_lvl_lvla::matrix_1_epve_wp_epvea() 
{
  int i, j; 
  // Local variables
  const int ngraphs = 3; 
  const int ncolor = 1; 
  std::complex<double> ztemp; 
  std::complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{1}}; 

  // Calculate color flows
  jamp[0] = -amp[0] - amp[1] - amp[2]; 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[0][i] += real(jamp[i] * conj(jamp[i])); 

  return matrix; 
}


}  // end namespace Pythia8
