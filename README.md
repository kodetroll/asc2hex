  Utilities for converting strings from hex to binary and back.

```
hex2asc - Converts a string of hex chars of the format '414243' to ASCII 'ABC'
asc2hex - Converts an ASCII string of the format 'ABC' to hex chars '414243'
hex2int - Converts a string representing an integer in hex to the decimal value
```

Program can accept input either by:

1) supplying it as the only command line arg:
	e.g. '<program> 313211'
    

2) The input can be specifed on the command line with the -i,--input argument

3) The input can be read from a file using the -f,--file argument

   -or- 
   
4) If no argument is supplied, then the program will prompt the user for
   input interactively using scanf.

To make the programs, simply run make, to install, run 'sudo make install'

(C) 2015 KB4OID Labs, a division of Kodetroll Heavy Industries


