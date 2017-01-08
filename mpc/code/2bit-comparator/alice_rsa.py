import random
import Crypto
from Crypto.PublicKey import RSA
from Crypto import Random
import ast
import pyDes
from Crypto.Cipher import DES

# alice run this, using rsa to generating private keys and public keys

random_generator = Random.new().read
key = RSA.generate(1024, random_generator) #generate pub and priv key, that is e and d,n is the 
publickey = key.publickey() # pub key export for exchange, stands for e
# encrypted = publickey.encrypt('encrypt this message', 32)
# print 'encrypted message: ', encrypted #ciphertext
# decrypted = key.decrypt(ast.literal_eval(str(encrypted)))
# print 'decrypted message: ', decrypted

private_pem = key.exportKey()

with open('alice-private.pem', 'w') as f:
    f.write(private_pem)
public_pem = key.publickey().exportKey()
with open('alice-public.pem', 'w') as f:
    f.write(public_pem)
public_n = key.n
print(public_n)
with open('alice-publickey.n.pem', 'w') as f:
    f.write(str(public_n))







