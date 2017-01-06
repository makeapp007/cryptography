a = 1234567
b = 1357
# a=10
# b=25
# a = 35
a = 1048601
b = 1048589*1048583
a = 13579
b = 1234567890

# >>> 475746*1048589*1048601+-276711*1048601*1048583+-199040*1048589*1048583=1
# a=1267650600229015279631679392293
# b=1267650600228679761459440273951
# >>> (844864*475746*1048589*1048601+179496*-276711*1048601*1048583+-199040*1048589*1048583*529640)%(1048589*1048583*1048601)
# 478285435179591789L

# print(a)
# print(a-b)

a1=a
b1=b

u0=1
v0=0
u1=0
v1=1
u2=0
v2=0
dividend=0

while(1):	
	if(a==1):
		break
	if(b==1):
		break
	if(a>b):
		dividend=int(a/b)
		a=a-b*dividend
	else:
		dividend=int(b/a)
		b=b-a*dividend
# should choose the last last one
	# print a,'  ',b
	# print '-----'
	u2=u0-u1*dividend
	v2=v0-v1*dividend
	print u2,'   ', v2
	u0=u1
	v0=v1
	u1=u2
	v1=v2
	if(a==0 or b==0):
		break
print '-------'
if(a1*u2+b1*v2):
	print a1*u2+b1*v2, '  ',u2,'  ',v2
else:
	print a1*u2+b1*v2, '  ',u0,'  ',v0

# if(a==1 or b==1):
# 	print('gcd num is ',1)
# 	print a1,'*',u2,'+',b1,'*',v2,'=','1'
# else:
# 	print('gcd num is: ',abs(a-b))
# 	print a1,'*',u2,'+',b1,'*',v2,'=',abs(a-b)


