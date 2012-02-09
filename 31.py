coins = [1,2,5,10,20,50,100,200]
ways = [1] + [0 for i in range (1,201)]

for c in coins:
    for x in range(c,201):
        ways[x] += ways[x-c]

print ways[200]
