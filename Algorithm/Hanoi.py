#汉诺塔问题求解

counts = 1
#递归求解
def hanoiSolve(num,sourse,target,auxiliary):
    global counts
    if num == 1:
        print("[STEP  {:>2}] {}->{}".format(counts,sourse,target))
        counts = counts + 1
    else:
        hanoiSolve(num-1,sourse,auxiliary,target)
        print("[STEP  {:>2}] {}->{}".format(counts,sourse,target))
        counts = counts + 1
        hanoiSolve(num-1,auxiliary,target,sourse)

number = eval(input())
hanoiSolve(number,'A','C','B')