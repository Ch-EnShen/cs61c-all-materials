#!/usr/bin/env python3

from __future__ import print_function

import sys

def main(args):
	file = open(args[1])
	lines = [l for l in file.readlines()]
	def mapper(string):
		try:
			return hex(int(string, 2))[2:]
		except Exception:
			return 'x'
	results = []
	for l in lines:
		hexes = list(map(mapper, l.split()))
		op = ''.join(hexes[:2])
		aluOutput = ''.join(hexes[2:10])
		aluSel = ''.join(hexes[10:11])
		inputA = ''.join(hexes[11:19])
		inputB = ''.join(hexes[19:27])
		result = [op, aluSel, inputA, inputB, aluOutput]
		results.append(result)
	print('Op#\tALUSel\tInputA\t\tInputB\t\tALU_Output')
	for r in results:
		string = '\t'.join(r)
		print(string)

if __name__ == '__main__':
	main(sys.argv)
