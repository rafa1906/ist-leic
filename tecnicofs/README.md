# TecnicoFS

## Overview
TecnicoFS is a very simple file system using a **binary search tree** and an **inode table** to store and access files.

The program enables **multiple users to use the file system at the same time** using the **Linux socket interface** for communication between client and server and the use of **multiple threads and locks** to handle different requests inside the server.


## Running TecnicoFS
Interaction with TecnicoFS happens through a terminal. The program can be compiled using the *Makefile* and the client compiled with *gcc* (with the server running in the background). TecnicoFS commands will look something like:

```console
c filename permissions
```

Where a file with the name **filename** is created with permissions **permissions**

A more thorough overview of possible commands (delete, rename, read, write, ...) can be found in *assignment.md* (in portuguese).


## Academic details
This project was developed for SO (Sistemas Operativos) - a second year programming class about introductory parallel computing and socket programming and the inner workings of an OS.

The final grade was **15.53/20.00**.
