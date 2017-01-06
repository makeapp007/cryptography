#

# >> print ord("a")
# 97
# >>> print ord("A")
# 65
# offset is 32


input_="OVDTHUFWVZZPISLRLFZHYLAOLYL"

key=0
output=""
# a="a"
# b=ord(a)+1
# print b
# print chr(b)
length=len(input_)
for i in range(0,26):
	output=""
	for j in range(0,length):
		cha=ord(input_[j])+i
		if cha>90:
			cha-=26
		output+=chr(cha+32)
	print output
		# print chr(ord(input_[j])+i),


#howmanypossiblekeysarethere

