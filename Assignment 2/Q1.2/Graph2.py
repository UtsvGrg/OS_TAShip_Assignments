import numpy as np
import matplotlib.pyplot as plt

barThick = 0.25

list_fifo = []
list_other = []
list_rr = []
f = open("f1.txt","r")
for x in f:
    temp = x.split()
    if(temp[0]=='SCHED_FIFO:'):
        list_fifo.append(float(temp[1]))
    if(temp[0]=='SCHED_RR:'):
        list_rr.append(float(temp[1]))
    if(temp[0]=='SCHED_OTHER:'):
        list_other.append(float(temp[1]))

br1 = np.arange(len(list_fifo))
br2 = [x + barThick for x in br1]
br3 = [x + barThick for x in br2]

plt.bar(br1,list_fifo,color='r',width=barThick,label="FIFO")
plt.bar(br2,list_rr,color='b',width=barThick,label="RR")
plt.bar(br3,list_other,color='g',width=barThick,label="OTHER")
plt.ylabel("Time Taken")
plt.legend()
plt.show()