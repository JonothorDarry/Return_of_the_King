import re

def p1(st):
    if st=='_':
        return '\_'
    if st=='%':
        return ''
    return st

def neon(fullst):
    return "".join([p1(y) for y in fullst])


lees=[]
with open("falka.txt", "r") as falk:
    for ln in falk:
        s=re.split(' ', ln);

        if s[0]=='code:':
            lees.append({})
        elif len(s)==1:
            continue
        if (s[1][-1]=='\n'):
            s[1]=s[1][:-1]


        lees[-1][s[0]]=s[1]

_=[print(x) for x in lees]
for i, x in enumerate(lees[0]):
    if (i>0):
        print("&", end=' ')
    print(neon(x), end=' ')
print('\\\\ \\hline')

for f in lees:
    for i, x in enumerate(f):
        if (i>0):
            print("&", end=' ')
        print(neon(f[x]), end=' ')
    print('\\\\ \\hline')

    
