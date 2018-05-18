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

        # write agent values to file
        f.write("""
    <xagent>
        <name>cluster</name>
        <x>%d</x>
        <y>%d</y>
        """ % (x,y))
        f.write("""<hasbank>0</hasbank>
        <direction>-1</direction>
        <neighbors>{-1,-1,-1,-1,-1,-1,-1,-1}</neighbors>
    </xagent>
            """)


i = 0
banksList = []

while (i < 3):
    bankX = (int)(random() * ix) + 1
    bankY = (int)(random() * jy) + 1
    if [bankX,bankY] not in banksList:
        money = random() * 1000 + 1

        f.write("""
    <xagent>
        <name>finance</name>
        <i>%d</i>
        <j>%d</j>
        """ % (bankX,bankY))
        f.write("""<type>2</type>
        <money>%d</money>
    </xagent>
            """  % (money))

        banksList.append([bankX, bankY])
        i = i + 1




for i in xrange(12):

    firmX = random()*ix + 1
    firmY = random()*jy + 1
    money = -(random() * 100 + 1)

    f.write("""
    <xagent>
        <name>finance</name>
        <i>%d</i>
        <j>%d</j>
        """ % (firmX,firmY))
    f.write("""<type>1</type>
        <money>%d</money>
    </xagent>
        """  % (money))


# End XML file and close
f.write("""
</states>\n""")
f.close();
print "Finish Writing on %s", outfile
