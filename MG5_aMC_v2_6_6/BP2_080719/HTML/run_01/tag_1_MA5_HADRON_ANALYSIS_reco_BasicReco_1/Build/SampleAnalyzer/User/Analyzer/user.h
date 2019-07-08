#ifndef analysis_user_h
#define analysis_user_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
class user : public AnalyzerBase
{
  INIT_ANALYSIS(user,"MadAnalysis5job")

 public : 
  virtual bool Initialize(const MA5::Configuration& cfg,
                          const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private : 
  // Declaring particle containers
};
}

#endif