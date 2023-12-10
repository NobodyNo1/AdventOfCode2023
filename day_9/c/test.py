lines = open("input.txt","rt").read().splitlines()

def f1(a):
  if a[0]==a[1]==a[-1]:
    return a[-1]
  return a[-1]+f1([a[i]-a[i-1] for i in range(1,len(a))])

print(sum(f1([int(e) for e in l.split()]) for l in lines))

def f2(a):
  if a[0]==a[1]==a[-1]:
    return a[0]
  return a[0]-f2([a[i]-a[i-1] for i in range(1,len(a))])

print(sum(f2([int(e) for e in l.split()]) for l in lines))