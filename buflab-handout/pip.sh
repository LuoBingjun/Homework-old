#!/bin/bash
cat "$@" | ./hex2raw | ./bufbomb -u 2017013573