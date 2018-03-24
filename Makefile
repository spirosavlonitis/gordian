PWD := $(PWD)

compile:
	cc *c -o gord

install: 
	sudo ln -s $(PWD)/gord /usr/bin/gord
