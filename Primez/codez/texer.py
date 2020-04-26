import re

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
        'DRAM_bound':'DRAMB',
        'DTLB_bound':'DTLBB',
}

codename={
        '01_erasto_single.cpp':'01_es',
        '02_most_primitive.cpp':'02_ss',
        '03_erasto_functional_static_schedule.cpp':'03_efss',
        '04_erasto_functional_handmade_scheduling.cpp':'04_efhs',
        '09_sqrt_domain.cpp':'09_sd',
        '08_sqrt_functional.cpp':'08_sf',
        '05_erasto_functional_dynamic_schedule.cpp':'05_efds',
        '07_erasto_domain.cpp':'09_ed',
}


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

    
