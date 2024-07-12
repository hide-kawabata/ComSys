# OpenMPによるプログラムの例

## 「円周率をモンテカルロ法で求める」

### 逐次実行（`mc_serial.c`）
```
$ make mc_serial
$ ./mc_serial
```
### OpenMPによる並列実行（`mc.c`）
```
$ make mc
$ ./mc
```
- スレッド数を指定して実行したい場合は以下のようにする．
    ```
    $ env OMP_NUM_THREADS=4 ./mc
    ```