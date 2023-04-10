# exam_06
Final exam of the 42 school common core 
- Write a program that will listen for client to connect on a certain port on 127.0.0.1 and will let clients to speak with each other.
The subject is in this repository.

## Launch the mini_server
```c
clang -Wall -Wextra -Werror mini_serv.c -o mini_serv && ./mini_serv 8080	# First terminal (server)
```

## Test your server with clients (launch at leasttwo clients)
```c
nc localhost 8080		# Second terminal (first client)
nc localhost 8080		# Third terminal (second client)
```
