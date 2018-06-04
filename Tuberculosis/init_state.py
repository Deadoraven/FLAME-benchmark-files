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
f.write("<states>\n <itno>0</itno>\n")

id = 0
bankId = 0
firmId = 0

for i in xrange(ix):
    x = i + 1
    for i in xrange(jy):
        id += 1
        y = i + 1
        alive = random() * 2
        if(alive):
            state = random() * 2
        else:
            state = 0
        # write agent values to file
        f.write("""
        <xagent>
            <name>bacteria</name>
            <i>%d</i>
            <j>%d</j>
            """ % (x,y))
        f.write("""<alive>%d</alive>
            <state>%d</state>
            <has_agents>-1</has_agents>
            <neighbors>{-1,-1,-1,-1,-1,-1,-1,-1}</neighbors>
        </xagent>
            """ % (alive, state))


for i in xrange(6):
    cleanX = random()*ix + 1
    cleanY = random()*jy + 1
    energy = 8

    f.write("""
    <xagent>
        <name>agents</name>
        <x>%d</x>
        <y>%d</y>
        """ % (cleanX,cleanY))
    f.write("""<energy>%d</energy>
        <state>0</state>
    </xagent>
        """%(energy))




for i in xrange(6):
    infectX = random()*ix + 1
    infectY = random()*jy + 1
    energy = 8

    f.write("""
    <xagent>
        <name>agents</name>
        <x>%d</x>
        <y>%d</y>
        """ % (infectX,infectY))
    f.write("""<energy>%d</energy>
        <a_state>1</a_state>
    </xagent>
        """%(energy))


# End XML file and close
f.write("</states>\n")
f.close();

print "Finish Writing on %s", outfile
