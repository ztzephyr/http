### Git Bash 配置

Windows下配置git_bash的外观和基本属性。

```bash
# 新建配置文件 ~/.minttyrc
BackgroundColour=0,43,54
Rows=43
Columns=174
CursorType=block
Font=Consolas
FontHeight=10
FontSmoothing=full
Locale=zh_CN
Charset=UTF-8
RightClickAction=past
```



### SSH密钥添加到Github账户

git_bash关联到Github，方便拉取代码。

```bash
# 配置用户名和邮箱(仅用作git提交记录)
git config --global user.name "zhengt"
git config --global user.email "zhengt@example.com"

# 在~/目录下执行, 生成: 私钥~/.ssh/id_ed25519，公钥~/.ssh/id_ed25519.pub
ssh-keygen -t ed25519 -C "zhengt@example.com"

# 查看公钥id_ed25519.pub
cat ~/.ssh/id_ed25519.pub

# github右上角-Setting-左侧栏-SSH and GPG Keys-new SSH key

```

