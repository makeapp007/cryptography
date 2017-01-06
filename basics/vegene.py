#substitution
import operator

input_='''CHREEVOAHMAERATBIAXXWTNXBEEOPHBSBQMQEQERBWRVXUOAKXAOSXXWEAHBWGJMMQMNKGRFVGXWTRZXWIAKLXFPSKAUTEMNDCMGTSXMXBTUIADNGMGPSRELXNJELXVRVPRTULHDNQWTWDTYGBPHXTFALJHASVBFXNGLLCHRZBWELEKMSJIKNBHWRJGNMGJSGLXFEYPHAGNRBIEQJTAMRVLCRREMNDGLXRRIMGNSNRWCHRQHAEYEVTAQEBBIPEEWEVKAKOEWADREMXMTBHHCHRTKDNVRZCHRCLQOHPWQAIIWXNRMGWOIIFKEE'''

print input_     

checkSet={}
length=len(input_)
for i in range(0,length):
	if input_[i] in checkSet:
		checkSet[input_[i]]+=1
	else:
		checkSet[input_[i]]=1


twoset={}
for i in range(0,length):
    try:
        sear=input_[i]+input_[i+1]
        if sear in twoset:
            twoset[sear]+=1
        else:
            twoset[sear]=1
    except:
        pass
#print twoset

sorted_x = sorted(twoset.items(), key=operator.itemgetter(1))
print sorted_x


threeset={}
for i in range(0,length):
    try:
        sear=input_[i]+input_[i+1]+input_[i+2]
        if sear in threeset:
            threeset[sear]+=1
        else:
            threeset[sear]=1
    except:
        pass
#print threeset

sorted_x = sorted(threeset.items(), key=operator.itemgetter(1))
print sorted_x

fourset={}
for i in range(0,length):
    try:
        sear=input_[i]+input_[i+1]+input_[i+2]+input_[i+3]
        if sear in fourset:
            fourset[sear]+=1
        else:
            fourset[sear]=1
    except:
        pass
#print fourset

sorted_x = sorted(fourset.items(), key=operator.itemgetter(1))
print sorted_x

key="janet"
final=""
for i in range(0,length,5):
#    input_[i].lower()
    try:
        thestring=""
        distance=ord(input_[i].lower())-ord(key[0])
        distance%=26
        offset=ord("a")
        output=chr(offset+distance)
        final+=output
        thestring+=output
        distance=ord(input_[i+1].lower())-ord(key[1])
        distance%=26
        offset=ord("a")
        output=chr(offset+distance)
        final+=output
        thestring+=output
        distance=ord(input_[i+2].lower())-ord(key[2])
        distance%=26
        offset=ord("a")
        output=chr(offset+distance)
        final+=output
        distance=ord(input_[i+3].lower())-ord(key[3])
        distance%=26
        offset=ord("a")
        output=chr(offset+distance)
        final+=output
        distance=ord(input_[i+4].lower())-ord(key[4])
        distance%=26
        offset=ord("a")
        output=chr(offset+distance)
        final+=output
    except:
        pass

print("plaintext:  ",final)

    
# output
# the almond tree was intentative blossom the days were longer often ending with magnificent evenings of corrugated pink skies the hunting season was over with hounds and guns put away for six months the vineyards were busy again as the well organized farmers treated their vines and the more lackadaisical neighbor shurried to do the pruning they should have done in november





