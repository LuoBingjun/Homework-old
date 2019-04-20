#!/bin/bash
cat "$@" | ./hex2raw -n | ./bufbomb -n -u 2017013573