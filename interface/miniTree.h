#ifndef MINITREE_H
#define MINITREE_H

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TSystem.h"
#include "TMath.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

#include <memory>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Analysis/leopard/interface/Event.h"
#include "Analysis/leopard/interface/physicsObjects.h"
#include "Analysis/leopard/interface/eventSelection.h"
#include "Analysis/leopard/interface/configuration.h"


class miniTree {
  public:
    // Default - so root can load based on a name;
    miniTree(configuration &cmaConfig);

    // Default - so we can clean up;
    virtual ~miniTree();

    // Run once at the start of the job;
    virtual void initialize(TFile& outputFile);

    // Run for every event (in every systematic) that needs saving;
    virtual void saveEvent(const std::map<std::string,double> features);

    // Clear stuff;
    virtual void finalize();


  protected:

    TTree * m_ttree;
    TTree * m_metadataTree;
    configuration * m_config;

    /**** Training branches ****/
    // weights for inputs
    float m_xsection;
    float m_kfactor;
    float m_sumOfWeights;
    float m_weight;
    float m_nominal_weight;

    // Deep learning features
    unsigned int m_target;

    float m_AK4_CSVv2;
    float m_mass_lep_AK4;
    float m_deltaR_lep_AK4;
    float m_ptrel_lep_AK4;
    float m_deltaPhi_met_AK4;
    float m_deltaPhi_met_lep;

    /**** Metadata ****/
    // which sample has which target value
    // many ROOT files will be merged together to do the training!
    std::string m_name;
    unsigned int m_target_value;
    unsigned int m_nEvents;
};

#endif
