#!/bin/bash
# Runs the time command for all three versions of the translator
# using the provided input

echo single
time ./translator_single $1 output.gz

echo double
time ./translator_double $1 output.gz

echo triple
time ./translator $1 output.gz
