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
    print >> sys.stderr, "\nUsage: %s <number of clusters>" % sys.argv[0]
    print >> sys.stderr, """ pleas add 1 integer numbers as arguments.
    More info:
    input: X number of clusters
    """
    sys.exit(1)


clusters = sys.argv[1]
print "input: ", clusters



if clusters < 2:
    print >> sys.stderr, "Error: There must be at least 2 clusters"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
ix = (int) (clusters)

f = open(outfile, "w")
f.write("<states>\n <itno>0</itno>\n")

id = 0

for i in xrange(ix):
    id += 1
        # write agent values to file
    f.write("""
    <xagent>
        <name>cluster</name>
        <id>%d</id>
        """ % (id))
    f.write("""<hasbank>0</hasbank>
        <destination>-1</destination>
    </xagent>
            """)


i = 0
banksList = []

while (i < 450):
    bankCID = (int)(random() * ix) + 1
    if bankCID not in banksList:
        money = random() * 1000 + 1

        f.write("""
    <xagent>
        <name>finance</name>
        <c_id>%d</c_id>
        """ % (bankCID))
        f.write("""<type>2</type>
        <money>%d</money>
    </xagent>
            """  % (money))

        banksList.append(bankCID)
        i = i + 1




for i in xrange(4500):

    firmCID = random()*ix + 1
    money = -(random() * 100 + 1)

    f.write("""
    <xagent>
        <name>finance</name>
        <c_id>%d</c_id>
        """ % (firmCID))
    f.write("""<type>1</type>
        <money>%d</money>
    </xagent>
        """  % (money))


# End XML file and close
f.write("""
</states>\n""")
f.close();
print "Finish Writing on %s", outfile
