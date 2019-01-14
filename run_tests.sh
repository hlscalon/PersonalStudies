#!/bin/bash

for arq in $(find build -iname "*.out"); do
	./${arq}
done
