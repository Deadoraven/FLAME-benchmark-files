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
mpirun -np $choice ./main $((numTurns)) 0.xml -r
;;
"2")
CSSmpdboot -n  &
wait
mpirun -np $choice ./main $((numTurns)) 0.xml -r
;;
"4")
CSSmpdboot -n  &
wait
mpirun -np $choice ./main $((numTurns)) 0.xml -r
;;
"8")
CSSmpdboot -n &
wait
mpirun -np $choice ./main $((numTurns)) 0.xml  -r
;;
*)
esac
