import random
import Crypto
from Crypto.PublicKey import RSA
from Crypto import Random
import ast
import pyDes
from Crypto.Cipher import DES


def enc(up_input,bo_input,bits):
	#des key 64bits 8bytes, input 32bits
	#in: up_input,bo_input 32bits
	#out: Ekx 96bits
	r=random.randint(0, 2**bits-1)
	# r=random.randint(2**(bits-3), 2**bits-1)
	r1=r
	r=(str(hex(r)))[2:]
	while(len(r)<8):
		r="0"+r
	key=str(hex(up_input))[2:]
	while(len(key)<8):
		key="0"+key

	# print(str(hex(up_input)))
	# print(key)

	deskey=DES.new(key)
	# print(r)
	# print(r[2:])

	cipher=deskey.encrypt(r)
	#cipher is 8 bytes
	length=len(cipher)
	fkr=0
	for i in range(length):
		fkr+=ord(cipher[i])<<(i*8)
	#fkr is 64 bits
	# long is bigger than 92 bits
	tmp=bo_input
	Ekx=long(r1<<(bits*2))+long(fkr^(tmp<<bits))
	return Ekx

def dec(Ekx,bob_key,bits):
	# from each 96bits encryption line, we can decrypt the 32bits keys as next input
	#in: Ekx 96bits, bob's OT key
	#out: -1 when this decrypt meaningless, else correct path, 32bits
	dec_r=Ekx>>(bits*2)
	dec_r1=dec_r
	# because Ekx contains L in the end
	dec_r=str(hex(dec_r1))[2:-1]
	dec_key=str(hex(bob_key))[2:]
	# because somethings it will contain L in the last letter
	if(dec_key[-1]=="L"):
		dec_key=dec_key[:-1]

	# print("in the decrypt  ",bob_key)
	# print(hex(bob_key))
	# print(dec_key)

	# print(len(dec_key))
	
	while(len(dec_key)<8):
		dec_key="0"+dec_key
	
	# print(len(dec_key))
	# print("dec_key   ",dec_key)
	# print("-----------")
	dec_deskey=DES.new(dec_key)
	# print("-----------")
	# print(dec_r)
	# print(hex(dec_r1))

	while(len(dec_r)<8):
		dec_r="0"+dec_r
	# print("final  ",dec_r)
	
	dec_cipher=dec_deskey.encrypt(dec_r)
	dec_length=len(dec_cipher)
	dec_fkr=0
	for i in range(dec_length):
		dec_fkr+=ord(dec_cipher[i])<<(i*8)
	Ekx_low64=Ekx&0xFFFFFFFFFFFFFFFF
	x0n=Ekx_low64^dec_fkr
	remain=x0n-((x0n>>bits)<<bits)
	if remain==0:
		return x0n>>bits
	else:
		return -1

def double_dec(Ekx,right,left):
	# decrypt cipher twice
	# in: 32*3*3 encrypt_line, right 32bits, left 32bits
	# out: 32bits, bottom, as next key
	Ekxlow96=Ekx&long(0xFFFFFFFFFFFFFFFFFFFFFFFF)
	Ekxmid96=((Ekx>>96)&0xFFFFFFFFFFFFFFFFFFFFFFFF)
	Ekxhigh96=Ekx>>(96*2)
	#decode, find the right key path
	Ekxlow32=dec(Ekxlow96,right,32)
	Ekxmid32=dec(Ekxmid96,right,32)
	Ekxhigh32=dec(Ekxhigh96,right,32)
	if Ekxlow32!=-1 and Ekxmid32!=-1 and Ekxhigh32 !=-1:
		Ekx=(Ekxlow32+(Ekxmid32<<32))+(Ekxhigh32<<64)
	else:
		return -1
	possible_next_key=dec(Ekx,left,32)
	if possible_next_key!=-1:
		return possible_next_key
	else:
		return -1
	#decode, find the left key path


def double_enc(right,left,bottom):
	# encrypt plaintext twice
	# in: three anonymous keys, each 32bits
	# out: 32*3*3 bits,contains high, mid,low
	# divide Ekx to 3*32 and encode each separately
	Ekx=enc(left,bottom,32)
	Ekxlow32=Ekx&0xFFFFFFFF
	Ekxmid32=((Ekx>>32)&0xFFFFFFFF)
	Ekxhigh32=Ekx>>64
	# return low96+ mid96 + high96
	return long(enc(right,Ekxlow32,32))+long(enc(right,Ekxmid32,32)<<96)+long(enc(right,Ekxhigh32,32)<<(96*2))


def not_enc(up_input0,up_input1,bo_input0,bo_input1,bits):
	# in: 4 keys, each 32bits
	# out: two 96 bits integer
	return (enc(up_input1,bo_input0,32),enc(up_input0,bo_input1,32))
def not_dec(Ekx,bob_key,bits):
	# in: ,bo_input 32bits
	# out: tuple, two 96 bits integer
	return dec(Ekx,bob_key,32)
def and_enc(right0,right1,left0,left1,bottom0,bottom1):
	# in: 6 keys
	# out: tuple, four 96*3 bits integer
	return (double_enc(right1,left1,bottom1),double_enc(right0,left1,bottom0),double_enc(right0,left0,bottom0),double_enc(right1,left0,bottom0))
def and_dec(Ekx,right,left):
	return double_dec(Ekx,right,left)
def or_enc(right0,right1,left0,left1,bottom0,bottom1):
	# in: 6 keys
	# out: tuple, four 96*3 bits integer
	return (double_enc(right1,left1,bottom1),double_enc(right0,left1,bottom1),double_enc(right0,left0,bottom0),double_enc(right1,left0,bottom1))
def or_dec(Ekx,right,left):
	return double_dec(Ekx,right,left)






