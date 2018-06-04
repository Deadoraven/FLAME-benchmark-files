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

# We expect 1 input arguments
if len(sys.argv) <= 1:
    print >> sys.stderr, "\nUsage: %s <cars><places>" % sys.argv[0]
    print >> sys.stderr, """ please add 2 integer numbers as arguments.
    More info:
    input: C for the number of cars and P for the number prlaces
    """
    sys.exit(1)


cars, places  = map(int, sys.argv[1:])
print "input: ", cars, places


if places < 3:
    print >> sys.stderr, "Error: There must be at least 3 place"
    sys.exit(1)

if cars < 5:
    print >> sys.stderr, "Error: There must be at least 5 cars"
    sys.exit(1)
# Open file and write preamble
print "Writing to file %s ... " % outfile

do_stiff_edge=False
ix = cars
iy = places

f = open(outfile, "w")
f.write("<states>\n <itno>0</itno>\n")


matrix = [[0 for x in xrange(iy)] for y in xrange(iy)]

for i in xrange(iy):
    for j in xrange(iy/2):
        if (i == j ):
            matrix [i][j] = 0
        else :
            matrix[i][j] = matrix [j][i] = (int)(random() * 60)



for i in xrange(iy):


    y = i + 1
    # write agent values to file
    f.write("""
    <xagent>
        <name>place</name>
        <p_id>%d</p_id>
        <num_cars>1</num_cars>
        <paths_found>0</paths_found>
        <destinations>{""" % y)

    for j in xrange(len(matrix[i])):

        if(j == len(matrix[i]) - 1):
            f.write("""%d""" % matrix[i][j])
        else:
            f.write("""%d""" % matrix[i][j])
            f.write(""", """)
    f.write("""}</destinations>
    </xagent>""")


for j in range(ix):
    final_dest = 0
    currPlace = 0
    x = j + 1
    while (final_dest == currPlace):
        final_dest = (int)(random()* iy + 1)
        currPlace = (int)(random()* iy + 1)


    f.write("""
    <xagent>
        <name>car</name>
        <c_id>%d</c_id>
        <current_place>%d</current_place>
        <final_dest>%d</final_dest>
        <path_received>0</path_received>
        <path>{}</path>
    </xagent>""" % (x,currPlace,final_dest))


# End XML file and close
f.write("""
</states>\n""")
f.close();
print "Finish Writing on %s", outfile
