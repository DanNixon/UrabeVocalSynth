import sys

vowel = ["A", "I", "U", "E", "O"]
char3 = ["SHI", "CHI", "TSU"]

prefix = "KanaTable::_"
suffix = ","

def main():
        with open ("input.txt", "r") as myfile:
                data=myfile.read().replace('\n', '').replace(' ', '').upper()
        print data
        print len(data)
        pos = 0
        while(pos < len(data)):
                if(data[pos:pos+3] in char3):
                        print prefix+data[pos:pos+3]+suffix
                        pos += 3
                elif(data[pos + 1] in vowel):
                        print prefix+data[pos:pos+2]+suffix
                        pos +=2
                else:
                        print prefix+data[pos]+suffix
                        pos += 1

main()
