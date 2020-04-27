import re
import sys

def p1(st):
    if st=='_':
        return '\_'
    if st=='%':
        return ''
    return st

def neon(fullst):
    return "".join([p1(y) for y in fullst])

reduct={
        'code:': 'name',
        'left_right:': 'LR',
        'threads:':'T',
        'Retired':'R',
        'Instructions_Retired':'IR',
        'Front-End_bound':'FEB',
        'Bront-End_bound':'BEB',
        'Memory_bound':'MB',
        'Core_bound':'CB',
        'L1_bound':'L1',
        'L2_bound':'L2',
        'L3_bound':'L3',
        'DRAM_bound':'DRB',
        'DTLB_bound':'DTB',
        'Effective_Cpu':'ECPU',
}

codename={
        '01_erasto_single.cpp':'01_es',
        '02_most_primitive.cpp':'02_ss',
        '03_erasto_functional_static_schedule.cpp':'03_efss',
        '04_erasto_functional_handmade_scheduling.cpp':'04_efhs',
        '05_erasto_functional_dynamic_schedule.cpp':'05_efds',
        '09_sqrt_domain.cpp':'09_sd',
        '07_erasto_domain.cpp':'07_ed',
        '08_erasto_super_domain.cpp':'08_esd'
}
if (len(sys.argv)>1):
    tfile=sys.argv[1]
else:
    tfile='falka.txt'


lees=[]
with open(tfile, "r") as falk:
    for ln in falk:
        s=re.split(' ', ln);

        if s[0]=='code:':
            lees.append({})
        elif len(s)==1:
            continue
        if (s[1][-1]=='\n'):
            s[1]=s[1][:-1]

        if (s[0]=='left_right:'):
            if (s[2][-1]=='\n'):
                s[2]=s[2][:-1]
            lees[-1]['left']=s[1]
            lees[-1]['right']=s[2]
        else:
            lees[-1][s[0]]=s[1]


mn=1000000
for f in lees:
    f['Elapsed']=float(f['Elapsed'])
    if f['Elapsed']<mn:
        mn=f['Elapsed']

for f in lees:
    f['Div']=f['Elapsed']/mn
    f['Eff']=f['Div']/float(f['threads:'])
    f['Avg']=(float(f['right'])-float(f['left']))/f['Elapsed']

for f in lees:
    for x in f:
        try:
            f[x]=float(f[x])
            if (f[x]>10000):
                f[x]=f"{f[x]:.2E}"
            elif len(str(f[x]))>6:
                f[x]=f"{f[x]:.2f}"
        except:
            pass
        f[x]=str(f[x])



_=[print(x) for x in lees]
for i, x in enumerate(lees[0]):
    if (i>0):
        print("&", end=' ')
    if (x in reduct):
        x=reduct[x]
    print(neon(x), end=' ')
print('\\\\ \\hline')


for f in lees:
    for i, x in enumerate(f):
        if (i>0):
            print("&", end=' ')
        elif (f[x] in codename):
            f[x]=codename[f[x]]
        print(neon(f[x]), end=' ')
    print('\\\\ \\hline')

    
