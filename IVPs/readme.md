# 启动测试

进入`build`文件夹，输入

```bash
cmake ..
make
```

## 测试收敛率

进入`build`文件夹，输入
```bash
../bin/cr_test
```
进入`output`文件夹，输入
```bash
python3 plot.py
```
图像会输出在`output/fig`文件夹下。

## 测试三种特殊算法

进入`build`文件夹，输入
```bash
../bin/main
```
进入`output`文件夹，输入
```bash
python3 plot.py
```
图像会输出在`output/fig`文件夹下。