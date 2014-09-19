#!/bin/bash
# Generates a file of $1 bytes and compresses using gzip
cat /dev/urandom | tr -dc 'a-zA-Z' | head -c $1 | gzip > $1text.gz
