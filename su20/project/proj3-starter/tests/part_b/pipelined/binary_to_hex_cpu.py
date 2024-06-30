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
		ra = ''.join(hexes[:8])
		sp = ''.join(hexes[8:16])
		t0 = ''.join(hexes[16:24])
		t1 = ''.join(hexes[24:32])
		t2 = ''.join(hexes[32:40])
		s0 = ''.join(hexes[40:48])
		s1 = ''.join(hexes[48:56])
		a0 = ''.join(hexes[56:64])
		fetchAddr = ''.join(hexes[64:72])
		inst = ''.join(hexes[72:80])
		time_step = ''.join(hexes[80:84])
		result = ['ra: ', ra, 'sp: ', sp, 't0: ', t0, 't1: ', t1, 't2: ', t2, 's0: ', s0, 's1: ', s1,
			'a0: ', a0, 'PC: ', fetchAddr, 'inst: ', inst, 'Time_Step: ', time_step]
		results.append(result)
	for i in range(len(results)):
		string2 = ' '.join(results[i])
		print(string2)

if __name__ == '__main__':
	main(sys.argv)
