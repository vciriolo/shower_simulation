#!/bin/sh

source /afs/cern.ch/sw/lcg/contrib/gcc/4.6/x86_64-slc6-gcc46-opt/setup.sh 
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.09/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh
source /afs/cern.ch/sw/lcg/contrib/gcc/4.6/x86_64-slc6-gcc46-opt/setup.sh

export SCRAM_ARCH=slc6_amd64_gcc472
export PATH=/afs/cern.ch/sw/lcg/external/MCGenerators/lhapdf/5.8.9/x86_64-slc6-gcc46-opt/bin/:$PATH
export PATH=/afs/cern.ch/cms/slc6_amd64_gcc472/external/pythia8/175-cms2/bin/:$PATH
export PATH=afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc46-opt/include/:$PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc46-opt/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/fastjet/3.0.3/x86_64-slc6-gcc46-opt/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/MCGenerators/lhapdf/5.8.9/x86_64-slc6-gcc46-opt/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/afs/cern.ch/cms/slc6_amd64_gcc472/external/pythia8/175-cms2/lib/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/HepMC/2.06.08/x86_64-slc6-gcc46-opt/lib/:$LD_LIBRARY_PATH
export PYTHIA8=/afs/cern.ch/cms/slc6_amd64_gcc472/external/pythia8/175-cms2/
export PYTHIA8DATA=/afs/cern.ch/cms/slc6_amd64_gcc472/external/pythia8/175-cms2/xmldoc
export LHAPDF=/afs/cern.ch/sw/lcg/external/MCGenerators/lhapdf/5.8.9/x86_64-slc6-gcc46-opt/lib/
export LHAPATH=/afs/cern.ch/sw/lcg/external/MCGenerators/lhapdf/5.8.9/share/lhapdf/PDFsets
