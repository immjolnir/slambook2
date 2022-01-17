
## Install

```
git submodule update --init --recursive
```
*  use the `--init` option which will make it initialize any uninitialized submodules.
  

The way I use is:
```
git submodule update --init --recursive
git submodule foreach --recursive git fetch
git submodule foreach git merge origin master
```
