# CVE-2018-10933
CVE-2018-10933 is called authentication bypass. It uses a bug existing in libssh 0.6.0 - 0.7.5 to get the unauthorized access to the server by presenting a messsage "SSH2_MSG_USERAUTH_SUCCESS" to the server during the authorization process. After that, the server will mistaken that the authorization process succeeds and grant the server to run command on the server. The client can even read or write the file from the server by running cat or touch command on the server. 

## Simulate the Bug
### Prepare the Server
First download the libssh-0.7.4 (an example of vulnerable version of ssh) from https://www.libssh.org/files/0.7/libssh-0.7.4.tar.xz

Decompress and direct to the filefold of libssh-0.7.4

Run the following command.

```
mkdir build
cd build
cmake ..
make
```

After run compile and install the server, direct to the libssh-0.7.4/examples and run the following command to start the server.

```
./ssh_server_fork (your host name) -p (your port)
```


### Attack the Server
On the client, create a file named cve-2018-10933.py and copy the code from 
https://www.exploit-db.com/exploits/46307
Then run the following command to attack the server:
```
python3 cve-2018-10933.py (your host name) (your port name) (command you want run)
```
In that case, you can run command like "cat /etc/ssh_config" so that you can view the configuration file of the server without knowing the password.
