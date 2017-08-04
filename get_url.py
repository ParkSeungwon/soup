import urllib as url
import sys 

f = url.urlopen(sys.argv[1])
print f.read()
