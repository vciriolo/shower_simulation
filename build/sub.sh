#!/bin/sh

source /afs/cern.ch/user/n/ntrevisa/setup_slc6.sh
source /afs/cern.ch/user/n/ntrevisa/myGeant4.sh

/afs/cern.ch/user/n/ntrevisa/geant4/shower/build/shower 300

cp 300GeV.root /afs/cern.ch/user/n/ntrevisa/public
