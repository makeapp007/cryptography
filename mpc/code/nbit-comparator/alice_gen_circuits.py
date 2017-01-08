#generate the garbled circuits using the public_method
# write inputs.txt, garbled_circuits.txt
from public_method import *
import random
import random
import Crypto
from Crypto.PublicKey import RSA
from Crypto import Random
import ast
import pyDes
import time
from Crypto.Cipher import DES
from config import max_input_bit_length

# this is alice's input
print("please input alice's data  ")
print("The input data should be in the decimal form like. ")
alice_bit=int(input())
print("alice input: ",alice_bit)
# alice_bit=0b11



start = time.clock()
n=max_input_bit_length
#loading public key
# publickeyfile=""
# with open('bob-public.pem', 'r') as f:
# 	publickeyfile=f.read()
# print(publickeyfile)
# publickey=RSA.importKey(publickeyfile)
# encrypted = publickey.encrypt('encrypt this message', 32)
# print 'encrypted message: ', encrypted #ciphertext

f=open('alice_ran_keys.txt')
alice_ran_keys=f.read().split()
f.close()
for i in range(len(alice_ran_keys)):
	alice_ran_keys[i]=int(alice_ran_keys[i])

with open('inputsa.txt', 'w') as f:
	a0=alice_bit&0b1
	a1=alice_bit>>1
	if(a0==1):
		f.write(str(alice_ran_keys[11])+'\n')
	else:
		f.write(str(alice_ran_keys[10])+'\n')
	if(a1==1):
		f.write(str(alice_ran_keys[7])+'\n')
	else:
		f.write(str(alice_ran_keys[6])+'\n')
	if(a1==1):
		f.write(str(alice_ran_keys[5])+'\n')
	else:
		f.write(str(alice_ran_keys[4])+'\n')
	alice_bit=alice_bit>>2	
	for i in range(n-2):
		if(alice_bit&0b1==0):
			f.write(str(alice_ran_keys[32+i*22])+'\n')
		else:
			f.write(str(alice_ran_keys[32+i*22+1])+'\n')
		if(alice_bit&0b1==0):
			f.write(str(alice_ran_keys[32+2+i*22])+'\n')
		else:
			f.write(str(alice_ran_keys[32+2+i*22+1])+'\n')
		alice_bit=alice_bit>>1




#generating the circuits
garbled_circuits=[]
garbled_circuits.append(
	(enc(alice_ran_keys[11],alice_ran_keys[16],32),
	enc(alice_ran_keys[10],alice_ran_keys[17],32)))
garbled_circuits.append(
	(double_enc(alice_ran_keys[17],alice_ran_keys[9],alice_ran_keys[21]),
	double_enc(alice_ran_keys[16],alice_ran_keys[9],alice_ran_keys[20]),
	double_enc(alice_ran_keys[16],alice_ran_keys[8],alice_ran_keys[20]),
	double_enc(alice_ran_keys[17],alice_ran_keys[8],alice_ran_keys[20]),))
garbled_circuits.append(
	(enc(alice_ran_keys[21],alice_ran_keys[24],32),
	enc(alice_ran_keys[20],alice_ran_keys[25],32)))
garbled_circuits.append(
	(enc(alice_ran_keys[7],alice_ran_keys[14],32),
	enc(alice_ran_keys[6],alice_ran_keys[15],32)))
garbled_circuits.append(
	(double_enc(alice_ran_keys[15],alice_ran_keys[3],alice_ran_keys[19]),
	double_enc(alice_ran_keys[14],alice_ran_keys[3],alice_ran_keys[18]),
	double_enc(alice_ran_keys[14],alice_ran_keys[2],alice_ran_keys[18]),
	double_enc(alice_ran_keys[15],alice_ran_keys[2],alice_ran_keys[18]),))
garbled_circuits.append(
	(enc(alice_ran_keys[19],alice_ran_keys[22],32),
	enc(alice_ran_keys[18],alice_ran_keys[23],32)))
garbled_circuits.append(
	(double_enc(alice_ran_keys[25],alice_ran_keys[23],alice_ran_keys[29]),
	double_enc(alice_ran_keys[24],alice_ran_keys[23],alice_ran_keys[28]),
	double_enc(alice_ran_keys[24],alice_ran_keys[22],alice_ran_keys[28]),
	double_enc(alice_ran_keys[25],alice_ran_keys[22],alice_ran_keys[28]),))
garbled_circuits.append(
	(enc(alice_ran_keys[1],alice_ran_keys[12],32),
	enc(alice_ran_keys[0],alice_ran_keys[13],32)))
garbled_circuits.append(
	(double_enc(alice_ran_keys[5],alice_ran_keys[13],alice_ran_keys[27]),
	double_enc(alice_ran_keys[4],alice_ran_keys[13],alice_ran_keys[26]),
	double_enc(alice_ran_keys[4],alice_ran_keys[12],alice_ran_keys[26]),
	double_enc(alice_ran_keys[5],alice_ran_keys[12],alice_ran_keys[26]),))
garbled_circuits.append(
	(double_enc(alice_ran_keys[29],alice_ran_keys[27],alice_ran_keys[31]),
	double_enc(alice_ran_keys[28],alice_ran_keys[27],alice_ran_keys[31]),
	double_enc(alice_ran_keys[28],alice_ran_keys[26],alice_ran_keys[30]),
	double_enc(alice_ran_keys[29],alice_ran_keys[26],alice_ran_keys[31]),))
# print(garbled_circuits)

#	augmented garbled circuits
if(n>2):
	for i in range(n-2):
		# print("i is  ",i)
		garbled_circuits.append(
			(enc(alice_ran_keys[32+i*22],alice_ran_keys[41+i*22],32),
			enc(alice_ran_keys[32+1+i*22],alice_ran_keys[40+i*22],32)))
		garbled_circuits.append(
			(double_enc(alice_ran_keys[41+i*22],alice_ran_keys[37+i*22],alice_ran_keys[43+i*22]),
			double_enc(alice_ran_keys[40+i*22],alice_ran_keys[37+i*22],alice_ran_keys[42+i*22]),
			double_enc(alice_ran_keys[40+i*22],alice_ran_keys[36+i*22],alice_ran_keys[42+i*22]),
			double_enc(alice_ran_keys[41+i*22],alice_ran_keys[36+i*22],alice_ran_keys[42+i*22]),))
		# print(garbled_circuits)
		garbled_circuits.append(
			(enc(alice_ran_keys[43+i*22],alice_ran_keys[44+i*22],32),
			enc(alice_ran_keys[42+i*22],alice_ran_keys[45+i*22],32)))
		garbled_circuits.append(
			(double_enc(alice_ran_keys[31+i*22],alice_ran_keys[45+i*22],alice_ran_keys[47+i*22]),
			double_enc(alice_ran_keys[30+i*22],alice_ran_keys[45+i*22],alice_ran_keys[46+i*22]),
			double_enc(alice_ran_keys[30+i*22],alice_ran_keys[44+i*22],alice_ran_keys[46+i*22]),
			double_enc(alice_ran_keys[31+i*22],alice_ran_keys[44+i*22],alice_ran_keys[46+i*22]),))
		garbled_circuits.append(
			(enc(alice_ran_keys[39+i*22],alice_ran_keys[48+i*22],32),
			enc(alice_ran_keys[38+i*22],alice_ran_keys[49+i*22],32)))
		garbled_circuits.append(
			(double_enc(alice_ran_keys[35+i*22],alice_ran_keys[49+i*22],alice_ran_keys[51+i*22]),
			double_enc(alice_ran_keys[34+i*22],alice_ran_keys[49+i*22],alice_ran_keys[50+i*22]),
			double_enc(alice_ran_keys[34+i*22],alice_ran_keys[48+i*22],alice_ran_keys[50+i*22]),
			double_enc(alice_ran_keys[35+i*22],alice_ran_keys[48+i*22],alice_ran_keys[50+i*22]),))
		garbled_circuits.append(
			(double_enc(alice_ran_keys[47+i*22],alice_ran_keys[51+i*22],alice_ran_keys[53+i*22]),
			double_enc(alice_ran_keys[46+i*22],alice_ran_keys[51+i*22],alice_ran_keys[53+i*22]),
			double_enc(alice_ran_keys[46+i*22],alice_ran_keys[50+i*22],alice_ran_keys[52+i*22]),
			double_enc(alice_ran_keys[47+i*22],alice_ran_keys[50+i*22],alice_ran_keys[53+i*22]),))



print("number of total generated keys ",len(alice_ran_keys))
	

with open('garbled_circuits.txt', 'w') as f:
    for i in range(len(garbled_circuits)):
    	f.write(str(garbled_circuits[i])+'\n')

end = time.clock()
print("Time for encrypt the branch and building the garbled_circuits:   ", end-start)













