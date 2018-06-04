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

for i in xrange(ix):

    id = i + 1
    friends = []
    numFriends = (int)(random()* ix)
    index = 0
    while ( index < numFriends):
        friend = (int)(random()* ix + 1)
        if friend not in friends:
            friends.append(friend)
            index += 1
    for i in friends:
        # write agent values to file
        f.write("""<xagent>
                <name>person</name>
                <id>%d</id>
                <friends>{""" % id)
        for j in xrange(numFriends):
            if( j == numFriends - 1):
                f.write("""%d""" % friends[j])
            else:
                f.write("""%d""" % friends[j])
                f.write(""", """)
        f.write("""}</friends>
                    </xagent>""")

# End XML file and close
f.write("</states>\n")
f.close();
