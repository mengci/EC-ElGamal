ENCODE=encode
GENKEY=genkey
ENCRYPTN=encryptn
DECRYPTN=decryptn
ENCRYPT=encrypt
DECRYPT=decrypt

MYINCLUDES=../lib/libps7.a

CC=g++

all: $(ENCODE) $(GENKEY) $(ENCRYPTN) $(DECRYPTN) $(ENCRYPT) $(DECRYPT)

$(ENCODE): encode.cpp
	$(CC) -Wall -O1 -g -o encode encode.cpp -Iinclude -Llib  -lgmp -lgmpxx $(MYINCLUDES)

$(GENKEY): genkey.cpp
	$(CC) -Wall -O1 -g -o genkey genkey.cpp -Iinclude -Llib  -lgmp -lgmpxx $(MYINCLUDES)

$(ENCRYPTN): encryptn.cpp
	$(CC) -Wall -O1 -g -o encryptn encryptn.cpp -Iinclude -Llib  -lgmp -lgmpxx $(MYINCLUDES)

$(DECRYPTN): decryptn.cpp
	$(CC) -Wall -O1 -g -o decryptn decryptn.cpp -Iinclude -Llib  -lgmp -lgmpxx $(MYINCLUDES)

$(ENCRYPT): encrypt.cpp
	$(CC) -Wall -O1 -g -o encrypt encrypt.cpp -Iinclude -Llib -lgmp -lgmpxx $(MYINCLUDES)

$(DECRYPT): decrypt.cpp
	$(CC) -Wall -O1 -g -o decrypt decrypt.cpp -Iinclude -Llib $(MYINCLUDES) -lgmp -lgmpxx 

clean:
	rm -f $(ENCODE) $(GENKEY) $(ENCRYPTN) $(DECRYPTN) $(ENCRYPT) $(DECRYPT) 
