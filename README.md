# Reticle
Code to support testing in the Vicon lab

##Load Rasbian on the Pi

##Config wireless

##Build ZeroMQ
     * There is no good package for ZMQ on the Raspberry Pi.
     * For some reason I was not able to clone the repo and had to download the .tar.gz version in the releases section for version 4.0.7.
     * The file `autogen.sh` in the home directory requires `libtool` and `autoconf` to build.  Both of these are available via `sudo apt-get install libtool autoconf`.
     * After these install then run `./autogen.sh`.  This should produce a `configure` script in the root directory of the source tree.  Then follow standard linux `.configure` `make` `sudo make install` procedures.
     * After the library built (about an hour between configure and make) I wrote the HelloWorld Server example on page 5 of the O'Reilly book.  It compiled fine with the compiler directive `gcc hello.c -lzmq`, but **IT DID NOT RUN THE EXECUTABLE AFTER IT COMPILED!**
     * It errored out like this:
```
     $ ./a.out
     ./a.out: error while loading shared libraries: libzmq.so.4; cannot open shared object file: No such file or directory
```

     * Found an example online where others had this same experience.  Running `ldconfig` again solved the problem.  I saw `ldconfig` run at the end of `sudo make install`, but apparently you need to run it one more time.  Note on `ldconfig` on the pi...the normal `/etc/ld.so.conf` file includes all the files in the directory `/etc/ld.so.conf.d`.  However one of those files already includes the `/usr/local/lib` directory where zmq installs.  So there is no need to make any alterations to the source code...just run `sudo ldconfig`.
     * After running the library config tool again, and then trying to run the test program it ran as expected!!!