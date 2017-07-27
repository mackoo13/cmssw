In order to run CTPPS simulation in CMSSW_8_0_27 follow these steps in terminal:
~~~~
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram project CMSSW CMSSW_8_0_27
cd CMSSW_8_0_27/src/
cmsenv
git cms-merge-topic mackoo13:simulation_8_0_27
scram b -j 8
cd Configuration/Test
cmsRun test.py
~~~~
The code is based on official CMS 8_0_27 release and Marcin Ziaber's fork (ziaber/simulation)
