#!/bin/bash

echo "Usage: run.sh <suffix>"

mkdir -p result
k6 run test01.js > result/output_$(date +"%Y%m%d_%H%M%S")$1.txt
