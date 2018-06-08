#!/bin/sh

echo "Number of nodes? {1, 2, 4, 8}: "
read choice
echo "Number of turns? "
read numTurns

mpdallexit
case "$choice" in
"1")
CSSmpdboot -n  &
wait
mpirun -n $choice ./main $((numTurns)) 0.xml -r -f 999999+999999
;;
"2")
CSSmpdboot -n  &
wait
mpirun -n $choice ./main $((numTurns)) 0.xml -r -f 999999+999999
;;
"4")
CSSmpdboot -n  &
wait
mpirun -n $choice ./main $((numTurns)) 0.xml -r -f 999999+999999
;;
"8")
CSSmpdboot -n &
wait
mpirun -n $choice ./main $((numTurns)) 0.xml  -r -f 999999+999999
;;
*)
esac
