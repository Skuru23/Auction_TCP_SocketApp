all:
	@$(MAKE) -C TCP_Server
	@$(MAKE) -C TCP_Client
clean:
	@$(MAKE) -C TCP_Server clean 
	@$(MAKE) -C TCP_Client clean
runs:
	./server 5550
runc:
	./client 127.0.0.1 5550