def findindex(x,procs):
	# print(procs,x)
	for i in range(len(procs)):
		if(int(procs[i][0])==x):
			return(i)
	return(-1)

def bursttime(proc):
	t=0
	while(len(proc)!=0):
		t += int(proc.pop())
		proc.pop()
	return(t)

def fcfs(n,procs):
	cpuq=[]
	ipq=[]
	opq=[]
	qt=0
	totaltat = 0
	totalrt = 0
	totalwt = 0
	while(len(procs)!=0):
		i=0
		# when the process arrives
		for i in range(len(procs)):
			if(int(procs[i][2])==qt):
				
				if(procs[i][-1]=='P'):
					cpuq = [[int(procs[i][0]),int(procs[i][-2])]] + cpuq
				elif(procs[i][-1]=='I'):
					ipq = [[int(procs[i][0]),int(procs[i][-2])]] + ipq
				elif(pros[i][-1]=='O'):
					opq = [[int(procs[i][0]),int(procs[i][-2])]] + opq
				procs[i].pop()
				procs[i].pop()
		

		if(len(cpuq)!=0):
			if(cpuq[-1][1] == 0):
				ind= findindex(cpuq[-1][0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)
					temp = cpuq.pop()

				else:
					if(procs[ind][-1]=='P'):
						cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
					cpuq.pop()
			else:
				cpuq[-1][1]-=1

		if(len(ipq)!=0):
			if(len(ipq)!=0 and ipq[-1][1] == 0):
				ind= findindex(ipq[-1][0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)
					temp = ipq.pop()
					
				else:
					if(procs[ind][-1]=='P'):
						cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
					ipq.pop()
			else:
				ipq[-1][1]-=1

		if(len(opq)!=0):
			if(len(opq)!=0 and opq[-1][1] == 0):
				ind= findindex(opq[-1][0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)
					temp = opq.pop()
					
				else:
					if(procs[ind][-1]=='P'):
						cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
					opq.pop()
			else:
				opq[-1][1]-=1

		# check the start of any process
		if(len(cpuq)!=0):
			top1=cpuq[-1][0]
			ind1 = findindex(top1,procs)
			if(procs[ind1][3]==-1):
				procs[ind1][3]=qt
		
		if(len(ipq)!=0):
			top2=ipq[-1][0]
			ind2 = findindex(top2,procs)
			if(procs[ind2][3]==-1):
				procs[ind2][3]=qt
		
		if(len(opq)!=0):
			top3=opq[-1][0]
			ind3 = findindex(top3,procs)
			if(procs[ind3][3]==-1):
				procs[ind3][3]=qt
		
		# print(qt,cpuq,ipq,opq)
		qt+=1

	print("Average TAT: ",totaltat/n)
	print("Average RT: ",totalrt/n)
	print("Average WT: ",totalwt/n)


def main():
	print("First Come First Serve")
	fd = open("input.dat","r")
	fd1 = fd.readlines()
	n = int(fd1[0])
	qt = int(fd1[1])
	procs = []
	for i in fd1[2:]:
		temp = i.split()
		procs.append( temp[:3] + [-1] +[bursttime(temp[4:][::-1])]  + temp[3:][::-1])
	fcfs(n,procs)
main()