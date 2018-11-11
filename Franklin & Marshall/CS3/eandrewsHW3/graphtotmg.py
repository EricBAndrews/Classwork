import sys
import math

if len(sys.argv) < 4:
    print("Too few arguments. Usage: python3 roadmap.py <graph file> <original tmg file> <output file>")
    exit(1)
    
graphIn = open(sys.argv[1])
tmgIn = open(sys.argv[2])
fout = open(sys.argv[3], 'w')

#Write the version line
fout.write(tmgIn.readline())

#Get the number of vertices and edges
graphNums = graphIn.readline()
tmgNums = tmgIn.readline()
graphNumV = int(graphNums.split()[0])
tmgNumV = int(tmgNums.split()[0])

if graphNumV != tmgNumV:
    print("Warning: Number of vertices is not the same! Using tmg's vertices...")

numE = int(graphNums.split()[1])

names = []

#Get the vertices
for i in range(max(graphNumV, tmgNumV)):
    if i < graphNumV:
        graphV = graphIn.readline()
    if i < tmgNumV:
        tmgV = tmgIn.readline()
    tmgName = tmgV.split()[0]
    if tmgName != graphV.strip():
        print("Warning: Vertices do not match. Using tmg's vertices...")
        
    names.append(tmgV)

#Get the edges
edges = {}
for i in range(numE):
    l = graphIn.readline()
    edge = l.split()
    e = edge[:2]
    e.sort()
    e = tuple(e)
    if e in edges:
        if edges[e] != edge[3]:
            print("Warning: bi-directional edge with mismatching labels. Using first weight encountered...")
    else:
        edges[e] = edge[3]

#Print the number of vertices and edges
fout.write(str(tmgNumV) + " " + str(len(edges)) + "\n")

#Print the vertices
for v in names:
    fout.write(v)
        
#Print the edges    
for e in edges:
    src = e[0]
    dest = e[1]
    label = edges[e]
    
    fout.write(str(src) + " " + str(dest) + " " + label + "\n")

