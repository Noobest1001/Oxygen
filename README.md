# Oxygen ⚛️
A rewrite/reimagining of Hydrogen

## Features
* Readable compiler code
* MPL-licensed
* Rolling-release

## Building
Once the build system has fully come in:
```bash
cmake .
make
sudo checkinstall
#make clean
```

And then if it installed correctly (at least, how I think it will work since the compiler code PR has not been merged yet):
```bash
make test_oxy
```
