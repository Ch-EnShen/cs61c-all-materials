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
		ra = ''.join(hexes[2:10])
		sp = ''.join(hexes[10:18])
		t0 = ''.join(hexes[18:26])
		t1 = ''.join(hexes[26:34])
		t2 = ''.join(hexes[34:42])
		s0 = ''.join(hexes[42:50])
		s1 = ''.join(hexes[50:58])
		a0 = ''.join(hexes[58:66])
		readData1 = ''.join(hexes[66:74])
		readData2 = ''.join(hexes[74:82])
		rs1 = ''.join(hexes[82:84])
		rs2 = ''.join(hexes[84:86])
		rd = ''.join(hexes[86:88])
		regWEn = ''.join(hexes[88:89])
		writeData = ''.join(hexes[89:97])
		result = [op,rd,rs1,rs2,regWEn,writeData,ra,sp,t0,t1,t2,s0,s1,a0,readData1,readData2]
		results.append(result)
	print('Op#\trd\trs1\trs2\tRegWEn\tWriteData\tra (x1)\t\tsp (x2)\t\tt0 (x5)\t\tt1 (x6)\t\tt2 (x7)\t\ts0 (x8)\t\ts1 (x9)\t\ta0 (x10)\tReadData1\tReadData2')
	for r in results:
		string = '\t'.join(r)
		print(string)

if __name__ == '__main__':
	main(sys.argv)
