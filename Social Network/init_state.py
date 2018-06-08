#!/usr/bin/env python
#
# Description:
#    Quick hack to create start states (0.xml) needed by the cellpotts abm
#	input: number of agents, number of agents per column

import re
import os
import sys
from random import random
from random import randint
from enum import Enum


outfile = "0.xml"

# We expect 2 input arguments
if len(sys.argv) <= 1:
    print >> sys.stderr, "\nUsage: %s <people>" % sys.argv[0]
    print >> sys.stderr, """ pleas add 1 integer numbers as arguments.
    More info:
    input: maxNumPpl number of People in the social network
    """
    sys.exit(1)


maxNumPpl = sys.argv[1]
print "input: ", maxNumPpl



if maxNumPpl < 5:
    print >> sys.stderr, "Error: There must be at least 5 persons"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
ix = (int)(maxNumPpl)
f = open(outfile, "w")
f.write("<states>\n   <itno>0</itno>\n")

friends = [[0 for x in xrange(ix)] for y in xrange(ix)]

for i in xrange(ix):
    for j in xrange(ix/2):
        if (i == j ):
            friends [i][j] = 0
        else :
            friends [i][j] = friends [j][i] = randint(0,1)

for i in xrange(ix):
    myfriends= []
    id = i + 1
    index = 0
    for k in xrange(len(friends[i])):
        if( friends[i][k] > 0):
            myfriends.append(k+1)

    # write agent values to file
    f.write("""
        <xagent>
            <name>person</name>
            <id>%d</id>
            <friends>{""" % id)

    for j in xrange(len(myfriends)):
        if (j == len(myfriends)-1):
            f.write("""%d""" % (myfriends[j]))
        else:
            f.write("""%d""" % (myfriends[j]))
            f.write(""", """)
    f.write("""}</friends>
        </xagent>""")

# End XML file and close
f.write("\n</states>\n")
f.close();
