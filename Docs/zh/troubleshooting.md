# 故障排查
## Setup脚本没有下载channeld
如果您在运行Setup前，已经配置了环境变量`%CHANNELD_PATH%`，Setup脚本会认为您已经安装了channeld，并跳过下载安装步骤。插件会根据环境变量`%CHANNELD_PATH%`来运行channeld。

如果您需要下载安装channeld到插件目录中，请先删除环境变量`%CHANNELD_PATH%`。

## 无法启动channeld服务
- 检查任务管理器中是否存在channeld进程，如果存在，请手动“结束任务”
- 如果输出日志中出现`failed to listen`的错误，说明端口被占用。请检查默认的端口12108和11288是否被其它程序占用，或者在channeld配置文件中修改端口号

## 游戏服务器启动后自动退出
- 检查channeld服务是否正常运行。在开启了channeld网络（`Enable Channeld Networking`）时，游戏服务器会尝试连接channeld服务。如果连接失败，游戏服务器会自动退出
- 检查游戏服务器的日志。日志文件通常位于项目目录下的`Saved/Logs`目录中，以项目名_{数字}命名。在单服模式下，数字为2是游戏服务器日志；在多服模式下，数字为2是主服务器日志，数字从3开始是空间服务器日志

## 无法保存蓝图
如果出现“无法保存资产”的错误提示，通常是由于游戏服务器仍在运行，导致蓝图文件被占用。请先关闭游戏服务器，再保存蓝图。

## 同步出现问题
- 确保使用最新生成的同步代码
- 有时候，生成的同步代码在编译后没有正常被热加载。此时需要重启UE编辑器。
- 检查游戏服务器的日志，查看是否有同步相关的错误信息

## 角色跨服后，亮边的颜色不正确
检查空间服务器是否都在正常运行。如果空间服务器已经退出，其控制的空间频道区域就无法正常模拟，跨服也会出现问题。

## 项目中存在其它Protobuf库的冲突
ChanneldUE插件使用了Protobuf库，并以ProtobufUE模块的方式进行引用。如果您的项目中也使用了Protobuf库，则需要将ChanneldUE插件或项目对ProtobufUE模块的引用改为您自己的模块，并重新编译。注意ChannelUE引用Protobuf使用的路径是`google/protobuf/*.h`，如果您使用的Protobuf库的根路径不同，会导致ChanneldUE插件编译错误。