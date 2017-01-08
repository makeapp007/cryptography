# bob: runs the garbled circuits
# all the input is stored in the inputs.txt
# the circuits are stored in garbled_circuits.txt
# demo for two bits comparison


from public_method import *
import random
import random
import Crypto
from Crypto.PublicKey import RSA
from Crypto import Random
import ast
import pyDes
from Crypto.Cipher import DES

i=0
def check4(Ekx,alltheinputs,index1,index2):
	k=0
	while(1):
		return_val=double_dec(Ekx[k],alltheinputs[index1],alltheinputs[index2])
		# print("return_val   ",return_val)
		# print("k=   ",k)
		# print("len Ekx",len(Ekx))
		if(return_val!=-1):
			break
		k=k+1
	return return_val
def check2(Ekx,alltheinputs,index):
	return_val=dec(Ekx[0],alltheinputs[index],32)
	if return_val==-1:
		return_val=dec(Ekx[1],alltheinputs[index],32)
	return return_val

def add4(garbled_circuits):
	global i
	Ekx=[]
	Ekx.append(long(garbled_circuits[i][1:-1]))
	i=i+1
	Ekx.append(long(garbled_circuits[i][0:-1]))
	i=i+1
	Ekx.append(long(garbled_circuits[i][0:-1]))
	i=i+1
	Ekx.append(long(garbled_circuits[i][0:-1]))
	i=i+1
	return Ekx	

def add2(garbled_circuits):
	global i
	Ekx=[]
	Ekx.append(long(garbled_circuits[i][1:-1]))
	i=i+1
	Ekx.append(long(garbled_circuits[i][0:-1]))
	i=i+1
	return Ekx


n=2
f=open('inputs.txt')
alltheinputs=f.read().split()
f.close()
for j in range(len(alltheinputs)):
	alltheinputs[j]=int(alltheinputs[j])


f=open('garbled_circuits.txt')
garbled_circuits=f.read().split()
f.close()

f=open('alice_ran_keys.txt')
alice_ran_keys=f.read().split()
f.close()

Ekx=[]

Ekx=add2(garbled_circuits)
alltheinputs[0]=check2(Ekx,alltheinputs,0)
print("check ",alltheinputs[0],"   ",alice_ran_keys[16])

# i=2

Ekx=add4(garbled_circuits)
# print("check ",alltheinputs[3],"   ",alice_ran_keys[8])
alltheinputs[0]=check4(Ekx,alltheinputs,0,3)
# print("check ",alltheinputs[0],"   ",alice_ran_keys[20])

# i=6
Ekx=add2(garbled_circuits)
alltheinputs[0]=check2(Ekx,alltheinputs,0)
# print("check ",alltheinputs[0],"   ",alice_ran_keys[25])

Ekx=add2(garbled_circuits)
alltheinputs[1]=check2(Ekx,alltheinputs,1)
# print("check ",alltheinputs[1],"   ",alice_ran_keys[15])

Ekx=add4(garbled_circuits)
alltheinputs[1]=check4(Ekx,alltheinputs,1,4)
# print("check **",alltheinputs[4],"   ",alice_ran_keys[18],alice_ran_keys[19],alice_ran_keys[20])
# print("check **",alltheinputs[1],"   ",alice_ran_keys[18],alice_ran_keys[19])

Ekx=add2(garbled_circuits)
alltheinputs[1]=check2(Ekx,alltheinputs,1)
# print("check ---",alltheinputs[1],"   ",alice_ran_keys[23])

Ekx=add4(garbled_circuits)
alltheinputs[0]=check4(Ekx,alltheinputs,0,1)
# print("check mid ",alltheinputs[0],"   ",alice_ran_keys[28])

Ekx=add2(garbled_circuits)
alltheinputs[5]=check2(Ekx,alltheinputs,5)
# print("check ",alltheinputs[5],"   ",alice_ran_keys[13])

Ekx=add4(garbled_circuits)
alltheinputs[2]=check4(Ekx,alltheinputs,2,5)
# print("check --=",alltheinputs[2],"   ",alice_ran_keys[26])


Ekx=add4(garbled_circuits)
alltheinputs[0]=check4(Ekx,alltheinputs,0,2)



print("the two-bit result is ",alltheinputs[0],"  please get it to alice")
# print("check ",alltheinputs[0],"   ",alice_ran_keys[30],"  ",alice_ran_keys[31])
print("the final result is ",alltheinputs[0]," ",alice_ran_keys[30])

# alice check the final result
if(alltheinputs[0]==long(alice_ran_keys[30])):
	print("a<b")
else:
	print("a>=b")

if(n>2):
	#augment garbled circuit
	Ekx=add2(garbled_circuits)
	alltheinputs[6]=check2(Ekx,alltheinputs,6)
	# print("check ",alltheinputs[1],"   ",alice_ran_keys[15])
	 
	Ekx=add4(garbled_circuits,i)
	alltheinputs[6]=check4(Ekx,alltheinputs,6,8)
	# print("check **",alltheinputs[4],"   ",alice_ran_keys[18],alice_ran_keys[19],alice_ran_keys[20])
	# print("check **",alltheinputs[1],"   ",alice_ran_keys[18],alice_ran_keys[19])

	Ekx=add2(garbled_circuits)
	alltheinputs[6]=check2(Ekx,alltheinputs,6)
	# print("check ---",alltheinputs[1],"   ",alice_ran_keys[23])


	Ekx=add4(garbled_circuits)
	alltheinputs[0]=check4(Ekx,alltheinputs,0,6)
	# print("check mid ",alltheinputs[0],"   ",alice_ran_keys[28])

	Ekx=add2(garbled_circuits)
	alltheinputs[9]=check2(Ekx,alltheinputs,9)
	# print("check ",alltheinputs[5],"   ",alice_ran_keys[13])

	Ekx=add4(garbled_circuits)
	alltheinputs[6]=check4(Ekx,alltheinputs,6,9)
	# print("check --=",alltheinputs[2],"   ",alice_ran_keys[26])


	Ekx=add4(garbled_circuits)
	alltheinputs[0]=check4(Ekx,alltheinputs,0,6)



	# print("check ",alltheinputs[0],"   ",alice_ran_keys[30],"  ",alice_ran_keys[31])
	print("the final result is ",alltheinputs[0],"  please get it to alice")

	# alice check the final result
	if(alltheinputs[0]==long(alice_ran_keys[52])):
		print("a<b")
	else:
		print("a>=b")







