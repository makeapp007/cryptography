import random

#n stands for the maximum length of the input
n=2


# add one bit will need 22 more keys, 8 of them as input, 14 of them will be added to the branches
# random generate 32 keys
alice_ran_keys=[]
for i in range(0,32+(n-2)*22):
	alice_ran_keys.append(random.randint(0, 2**32-1))
print alice_ran_keys	

# write 32 keys to file
with open('alice_ran_keys.txt', 'w') as f:
	for i in range(len(alice_ran_keys)):
		f.write(str(alice_ran_keys[i])+'\n')


