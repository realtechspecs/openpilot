#pragma once
#include <map>
#include "cereal/gen/cpp/log.capnp.h"

#if defined(QCOM) || defined(QCOM2)
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#endif

typedef cereal::CarControl::HUDControl::AudibleAlert AudibleAlert;

class Sound {
 public:
  Sound() = default;
  bool init(int volume);
  bool play(AudibleAlert alert, int repeat = 0);
  void stop();
  void setVolume(int volume, int timeout_seconds = 5);
  AudibleAlert currentPlaying();
  ~Sound();

 private:
#if defined(QCOM) || defined(QCOM2)
  SLObjectItf engine_ = nullptr;
  SLObjectItf outputMix_ = nullptr;
  int last_volume_ = 0;
  double last_set_volume_time_ = 0.;
  AudibleAlert currentSound_ = AudibleAlert::NONE;
  struct Player;
  std::map<AudibleAlert, Player *> player_;
  friend void SLAPIENTRY slplay_callback(SLPlayItf playItf, void *context, SLuint32 event);
#endif
};
