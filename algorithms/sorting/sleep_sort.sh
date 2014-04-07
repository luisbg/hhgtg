#!/bin/bash
sleepsort() {
    while [ -n "$1" ]
    do
       (sleep "$1"; echo "$1") &
       shift
    done
    wait
}
sleepsort "$@"

# run: sh sleepsort 6 3 1 2 3 4 5
# hahahahahaha
