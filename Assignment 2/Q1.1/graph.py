from matplotlib import pyplot as plt
list_fifo = []
priority_fifo = []
list_other = []
priority_other = []
list_rr = []
priority_rr = []
f = open("fileopen.txt","r")
for x in f:
    temp = x.split()
    if(temp[0]=='f:'):
        list_fifo.append(float(temp[1]))
        priority_fifo.append(int(temp[2]))
    if(temp[0]=='r:'):
        list_rr.append(float(temp[1]))
        priority_rr.append(int(temp[2]))
    if(temp[0]=='o:'):
        list_other.append(float(temp[1]))
        priority_other.append(int(temp[2]))
plt.plot(priority_fifo,list_fifo)
plt.xlabel("FIFO Priority Graph")
plt.ylabel("Time (s)")
plt.show()
plt.plot(priority_rr,list_rr)
plt.xlabel("RR Priority Graph")
plt.ylabel("Time (s)")
plt.show()
plt.plot(priority_other,list_other)
plt.xlabel("Other Priority Graph")
plt.ylabel("Time (s)")
plt.show()