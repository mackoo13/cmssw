#ifndef SimTotem_UFSDDigiProducer_UFSDDigiProducer_h
#define SimTotem_UFSDDigiProducer_UFSDDigiProducer_h

// -*- C++ -*-
//
// Package:    UFSDDigiProducer
// Class:      UFSDDigiProducer
//
#include "boost/shared_ptr.hpp"

// system include files
#include <memory>
#include <vector>
#include <map>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "SimTotem/RPDigiProducer/interface/RPSimTypes.h"

#include "SimTotem/RPDigiProducer/interface/UFSDDetDigitizer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"
#include "SimTotem/RPDigiProducer/interface/DeadChannelsManager.h"

//
// class decleration
//


namespace CLHEP {
    class HepRandomEngine;
}


class UFSDDigiProducer : public edm::EDProducer {
public:
    explicit UFSDDigiProducer(const edm::ParameterSet&);
    ~UFSDDigiProducer();

private:
    virtual void beginRun(edm::Run&, edm::EventSetup const&);
    virtual void produce(edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    edm::DetSet<CTPPSDiamondDigi> convertRPStripDetSet(const edm::DetSet<RPStripDigi>&);

    // ----------member data ---------------------------
    std::vector<std::string> RP_hit_containers_;
    typedef std::map<unsigned int, std::vector<PSimHit> > simhit_map;
    typedef simhit_map::iterator simhit_map_iterator;
    simhit_map SimHitMap;

    edm::ParameterSet conf_;
    std::map<RPDetId, boost::shared_ptr<UFSDDetDigitizer> > theAlgoMap;
    std::vector<edm::DetSet<CTPPSDiamondDigi> > theDigiVector;
    std::vector<edm::DetSet<RPDetTrigger> > theTriggerVector;

    CLHEP::HepRandomEngine* rndEngine = nullptr;
    int verbosity_;

    /**
     * this variable answers the question whether given channel is dead or not
     */
    DeadChannelsManager deadChannelsManager;
    /**
     * this variable indicates whether we take into account dead channels or simulate as if all
     * channels work ok (by default we do not simulate dead channels)
     */
    bool simulateDeadChannels;

    edm::EDGetTokenT<CrossingFrame<PSimHit>> tokenCrossingFrameTotemRP;
};


#endif  //SimTotem_UFSDDigiProducer_UFSDDigiProducer_h
