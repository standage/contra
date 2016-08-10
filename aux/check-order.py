#!/usr/bin/env python
import sys

data = next(sys.stdin)
lastvalue = None
for value in data.split():
    if value in ['[', ']']:
        continue
    val = int(value)
    if lastvalue is not None:
        assert lastvalue < val
    lastvalue = val
sys.stdout.write('Valid!\n')
