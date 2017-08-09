import urllib as url
import sys, ssl

context = ssl._create_unverified_context()
f = url.urlopen(sys.argv[1], context=context)
print f.read()
