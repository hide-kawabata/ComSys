# Pthreadsによるプログラムの例

## とりあえず動かしてみる
### hello 
```
$ make hello
$ ./hello
```
- 起動するスレッド数はプログラムで制御
	- `pthread_create`を1回呼べば1つ増える．