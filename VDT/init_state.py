#!/usr/bin/env python
#
# Description:
#    Quick hack to create start states (0.xml) needed by the cellpotts abm
#    input: number of agents, number of agents per column

import re
import os
import sys
from random import random
from enum import Enum



outfile = "0.xml"

# We expect 1 input arguments
if len(sys.argv) <= 1:
    print >> sys.stderr, "\nUsage: %s <row> <column>" % sys.argv[0]
    print >> sys.stderr, """ pleas add 1 integer numbers as arguments.
        More info:
        input: P for the number projects
        """
    sys.exit(1)


projects = sys.argv[1]
print "input: ", projects



if projects < 2:
    print >> sys.stderr, "Error: There must be at least 2 projects"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
ix = (int)(projects)

f = open(outfile, "w")
f.write("<states>\n <itno>0</itno>\n")

numPhases = []

for i in xrange(ix):
    x = i + 1
    numPhases.append((int)(random() * 3) + 3)
    # write agent values to file
    f.write("""
        <xagent>
            <name>supervisor</name>
            <id>%d</id>
            <phase_id>1</phase_id>
            <total_phases>%d</total_phases>
            <fund>0</fund>
            <is_hiring>0</is_hiring>
            <employees>{}</employees>
        </xagent>""" % (x,numPhases[i]))

for i in range(len(numPhases)):
    x = i + 1
    for j in range(numPhases[i]):
        y = j + 1
        devs = (int)(random() * 3) + 1
        initMoney = (int)(random() * 500) + 1
        totMoney = devs * 1000 + initMoney

        f.write("""
    <xagent>
        <name>phase</name>
        <p_id>%d</p_id>
        <p_super_id>%d</p_super_id>
        <needed_money>%d</needed_money>
        <needed_dev>%d</needed_dev>
        <is_done>0</is_done>
    </xagent>""" % (y,x,totMoney,devs))




for i in range (20):
    x = i + 1
    f.write("""
    <xagent>
        <name>developer</name>
        <d_id>%d</d_id>
        <is_working>0</is_working>
    </xagent>""" % (x))

hqMoney = random() * 100000
f.write("""
    <xagent>
        <name>headquarter</name>
        <money>%d</money>
    </xagent>""" % (hqMoney))


# End XML file and close
f.write("""
    </states>\n""")
f.close();
print "Finish Writing on %s", outfile
