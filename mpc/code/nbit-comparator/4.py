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
from config import max_input_bit_length
import time

start = time.clock()
i=0
def check4(Ekx,index1,index2):
	k=0
	while(1):
		return_val=double_dec(Ekx[k],index1,index2)
		# print("return_val   ",return_val)
		# print("k=   ",k)
		# print("len Ekx",len(Ekx))
		if(return_val!=-1):
			break
		k=k+1
	return return_val
def check2(Ekx,index):
	return_val=dec(Ekx[0],index,32)
	if return_val==-1:
		return_val=dec(Ekx[1],index,32)
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


n=max_input_bit_length
f=open('inputsa.txt')
inputa=f.read().split()
f.close()
f=open('inputsb.txt')
inputb=f.read().split()
f.close()
for j in range(len(inputa)):
	inputa[j]=int(inputa[j])
for j in range(len(inputb)):
	inputb[j]=int(inputb[j])


f=open('garbled_circuits.txt')
garbled_circuits=f.read().split()
f.close()

f=open('alice_ran_keys.txt')
alice_ran_keys=f.read().split()
f.close()

Ekx=[]

Ekx=add2(garbled_circuits)
inputa[0]=check2(Ekx,inputa[0])
# print("check ",inputa[0],"   ",alice_ran_keys[16])

# i=2

Ekx=add4(garbled_circuits)
# print("check ",alltheinputs[3],"   ",alice_ran_keys[8])
inputa[0]=check4(Ekx,inputa[0],inputb[0])
# print("check ",alltheinputs[0],"   ",alice_ran_keys[20])

# i=6
Ekx=add2(garbled_circuits)
inputa[0]=check2(Ekx,inputa[0])
# print("check ",alltheinputs[0],"   ",alice_ran_keys[25])

Ekx=add2(garbled_circuits)
inputa[1]=check2(Ekx,inputa[1])
# print("check ",alltheinputs[1],"   ",alice_ran_keys[15])

Ekx=add4(garbled_circuits)
inputa[1]=check4(Ekx,inputa[1],inputb[1])
# print("check **",alltheinputs[4],"   ",alice_ran_keys[18],alice_ran_keys[19],alice_ran_keys[20])
# print("check **",alltheinputs[1],"   ",alice_ran_keys[18],alice_ran_keys[19])

Ekx=add2(garbled_circuits)
inputa[1]=check2(Ekx,inputa[1])
# print("check ---",alltheinputs[1],"   ",alice_ran_keys[23])

Ekx=add4(garbled_circuits)
inputa[0]=check4(Ekx,inputa[0],inputa[1])
# print("check mid ",alltheinputs[0],"   ",alice_ran_keys[28])

Ekx=add2(garbled_circuits)
inputb[2]=check2(Ekx,inputb[2])
# print("check ",alltheinputs[5],"   ",alice_ran_keys[13])

Ekx=add4(garbled_circuits)
inputa[2]=check4(Ekx,inputa[2],inputb[2])
# print("check --=",alltheinputs[2],"   ",alice_ran_keys[26])


Ekx=add4(garbled_circuits)
inputa[0]=check4(Ekx,inputa[0],inputa[2])



# print("the two-bit result is ",inputa[0],"  please get it to alice")
# print("check ",alltheinputs[0],"   ",alice_ran_keys[30],"  ",alice_ran_keys[31])
# print("the final result is ",inputa[0]," ",alice_ran_keys[30])

# alice check the final result
# if(inputa[0]==long(alice_ran_keys[30])):
# 	print("a<b")
# else:
# 	print("a>=b")


# print("len of alice_ran_keys  ",len(alice_ran_keys))
# print('\n')
print('\n')
if(n>2):
	for k in range(n-2):
		#augment garbled circuit
		Ekx=add2(garbled_circuits)
		inputa[3+2*k]=check2(Ekx,inputa[3+2*k])
		# print("finish one")
		# print("check ",alltheinputs[1],"   ",alice_ran_keys[15])
		 
		Ekx=add4(garbled_circuits)
		# print(Ekx)
		inputa[3+2*k]=check4(Ekx,inputa[3+2*k],inputb[3+2*k])
		# print("finish two")
		# print("check **",alltheinputs[4],"   ",alice_ran_keys[18],alice_ran_keys[19],alice_ran_keys[20])
		# print("check **",alltheinputs[1],"   ",alice_ran_keys[18],alice_ran_keys[19])

		Ekx=add2(garbled_circuits)
		inputa[3+2*k]=check2(Ekx,inputa[3+2*k])
		# print("check ---",inputa[3+2*k],"   ",alice_ran_keys[23])
		# print("----------------")
		# print("----------------")

		Ekx=add4(garbled_circuits)
		inputa[0]=check4(Ekx,inputa[0],inputa[3+2*k])
		# print("check mid ",inputa[0],"   ",alice_ran_keys[28])
		# print("finish four")

		Ekx=add2(garbled_circuits)
		inputb[4+2*k]=check2(Ekx,inputb[4+2*k])
		# print("check ",inputa[4+2*k],"   ",alice_ran_keys[13])
		# print("finish five")

		Ekx=add4(garbled_circuits)
		inputa[4+2*k]=check4(Ekx,inputa[4+2*k],inputb[4+2*k])
		# print("check --=",inputa[4+2*k],"   ",alice_ran_keys[26])
		# print("finish six")

		Ekx=add4(garbled_circuits)
		inputa[0]=check4(Ekx,inputa[0],inputa[4+2*k])

		# print("----------------------finish seven")

# print("check ",alltheinputs[0],"   ",alice_ran_keys[30],"  ",alice_ran_keys[31])
# print("the final result is ",inputa[0],"  please get it to alice")
# print(len(alice_ran_keys))
# print(alice_ran_keys)

# alice check the final result
# if(inputa[0]==long(alice_ran_keys[52])):
# 	print("a<b")
# else:
# 	print("a>=b")

print("final result is ")
if(inputa[0]==long(alice_ran_keys[32+(n-2)*22-2])):
	print("a<b")
else:
	print("a>=b")

end = time.clock()
print("Time for bob to run the circuits   ", end-start)







