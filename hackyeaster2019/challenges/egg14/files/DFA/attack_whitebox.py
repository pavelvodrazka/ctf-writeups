#!/usr/bin/env python3

import deadpool_dfa
import phoenixAES
import struct
import re

def processinput(iblock, blocksize):
    return (bytes.fromhex('%0*x' % (2*blocksize, iblock)), None)

def processoutput(output, blocksize):
    result = re.search('Enter Message to encrypt: ([0-9a-f]+)', output.decode()).group(1)
    return int(result, 16)

engine=deadpool_dfa.Acquisition(targetbin='./WhiteBox', targetdata='./WhiteBox', goldendata='./WhiteBox.gold',
        dfa=phoenixAES, processinput=processinput, processoutput=processoutput, verbose=2, minleaf=1, minleafnail=1)

tracefiles_sets=engine.run()
for tracefile in tracefiles_sets[0]:
    if phoenixAES.crack_file(tracefile):
        break
