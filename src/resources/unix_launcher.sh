#!/bin/bash

# Template for launching on unix. 
# Solves problem of force closing
# http://stackoverflow.com/questions/18279540/bash-shutdown-hook-or-kill-all-background-processes-when-main-process-is-kille

trap 'jobs -p | xargs kill' EXIT  # part of the solution

{} &

# other part of the solution:
while pgrep -P "$BASHPID" > /dev/null; do
  wait
done
