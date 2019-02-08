# Debug Tools for FPGA

Linux上で物理メモリのデータを読み書きするツールです。

/dev/memにアクセス権限があればメモリの読み書きができます。

# コンパイル方法

```txt
$ gcc -o memdump memdump.c
$ gcc -o memwrite memwrite.c
```

# 使用方法

## メモリダンプ

```txt
./memdump ADDRESS(hex) NUM(dec)
```

## メモリライト

```txt
./memwrite ADDRESS(hex) DATA(hex)
```
