# 安装库

使用前请在`build`文件夹下执行

```
cmake ..
make Multigrid
make genJson
```

# 测试

开始测试请在`build`文件夹下执行

```
make test1
make test2
../bin/test1
../bin/test2
```

# 画图

在文件夹`plot`下执行

```
python plot.py
```

图像会输出在`plot/fig`中