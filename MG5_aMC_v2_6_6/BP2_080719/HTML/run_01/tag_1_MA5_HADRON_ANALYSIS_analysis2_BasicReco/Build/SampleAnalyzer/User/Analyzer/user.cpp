#include "SampleAnalyzer/User/Analyzer/user.h"
using namespace MA5;

bool user::Initialize(const MA5::Configuration& cfg,
                      const std::map<std::string,std::string>& parameters)
{
  // Initializing PhysicsService for MC
  PHYSICS->mcConfig().Reset();

  // definition of the multiparticle "hadronic"
  PHYSICS->mcConfig().AddHadronicId(-5);
  PHYSICS->mcConfig().AddHadronicId(-4);
  PHYSICS->mcConfig().AddHadronicId(-3);
  PHYSICS->mcConfig().AddHadronicId(-2);
  PHYSICS->mcConfig().AddHadronicId(-1);
  PHYSICS->mcConfig().AddHadronicId(1);
  PHYSICS->mcConfig().AddHadronicId(2);
  PHYSICS->mcConfig().AddHadronicId(3);
  PHYSICS->mcConfig().AddHadronicId(4);
  PHYSICS->mcConfig().AddHadronicId(5);
  PHYSICS->mcConfig().AddHadronicId(21);

  // definition of the multiparticle "invisible"
  PHYSICS->mcConfig().AddInvisibleId(-16);
  PHYSICS->mcConfig().AddInvisibleId(-14);
  PHYSICS->mcConfig().AddInvisibleId(-12);
  PHYSICS->mcConfig().AddInvisibleId(12);
  PHYSICS->mcConfig().AddInvisibleId(14);
  PHYSICS->mcConfig().AddInvisibleId(16);
  PHYSICS->mcConfig().AddInvisibleId(1000022);

  // ===== Signal region ===== //
  Manager()->AddRegionSelection("myregion");

  // ===== Selections ===== //

  // ===== Histograms ===== //
  Manager()->AddHisto("1_MET", 40,0.0,500.0);
  Manager()->AddHisto("2_THT", 40,0.0,500.0);
  Manager()->AddHisto("3_PT", 40,0.0,500.0);
  Manager()->AddHisto("4_ETA", 40,-10.0,10.0);
  Manager()->AddHisto("5_MT_MET", 40,0.0,500.0);
  Manager()->AddHisto("6_PT", 40,0.0,500.0);
  Manager()->AddHisto("7_ETA", 40,-10.0,10.0);
  Manager()->AddHisto("8_MT_MET", 40,0.0,500.0);
  Manager()->AddHisto("9_PT", 40,0.0,500.0);
  Manager()->AddHisto("10_ETA", 40,-10.0,10.0);
  Manager()->AddHisto("11_MT_MET", 40,0.0,500.0);
  Manager()->AddHisto("12_PT", 40,0.0,500.0);
  Manager()->AddHisto("13_ETA", 40,-10.0,10.0);
  Manager()->AddHisto("14_MT_MET", 40,0.0,500.0);
  Manager()->AddHisto("15_M", 40,0.0,500.0);
  Manager()->AddHisto("16_M", 40,0.0,500.0);
  Manager()->AddHisto("17_M", 40,0.0,500.0);
  Manager()->AddHisto("18_M", 40,0.0,500.0);
  Manager()->AddHisto("19_M", 40,0.0,500.0);
  Manager()->AddHisto("20_M", 40,0.0,500.0);
  Manager()->AddHisto("21_DELTAR", 40,0.0,10.0);
  Manager()->AddHisto("22_DELTAR", 40,0.0,10.0);
  Manager()->AddHisto("23_DELTAR", 40,0.0,10.0);
  Manager()->AddHisto("24_DELTAR", 40,0.0,10.0);
  Manager()->AddHisto("25_DELTAR", 40,0.0,10.0);
  Manager()->AddHisto("26_DELTAR", 40,0.0,10.0);

  // No problem during initialization
  return true;
}

bool user::Execute(SampleFormat& sample, const EventFormat& event)
{
  MAfloat32 __event_weight__ = 1.0;
  if (weighted_events_ && event.mc()!=0) __event_weight__ = event.mc()->weight();

  if (sample.mc()!=0) sample.mc()->addWeightedEvents(__event_weight__);
  Manager()->InitializeForNewEvent(__event_weight__);

  // Clearing particle containers
  {
      _P_bPTorderingfinalstate_REG_.clear();
      _P_j_I1I_PTorderingfinalstate_REG_.clear();
      _P_e_I1I_PTorderingfinalstate_REG_.clear();
      _P_j_I2I_PTorderingfinalstate_REG_.clear();
      _P_mu_I1I_PTorderingfinalstate_REG_.clear();
      _P_ePTorderingfinalstate_REG_.clear();
      _P_jPTorderingfinalstate_REG_.clear();
      _P_muPTorderingfinalstate_REG_.clear();
  }

  // Filling particle containers
  {
    for (MAuint32 i=0;i<event.mc()->particles().size();i++)
    {
      if (isP__bPTorderingfinalstate((&(event.mc()->particles()[i])))) _P_bPTorderingfinalstate_REG_.push_back(&(event.mc()->particles()[i]));
      if (isP__ePTorderingfinalstate((&(event.mc()->particles()[i])))) _P_ePTorderingfinalstate_REG_.push_back(&(event.mc()->particles()[i]));
      if (isP__jPTorderingfinalstate((&(event.mc()->particles()[i])))) _P_jPTorderingfinalstate_REG_.push_back(&(event.mc()->particles()[i]));
      if (isP__muPTorderingfinalstate((&(event.mc()->particles()[i])))) _P_muPTorderingfinalstate_REG_.push_back(&(event.mc()->particles()[i]));
    }
  }

  // Sorting particles
  // Sorting particle collection according to PTordering
  // for getting 1th particle
  _P_j_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,1,PTordering);

  // Sorting particle collection according to PTordering
  // for getting 1th particle
  _P_e_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_ePTorderingfinalstate_REG_,1,PTordering);

  // Sorting particle collection according to PTordering
  // for getting 2th particle
  _P_j_I2I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,2,PTordering);

  // Sorting particle collection according to PTordering
  // for getting 1th particle
  _P_mu_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_muPTorderingfinalstate_REG_,1,PTordering);

  // Object selection number 1
  //   * Cut: select ( j ) PT > 20.0, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_jPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_jPTorderingfinalstate_REG_[muf]->pt()>20.0) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_jPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_jPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_jPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_jPTorderingfinalstate_REG_[i]);
    }
    _P_jPTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_j_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,1,PTordering);

    }
    {
      _P_j_I2I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,2,PTordering);

    }
  }
  }

  // Object selection number 2
  //   * Cut: select ( b ) PT > 20.0, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_bPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_bPTorderingfinalstate_REG_[muf]->pt()>20.0) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_bPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_bPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_bPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_bPTorderingfinalstate_REG_[i]);
    }
    _P_bPTorderingfinalstate_REG_=tmp;
    }
  }
  }

  // Object selection number 3
  //   * Cut: select ( e ) PT > 10.0, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_ePTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_ePTorderingfinalstate_REG_[muf]->pt()>10.0) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_ePTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_ePTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_ePTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_ePTorderingfinalstate_REG_[i]);
    }
    _P_ePTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_e_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_ePTorderingfinalstate_REG_,1,PTordering);

    }
  }
  }

  // Object selection number 4
  //   * Cut: select ( mu ) PT > 10.0, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_muPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_muPTorderingfinalstate_REG_[muf]->pt()>10.0) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_muPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_muPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_muPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_muPTorderingfinalstate_REG_[i]);
    }
    _P_muPTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_mu_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_muPTorderingfinalstate_REG_,1,PTordering);

    }
  }
  }

  // Object selection number 5
  //   * Cut: select ( j ) ABSETA < 2.5, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_jPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_jPTorderingfinalstate_REG_[muf]->abseta()<2.5) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_jPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_jPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_jPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_jPTorderingfinalstate_REG_[i]);
    }
    _P_jPTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_j_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,1,PTordering);

    }
    {
      _P_j_I2I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_jPTorderingfinalstate_REG_,2,PTordering);

    }
  }
  }

  // Object selection number 6
  //   * Cut: select ( b ) ABSETA < 2.5, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_bPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_bPTorderingfinalstate_REG_[muf]->abseta()<2.5) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_bPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_bPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_bPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_bPTorderingfinalstate_REG_[i]);
    }
    _P_bPTorderingfinalstate_REG_=tmp;
    }
  }
  }

  // Object selection number 7
  //   * Cut: select ( e ) ABSETA < 2.5, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_ePTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_ePTorderingfinalstate_REG_[muf]->abseta()<2.5) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_ePTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_ePTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_ePTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_ePTorderingfinalstate_REG_[i]);
    }
    _P_ePTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_e_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_ePTorderingfinalstate_REG_,1,PTordering);

    }
  }
  }

  // Object selection number 8
  //   * Cut: select ( mu ) ABSETA < 2.5, regions = []
  {
  {
    std::vector<const MCParticleFormat*> toRemove;
    for (MAuint32 muf=0;muf<_P_muPTorderingfinalstate_REG_.size();muf++)
    {
      std::vector<MAbool> filter(1,false);
      {
        if (_P_muPTorderingfinalstate_REG_[muf]->abseta()<2.5) filter[0]=true;
      }
      MAbool filter_global = (filter[0]);
      if (!filter_global) toRemove.push_back(_P_muPTorderingfinalstate_REG_[muf]);
    }
    // Removing rejected candidates from all containers
    {
    std::vector<const MCParticleFormat*> tmp;
    for (unsigned int i=0;i<_P_muPTorderingfinalstate_REG_.size();i++)
    {
      MAbool reject=false;
      for (unsigned int j=0;j<toRemove.size();j++)
      {
        if (toRemove[j]==_P_muPTorderingfinalstate_REG_[i]) {reject=true;break;}
      }
      if (!reject) tmp.push_back(_P_muPTorderingfinalstate_REG_[i]);
    }
    _P_muPTorderingfinalstate_REG_=tmp;
    }
    // Sorting particles according PTrank
    {
      _P_mu_I1I_PTorderingfinalstate_REG_=SORTER->rankFilter(_P_muPTorderingfinalstate_REG_,1,PTordering);

    }
  }
  }

  // Histogram number 1
  //   * Plot: MET
  {
    Manager()->FillHisto("1_MET", PHYSICS->Transverse->EventMET(event.mc()));
  }

  // Histogram number 2
  //   * Plot: THT
  {
    Manager()->FillHisto("2_THT", PHYSICS->Transverse->EventTHT(event.mc()));
  }

  // Histogram number 3
  //   * Plot: PT ( j[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("3_PT", _P_j_I1I_PTorderingfinalstate_REG_[ind[0]]->pt());
    }
  }
  }

  // Histogram number 4
  //   * Plot: ETA ( j[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("4_ETA", _P_j_I1I_PTorderingfinalstate_REG_[ind[0]]->eta());
    }
  }
  }

  // Histogram number 5
  //   * Plot: MT_MET ( j[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("5_MT_MET", _P_j_I1I_PTorderingfinalstate_REG_[ind[0]]->mt_met(event.mc()->MET().momentum()));
    }
  }
  }

  // Histogram number 6
  //   * Plot: PT ( j[2] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("6_PT", _P_j_I2I_PTorderingfinalstate_REG_[ind[0]]->pt());
    }
  }
  }

  // Histogram number 7
  //   * Plot: ETA ( j[2] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("7_ETA", _P_j_I2I_PTorderingfinalstate_REG_[ind[0]]->eta());
    }
  }
  }

  // Histogram number 8
  //   * Plot: MT_MET ( j[2] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("8_MT_MET", _P_j_I2I_PTorderingfinalstate_REG_[ind[0]]->mt_met(event.mc()->MET().momentum()));
    }
  }
  }

  // Histogram number 9
  //   * Plot: PT ( e[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("9_PT", _P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->pt());
    }
  }
  }

  // Histogram number 10
  //   * Plot: ETA ( e[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("10_ETA", _P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->eta());
    }
  }
  }

  // Histogram number 11
  //   * Plot: MT_MET ( e[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("11_MT_MET", _P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->mt_met(event.mc()->MET().momentum()));
    }
  }
  }

  // Histogram number 12
  //   * Plot: PT ( mu[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("12_PT", _P_mu_I1I_PTorderingfinalstate_REG_[ind[0]]->pt());
    }
  }
  }

  // Histogram number 13
  //   * Plot: ETA ( mu[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("13_ETA", _P_mu_I1I_PTorderingfinalstate_REG_[ind[0]]->eta());
    }
  }
  }

  // Histogram number 14
  //   * Plot: MT_MET ( mu[1] ) 
  {
  {
    MAuint32 ind[1];
    for (ind[0]=0;ind[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
      Manager()->FillHisto("14_MT_MET", _P_mu_I1I_PTorderingfinalstate_REG_[ind[0]]->mt_met(event.mc()->MET().momentum()));
    }
  }
  }

  // Histogram number 15
  //   * Plot: M ( e[1] mu[1] ) 
  {
  {
    MAuint32 ind[2];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    ParticleBaseFormat q;
    q+=_P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_mu_I1I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("15_M", q.m());
    }
    }
  }
  }

  // Histogram number 16
  //   * Plot: M ( e[1] j[1] ) 
  {
  {
    MAuint32 ind[2];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    ParticleBaseFormat q;
    q+=_P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_j_I1I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("16_M", q.m());
    }
    }
  }
  }

  // Histogram number 17
  //   * Plot: M ( j[1] j[2] ) 
  {
  {
    MAuint32 ind[2];
    std::vector<std::set<const MCParticleFormat*> > combis;
    for (ind[0]=0;ind[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    if (_P_j_I2I_PTorderingfinalstate_REG_[ind[1]]==_P_j_I1I_PTorderingfinalstate_REG_[ind[0]]) continue;

    // Checking if consistent combination
    std::set<const MCParticleFormat*> mycombi;
    for (MAuint32 i=0;i<2;i++)
    {
      mycombi.insert(_P_j_I1I_PTorderingfinalstate_REG_[ind[i]]);
      mycombi.insert(_P_j_I2I_PTorderingfinalstate_REG_[ind[i]]);
    }
    MAbool matched=false;
    for (MAuint32 i=0;i<combis.size();i++)
      if (combis[i]==mycombi) {matched=true; break;}
    if (matched) continue;
    else combis.push_back(mycombi);

    ParticleBaseFormat q;
    q+=_P_j_I1I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_j_I2I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("17_M", q.m());
    }
    }
  }
  }

  // Histogram number 18
  //   * Plot: M ( j[1] mu[1] ) 
  {
  {
    MAuint32 ind[2];
    for (ind[0]=0;ind[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    ParticleBaseFormat q;
    q+=_P_j_I1I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_mu_I1I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("18_M", q.m());
    }
    }
  }
  }

  // Histogram number 19
  //   * Plot: M ( e[1] j[2] ) 
  {
  {
    MAuint32 ind[2];
    for (ind[0]=0;ind[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    ParticleBaseFormat q;
    q+=_P_e_I1I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_j_I2I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("19_M", q.m());
    }
    }
  }
  }

  // Histogram number 20
  //   * Plot: M ( j[2] mu[1] ) 
  {
  {
    MAuint32 ind[2];
    for (ind[0]=0;ind[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();ind[0]++)
    {
    for (ind[1]=0;ind[1]<_P_mu_I1I_PTorderingfinalstate_REG_.size();ind[1]++)
    {
    ParticleBaseFormat q;
    q+=_P_j_I2I_PTorderingfinalstate_REG_[ind[0]]->momentum();
    q+=_P_mu_I1I_PTorderingfinalstate_REG_[ind[1]]->momentum();
      Manager()->FillHisto("20_M", q.m());
    }
    }
  }
  }

  // Histogram number 21
  //   * Plot: DELTAR ( e[1] , mu[1] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();b[0]++)
    {
      Manager()->FillHisto("21_DELTAR", _P_e_I1I_PTorderingfinalstate_REG_[a[0]]->dr(_P_mu_I1I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  // Histogram number 22
  //   * Plot: DELTAR ( j[1] , e[1] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();b[0]++)
    {
      Manager()->FillHisto("22_DELTAR", _P_j_I1I_PTorderingfinalstate_REG_[a[0]]->dr(_P_e_I1I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  // Histogram number 23
  //   * Plot: DELTAR ( j[1] , j[2] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();b[0]++)
    {
     if ( _P_j_I1I_PTorderingfinalstate_REG_[a[0]] == _P_j_I2I_PTorderingfinalstate_REG_[b[0]] ) continue;
      Manager()->FillHisto("23_DELTAR", _P_j_I1I_PTorderingfinalstate_REG_[a[0]]->dr(_P_j_I2I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  // Histogram number 24
  //   * Plot: DELTAR ( j[1] , mu[1] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_j_I1I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();b[0]++)
    {
      Manager()->FillHisto("24_DELTAR", _P_j_I1I_PTorderingfinalstate_REG_[a[0]]->dr(_P_mu_I1I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  // Histogram number 25
  //   * Plot: DELTAR ( j[2] , e[1] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_e_I1I_PTorderingfinalstate_REG_.size();b[0]++)
    {
      Manager()->FillHisto("25_DELTAR", _P_j_I2I_PTorderingfinalstate_REG_[a[0]]->dr(_P_e_I1I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  // Histogram number 26
  //   * Plot: DELTAR ( j[2] , mu[1] ) 
  {
  {
    MAuint32 a[1];
    for (a[0]=0;a[0]<_P_j_I2I_PTorderingfinalstate_REG_.size();a[0]++)
    {
    MAuint32 b[1];
    for (b[0]=0;b[0]<_P_mu_I1I_PTorderingfinalstate_REG_.size();b[0]++)
    {
      Manager()->FillHisto("26_DELTAR", _P_j_I2I_PTorderingfinalstate_REG_[a[0]]->dr(_P_mu_I1I_PTorderingfinalstate_REG_[b[0]]));
    }
    }
  }
  }

  return true;
}

void user::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
}
