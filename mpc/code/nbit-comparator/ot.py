import random
import Crypto
from Crypto.PublicKey import RSA
from Crypto import Random
import ast
import pyDes
from Crypto.Cipher import DES
from config import max_input_bit_length
import time


def OT_transfer(m0,m1,bit):
	m0=int(m0)
	m1=int(m1)
	x0=random.randint(0, 2**1024-1)
	x1=random.randint(0, 2**1024-1)
	#loading public key
	publickeyfile=""
	with open('alice-public.pem', 'r') as f:
		publickeyfile=f.read()
	# print(publickeyfile)
	n=0
	with open('alice-publickey.n.pem', 'r') as f:
		n=f.read()
	# print(n)
	n=long(n)
	publickey=RSA.importKey(publickeyfile)
	with open('alice-private.pem', 'r') as f:
		privatekeyfile=f.read()
	privatekey=RSA.importKey(privatekeyfile)
	#bob choose random k
	k=random.randint(0, 2**32-1)
	# send x1, so choose 1 instead of index 0
	if(bit==1):	
		v=(x1+publickey.encrypt(long(k), 32)[0])%(n)
	else:
		v=(x0+publickey.encrypt(long(k), 32)[0])%(n)
	k0=privatekey.decrypt(v-x0)%n
	k1=privatekey.decrypt(v-x1)%n
	m00=m0+k0
	m11=m1+k1
	if(bit==1):
		mf=m11-k
	else:
		mf=m00-k
	return mf

start = time.clock()
n=max_input_bit_length

#bob runs this file

#using rsa to generating private keys and public keys

# random_generator = Random.new().read
# key = RSA.generate(1024, random_generator) #generate pub and priv key, that is e and d,n is the 
# publickey = key.publickey() # pub key export for exchange, stands for e
# encrypted = publickey.encrypt('encrypt this message', 32)
# print 'encrypted message: ', encrypted #ciphertext
# decrypted = key.decrypt(ast.literal_eval(str(encrypted)))
# print 'decrypted message: ', decrypted

# private_pem = key.exportKey()

# with open('bob-private.pem', 'w') as f:
#     f.write(private_pem)
# public_pem = key.publickey().exportKey()
# with open('bob-public.pem', 'w') as f:
#     f.write(public_pem)
# public_n = key.n
# with open('bob-publickey.n.pem', 'w') as f:
#     f.write(public_n)


f=open('alice_ran_keys.txt')
alice_ran_keys=f.read().split()
f.close()

# bob_bit=0b10
print("please input bob's data  ")
bob_bit=int(input())
print("bob_input:  ",bob_bit)

bob_input=[]
bob_input.append(OT_transfer(alice_ran_keys[8],alice_ran_keys[9],bob_bit&0b1))
bob_input.append(OT_transfer(alice_ran_keys[2],alice_ran_keys[3],bob_bit>>1))
bob_input.append(OT_transfer(alice_ran_keys[0],alice_ran_keys[1],bob_bit>>1))
bob_bit=bob_bit>>2

#augmented
# for i in range(n-2):
# print("bob_bit  ",bob_bit)
if(n>2):
	# print("n is bigger than 2")
	for i in range(n-2):
		bob_input.append(OT_transfer(alice_ran_keys[36+i*22],alice_ran_keys[37+i*22],bob_bit&0b1))
		bob_input.append(OT_transfer(alice_ran_keys[38+i*22],alice_ran_keys[39+i*22],bob_bit&0b1))
		bob_bit=bob_bit>>1
# print("in ot test")
# print(alice_ran_keys[36])
# print(bob_input[3])
# print(alice_ran_keys[38])
# print(bob_input[4])



with open('inputsb.txt', 'w') as f:
	for i in range(len(bob_input)):
		f.write(str(bob_input[i])+'\n')



end = time.clock()
print("Time for doing obvious transfer   ", end-start)














