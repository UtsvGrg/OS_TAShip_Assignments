import numpy as np
import matplotlib.pyplot as plt

barThick = 0.25

list_fifo = []
priority = []
list_other = []
list_rr = []
f = open("fileopen.txt","r")
for x in f:
    temp = x.split()
    if(temp[0]=='f:'):
        list_fifo.append(float(temp[1]))
        priority.append(int(temp[2]))
    if(temp[0]=='r:'):
        list_rr.append(float(temp[1]))
    if(temp[0]=='o:'):
        list_other.append(float(temp[1]))

br1 = np.arange(len(list_fifo))
br2 = [x + barThick for x in br1]
br3 = [x + barThick for x in br2]

plt.bar(br1,list_fifo,color='r',width=barThick,label="FIFO")
plt.bar(br2,list_rr,color='b',width=barThick,label="RR")
plt.bar(br3,list_other,color='g',width=barThick,label="OTHER")
plt.xlabel("Priority")
plt.ylabel("Time Taken")
plt.xticks([r + barThick for r in range(len(list_fifo))],priority)
plt.legend()
plt.show()