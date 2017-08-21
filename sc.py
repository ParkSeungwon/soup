from konlpy.tag import Twitter
from konlpy.utils import pprint
from posix_ipc import SharedMemory
import os, sys

f = SharedMemory('sharedMEM')
sz = int(sys.argv[1])
doc = os.read(f.fd, sz)
unidoc = unicode(doc, 'utf-8')
print doc
os.close(f.fd)

pos = Twitter().pos(unidoc)
for i in pos:
    pprint(i[0])
    pprint(i[1])

