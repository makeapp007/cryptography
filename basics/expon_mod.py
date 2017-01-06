n=1234567890

a=13579
out=[0]
for i in range(15):
	b=a*a % n;
	print i+1," = ",b 
	out.append(b)
	a=b


print out
print out[14]
tmp=1
print '---'
for i in (3,5,6,13,14):
	print out[i]
	tmp=tmp*out[i]%n

print tmp
