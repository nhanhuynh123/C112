from collections import defaultdict
n, s_v = input().split()
ad_list = defaultdict(dict)
for i in range(int(n)):
    v1, v2, w = input().split()
    ad_list[v1][v2] = int(w)

res = []
open = []
open.append([s_v, 0, []])
while True:
    top = open.pop(0)
    cur_v = top[0]
    cost = top[1]
    path = top[2]
    if cur_v == s_v and len(path) == len(ad_list):
        res = path + ([s_v])
        break
    if len(path) + 1 == len(ad_list):
        open.append([s_v, cost + ad_list[cur_v][s_v], path + ([cur_v])])
    else:
        for v in ad_list[cur_v]:
            if v not in path:
                open.append([v, cost + ad_list[cur_v][v], path + ([cur_v])])
    
    open.sort(key=lambda x: x[1])
    print("open")
    for i in open:
        print(i)

for i in res:
    print(i, end=" ")