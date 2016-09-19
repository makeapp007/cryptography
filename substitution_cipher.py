#substitution

input_='''JGRMQOYGHMVBJWRWQFPWHGFFDQGFPFZRKBEEBJIZQQOCIBZKLFAFGQVFZFWWEOGWOPFGFHWOLPHLRLOLFDMFGQWBLWBWQOLKFWBYLBLYLFSFLJGRMQBOLWJVFPFWQVHQWFFPQOQVFPQOCFPOGFWFJIGFQVHLHLROQVFGWJVFPFOLFHGQVQVFILEOGQILHQFQGIQVVOSFAFGBWQVHQWIJVWJVFPFWHGFIWIHZZRQGBABHZQOCGFHX'''

print input_     

checkSet={}
length=len(input_)
for i in range(0,length):
	if input_[i] in checkSet:
		checkSet[input_[i]]+=1
	else:
		checkSet[input_[i]]=1

# print checkSet['A']
# print checkSet
# {'A': 3, 'C': 3, 'B': 12, 'E': 4, 'D': 2, 'G': 19, 'F': 37, 'I': 9, 'H': 14, 'K': 3, 'J': 9, 'M': 4, 'L': 17, 'O': 16, 'Q': 26, 'P': 10, 'S': 2, 'R': 7, 'W': 21, 'V': 15, 'Y': 3, 'X': 1, 'Z': 7}
input_=input_.replace("F","e")
# print input_
# JGRMQOYGHMVBJWRWQePWHGeeDQGePeZRKBEEBJIZQQOCIBZKLeAeGQVeZeWWEOGWOPeGeHWOLPHLRLOLeDMeGQWBLWBWQOLKeWBYLBLYLeSeLJGRMQBOLWJVePeWQVHQWeePQOQVePQOCePOGeWeJIGeQVHLHLROQVeGWJVePeOLeHGQVQVeILEOGQILHQeQGIQVVOSeAeGBWQVHQWIJVWJVePeWHGeIWIHZZRQGBABHZQOCGeHX
theset={}
for i in range(0,length):
	if input_[i]=="e":
		try:
			sear=input_[i-2]+input_[i-1]+input_[i]
			if sear in theset:
				theset[sear]+=1
			else:
				theset[sear]=1
		except:
			pass
print theset
# {'OLe': 2, 'Wee': 1, 'QVe': 4, 'CGe': 1, 'ePe': 4, 'OSe': 1, 'eGe': 1, 'DMe': 1, 'LKe': 1, 'OCe': 1, 'YLe': 1, 'Gee': 1, 'eZe': 1, 'QGe': 1, 'HQe': 1, 'QWe': 1, 'eWe': 1, 'OPe': 1, 'eSe': 1, 'OGe': 1, 'WQe': 1, 'KLe': 1, 'eAe': 2, 'IGe': 1, 'HGe': 2, 'JVe': 3}
input_=input_.replace("Q","t")
input_=input_.replace("V","h")
print input_
# JGRMtOYGHMhBJWRWtePWHGeeDtGePeZRKBEEBJIZttOCIBZKLeAeGtheZeWWEOGWOPeGeHWOLPHLRLOLeDMeGtWBLWBWtOLKeWBYLBLYLeSeLJGRMtBOLWJhePeWthHtWeePtOthePtOCePOGeWeJIGethHLHLROtheGWJhePeOLeHGththeILEOGtILHtetGIthhOSeAeGBWthHtWIJhWJhePeWHGeIWIHZZRtGBABHZtOCGeHX

twoset={}
for i in range(0,length):
	try:
		sear=input_[i]+input_[i+1]
	except:
		pass
	finally:
		if sear in twoset:
			twoset[sear]+=1
		else:
			twoset[sear]=1
print twoset
import operator
sorted_x = sorted(twoset.items(), key=operator.itemgetter(1))
print sorted_x





