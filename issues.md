# issues

## libs not found

```shell
LIBMICROHTTPD
    linked by target "server" in directory /Users/brad/works/version_control/GE-learn/c++-learn/projects/musikcube/src/plugins/server
LIBNCURSES
    linked by target "musikcube" in directory /Users/brad/works/version_control/GE-learn/c++-learn/projects/musikcube/src/musikcube
LIBPANEL
    linked by target "musikcube" in directory /Users/brad/works/version_control/GE-learn/c++-learn/projects/musikcube/src/musikcube
```

```shell
brew install libmicrohttpd
brew install ncurses
brew install libopenmpt
```

## build

```shell
mdkir build && cd build && cmake .. && cmake --build -j 10 .
```
