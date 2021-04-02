class Heap:
	def __init__(self):
		self.heap = []
	def insert(self,key):
		
		self.heap.append(key)
		# print(self.heap)
		i=len(self.heap)-1
		while(i>0 and self.heap[i//2][1]>key[1]):
			self.heap[i][1]=self.heap[i//2][1]
			i=i//2
		self.heap[i][1]=key[1]
		# print(self.heap)

	def deletemax(self):
		# print(self.heap)
		n=len(self.heap)
		self.heap[1][1],self.heap[len(self.heap)-1][1]=self.heap[len(self.heap)-1][1],self.heap[1][1]
		x=self.heap.pop(-1)
		i=1
		while(i<n):
			l=2*i
			r=2*i+1
			if(l<len(self.heap) and self.heap[l][1]<self.heap[i][1]):
				gt=l
			else:
				gt=i
			if(r<len(self.heap) and self.heap[r][1]<self.heap[gt][1]):
				gt=r
			if(gt!=i):
				self.heap[i][1],self.heap[gt][1]=self.heap[gt][1],self.heap[i][1]
				i=gt
			else:
				break
		return(x)

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

def sjf(n,procs):
	cpuq=Heap()
	ipq=Heap()
	opq=Heap()
	cpuq.heap.append([-1,-1])
	ipq.heap.append([-1,-1])
	opq.heap.append([-1,-1])
	ccwp = []
	icwp = []
	ocwp = []
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
					cpuq.insert([int(procs[i][0]),int(procs[i][-2])])
				elif(procs[i][-1]=='I'):
					ipq.insert([int(procs[i][0]),int(procs[i][-2])])
					# ipq = [[int(procs[i][0]),int(procs[i][-2])]] + ipq
				elif(pros[i][-1]=='O'):
					opq.insert([int(procs[i][0]),int(procs[i][-2])])
					# opq = [[int(procs[i][0]),int(procs[i][-2])]] + opq
				procs[i].pop()
				procs[i].pop()
				if(len(ccwp)==0 and len(cpuq.heap)>1):
					ccwp = cpuq.deletemax()
				if(len(icwp)==0 and len(ipq.heap)>1):
					icwp = ipq.deletemax()
				if(len(ocwp)==0 and len(opq.heap)>1):
					ocwp = opq.deletemax()
				
		
		# print(qt,ccwp,cpuq.heap,icwp,ipq.heap,ocwp,opq.heap)
		if(len(ccwp)==0):
			if(len(cpuq.heap)>1):
				ccwp = cpuq.deletemax()
		else:
			if(ccwp[1]==0):
				ind= findindex(ccwp[0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)

				else:
					if(procs[ind][-1]=='P'):
						cpuq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
				if(len(cpuq.heap)>1):
					ccwp = cpuq.deletemax()
				else:
					ccwp=[]
					
		if(len(ccwp)!=0):
			ccwp[1]-=1
				
		if(len(icwp)==0):
			if(len(ipq.heap)>1):
				icwp = ipq.deletemax()
		else:
			if(icwp[1]==0):
				ind= findindex(icwp[0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)

				else:
					if(procs[ind][-1]=='P'):
						cpuq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
				if(len(ipq.heap)>1):
					icwp = ipq.deletemax()
				else:
					icwp = []
		if(len(icwp)!=0):
			icwp[1]-=1

		if(len(ocwp)==0):
			if(len(opq.heap)>1):
				ocwp = opq.deletemax()
		else:
			if(ocwp[1]==0):
				ind= findindex(ocwp[0],procs)
				if(procs[ind][-1]=='-1'):
					tat = qt - int(procs[ind][2])
					wt = tat - procs[ind][4]
					rt = int(procs[ind][3])-int(procs[ind][2])
					totaltat += tat
					totalrt += rt
					totalwt += wt
					print("At time",qt," Process ",procs[ind][0],"ends. TAT time: ",tat,"Response time: ",rt,"Waiting time: ",wt)
					procs.pop(ind)

				else:
					if(procs[ind][-1]=='P'):
						cpuq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# cpuq=[[int(procs[ind][0]),int(procs[ind][-2])]] + cpuq
					elif(procs[ind][-1]=='I'):
						ipq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# ipq = [[int(procs[ind][0]),int(procs[ind][-2])]] + ipq
					elif(procs[ind][-1]=='O'):
						opq.insert([int(procs[ind][0]),int(procs[ind][-2])])
						# opq = [[int(procs[ind][0]),int(procs[ind][-2])]] + opq
					procs[ind].pop()
					procs[ind].pop()
				if(len(opq.heap)>1):
					ocwp = opq.deletemax()
				else:
					ocwp = []
		if(len(ocwp)!=0):
			ocwp[1]-=1

		# check the start of any process
		if(len(ccwp)!=0):
			top1=ccwp[0]
			ind1 = findindex(top1,procs)
			if(procs[ind1][3]==-1):
				procs[ind1][3]=qt
		
		if(len(icwp)!=0):
			top2=icwp[0]
			ind2 = findindex(top2,procs)
			if(procs[ind2][3]==-1):
				procs[ind2][3]=qt
		
		if(len(ocwp)!=0):
			top3=ocwp[0]
			ind3 = findindex(top3,procs)
			if(procs[ind3][3]==-1):
				procs[ind3][3]=qt
		
		# print(qt,cpuq,ipq,opq)
		qt+=1

	print("Average TAT: ",totaltat/n)
	print("Average RT: ",totalrt/n)
	print("Average WT: ",totalwt/n)





def main():
	print("Short Job First")
	fd = open("input.dat","r")
	fd1 = fd.readlines()
	n = int(fd1[0])
	qt = int(fd1[1])
	procs = []
	for i in fd1[2:]:
		temp = i.split()
		procs.append( temp[:3] + [-1] + [bursttime(temp[4:][::-1])] + temp[3:][::-1])
	sjf(n,procs)
main()
