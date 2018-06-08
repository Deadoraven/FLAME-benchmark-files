#!/usr/bin/env python
#
# Description:
#    Quick hack to create start states (0.xml) needed by the cellpotts abm
#	input: number of agents, number of agents per column

import re
import os
import sys
from random import random
from enum import Enum



outfile = "0.xml"

# We expect 2 input arguments
if len(sys.argv) <= 2:
    print >> sys.stderr, "\nUsage: %s <row> <column>" % sys.argv[0]
    print >> sys.stderr, """ pleas add 2 integer numbers as arguments.
    More info:
    input: X number of Rows, Y number of Columns
    """
    sys.exit(1)


row, col  = map(int, sys.argv[1:])
print "input: ", row, col



if row < 2:
    print >> sys.stderr, "Error: There must be at least 2 rows"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
ix, jy = row,col

f = open(outfile, "w")
f.write("<states>\n   <itno>0</itno>\n")
id = 0

for i in xrange(ix):
    x = i + 1
    for i in xrange(jy):
        y = i + 1
        weight = random()*100

        #INACTIVE = 0
        #NEUTRAL = 1
        #ACTIVE = 2
        if (weight < 10):
            type = 2
        elif (weight < 20):
            type = 0
        else:
            type = 1

        # write agent values to file
        f.write("""
            <xagent>
                <name>neuron</name>
                <i>%d</i>
                <j>%d</j>
                <type>%d</type>
                <direction_x>-1</direction_x>
                <direction_y>-1</direction_y>
            </xagent>
            """ % (x,y,type))

# End XML file and close
f.write("</states>\n")
f.close();
